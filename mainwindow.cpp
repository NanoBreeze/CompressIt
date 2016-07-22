#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
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
        ui->dockWidget->show();
    }
    else {
        ui->dockWidget->hide();
    }
    qDebug() << QString(arg1);
}
