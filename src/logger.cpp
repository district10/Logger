#include "logger.h"

using namespace BCD;

const Logger::Type Logger::types = Logger::initTypes();
const Logger::Action Logger::actions = Logger::initActions();
const QString Logger::logPath = QString().sprintf( LOG_OUTPATH_FORMAT,
                                                   Util::ts( ) );
const int Logger::widthActionInfo = Logger::initActionInfoWidth( );
size_t Log::counter = 0;
QMutex Logger::mutex;
QList<Log> Logger::logs;

void Logger::saveLogs( const QList<Log> &logs, ActionInfo::Level level )
{
    log() << "Saving logs...";

    // UTF-8 without BOM
    FILE *fp = fopen( qPrintable(logPath), "a+" );
    if ( NULL == fp ) {
        return;
    }

    int widthTimestamp = Util::ts2YYYYMMDD_HHMMSS_MS().length();
    static size_t i = 0;
    if ( 0 == i ) {
        // header entries (in Markdown syntax)
#define H(header, width) \
     arg("", (##width-QObject::tr(##header).length())/2, ' ') \
    .arg(QObject::tr(##header)) \
    .arg("", ##width-QObject::tr(##header).length()-(##width-QObject::tr(##header).length())/2, ' ')

        fputs( qPrintable( QString( "| %1%2%3 "          // index
                                    "| %4%5%6 "          // timestamp
                                    "| %7%8%9 "          // log level
                                    "| %10%11%12 "       // type
                                    "| %13%14%15 "       // action
                                    "| %16%17%18 |\n" )  // remarks
                                    .H( "INDEX",        WIDTH_INDEX )
                                    .H( "TIMESTAMP", widthTimestamp )
                                    .H( "LEVEL",        WIDTH_LEVEL )
                                    .H( "TYPE",          WIDTH_TYPE )
                                    .H( "ACTION",   widthActionInfo )
                                    .H( "REMARKS",    WIDTH_REMARKS ) ), fp );

#undef H
        //          | idx | timestamp | level | type | action | remarks |
        fputs( QString( "| :%1: | :%2: | :%3: | :%4: | :%5: | :%6: |\n" )
                        .arg( "", WIDTH_INDEX-2,     '-' )
                        .arg( "", widthTimestamp-2,  '-' )
                        .arg( "", WIDTH_LEVEL-2,     '-' )
                        .arg( "", WIDTH_TYPE-2,      '-' )
                        .arg( "", widthActionInfo-2, '-' )
                        .arg( "", WIDTH_REMARKS-2,   '-' )
                        .toStdString().c_str(), fp );
    }  // header

    int i0 = i;
    foreach ( const Log &log, logs ) {
        // current level
        ActionInfo::Level cl = actions.value(log.action).level;
        if ( cl <= level ) {
            int len = strlen( qPrintable( types.value(log.type) ) );
            fprintf( fp,
                     "| %*i "              // index
                     "| %*s "              // timestamp
                     "| %*s%d%*s "         // log level
                     "| %*s%s%*s "         // type (aligned to center)
                     "| %-*s "             // action
                     "| %*s |\n",          // message
   /* index     */   WIDTH_INDEX, ++i,
   /* timestamp */   widthTimestamp, qPrintable(Util::ts2YYYYMMDD_HHMMSS_MS(log.timestamp)),
   /* log level */   (WIDTH_LEVEL-1)/2, "", (int)actions.value(log.action).level+1, WIDTH_LEVEL-(WIDTH_LEVEL-1)/2-1, "",
   /* type      */   (WIDTH_TYPE-len)/2, "", qPrintable(types.value(log.type)), WIDTH_TYPE-len-(WIDTH_TYPE-len)/2, "",
   /* action    */   widthActionInfo, qPrintable(actions.value(log.action).info),
   /* message   */   WIDTH_REMARKS, log.message.isEmpty() ? "" : qPrintable(log.message) );
        }
    }  // foreach

    fclose( fp );
    log() << "Saving logs, done. ("
          << (i-i0) << "out of "
          << logs.size() << "logs)";
}

QList<Log> Logger::refresh( )
{
    QList<Log> copy;

    QMutexLocker locker( &mutex );
    foreach ( const Log &log, logs ) {
        copy.append( log );
    }
    logs.clear();

    return copy;
}

void Logger::save( ActionInfo::Level level )
{
    saveLogs( refresh(), level );
}

int Logger::initActionInfoWidth( )
{
    int width = 0;
    foreach ( const ActionInfo &ai, actions.values() ) {
        if ( ai.info.length() > width ) {
            width = ai.info.length();
        }
    }
    return width;
}

QDebug Logger::log( int level  )
{
    // bound level to [min, max]
    level = qBound( (int)LOG_LEVEL_MIN, level, (int)LOG_LEVEL_MAX );
    // prefix of log
    fprintf( stderr, "+>%s> ",
             qPrintable(QString("%1").arg("", LOG_LEVEL_STEP*level, '=')) );

    // return qDebug instance
    return qDebug();
}

Log &Log::show( )
{
    if ( LOG_CONSOLE ) {
        int level = Logger::actions.value( action ).level;
        if ( level <= LOG_FILTER_CONSOLE ) {
            fprintf( stderr,
                     "[ %s ]"                              // timestamp
                     "[ %d ]"                              // level
                     "[ %-*s] "                            // type
                     "[ %-s ]"                             // action
                     "( %s )\n"                            // remarks
                     , qPrintable( Util::ts2HHMMSS_MS( timestamp ) )
                     , level+1
                     , WIDTH_TYPE, qPrintable( Logger::types.value( type ) )
                     , qPrintable( Logger::actions.value( action ).info )
                     , qPrintable( message ) );
        }
    }
    return *this;
}

Logger::Type Logger::initTypes( )
{
    Type types;
    types[  TYPE_LMS       ] = QObject::tr(  "LMS"       );
    types[  TYPE_UR        ] = QObject::tr(  "UR"        );
    types[  TYPE_SP20000C  ] = QObject::tr(  "SP20000C"  );
    return types;
}

static ActionInfo actionInfo( ActionInfo::Level level, const QString &info )
{
    ActionInfo ai;
    ai.level = level;
    ai.info  = info;
    return ai;
}

Logger::Action Logger::initActions( )
{
    QHash<ActionID, ActionInfo> actions;
#define ADD_ACTION(aid, level, info) \
    actions[(int)aid]=actionInfo(ActionInfo::LEVEL##level,QObject::tr(info));
    /* {1..5} => ActionInfo::LEVEL{1..5} */

    // LMS
    ADD_ACTION( LMS::TURN_ON_READING,            1, "turn on READING" );
    ADD_ACTION( LMS::TURN_OFF_READING,           1, "turn off READING" );
    // UR
    ADD_ACTION( UR::DISCONNECT,                  1, "stop getting image" );
    // SP20000C
    ADD_ACTION( SP20000C::TURN_OFF,              1, "start getting image" );
    ADD_ACTION( SP20000C::TURN_ON,               1, "stop getting image" );

#undef ADD_ACTION

    return actions;
}