/*
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
*/

#include "loggeragent.h"
#include "logger.h"
#include <stdlib.h>
#include <QApplication>

void saveLogs()
{
    Logger::log() << "How nice, how nice, saving logs from vanishing.";
    Logger::save();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    atexit(saveLogs);

    LoggerAgent w;
    w.show();

    return a.exec();
}
