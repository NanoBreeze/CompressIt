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

    ui->statusBar->showMessage("This is the status bar");

}

void MainWindow::setupHistoryTableView()
{
    //adding layout to historyDockWidget to enable it resizes. Adding this in Qt Designer won't make resizing happen!
    QGridLayout*vertLayout = new QGridLayout(this);
    vertLayout->addWidget(ui->historyTableView);
    ui->historyDockWidgetContents->setLayout(vertLayout);

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
}

void MainWindow::setupCurrentFilesTableWidget()
{
    ui->currentFilesTableWidget->setColumnCount(5);
    ui->currentFilesTableWidget->setRowCount(2);

    ui->currentFilesTableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("File"));
    ui->currentFilesTableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Size"));
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

    for (const QUrl url: selectedFileUrls)
    {
        QString fileName = extractFileName(url);
        double fileSize = getFileSize(url);

        displayFileData(fileName, fileSize);
    }
}

//toggles whether to show or hide History dock widget
void MainWindow::on_action_History_toggled(bool arg1)
{
    if (arg1) { ui->historyDockWidget->show(); }
    else { ui->historyDockWidget->hide(); }
    qDebug() << QString(arg1);
}

void MainWindow::on_historyTableView_clicked(const QModelIndex &index)
{
    qDebug() << "The size of the stats dock table is: " << ui->historyDockWidget->height();

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

void MainWindow::dropEvent(QDropEvent *event)
{

    const QMimeData* mimeData = event->mimeData();

    // check for our needed mime type, here a file or a list of files
    if (mimeData->hasUrls())
    {
        QList<QUrl> urls = mimeData->urls();

        for (const QUrl url : urls )
        {
            QString fileName = extractFileName(url);
            double fileSize = getFileSize(url);

            displayFileData(fileName, fileSize);
        }
    }
}

QString MainWindow::extractFileName(const QUrl &url)
{

    QString fileUrl = url.toString().right(url.toString().count() - 8);
    qDebug() << "The fileUrl is: " << fileUrl;


    QFile file(fileUrl);
    Q_ASSERT( file.exists()); //since the user selected the file, it must exist!

    QFileInfo fileInfo(file.fileName()); //us

    QString fileName = fileInfo.fileName();
    qDebug() << fileName;
    return fileName;

    double fileSize = file.size();

    qDebug() << fileSize;
}

double MainWindow::getFileSize(const QUrl &url)
{

    QString fileUrl = url.toString().right(url.toString().count() - 8);
    QFile file(fileUrl);

    qDebug() << file.size();
    return file.size();
}
