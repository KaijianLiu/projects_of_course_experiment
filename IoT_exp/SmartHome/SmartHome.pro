#-------------------------------------------------
#
# Project created by QtCreator 2016-04-24T15:04:36
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SmartHome
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sensordaemon.cpp \
    infowidget.cpp \
    def.cpp \
    demo.cpp \
    iot.cpp \
    foo.cpp


HEADERS  += mainwindow.h \
    sensordaemon.h \
    infowidget.h \
    def.h \
    foo.h


FORMS    += mainwindow.ui \
    foo.ui
