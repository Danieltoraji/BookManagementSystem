#ifndef CONSOLE_USER_MENU_H
#define CONSOLE_USER_MENU_H

#include "menu_base.h"
#include <vector>
#include "model/book.h"
#include "services/bookservice.h"
#include "console/user_submenu/search_info_menu.h"
#include "console/user_submenu/loan_menu.h"
#include "console/user_submenu/personal_info_menu.h"

// 普通用户菜单：图书搜索、显示、文件读取
class UserMenu : public MenuBase
{
public:
    void show();

private:
    // 菜单操作
    void searchBooks();
    void displayAllBooks();
    //void searchCopies();
    //void borrowBook();
    //void returnBook();

    // 辅助：构造搜索条件
    void buildSearchQuery(searchQuery &query);

    // 辅助：打印图书列表
    void printBooks(const std::vector<Book> &books);
};

#endif // CONSOLE_USER_MENU_H