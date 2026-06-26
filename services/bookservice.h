#ifndef BOOKSERVICE_H
#define BOOKSERVICE_H
#include <string>
#include <list>
#include <vector>
#include "model/book.h"
#include "dao/bookdao.h"

/*searchQuery用于封装搜索条件，借鉴了清华大学图书馆水木搜索的设计。本系统搜索条件为：
字段1 判断1 内容1 逻辑 字段2 判断2 内容2
字段包括ISBN、标题、作者，判断包括等于、包含、前段相同，逻辑包括与、或。*/
struct searchQuery{
    enum class Field { Empty, ISBN, Title, Author };
    enum class Condition { Equals, Contains, StartsWith };
    enum class Logic { And, Or };
    Field field1;
    Condition condition1;
    std::string value1;
    Logic logic;
    Field field2;
    Condition condition2;
    std::string value2;
};

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

    // 图书搜索
    std::vector<const Book*> searchBooks(const searchQuery& query) const;

private:
    BookService();

    // 数据主存
    std::vector<Book> books;
};

#endif // BOOKSERVICE_H
