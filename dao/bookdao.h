#ifndef BOOKDAO_H
#define BOOKDAO_H
#include <string>
#include <list>
#include <vector>
#include "model/book.h"
class BookDao {
public:
    // 单例实现
    static BookDao& getInstance();
    BookDao(const BookDao&) = delete;
    BookDao& operator=(const BookDao&) = delete;
    BookDao(BookDao&&) = delete;
    BookDao& operator=(BookDao&&) = delete;

    // 文件更新
    bool loadBooksFromFile(const std::string& filename);
    bool saveBooksToFile(const std::string& filename) const;

    // 图书管理
    std::vector<Book> getAllBooks();
    bool addBook(const Book& book);
    bool removeBook(const std::string& isbn);
    bool updateBook(const std::string& isbn, const Book& book);

    std::vector<const Book*> searchBooksByISBN(const std::string& isbn) const;
    std::vector<const Book*> searchBooksByTitle(const std::string& title) const;
    std::vector<const Book*> searchBooksByAuthor(const std::string& author) const;

private:
    BookDao() = default;

    // 数据主存
    std::vector<Book> books;

    // 序列化辅助函数
    std::string bookToString(const Book& book) const;
    Book stringToBook(const std::string& bookStr) const;
};
#endif // BOOKDAO_H

/*
图书文件设计格式：
每行一个图书信息，字段之间用|分隔
ISBN|Title|Author|Publisher|PublishingYear|Category|Copies|Remarks
其中Copies是list.
978-7-121-12345-6|C++ Primer|Lippman|电子工业出版社|2020|编程|CP001,CP002,CP003|畅销书
*/