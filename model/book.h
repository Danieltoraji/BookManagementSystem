#ifndef BOOK_H
#define BOOK_H

#include <string>

class Book
{
private:
    std::string ISBN;
    std::string Title;
    std::string Author;
    std::string Publisher;
    int PublishingYear;
    std::string Category;
    std::string Remarks;

public:
    // Initialization
    Book(const std::string &isbn = "", const std::string &title = "", const std::string &author = "",
         const std::string &publisher = "", int year = 0, const std::string &category = "",
          const std::string &remarks = "");

    // Getters
    std::string getISBN() const;
    std::string getTitle() const;
    std::string getAuthor() const;
    std::string getPublisher() const;
    int getPublishingYear() const;
    std::string getCategory() const;
    std::string getRemarks() const;

    // Setters
    void setISBN(const std::string &value);
    void setTitle(const std::string &value);
    void setAuthor(const std::string &value);
    void setPublisher(const std::string &value);
    void setPublishingYear(int year);
    void setCategory(const std::string &value);
    void setRemarks(const std::string &value);
};

#endif // BOOK_H
