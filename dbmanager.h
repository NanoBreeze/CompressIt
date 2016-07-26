#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QDebug>
#include <QSql>
#include <QFileInfo>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDir>

//manages all database interactions, initializing, reading and writing data
class DbManager
{
public:
    static void initDatabase(const QString& path); //initializes the SQLite database and the relevant tables
    DbManager();
};

#endif // DBMANAGER_H
