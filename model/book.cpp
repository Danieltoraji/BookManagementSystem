#include "book.h"
#include <algorithm>

Book::Book(const std::string &isbn, const std::string &title, const std::string &author,
    const std::string &publisher, int year, const std::string &category,
    const std::string &remarks, const std::list<std::string> &copies)
    : ISBN(isbn), Title(title), Author(author), Publisher(publisher),
     PublishingYear(year), Category(category), Copies(copies), Remarks(remarks)
{
}

// Getters
std::string Book::getISBN() const { return ISBN; }
std::string Book::getTitle() const { return Title; }
std::string Book::getAuthor() const { return Author; }
std::string Book::getPublisher() const { return Publisher; }
int Book::getPublishingYear() const { return PublishingYear; }
std::string Book::getCategory() const { return Category; }
std::list<std::string> Book::getCopies() const { return Copies; }
std::string Book::getRemarks() const { return Remarks; }

// Setters
void Book::setISBN(const std::string &value) { ISBN = value; }
void Book::setTitle(const std::string &value) { Title = value; }
void Book::setAuthor(const std::string &value) { Author = value; }
void Book::setPublisher(const std::string &value) { Publisher = value; }
void Book::setPublishingYear(int year) { PublishingYear = year; }
void Book::setCategory(const std::string &value) { Category = value; }
void Book::setRemarks(const std::string &value) { Remarks = value; }

// Copy management
void Book::addCopy(const std::string &libCode)
{
    Copies.push_back(libCode);
}

void Book::removeCopy(const std::string &libCode)
{
    Copies.remove(libCode);
}

bool Book::hasCopy(const std::string &libCode) const
{
    return std::find(Copies.begin(), Copies.end(), libCode) != Copies.end();
}
