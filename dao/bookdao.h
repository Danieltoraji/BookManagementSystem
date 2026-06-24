#ifndef BOOKDAO_H
#define BOOKDAO_H

#include <QString>
#include <vector>
#include <optional>

class Book;
class DatabaseManager;

class BookDao
{
public:
    explicit BookDao(DatabaseManager &db);

    bool insert(const Book &book);
    std::optional<Book> findByISBN(const QString &isbn);
    std::vector<Book> searchByTitle(const QString &keyword);
    std::vector<Book> listAll();
    bool update(const Book &book);
    bool remove(const QString &isbn);

private:
    DatabaseManager &m_db;
};

#endif // BOOKDAO_H
