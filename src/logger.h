#ifndef LOGGER_H
#define LOGGER_H

/*
 * Usages:
 *      Logger::log( ) << 3 << "is three.";
 *      Logger::log( 8 ) << "emphasized log."; // 0..9
 *      Logger::log( BCD::LMS::CONNECTION_ERROR, QString("some optional remarks") );
 *      Logger::log( BCD::LMS::CONNECT, "this works too" );
 */

// configuration
#define LOG_OUTPATH_FORMAT ( "D:/log_%lld.txt"         ) // log_<timestamp>.txt
#define LOG_CONSOLE        (  true                     )
#define LOG_GUI            (  true                     )
#define LOG_FILTER_CONSOLE (  BCD::ActionInfo::LEVEL5  )
#define LOG_FILTER_GUIVIEW (  BCD::ActionInfo::LEVEL5  )
#define LOG_FILTER_ARCHIVE (  BCD::ActionInfo::LEVEL5  )
enum LOG_CONFIGS {
    WIDTH_INDEX            =  10,
    WIDTH_TYPE             =  10,
    WIDTH_LEVEL            =   5,
    WIDTH_REMARKS          =  40,
    LOG_LEVEL_MAX          =   9,
    LOG_LEVEL_MIN          =   0,
    LOG_LEVEL_STEP         =   5,
    LOG_LEVEL_DEFAULT      =   4,
    LOG_ENTRY_OFFSET       =   8, // at most 2^8 actions of each type
};

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <QDebug>
#include <QObject>
#include <QString>
#include <QDateTime>
#include <QHash>
#include <QMutex>

namespace BCD {
// types
enum TypeID {
    TYPE_LMS,
    TYPE_UR,
    TYPE_SP20000C,
};
typedef QString TypeInfo;

// actions
typedef int ActionID;
typedef struct {
    enum Level { LEVEL1, LEVEL2, LEVEL3, LEVEL4, LEVEL5, } level;
    QString info;
} ActionInfo;

// LMS
namespace LMS {
enum Action {
    LMS                           = TYPE_LMS<<LOG_ENTRY_OFFSET,
    TURN_ON_READING,
    TURN_OFF_READING,
};
}  // namespace LMS

// UR
namespace UR {
enum Action {
    UR                            = TYPE_UR<<LOG_ENTRY_OFFSET,
    DISCONNECT,
};
}  // namespace UR

// SP20000C
namespace SP20000C {
enum Action {
    SP20000C                      = TYPE_SP20000C<<LOG_ENTRY_OFFSET,
    TURN_ON,
    TURN_OFF,
};
}  // namespace SP20000C
}  // namespace BCD

class Log
{
private:
    static size_t    counter;

public:
    BCD::TypeID      type;
    BCD::ActionID    action;
    QString          message;
    qint64           timestamp;

public:
    Log( BCD::TypeID tid, BCD::ActionID aid, QString msg="", qint64 ts=0 ) :
        type( tid ),
        action( aid ),
        message( msg ),
        timestamp( 0 == ts ? QDateTime::currentMSecsSinceEpoch() : ts )
    { ++counter; }

    Log &show( );
};

class Logger
{
private:
    static QMutex           mutex;
    static QList<Log>       logs;
    const static QString    logPath;

private:
    typedef QHash<BCD::TypeID, BCD::TypeInfo> Type;
    typedef QHash<BCD::ActionID, BCD::ActionInfo> Action;

    static int initActionInfoWidth( );
    static Type initTypes( );
    static Action initActions( );
    static QList<Log> refresh( );
    static void saveLogs( const QList<Log> &logs,
                          BCD::ActionInfo::Level level );

public:
    const static int widthActionInfo;
    const static Type types;
    const static Action actions;

public:
    Logger( ) { /* Empty Logger Constructor */ }

    static QDebug log( int level = LOG_LEVEL_DEFAULT );

    // generic log (meta programming, saved a lot of typing...)
#define GENERIC_LOG(TYPE) \
        static void log( BCD::##TYPE::Action action, QString message = "" ) \
        { \
            QMutexLocker locker( &mutex ); \
            logs.append( Log( BCD::TYPE_##TYPE, action, message ).show() ); \
        }

       GENERIC_LOG(  UR        )
       GENERIC_LOG(  SP20000C  )

#undef GENERIC_LOG

    // for demonstration & debugging purpose, same as `GENERIC_LOG( LMS )'
    static void log( BCD::LMS::Action action, QString message = "" )
    {
        QMutexLocker locker( &mutex );
        logs.append( Log( BCD::TYPE_LMS, action, message ).show() );
    }

#define GENERIC_LOG_CSTR(TYPE) \
       static void log( BCD::##TYPE::Action action, char *message ) \
       { log( action, QString( message ) ); }

       GENERIC_LOG_CSTR(  LMS       )
       GENERIC_LOG_CSTR(  UR        )
       GENERIC_LOG_CSTR(  SP20000C  )

#undef GENERIC_LOG_CSTR

    static void save( BCD::ActionInfo::Level level = LOG_FILTER_ARCHIVE );
};

#endif  // LOGGER_H