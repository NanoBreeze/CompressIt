#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupHistoryTableView();
    setupCurrentFilesTableWidget();

    setAcceptDrops(true);

    connect(this, SIGNAL(databaseChanged()), this, SLOT(refreshHistoryTableView()));

//    ui->statusBar->showMessage("This is the status bar");

}

void MainWindow::setupHistoryTableView()
{
    //adding layout to historyDockWidget to enable it resizes. Adding this in Qt Designer won't make resizing happen!
    QGridLayout*vertLayout = new QGridLayout(this);
    vertLayout->addWidget(ui->historyTableView);
    ui->historyDockWidgetContents->setLayout(vertLayout);

    historyTableViewModel= new QSqlQueryModel(this);

    historyTableViewModel->setQuery("SELECT id, fileName, dateTime, compressionRatio FROM History");

    historyTableViewModel->setHeaderData(0, Qt::Horizontal, QString("Id"));
    historyTableViewModel->setHeaderData(1, Qt::Horizontal, QString("File"));
    historyTableViewModel->setHeaderData(2, Qt::Horizontal, QString("Date/Time"));
    historyTableViewModel->setHeaderData(3, Qt::Horizontal, QString("Compression Ratio"));

    historyTableViewProxyModel=new QSortFilterProxyModel(this);
//    historyTableViewProxyModel->setDynamicSortFilter(true);
    historyTableViewProxyModel->setSourceModel(historyTableViewModel);
    ui->historyTableView->setModel(historyTableViewProxyModel);


    ui->historyTableView->setSortingEnabled(true);
    ui->historyTableView->setColumnHidden(0, true); //hides the id column
    ui->historyTableView->verticalHeader()->setHidden(true);
}

void MainWindow::setupCurrentFilesTableWidget()
{
    ui->currentFilesTableWidget->setColumnCount(5);

    ui->currentFilesTableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("File"));
    ui->currentFilesTableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Size (bytes)"));
    ui->currentFilesTableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Progress"));
    ui->currentFilesTableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("Compressed Size"));
    ui->currentFilesTableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem("Ratio"));

}

MainWindow::~MainWindow()
{
    delete ui;
}


//opens a file browser for user to choose which file to compress, and add the chosen file names and size to
//tableview containing all to-be-compressed files
void MainWindow::on_action_Load_triggered()
{
    QList<QUrl> selectedFileUrls = fileDialog.getOpenFileUrls(this, "Load file");

    extractFileInsights(selectedFileUrls);}

//these two methods "on_action_History_toggled" and "on_historyDockWidget_visibilityChanged" are like observables
//there might be an existing function that handles visibility changes
//toggles whether to show or hide History dock widget
void MainWindow::on_action_History_toggled(bool arg1)
{
    if (arg1) { ui->historyDockWidget->show(); }
    else { ui->historyDockWidget->hide(); }
    qDebug() << QString(arg1);
}

void MainWindow::on_historyDockWidget_visibilityChanged(bool visible)
{
    ui->action_History->setChecked(visible);
}

void MainWindow::on_action_Stats_toggled(bool arg1)
{
    if (arg1) { ui->statsDockWidget->show(); }
    else { ui->statsDockWidget->hide(); }
}


void MainWindow::on_statsDockWidget_visibilityChanged(bool visible)
{
    ui->action_Stats->setChecked(visible);
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
    ui->fileName_lbl->setText("<b>File Name: </b>" + historyItem.fileName);
    ui->date_time_lbl->setText("<b>Datetime: </b>" + historyItem.dateTime);
    ui->originalSize_lbl->setText("<b>Original Size (b): </b>" + QString::number(historyItem.originalSize));
    ui->compressedSize_lbl->setText("<b>Compressed Size (b): </b>" + QString::number(historyItem.compressedSize));
    ui->executionTime_lbl->setText("<b>Execution Time (ms): </b>" + QString::number(historyItem.executionTime));
    ui->compressionRatio_lbl->setText("<b>Compression Ratio: </b>" + QString::number(historyItem.compressionRatio) + "%");
    ui->notes_lbl->setText(historyItem.notes);
}


