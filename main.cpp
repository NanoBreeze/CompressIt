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
//    dbManager.addHistoryItem("newFile", 56, 12.5, 45.9, 65.8, 7897.5, "notes");
    MainWindow w;
    w.show();
    return a.exec();
}
