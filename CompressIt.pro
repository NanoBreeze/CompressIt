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
    dbmanager.cpp \
    testing.cpp \
    prefixtreenode.cpp \
    prefixtree.cpp \
    Algorithms/huffman.cpp \
    Algorithms/huffmannode.cpp \
    Algorithms/code.cpp

HEADERS  +=    mainwindow.h \
    testmainwindow.h \
    dbmanager.h \
    historyitem.h \
    testing.h \
    prefixtreenode.h \
    prefixtree.h \
    Algorithms/huffman.h \
    Algorithms/huffmannode.h \
    Algorithms/code.h

FORMS    += mainwindow.ui \
    testmainwindow.ui
