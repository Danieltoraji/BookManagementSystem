#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <list>

class Book
{
private:
    std::string ISBN;
    std::string Title;
    std::string Author;
    std::string Publisher;
    int PublishingYear;
    std::string Category;
    std::list<std::string> Copies;

public:
    Book();

    // Getters
    std::string getISBN() const;
    std::string getTitle() const;
    std::string getAuthor() const;
    std::string getPublisher() const;
    int getPublishingYear() const;
    std::string getCategory() const;
    std::list<std::string> getCopies() const;

    // Setters
    void setISBN(const std::string &value);
    void setTitle(const std::string &value);
    void setAuthor(const std::string &value);
    void setPublisher(const std::string &value);
    void setPublishingYear(int year);
    void setCategory(const std::string &value);

    // Copy management
    void addCopy(const std::string &libCode);
    void removeCopy(const std::string &libCode);
    bool hasCopy(const std::string &libCode) const;
};

#endif // BOOK_H
