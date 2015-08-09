#-------------------------------------------------
#
# Project created by QtCreator 2015-07-25T20:06:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Logger
TEMPLATE = app


SOURCES += main.cpp\
        loggeragent.cpp \
    logger.cpp \
    utils.cpp

HEADERS  += loggeragent.h \
    logger.h \
    utils.h

FORMS    += loggeragent.ui
