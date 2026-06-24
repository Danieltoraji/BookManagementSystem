#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QString>

class DatabaseManager
{
public:
    DatabaseManager();
    ~DatabaseManager();

    bool initialize(const QString &dbPath = "library.db");
    QSqlDatabase &database();//访问口

private:
    void createTables();
    QSqlDatabase m_db;
};

#endif // DATABASEMANAGER_H
