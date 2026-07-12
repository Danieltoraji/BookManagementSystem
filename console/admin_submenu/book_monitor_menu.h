#ifndef BOOK_MONITOR_MENU_H
#define BOOK_MONITOR_MENU_H

#include "../menu_base.h"
#include <vector>
#include "model/book.h"
#include "services/bookservice.h"
#include "services/bookcopyservice.h"

// 图书监控菜单：搜索、显示、增删改图书，文件读写
class BookMonitorMenu : public MenuBase
{
public:
    void show();

private:
    // 菜单操作
    void searchBooks();
    void displayAllBooks();
    void searchByISBN();
    void addBook();
    void updateBook();
    void deleteBook();
    void readFromFile();
    void saveToFile();

    // 辅助：构造搜索条件
    void buildSearchQuery(searchQuery &query);

    // 辅助：打印图书列表
    void printBooks(const std::vector<Book> &books);
};

#endif // BOOK_MONITOR_MENU_H
