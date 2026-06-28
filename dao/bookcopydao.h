#ifndef BOOKCOPYDAO_H
#define BOOKCOPYDAO_H
#include <string>
#include <list>
#include <vector>
#include "model/bookcopy.h"

class BookCopyDao
{
public:
    // 单例实现
    static BookCopyDao& getInstance();
    BookCopyDao(const BookCopyDao&) = delete;
    BookCopyDao& operator=(const BookCopyDao&) = delete;
    BookCopyDao(BookCopyDao&&) = delete;
    BookCopyDao& operator=(BookCopyDao&&) = delete;

    // 文件更新
    std::vector<BookCopy> loadBookCopiesFromFile(const std::string& filename);
    bool saveBookCopiesToFile(const std::string& filename, const std::vector<BookCopy>& bookCopies) const;


private:
    std::string bookCopyToString(const BookCopy& bookcopy);
    BookCopy stringToBookCopy (const std::string& bookcopystr) const;
    BookCopyDao();
};

#endif // BOOKCOPYDAO_H

/*图书纸本副本文件设计格式：
ISBN|libCode|bookLocation|status
978-7-121-12345-6|CP001|北馆-3-4-1-2|available
*/