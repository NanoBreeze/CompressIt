#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QGridLayout>

#include <QDebug>

#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSortFilterProxyModel>

#include "historyitem.h"
#include "dbmanager.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_action_Load_triggered();

    void on_action_History_toggled(bool arg1);

    void on_historyTableView_clicked(const QModelIndex &index);

    void resizeEvent ( QResizeEvent * event )
    {
            qDebug() << "Resizing happening";
    };


private:
    Ui::MainWindow *ui;
    void populateStatsDockWidget(const int& id) const; //populate with the stats associated with the record with the given id

};

#endif // MAINWINDOW_H
