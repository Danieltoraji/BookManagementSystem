#include "databasemanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

DatabaseManager::DatabaseManager() {}

DatabaseManager::~DatabaseManager()
{
    if (m_db.isOpen())
        m_db.close();
}

bool DatabaseManager::initialize(const QString &dbPath)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(dbPath);

    if (!m_db.open()) {
        qWarning() << "Failed to open database:" << m_db.lastError().text();
        return false;
    }

    createTables();
    return true;
}

QSqlDatabase &DatabaseManager::database()
{
    return m_db;
}

void DatabaseManager::createTables()
{
    QSqlQuery query(m_db);

    // Enable foreign key enforcement
    query.exec("PRAGMA foreign_keys = ON");

    // ── users ── (User / Admin / Patron)
    query.exec(
        "CREATE TABLE IF NOT EXISTS users ("
        "  id          TEXT PRIMARY KEY,"
        "  username    TEXT NOT NULL,"
        "  phone       TEXT,"
        "  email       TEXT,"
        "  user_type   TEXT NOT NULL CHECK(user_type IN ('admin', 'patron')),"
        "  borrow_limit INTEGER DEFAULT 0"
        ")"
    );

    // ── books ──
    query.exec(
        "CREATE TABLE IF NOT EXISTS books ("
        "  isbn            TEXT PRIMARY KEY,"
        "  title           TEXT NOT NULL,"
        "  author          TEXT,"
        "  publisher       TEXT,"
        "  publishing_year INTEGER,"
        "  category        TEXT"
        ")"
    );

    // ── book_copies ── (embeds Location)
    query.exec(
        "CREATE TABLE IF NOT EXISTS book_copies ("
        "  lib_code  TEXT PRIMARY KEY,"
        "  isbn      TEXT NOT NULL,"
        "  lib       TEXT,"
        "  floor     INTEGER,"
        "  row_num   INTEGER,"
        "  unit_num  INTEGER,"
        "  level_num INTEGER,"
        "  FOREIGN KEY (isbn) REFERENCES books(isbn)"
        ")"
    );

    // ── loans ── (合并了 Borrow，loan_date 即 borrowDate)
    query.exec(
        "CREATE TABLE IF NOT EXISTS loans ("
        "  id          TEXT PRIMARY KEY,"
        "  lib_code    TEXT NOT NULL,"
        "  user_id     TEXT NOT NULL,"
        "  loan_date   TEXT NOT NULL,"
        "  due_date    TEXT,"
        "  return_date TEXT,"
        "  FOREIGN KEY (lib_code) REFERENCES book_copies(lib_code),"
        "  FOREIGN KEY (user_id)  REFERENCES users(id)"
        ")"
    );

    // ── reservations ──
    query.exec(
        "CREATE TABLE IF NOT EXISTS reservations ("
        "  id               TEXT PRIMARY KEY,"
        "  lib_code         TEXT NOT NULL,"
        "  user_id          TEXT NOT NULL,"
        "  reservation_date TEXT NOT NULL,"
        "  FOREIGN KEY (lib_code) REFERENCES book_copies(lib_code),"
        "  FOREIGN KEY (user_id)  REFERENCES users(id)"
        ")"
    );

    // ── fines ──
    query.exec(
        "CREATE TABLE IF NOT EXISTS fines ("
        "  id      TEXT PRIMARY KEY,"
        "  user_id TEXT NOT NULL,"
        "  amount  REAL NOT NULL,"
        "  FOREIGN KEY (user_id) REFERENCES users(id)"
        ")"
    );
}
