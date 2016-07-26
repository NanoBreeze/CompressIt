#-------------------------------------------------
#
# Project created by QtCreator 2016-07-20T18:46:47
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CompressIt
TEMPLATE = app
CONFIG += c++11


SOURCES += main.cpp\
        mainwindow.cpp \
    testmainwindow.cpp \
    historyitemmodel.cpp \
    historyitem.cpp \
    dbmanager.cpp

HEADERS  += mainwindow.h \
    testmainwindow.h \
    historyitemmodel.h \
    historyitem.h \
    dbmanager.h

FORMS    += mainwindow.ui \
    testmainwindow.ui
