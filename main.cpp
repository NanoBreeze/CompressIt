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

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    DbManager dbManager = DbManager::getDbManager();
    dbManager.connectHistoryTable("C://Users//Lenny//Documents//CompressIt//database.db");
    HistoryItem h = dbManager.getHistoryItem(2);
    qDebug() << h.originalSize;
//    for (int i = 0 ; i < 20; i++)
//    {
//    dbManager.addHistoryItem("newFile" + QString(i), i, i, i, i, i, "notes" + QString(i));
//    }
    MainWindow w;
    w.show();
    return a.exec();
}
