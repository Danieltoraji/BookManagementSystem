#ifndef BOOKSERVICE_H
#define BOOKSERVICE_H
#include <string>
#include <list>
#include <vector>
#include "model/book.h"
#include "dao/bookdao.h"

class BookService
{
public:
    static BookService& getInstance();
    BookService(const BookService&) = delete;
    BookService& operator=(const BookService&) = delete;
    BookService(BookService&&) = delete;
    BookService& operator=(BookService&&) = delete;

    // 强制存写
    bool readBooksFromFile();
    bool writeBooksToFile() const;

    // 图书管理
    std::vector<Book> getAllBooks();
    bool addBook(const Book& book);
    bool removeBook(const std::string& isbn);
    bool updateBook(const std::string& isbn, const Book& book);

    
private:
    BookService();

    // 数据主存
    std::vector<Book> books;
};

#endif // BOOKSERVICE_H
