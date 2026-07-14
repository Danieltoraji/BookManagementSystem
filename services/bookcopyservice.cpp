#include "bookcopyservice.h"
#include "dao/bookcopydao.h"
#include "loanservice.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>


bookCopyService::bookCopyService()
{
    readBookCopiesFromFile();
}

bookCopyService& bookCopyService::getInstance()
{
    static bookCopyService instance;
    return instance;
}

bool bookCopyService::readBookCopiesFromFile()
{
    BookCopyDao& dao = BookCopyDao::getInstance();
    bookCopies = dao.loadBookCopiesFromFile("data/bookcopies.txt");
    return !bookCopies.empty();
}
bool bookCopyService::writeBookCopiesToFile() const
{
    BookCopyDao& dao = BookCopyDao::getInstance();
    return dao.saveBookCopiesToFile("data/bookcopies.txt", bookCopies);
}

bool bookCopyService::addBookCopy(const BookCopy& bookcopy)
{
    bookCopies.push_back(bookcopy);
    return true;
}
bool bookCopyService::cancelBookCopy(const std::string& isbn, const std::string& libCode)
{
    auto it = std::find_if(bookCopies.begin(), bookCopies.end(),
                            [&](const BookCopy& bc) { return bc.getISBN() == isbn && bc.getLibCode() == libCode; });
    if (it != bookCopies.end()) {
        // 若副本正在被借出，先将对应借阅记录标记为已返还
        if (it->getStatus() == borrowed) {
            std::string errMsg;
            loanService::getInstance().returnBookByLibCode(libCode, errMsg);
        }
        it->setStatus(cancelled);
        writeBookCopiesToFile(); // 自动更新文件
        return true;
    }
    return false;
}
bool bookCopyService::removeBookCopy(const std::string& isbn, const std::string& libCode)
{
    // 先处理被借出副本的借阅记录
    for (const auto& bc : bookCopies) {
        if (bc.getISBN() == isbn && bc.getLibCode() == libCode && bc.getStatus() == borrowed) {
            std::string errMsg;
            loanService::getInstance().returnBookByLibCode(libCode, errMsg);
        }
    }
    auto it = std::remove_if(bookCopies.begin(), bookCopies.end(),
                             [&](const BookCopy& bc) { return bc.getISBN() == isbn && bc.getLibCode() == libCode; });
    if (it != bookCopies.end()) {
        bookCopies.erase(it, bookCopies.end());
        writeBookCopiesToFile(); // 自动更新文件
        return true;
    }
    return false;
}
bool bookCopyService::cancelAllBookCopiesByISBN(const std::string& isbn, std::string& errorMessage)
{
    bool found = false;
    for (auto& bc : bookCopies) {
        if (bc.getISBN() == isbn) {
            // 若副本正在被借出，先将对应借阅记录标记为已返还
            if (bc.getStatus() == borrowed) {
                std::string errMsg;
                loanService::getInstance().returnBookByLibCode(bc.getLibCode(), errMsg);
            }
            bc.setStatus(cancelled);
            found = true;
        }
    }
    if (found) {
        writeBookCopiesToFile();
    } else {
        errorMessage = "未找到该ISBN对应的图书副本";
    }
    return found;
}
bool bookCopyService::updateBookCopy(const std::string& isbn, const std::string& libCode, const BookCopy& bookcopy)
{
    auto it = std::find_if(bookCopies.begin(), bookCopies.end(),
                            [&](const BookCopy& bc) { return bc.getISBN() == isbn && bc.getLibCode() == libCode; });
    if (it != bookCopies.end()) {
        *it = bookcopy;
        writeBookCopiesToFile(); // 自动更新文件
        return true;
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
BookCopy* bookCopyService::getBookCopyByLibCode(const std::string& libCode) const
{
    for(const auto& bc : bookCopies){
        if(bc.getLibCode() == libCode){
            return const_cast<BookCopy*>(&bc);
        }
    }
    return nullptr;
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
bool bookCopyService::isLibCodeAvailable(const std::string& libCode) const
{
    for (const auto& bc : bookCopies) {
        if (bc.getLibCode() == libCode) {
            return false; // 如果找到了相同的馆藏号，返回false
        }
    }
    return true; // 没有找到相同的馆藏号，返回true
}