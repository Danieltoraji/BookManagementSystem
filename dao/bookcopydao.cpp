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

std::string BookCopyDao::bookCopyToString(const BookCopy& bookcopy) const{
    std::ostringstream stream;
    stream << bookcopy.getISBN() << '|'
           << bookcopy.getLibCode() << '|'
           << bookcopy.getBookLocation() << '|';
    switch (bookcopy.getStatus()) {
        case available:  stream << "available";  break;
        case borrowed:   stream << "borrowed";   break;
        case cancelled:  stream << "cancelled";  break;
        default:         stream << "available";  break;
    }
    return stream.str();
}

BookCopy BookCopyDao::stringToBookCopy(const std::string& bookcopystr) const{
    std::istringstream stream(bookcopystr);
    std::string field;
    std::vector<std::string> fields;
    while(std::getline(stream,field,'|')){
        fields.push_back(field);
    }
    BookCopy bookcopy;
    if(fields.size() == 4){
        bookcopy.setISBN(fields[0]);
        bookcopy.setLibCode(fields[1]);
        bookcopy.setBookLocation(fields[2]);
        switch (fields[3][0]){
            case 'a':
                bookcopy.setStatus(available);
                break;
            case 'b':
                bookcopy.setStatus(borrowed);
                break;
            case 'c':
                bookcopy.setStatus(cancelled);
                break;
            default:
                bookcopy.setStatus(available);
        }
    }
    return bookcopy;
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
        bookCopies.push_back(stringToBookCopy(line));
    }
    return bookCopies;
}


bool BookCopyDao::saveBookCopiesToFile(const std::string& filename, const std::vector<BookCopy>& bookCopies) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    for (const auto& bookcopy : bookCopies) {
        file << bookCopyToString(bookcopy) << std::endl;
    }

    return true;
}