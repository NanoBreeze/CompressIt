#include "mainwindow.h"
#include "testmainwindow.h"
#include "dbmanager.h"

#include <QApplication>

#include <QDebug>
#include <QFileDialog>

#include <QAbstractItemModel>
#include <QStringListModel>
#include <QListView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    QStringList numbers;
//    numbers << "One" << "Two" << "Three" << "Four";
//    QAbstractItemModel *model = new QStringListModel();


//    QListView *view = new QListView();
//    view->setModel(model);

//    view->show();

//    TestMainWindow w;
//    w.show();

//    TestMainWindow w;
//    w.show();
    DbManager::initDatabase("C://Users//Lenny//Documents//CompressIt//database.db");
    return a.exec();
}
