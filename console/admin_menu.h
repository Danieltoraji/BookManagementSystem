#ifndef CONSOLE_ADMIN_MENU_H
#define CONSOLE_ADMIN_MENU_H

#include "menu_base.h"
#include "console/admin_submenu/user_monitor_menu.h"
#include "console/admin_submenu/book_monitor_menu.h"
#include "console/admin_submenu/bookcopy_monitor_menu.h"
#include "console/admin_submenu/loan_monitor_menu.h"

// 管理员菜单：调度各监控子菜单
class AdminMenu : public MenuBase
{
public:
    void show();
};

#endif // CONSOLE_ADMIN_MENU_H