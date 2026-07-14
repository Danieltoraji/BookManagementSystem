#ifndef CONSOLE_ABOUT_MENU_H
#define CONSOLE_ABOUT_MENU_H

#include "menu_base.h"
#include <iostream>
#include <windows.h>

class AboutMenu : public MenuBase
{
public:
    void show();
};

#endif // CONSOLE_ABOUT_MENU_H