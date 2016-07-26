#include "dbmanager.h"

DbManager::DbManager()
{

}

void DbManager::initDatabase(const QString &path){
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName(path);
    mydb.open();

    QSqlQuery query;
    bool return_value=query.exec("CREATE TABLE History "
                                 "(id integer primary key, "
                                 "fileName TEXT,"
                                 "dateTime INTEGER, "
                                 "compressionRatio REAL, "
                                 "originalSize REAL, "
                                 "compressedSize REAL, "
                                 "executionTime REAL, "
                                 "notes TEXT"
                                 ");");
    qDebug() << return_value;
}
