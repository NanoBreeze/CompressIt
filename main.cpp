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

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //    Testing testing;
    //    testing.readFile("C://Users//Lenny//Desktop//Testing.txt");
    QStringList stringList;
    stringList << "twice" << "once" << "ab" << "twiceeee" << "twi";
    //    testing.buildPrefixTree(stringList);

    PrefixTree prefixTree;
    prefixTree.insertWords(stringList);
    qDebug() << "The word 'once' exists? " <<prefixTree.searchWord("once");
    //    qDebug() << "The word 'a' exists? " << testing.search("a");
    qDebug() << "The word 'twice' exists? " <<prefixTree.searchWord("twice");
    qDebug() << "The word 'ab' exists? " <<prefixTree.searchWord("ab");
    qDebug() << "The word 'twiceeee' exists? " <<prefixTree.searchWord("twiceeee");

    qDebug() << "The word 'abc' exists? " <<prefixTree.searchWord("abc");

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
