#include "utils.h"

qint64 Util::timestamp( )
{
    return QDateTime::currentMSecsSinceEpoch();
}

qint64 Util::ts( )
{
    return timestamp();
}

qint64 &Util::ts( qint64 &t )
{
    return (t == 0) ? t = QDateTime::currentMSecsSinceEpoch() : t;
}

QDateTime Util::timestamp2datetime( qint64 ts )
{
    return QDateTime::fromMSecsSinceEpoch( ts );
}

QDateTime Util::ts2dt( qint64 ts/*=0*/ )
{
    return timestamp2datetime( ts == 0
                             ? QDateTime::currentMSecsSinceEpoch()
                             : ts );
}

QString Util::ts2HHMMSS_MS( qint64 ts/* =0 */ )
{
    QDateTime dt = ts2dt( ts );
    return QString().sprintf( "%02d:%02d:%02d.%03d"  // e.g. 01:23:45.678
                            , dt.time().hour()
                            , dt.time().minute()
                            , dt.time().second()
                            , dt.time().msec() );
}

QString Util::ts2YYYYMMDD_HHMMSS_MS( qint64 ts/*=0*/
    , const char *format/*="%4d/%02d/%02d %02d:%02d:%02d:%03d"*/ )
{
    QDateTime dt = ts2dt( ts );
    return QString().sprintf( format
                            , dt.date().year()
                            , dt.date().month()
                            , dt.date().day()
                            , dt.time().hour()
                            , dt.time().minute()
                            , dt.time().second()
                            , dt.time().msec() );
}

const char *Util::c_str( const QString &str )
{
    return str.toStdString().c_str();
}

const std::string Util::string( const QString &str )
{
    return str.toStdString();
}

bool Util::mkpath( const char *path )
{
    return QDir().mkpath( QString( path ) );
}

QTime Util::ts2time( qint64 ts/*=0*/ )
{
    return timestamp2datetime( ts ).time();
}