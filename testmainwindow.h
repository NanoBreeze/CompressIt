#ifndef TESTMAINWINDOW_H
#define TESTMAINWINDOW_H

#include <QMainWindow>

#include <QStringListModel>
#include <QStandardItemModel>
#include <QDebug>
#include <QSql>
#include <QFileInfo>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDir>

#include <QFileSystemModel>
#include <QQueue>
#include "Algorithms/huffman.h"
#include "Algorithms/huffmannode.h"


//#include "historyitem.h"


namespace Ui {
class TestMainWindow;
}

class TestMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TestMainWindow(QWidget *parent = 0);
    ~TestMainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::TestMainWindow *ui;
    QStringListModel *model = nullptr;
    QStringList numbers;

};

#endif // TESTMAINWINDOW_H
