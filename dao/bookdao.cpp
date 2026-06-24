#include "bookdao.h"
#include "databasemanager.h"
#include "../model/book.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

using namespace std::string_literals;

BookDao::BookDao(DatabaseManager &db)
    : m_db(db)
{}

// ── INSERT ──────────────────────────────────────────────────────────
bool BookDao::insert(const Book &book)
{
    QSqlQuery query(m_db.database());
    query.prepare(
        "INSERT INTO books (isbn, title, author, publisher, publishing_year, category) "
        "VALUES (?, ?, ?, ?, ?, ?)"
    );
    query.addBindValue(QString::fromStdString(book.getISBN()));
    query.addBindValue(QString::fromStdString(book.getTitle()));
    query.addBindValue(QString::fromStdString(book.getAuthor()));
    query.addBindValue(QString::fromStdString(book.getPublisher()));
    query.addBindValue(book.getPublishingYear());
    query.addBindValue(QString::fromStdString(book.getCategory()));

    if (!query.exec()) {
        qWarning() << "BookDao::insert failed:" << query.lastError().text();
        return false;
    }
    return true;
}

// ── SELECT by ISBN ──────────────────────────────────────────────────
std::optional<Book> BookDao::findByISBN(const QString &isbn)
{
    QSqlQuery query(m_db.database());
    query.prepare("SELECT isbn, title, author, publisher, publishing_year, category "
                  "FROM books WHERE isbn = ?");
    query.addBindValue(isbn);

    if (!query.exec()) {
        qWarning() << "BookDao::findByISBN failed:" << query.lastError().text();
        return std::nullopt;
    }

    if (!query.next())
        return std::nullopt;

    Book book;
    book.setISBN(query.value(0).toString().toStdString());
    book.setTitle(query.value(1).toString().toStdString());
    book.setAuthor(query.value(2).toString().toStdString());
    book.setPublisher(query.value(3).toString().toStdString());
    book.setPublishingYear(query.value(4).toInt());
    book.setCategory(query.value(5).toString().toStdString());
    return book;
}

// ── SEARCH by title (LIKE) ──────────────────────────────────────────
std::vector<Book> BookDao::searchByTitle(const QString &keyword)
{
    std::vector<Book> results;
    QSqlQuery query(m_db.database());
    query.prepare("SELECT isbn, title, author, publisher, publishing_year, category "
                  "FROM books WHERE title LIKE ?");
    query.addBindValue("%" + keyword + "%");

    if (!query.exec()) {
        qWarning() << "BookDao::searchByTitle failed:" << query.lastError().text();
        return results;
    }

    while (query.next()) {
        Book book;
        book.setISBN(query.value(0).toString().toStdString());
        book.setTitle(query.value(1).toString().toStdString());
        book.setAuthor(query.value(2).toString().toStdString());
        book.setPublisher(query.value(3).toString().toStdString());
        book.setPublishingYear(query.value(4).toInt());
        book.setCategory(query.value(5).toString().toStdString());
        results.push_back(std::move(book));
    }
    return results;
}

// ── SELECT all ──────────────────────────────────────────────────────
std::vector<Book> BookDao::listAll()
{
    std::vector<Book> results;
    QSqlQuery query(m_db.database());
    query.exec("SELECT isbn, title, author, publisher, publishing_year, category "
               "FROM books");

    while (query.next()) {
        Book book;
        book.setISBN(query.value(0).toString().toStdString());
        book.setTitle(query.value(1).toString().toStdString());
        book.setAuthor(query.value(2).toString().toStdString());
        book.setPublisher(query.value(3).toString().toStdString());
        book.setPublishingYear(query.value(4).toInt());
        book.setCategory(query.value(5).toString().toStdString());
        results.push_back(std::move(book));
    }
    return results;
}

// ── UPDATE ──────────────────────────────────────────────────────────
bool BookDao::update(const Book &book)
{
    QSqlQuery query(m_db.database());
    query.prepare(
        "UPDATE books SET title=?, author=?, publisher=?, publishing_year=?, category=? "
        "WHERE isbn=?"
    );
    query.addBindValue(QString::fromStdString(book.getTitle()));
    query.addBindValue(QString::fromStdString(book.getAuthor()));
    query.addBindValue(QString::fromStdString(book.getPublisher()));
    query.addBindValue(book.getPublishingYear());
    query.addBindValue(QString::fromStdString(book.getCategory()));
    query.addBindValue(QString::fromStdString(book.getISBN()));

    if (!query.exec()) {
        qWarning() << "BookDao::update failed:" << query.lastError().text();
        return false;
    }
    return true;
}

// ── DELETE ──────────────────────────────────────────────────────────
bool BookDao::remove(const QString &isbn)
{
    QSqlQuery query(m_db.database());
    query.prepare("DELETE FROM books WHERE isbn = ?");
    query.addBindValue(isbn);

    if (!query.exec()) {
        qWarning() << "BookDao::remove failed:" << query.lastError().text();
        return false;
    }
    return true;
}
