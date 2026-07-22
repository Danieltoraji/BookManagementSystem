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
    std::vector<Book> loadBooksFromFile(const std::string& filename);
    bool saveBooksToFile(const std::string& filename, const std::vector<Book>& books) const;

private:
    BookDao() = default;

    // 序列化辅助函数
    std::string bookToString(const Book& book) const;
    Book stringToBook(const std::string& bookStr) const;
};
#endif // BOOKDAO_H

/*
图书文件设计格式：
每行一个图书信息，字段之间用|分隔
ISBN|Title|Author|Publisher|PublishingYear|Category|Remarks
978-7-121-12345-6|C++ Primer|Lippman|电子工业出版社|2020|编程|畅销书
978-7-302-52690-2|C/C++程序设计教程|黄永峰、孙甲松|清华大学出版社|2019|编程|教材，清华大学电子工程系核心课
*/