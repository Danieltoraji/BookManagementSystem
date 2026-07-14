#ifndef BOOKCOPYSERVICE_H
#define BOOKCOPYSERVICE_H
#include <string>
#include <list>
#include <vector>
#include "model/bookcopy.h"

class bookCopyService
{
public:
    static bookCopyService& getInstance();
    bookCopyService(const bookCopyService&) = delete;
    bookCopyService& operator=(const bookCopyService&) = delete;
    bookCopyService(bookCopyService&&) = delete;
    bookCopyService& operator=(bookCopyService&&) = delete;

    bool readBookCopiesFromFile();
    bool writeBookCopiesToFile() const;

    //现在管理后有自动更新文件了！
    bool addBookCopy(const BookCopy& bookcopy);
    bool cancelBookCopy(const std::string& isbn, const std::string& libCode);
    bool removeBookCopy(const std::string& isbn, const std::string& libCode);
    bool updateBookCopy(const std::string& isbn, const std::string& libCode, const BookCopy& bookcopy);

    std::vector<BookCopy> getAllBookCopies() const;
    std::vector<BookCopy> getBookCopiesByISBN(const std::string& isbn) const;
    BookCopy* getBookCopyByLibCode(const std::string& libCode) const;
    std::vector<BookCopy> getBookCopiesByLocation(const std::string& lib = "", const short floor = 0, const short row = 0,
         const short unit = 0, const short level = 0) const;
    bool isLibCodeAvailable(const std::string& libCode) const;

    std::vector<BookCopy> bookCopies;
private:
    bookCopyService();
};

#endif // BOOKCOPYSERVICE_H
