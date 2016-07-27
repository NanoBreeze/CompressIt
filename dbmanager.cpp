#include "dbmanager.h"

DbManager::DbManager()
{

}

DbManager::~DbManager()
{

}

//return singleton
DbManager& DbManager::getDbManager()
{
    static DbManager dbManager;
    return dbManager;
}

//open database and if the History table is not created, create it
void DbManager::connectHistoryTable(const QString &path)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);

    if (!db.open())
    {
        qCritical() << "The database connection cannot be opened!";
    }

    QSqlQuery query(db);
    query.exec("CREATE TABLE IF NOT EXISTS History "
               "(id integer primary key, "
               "fileName TEXT,"
               "dateTime INTEGER, "
               "compressionRatio REAL, "
               "originalSize REAL, "
               "compressedSize REAL, "
               "executionTime REAL, "
               "notes TEXT"
               ");");
}

void DbManager::addHistoryItem(const QString &fileName, const int &dateTime, const double &compressionRatio, const double &originalSize, const double &compressedSize, const double &executionTime, const QString &notes)
{
    QSqlQuery query;
    query.prepare("INSERT INTO History "
                  "(fileName, dateTime, compressionRatio, originalSize, compressedSize, executionTime, notes) "
                  "VALUES (:fileName, :dateTime, :compressionRatio, :originalSize, :compressedSize, :executionTime, :notes)");
    query.bindValue(":fileName", fileName);
    query.bindValue(":dateTime", dateTime);
    query.bindValue(":compressionRatio", compressionRatio);
    query.bindValue(":originalSize", originalSize);
    query.bindValue(":compressedSize", compressedSize);
    query.bindValue(":executionTime", executionTime);
    query.bindValue(":notes", notes);

    if (!query.exec())
    {
        qCritical() << "The statement was not added to the database";
    }
}

void DbManager::clearHistoryTable()
{
    QSqlQuery query;
    query.exec("DELETE FROM table_name;");

}

//returns all info associated with the record of specified id
HistoryItem DbManager::getHistoryItem(const int& id) const
{

    QSqlQuery query;
    query.prepare("SELECT * FROM History WHERE id = :id");
    query.bindValue(":id", id);
    if (!query.exec()) { qCritical() << "The getHistoryItemStats select statement couldn't be executed"; }

    qDebug() << query.size();

    HistoryItem historyItem;

    if (query.next())
    {
        historyItem.id= query.value(query.record().indexOf("id")).toInt();
        historyItem.fileName = query.value(query.record().indexOf("fileName")).toString();  //Get the data from the query
        historyItem.dateTime = query.value(query.record().indexOf("dateTime")).toInt();
        historyItem.compressionRatio= query.value(query.record().indexOf("compressionRatio")).toDouble();
        historyItem.originalSize= query.value(query.record().indexOf("originalSize")).toDouble();
        historyItem.compressedSize = query.value(query.record().indexOf("compressedSize")).toDouble();
        historyItem.executionTime= query.value(query.record().indexOf("executionTime")).toDouble();
        historyItem.notes= query.value(query.record().indexOf("notes")).toString();
    }

    //checking that there was indeed only one query returned. BTW, query.size() always returns 0
    query.last();
    Q_ASSERT( query.at() + 1 == 1); //how can there be more than one record associated with the unique id?


    return historyItem;
}
