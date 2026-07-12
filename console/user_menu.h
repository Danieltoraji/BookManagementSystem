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

};

#endif // CONSOLE_USER_MENU_H