#include "testmainwindow.h"
#include "ui_testmainwindow.h"

TestMainWindow::TestMainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::TestMainWindow)
{
    ui->setupUi(this);

    QStandardItemModel *standardModel = new QStandardItemModel(this);

    Huffman huffman;
    huffman.compress("C://Users//Lenny//Desktop//Testing.txt");
    huffman.populateItemModel(standardModel);
    huffman.printCodewordLengths();
    ui->treeView->setModel(standardModel);
    ui->treeView->expandAll();

////    QFileSystemModel *model = new QFileSystemModel();
//    QStandardItemModel *standardModel = new QStandardItemModel(this);

//    QQueue<QStandardItem*> q;

//    QStandardItem *rootNode = standardModel->invisibleRootItem();

//    //defining a couple of items
////    QStandardItem americaItemNormal;
////    americaItemNormal.setText("America");
//    QStandardItem *americaItem = new QStandardItem("America");
//    QStandardItem *mexicoItem =  new QStandardItem("Canada");
//    QStandardItem *usaItem =     new QStandardItem("USA");
//    QStandardItem *bostonItem =  new QStandardItem("Boston");
//    QStandardItem *europeItem =  new QStandardItem("Europe");
//    QStandardItem *italyItem =   new QStandardItem("Italy");
//    QStandardItem *romeItem =    new QStandardItem("Rome");
//    QStandardItem *veronaItem =  new QStandardItem("Verona");

////    QStandardItem* americaItem = &americaItemNormal;

//    //building up the hierarchy
//    rootNode->    appendRow(americaItem);
//    rootNode->    appendRow(europeItem);
//    americaItem->appendRow(mexicoItem);
//    americaItem->appendRow(usaItem);
//    usaItem->     appendRow(bostonItem);
//    europeItem->  appendRow(italyItem);
//    italyItem->   appendRow(romeItem);
//    italyItem->   appendRow(veronaItem);

//    q.enqueue(americaItem);

//    QStandardItem* a = q.dequeue();

////    QBrush b(Qt::blue);
////    americaItem->setBackground(b);

//    //register the model
//    ui->treeView->setModel(standardModel);
//    ui->treeView->expandAll();



//    model->setRootPath(QDir::currentPath());
//    ui->treeView->setModel(model);



//    QDir databasePath;
//    QString path = databasePath.currentPath() + "myDb.db";
//    qDebug() << path;
//    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
//    mydb.setDatabaseName("C://Users//Lenny//Documents//CompressIt//database.db");
//    mydb.open();
//    QSqlQuery query;
//    query.exec("create table person "
//              "(id integer primary key, "
//              "firstname varchar(20), "
//              "lastname varchar(30), "
//              "age integer)");

//    if (mydb.open()) { qDebug() << "Database is open"; }
//    else { qDebug() << "Database is closed"; }

//    QSqlQuery query;
//    bool return_value=query.exec("CREATE TABLE History "
//                                 "(id integer primary key, "
//                                 "fileName TEXT,"
//                                 "dateTime INTEGER"
//                                 "compressionRatio REAL"
//                                 "originalSize REAL"
//                                 "compressedSize REAL"
//                                 "executionTime REAL"
//                                 "notes TEXT"
//                                 ");");
//    qDebug() << return_value;


//    numbers << "One" << "Two" << "Three";

//    model = new QStringListModel(numbers, this);

//    ui->listView->setModel(model);
//    ui->listView->setEditTriggers(QAbstractItemView::DoubleClicked);

//    ui->listView_2->setModel(model);
//    ui->listView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);

////QTableView
//QStandardItemModel *tableModel = new QStandardItemModel(5, 2, this);
//tableModel->setHorizontalHeaderItem(0, new QStandardItem("Column 0"));


////tableModel->setHorizontalHeaderItem(1, new QStandardItem("Column 1"));
//tableModel->setHorizontalHeaderItem(1, new QStandardItem("Column 0"));

//for (int row = 0; row < tableModel->rowCount(); row++)
//{
//    for (int column = 0; column < tableModel->columnCount(); column++)
//    {
//        QModelIndex index = tableModel->index(row, column);
////        HistoryItem* h = new HistoryItem(QString("fileName"), QString("fileType"), 35.98);
//        tableModel->setData(index, 4);
//    }
//}

//ui->tableView->setModel(tableModel);


}

TestMainWindow::~TestMainWindow()
{
    delete ui;
}

void TestMainWindow::on_pushButton_clicked()
{
    //add

    int row = model->rowCount();
    model->insertRow(row);

    QModelIndex index = model->index(row);

    ui->listView->setCurrentIndex(index);
    ui->listView->edit(index);
}

void TestMainWindow::on_pushButton_2_clicked()
{
    model->removeRow(ui->listView->currentIndex().row());
    //delete
}

void TestMainWindow::on_pushButton_3_clicked()
{
    int currentRow = ui->listView->currentIndex().row();
    model->insertRow(currentRow);

    QModelIndex index = model->index(currentRow);

    ui->listView->setCurrentIndex(index);
    ui->listView->edit(index);
}
