#include "bookcopydao.h"
#include <algorithm>
#include <fstream>
#include <sstream>

BookCopyDao::BookCopyDao() {}

BookCopyDao& BookCopyDao::getInstance()
{
    static BookCopyDao instance;
    return instance;
}

std::string BookCopyDao::bookCopyToString(const BookCopy& bookcopy){
    std::string result;
    std::ostringstream string;
    string<<bookcopy.getISBN()<<bookcopy.getLibCode()<<bookcopy.getBookLocation()<<bookcopy.getStatus();
}

BookCopy BookCopyDao::stringToBookCopy(const std::string& bookcopystr) const{
    std::istringstream stream(bookcopystr);
    std::vector<std::string> fields;
    std::getline(stream,fields,'|');
}

std::vector<BookCopy> BookCopyDao::loadBookCopiesFromFile(const std::string& filename)
{
    std::vector<BookCopy> bookCopies;
    std::ifstream file(filename);
    if (!file.is_open()) {
        return bookCopies;
    }

    std::string line;
    while (std::getline(file,line)){
        if (line.empty()){
            continue;
        }

    }
}

