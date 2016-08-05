#include "mainwindow.h"
#include "testmainwindow.h"
#include "dbmanager.h"
#include "historyitem.h"

#include <QApplication>

#include <QDebug>
#include <QFileDialog>

#include <QAbstractItemModel>
#include <QStringListModel>
#include <QListView>
#include <QStringList>

#include "testing.h"
#include "prefixtree.h"

#include <QMap>

#include "Algorithms/huffman.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    TestMainWindow testMainWindow;
//    testMainWindow.show();

//    QMap<QString, int> ses; //all nodes we operate on come from this (sorted) map ses.insert("one", 1);
//    ses.insert("two", 2);
//    ses.insert("three", 3);
//    ses.insert("four", 4);
//    ses.insert("five", 5);
//    ses.insert("six", 6);
//    ses.insert("seven", 7);
//    QMap<QString, int>::const_iterator i = ses.constBegin();
//    while (i != ses.constEnd())
//    {
//       //create a HuffmanNode and add it to the the QMap
//        qDebug() << "Key: " << i.key() << "; Value: " << i.value();
//        ++i;
//    }
        Huffman huffman;
        huffman.compress("C://Users//Lenny//Desktop//Testing.txt");
        huffman.printNodesWithoutChildren();
//    QStringList stringList;
//    stringList << "twice" << "once" << "ab" << "twiceeee" << "twi";
    //    testing.buildPrefixTree(stringList);

//    PrefixTree prefixTree;
//    prefixTree.insertWords(stringList);
//    qDebug() << "The word 'once' exists? " <<prefixTree.searchWord("once");
    //    qDebug() << "The word 'a' exists? " << testing.search("a");
//    qDebug() << "The word 'twice' exists? " <<prefixTree.searchWord("twice");
//    qDebug() << "The word 'ab' exists? " <<prefixTree.searchWord("ab");
//    qDebug() << "The word 'twiceeee' exists? " <<prefixTree.searchWord("twiceeee");

//    qDebug() << "The word 'abc' exists? " <<prefixTree.searchWord("abc");

    //    DbManager dbManager = DbManager::getDbManager();
    //    dbManager.connectHistoryTable("C://Users//Lenny//Documents//CompressIt//database.db");
    //    HistoryItem h = dbManager.getHistoryItem(2);
    //    qDebug() << h.originalSize;
    //    for (int i = 0 ; i < 20; i++)
    //    {
    //    dbManager.addHistoryItem("newFile" + QString::number(i), i, i, i, i, i, "notes" + QString(i));
    //    }
    //    MainWindow w;
    //    w.show();
    return a.exec();
}
