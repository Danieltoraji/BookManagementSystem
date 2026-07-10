#ifndef CONSOLE_ADMIN_MENU_H
#define CONSOLE_ADMIN_MENU_H

#include "menu_base.h"
#include <vector>
#include "model/book.h"
#include "services/bookservice.h"

// 管理员菜单：图书搜索、显示、文件读写、增删
class AdminMenu : public MenuBase
{
public:
    void show();

private:
    // 菜单操作
    void searchBooks();
    void displayAllBooks();
    void readFromFile();
    void saveToFile();
    void addBook();
    void deleteBook();

    // 辅助：构造搜索条件
    void buildSearchQuery(searchQuery &query);

    // 辅助：打印图书列表
    void printBooks(const std::vector<Book> &books);
};

#endif // CONSOLE_ADMIN_MENU_H