#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QDebug>
#include <QSql>
#include <QFileInfo>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDir>
#include <QFile>

#include "historyitem.h"

//manages all database interactions, initializing, reading and writing data
class DbManager
{
public:
    static DbManager& getDbManager(); //returns the DbManager singleton
    void addHistoryItem(const QString& fileName,
                        const QString& dateTime,
                        const double& compressionRatio,
                        const double& originalSize,
                        const double& compressedSize,
                        const double& executionTime,
                        const QString& notes);

    void connectHistoryTable(const QString& path);//connects and initializes the SQLite database and the relevant table
    void clearHistoryTable(); //clears the History table of all records
    HistoryItem getHistoryItem(const int& id) const;
    ~DbManager();

private:\
    DbManager();


};

#endif // DBMANAGER_H
