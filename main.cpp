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
#include "Algorithms/huffmandecode.h"

#include "Algorithms/arithmetic.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    TestMainWindow testMainWindow;
//    testMainWindow.show();
//    Testing testing;
//    testing.experimentOnByteArray();



//        Huffman huffman;
//        huffman.compress("C://Users//Lenny//Desktop//Testing.txt");
//        huffman.printNodesWithoutChildren();

//    HuffmanDecode huffmanDecode;
//    huffmanDecode.decompress("C://Users//Lenny//Desktop//WriteBin.bin");


    Arithmetic arithmetic;
    arithmetic.compress("C://Users//Lenny//Desktop//Testing.txt");

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