void MainWindow::displayFileData(const QString& fileName, const double& fileSize)
{
    ui->currentFilesTableWidget->insertRow(ui->currentFilesTableWidget->rowCount());
    int lastRowIndex = ui->currentFilesTableWidget->rowCount() - 1;
    ui->currentFilesTableWidget->setItem(lastRowIndex, 0, new QTableWidgetItem(fileName));
    ui->currentFilesTableWidget->setItem(lastRowIndex, 1, new QTableWidgetItem(QString::number(fileSize)));

}



void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    event->accept();
}

//user can drag-drop file to add file to the "to be compressed" queue
void MainWindow::dropEvent(QDropEvent *event)
{
    const QMimeData* mimeData = event->mimeData();

    // check for our needed mime type, here a file or a list of files
    if (mimeData->hasUrls())
    {
        QList<QUrl> urls = mimeData->urls();

        extractFileInsights(urls);
    }
}

void MainWindow::extractFileInsights(const QList<QUrl> &urls)
{
        foreach (QUrl url, urls)
        {
            QString filePath = getFilePath(url);
            QString fileName = getFileName(filePath);
            double fileSize = getFileSize(filePath);

            filePaths.append(filePath);

            displayFileData(fileName, fileSize);
        }
}


QString MainWindow::getFileName(const QString& filePath)
{
    QFile file(filePath);
    Q_ASSERT( file.exists()); //since the user selected the file, it must exist!

    QFileInfo fileInfo(file.fileName()); //us

    QString fileName = fileInfo.fileName();
    qDebug() << fileName;
    return fileName;

}

double MainWindow::getFileSize(const QString &filePath)
{
    QFile file(filePath);

    qDebug() << file.size();
    return file.size();
}

QString MainWindow::getFilePath(const QUrl& url)
{
    return url.toString().right(url.toString().count() - 8);
}

void MainWindow::on_currentFilesTableWidget_clicked(const QModelIndex &index)
{
    if (index.isValid())
    {
        int rowIndex = index.row();
        ui->currentFilesTableWidget->selectRow(rowIndex);
    }
}


//asks if user is sure to delete history and then clears the model.
//Might consider using Observer pattern later when compression algos implemented and appending new entries
void MainWindow::on_actionClear_History_triggered()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,
                                  "Clear History", "Are you sure you want to clear history of previously compressed files?",
                                  QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        DbManager::getDbManager().clearHistoryTable();
        emit databaseChanged();
    }
}

//intended to trigger compressing the files. For now, just insert a record into database
void MainWindow::on_actionCompressIt_triggered()
{
    //always Huffman encode for now
    while(!filePaths.isEmpty())
    {
        QString filePath = filePaths.dequeue();

        QElapsedTimer timer;
        timer.start();
        compressionController.compress(filePath, AlgorithmEnum::Huffman);
        int compressionTime = timer.elapsed(); //compression time is in ms

        QString filePathBin = filePath; //gest the binary file url
        filePathBin.chop(3);
        filePathBin += "bin";

        QString fileName = getFileName(filePath);
        double originalSize = getFileSize(filePath);
        double compressedSize = getFileSize(filePathBin);
        double compressionRatio = (compressedSize / originalSize) * 100; //as percentage
        QString dateTime = QDateTime::currentDateTime().toString();

        DbManager::getDbManager().addHistoryItem(fileName, dateTime, compressionRatio, originalSize, compressedSize, compressionTime, "");

        emit databaseChanged();
    }
    Q_ASSERT(filePaths.isEmpty()); //the queue should be empty after compressing

ui->currentFilesTableWidget->clearContents();

}


void MainWindow::refreshHistoryTableView()
{
    qDebug() << "refreshHistoryTableView called";
    historyTableViewModel->setQuery("SELECT id, fileName, dateTime, compressionRatio FROM History");

}


void MainWindow::on_actionDecompress_triggered()
{
    QUrl selectedBinaryFileUrl = fileDialog.getOpenFileUrl(this, "Load file", QUrl(), "Binary Files (*.bin)");
    QString filePath = getFilePath(selectedBinaryFileUrl);

compressionController.decompress(filePath);

}
