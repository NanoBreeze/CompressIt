#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->statusBar->showMessage("This is the status bar");

    historyTableModel = new QStandardItemModel(10, 4, this);
    historyTableModel->setHorizontalHeaderItem(0, new QStandardItem("File Name"));
    historyTableModel->setHorizontalHeaderItem(1, new QStandardItem("File Type"));
    historyTableModel->setHorizontalHeaderItem(2, new QStandardItem("Time of Compression"));
    historyTableModel->setHorizontalHeaderItem(3, new QStandardItem("Compression Ratio"));


    for (int row = 0; row < historyTableModel->rowCount(); row++)
    {
        for (int column = 0; column < historyTableModel->columnCount(); column++)
        {
            QModelIndex index = historyTableModel->index(row, column);
            historyTableModel->setData(index, row);
        }
    }



    ui->historyTableView->setModel(historyTableModel);
    ui->historyTableView->setSortingEnabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete historyTableModel;
}

//opens a file browser for user to choose which file to compress
void MainWindow::on_action_Load_triggered()
{
    QString selectedFile = QFileDialog::getOpenFileName(this, "Load file");

    qDebug() << selectedFile;
}

//toggles whether to show or hide History dock widget
void MainWindow::on_action_History_toggled(bool arg1)
{
    if (arg1) {
        ui->historyDockWidget->show();
    }
    else {
        ui->historyDockWidget->hide();
    }
    qDebug() << QString(arg1);
}
