#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

class DBManager
{
public:
    DBManager(const QString& path);
    ~DBManager();


    bool isOpen() const;
    bool createTable();
    void printAllPersons() const;
    bool addPerson(const QString& name);
private:
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H
