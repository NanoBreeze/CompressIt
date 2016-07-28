#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSqlQueryModel* model = new QSqlQueryModel(this);

    model->setQuery("SELECT id, fileName, dateTime, compressionRatio FROM History");

    model->setHeaderData(0, Qt::Horizontal, QString("Id"));
    model->setHeaderData(1, Qt::Horizontal, QString("File"));
    model->setHeaderData(2, Qt::Horizontal, QString("Date/Time"));
    model->setHeaderData(3, Qt::Horizontal, QString("Compression Ratio"));

    QSortFilterProxyModel *m=new QSortFilterProxyModel(this);
    m->setDynamicSortFilter(true);
    m->setSourceModel(model);
    ui->historyTableView->setModel(m);
    ui->historyTableView->setSortingEnabled(true);
    ui->historyTableView->setColumnHidden(0, true); //hides the id column
    ui->historyTableView->verticalHeader()->setHidden(true);


    ui->statusBar->showMessage("This is the status bar");

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
        ui->historyDockWidget->show();
    }
    else {
        ui->historyDockWidget->hide();
    }
    qDebug() << QString(arg1);
}

void MainWindow::on_historyTableView_clicked(const QModelIndex &index)
{
    if (index.isValid())
    {
        int rowIndex = index.row();
        ui->historyTableView->selectRow(rowIndex);

        int id = index.sibling(rowIndex, 0).data().toInt();
        populateStatsDockWidget(id);
        qDebug() << id;
        QString cellText = index.data().toString();
        qDebug() << cellText;

    }
    else { qCritical() << "The index is invalid"; }
}

//change Stats dock's labels to show the stats associated with this compressed file
void MainWindow::populateStatsDockWidget(const int& id) const
{
    HistoryItem historyItem = DbManager::getDbManager().getHistoryItem(id);
    ui->fileName_lbl->setText(historyItem.fileName);
    ui->date_time_lbl->setText(QString::number(historyItem.dateTime));
    ui->originalSize_lbl->setText(QString::number(historyItem.originalSize));
    ui->compressedSize_lbl->setText(QString::number(historyItem.compressedSize));
    ui->executionTime_lbl->setText(QString::number(historyItem.executionTime));
    ui->compressionRatio_lbl->setText(QString::number(historyItem.compressionRatio));
    ui->notes_lbl->setText(historyItem.notes);
}
