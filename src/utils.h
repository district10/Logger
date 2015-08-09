#ifndef UTILS_H
#define UTILS_H

#include "logger.h"
#include <QString>
#include <QDateTime>
#include <QDebug>
#include <QDir>

namespace Util {
// timestamp
qint64 ts( );
qint64 &ts( qint64 &t );
qint64 timestamp( );
QDateTime ts2dt( qint64 ts = 0 );
QDateTime timestamp2datetime( qint64 ts = 0 );
QTime ts2time( qint64 ts = 0 );
QString ts2HHMMSS_MS( qint64 ts = 0 );  // 01:23:45.678
QString ts2YYYYMMDD_HHMMSS_MS( qint64 ts = 0,
    const char *format = "%4d/%02d/%02d %02d:%02d:%02d:%03d" );
// c_str()
const char *c_str( const QString &str );
const std::string string( const QString &str );
// dir, path
bool mkpath( const char *path );
}  // namespace Util

#endif  // UTILS_H
