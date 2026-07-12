#ifndef SEARCH_INFO_MENU_H
#define SEARCH_INFO_MENU_H
#include "../menu_base.h"
#include "model/book.h"
#include "model/bookcopy.h"
#include "services/bookservice.h"
#include "services/bookcopyservice.h"
#include "model/location.h"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
class SearchInfoMenu : public MenuBase
{
public:
    void show();
private:
    void displayAllBooks();
    void displayAllBookCopies();
    void searchBooks();
    void searchCopies();
    void viewShelves();

    void buildSearchQuery(searchQuery &query);
    void printBooks(const std::vector<Book> &books);
    void printBookCopies(const std::vector<BookCopy> &bookCopies);
};

#endif // SEARCH_INFO_MENU_H