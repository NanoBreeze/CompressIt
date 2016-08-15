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
    Algorithms/huffman.cpp \
    Algorithms/huffmannode.cpp \
    Algorithms/code.cpp \
    Algorithms/huffmandecode.cpp \
    Algorithms/prefixtreecodenode.cpp \
    Algorithms/arithmetic.cpp \
    Algorithms/lz77.cpp \
    compressioncontroller.cpp

HEADERS  +=    mainwindow.h \
    testmainwindow.h \
    dbmanager.h \
    historyitem.h \
    testing.h \
    Algorithms/huffman.h \
    Algorithms/huffmannode.h \
    Algorithms/code.h \
    Algorithms/huffmandecode.h \
    Algorithms/prefixtreecodenode.h \
    Algorithms/arithmetic.h \
    Algorithms/lz77.h \
    compressioncontroller.h \
    algorithmenum.h

FORMS    += mainwindow.ui \
    testmainwindow.ui
