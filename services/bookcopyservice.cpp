#include "bookcopyservice.h"
#include "dao/bookcopydao.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>


bookCopyService::bookCopyService() {}

bookCopyService& bookCopyService::getInstance()
{
    static bookCopyService instance;
    return instance;
}

bool bookCopyService::readBookCopiesFromFile()
{
    BookCopyDao& dao = BookCopyDao::getInstance();
    bookCopies = dao.loadBookCopiesFromFile("bookcopies.txt");
    return !bookCopies.empty();
}
bool bookCopyService::writeBookCopiesToFile() const
{
    BookCopyDao& dao = BookCopyDao::getInstance();
    return dao.saveBookCopiesToFile("bookcopies.txt", bookCopies);
}

bool bookCopyService::addBookCopy(const BookCopy& bookcopy)
{
    bookCopies.push_back(bookcopy);
    return true;
}
bool bookCopyService::removeBookCopy(const std::string& isbn, const std::string& libCode)
{
    auto it = std::remove_if(bookCopies.begin(), bookCopies.end(),
                             [&](const BookCopy& bc) { return bc.getISBN() == isbn && bc.getLibCode() == libCode; });
    if (it != bookCopies.end()) {
        bookCopies.erase(it, bookCopies.end());
        return true;
        writeBookCopiesToFile(); // 自动更新文件
    }
    return false;
}
bool bookCopyService::updateBookCopy(const std::string& isbn, const std::string& libCode, const BookCopy& bookcopy)
{
    auto it = std::find_if(bookCopies.begin(), bookCopies.end(),
                            [&](const BookCopy& bc) { return bc.getISBN() == isbn && bc.getLibCode() == libCode; });
    if (it != bookCopies.end()) {
        *it = bookcopy;
        return true;
        writeBookCopiesToFile(); // 自动更新文件
    }
    return false;
}

std::vector<BookCopy> bookCopyService::getAllBookCopies() const
{
    return bookCopies;
}
std::vector<BookCopy> bookCopyService::getBookCopiesByISBN(const std::string& isbn) const
{
    std::vector<BookCopy> result;
    for(auto & bc : bookCopies){
        if(bc.getISBN() == isbn){
            result.push_back(bc);
        }
    }
    return result;
}
std::vector<BookCopy> bookCopyService::getBookCopiesByLibCode(const std::string& libCode) const
{
    std::vector<BookCopy> result;
    for(auto & bc : bookCopies){
        if(bc.getLibCode() == libCode){
            result.push_back(bc);
        }
    }
    return result;
}
std::vector<BookCopy> bookCopyService::getBookCopiesByLocation(const std::string& lib, const short floor, const short row,
     const short unit, const short level) const
{
    std::vector<BookCopy> result;
    for(auto & bc : bookCopies){
        Location loc = bc.getBookLocation();
        if((lib.empty() || loc.getLib() == lib) &&
           (floor == 0 || loc.getFloor() == floor) &&
           (row == 0 || loc.getRow() == row) &&
           (unit == 0 || loc.getUnit() == unit) &&
           (level == 0 || loc.getLevel() == level)){
            result.push_back(bc);
        }
    }//对应项为0表示不限制该项
    return result;
}