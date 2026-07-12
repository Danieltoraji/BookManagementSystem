#ifndef SEARCH_INFO_MENU_H
#define SEARCH_INFO_MENU_H
#include "menu_base.h"

class SearchInfoMenu : public MenuBase
{
public:
    void show();
private:
    void displayAllBooks();
    void searchBooks();
    void searchCopies();
    void viewShelves();

    void buildSearchQuery(searchQuery &query);
    void printBooks(const std::vector<Book> &books);
    void printBookCopies(const std::vector<BookCopy> &bookCopies);
};

#endif // SEARCH_INFO_MENU_H