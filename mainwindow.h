#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QFileDialog>
#include <QUrl>
#include <QFileInfo>
#include <QFile>
#include <QMimeData>

#include <QDragEnterEvent>

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

    void on_currentFilesTableWidget_clicked(const QModelIndex &index);

    void on_historyDockWidget_visibilityChanged(bool visible);

    void on_action_Stats_toggled(bool arg1);

    void on_statsDockWidget_visibilityChanged(bool visible);

    void on_actionClear_History_triggered();

    void on_actionCompressIt_triggered();

    void refreshHistoryTableView();

signals:
    void databaseChanged(); //signal to indicate the database is changed. Attached slot refreshes the historyTableView to accomodate newly changed values

protected:
    void dropEvent(QDropEvent* event);
    void dragEnterEvent(QDragEnterEvent* event);

private:
    Ui::MainWindow *ui;
    QFileDialog fileDialog;
    QSqlQueryModel* historyTableViewModel = nullptr;
    QSortFilterProxyModel* historyTableViewProxyModel = nullptr;
    void populateStatsDockWidget(const int& id) const; //populate with the stats associated with the record with the given id
    void setupCurrentFilesTableWidget(); //sets the horizontal headers, number of columns and rows
    void setupHistoryTableView(); //sets the model and resizing capabilities of the history table view
    void displayFileData(const QString& fileName, const double& fileSize); //populates currentFilesTableWidget with the data associated with the file

    QString extractFileName(const QUrl& url); //returns the name of the file given its URL
    double getFileSize(const QUrl& url); //returns the size of the specified file
};

#endif // MAINWINDOW_H
