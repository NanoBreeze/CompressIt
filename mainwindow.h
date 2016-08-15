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
#include <QElapsedTimer>

#include <QDragEnterEvent>

#include <QDebug>

#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSortFilterProxyModel>
#include <QQueue>
#include <QDateTime>

#include "historyitem.h"
#include "dbmanager.h"
#include "compressioncontroller.h"
#include "algorithmenum.h"


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

    void on_actionDecompress_triggered();

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
    CompressionController compressionController;
    QQueue<QString> filePaths;

    void populateStatsDockWidget(const int& id) const; //populate with the stats associated with the record with the given id
    void setupCurrentFilesTableWidget(); //sets the horizontal headers, number of columns and rows
    void setupHistoryTableView(); //sets the model and resizing capabilities of the history table view
    void displayFileData(const QString& fileName, const double& fileSize); //populates currentFilesTableWidget with the data associated with the file

    QString getFileName(const QString& filePath); //returns the name of the file given its URL
    double getFileSize(const QString& filePath); //returns the size of the specified file
    QString getFilePath(const QUrl& url); //returns the properly formated file path

    void extractFileInsights(const QList<QUrl>& urls);


};

#endif // MAINWINDOW_H
