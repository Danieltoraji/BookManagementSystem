#ifndef BOOKSERVICE_H
#define BOOKSERVICE_H
#include <string>
#include <list>
#include <vector>
#include "model/book.h"
#include "dao/bookdao.h"

class bookService
{
public:
    bookService();
private:
    // 数据主存
    std::vector<Book> books;

    // 图书管理
    std::vector<Book> getAllBooks();
    bool addBook(const Book& book);
    bool removeBook(const std::string& isbn);
    bool updateBook(const std::string& isbn, const Book& book);

    std::vector<const Book*> searchBooksByISBN(const std::string& isbn) const;
    std::vector<const Book*> searchBooksByTitle(const std::string& title) const;
    std::vector<const Book*> searchBooksByAuthor(const std::string& author) const;

};

#endif // BOOKSERVICE_H
