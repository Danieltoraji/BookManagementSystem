#include "menu_base.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <sstream>

#ifdef _WIN32
#include <cstdlib>
#else
#include <unistd.h>
#endif

int MenuBase::displayMenu(const std::string &title, const std::vector<std::string> &options)
{
    clearScreen();
    printSeparator('=');
    std::cout << "  " << title << std::endl;
    printSeparator('=');
    for (size_t i = 0; i < options.size(); ++i) {
        std::cout << "  " << (i + 1) << ". " << options[i] << std::endl;
    }
    printSeparator('-');

    int choice = 0;
    while (true) {
        std::cout << "请选择操作: ";
        std::string line;
        if (!std::getline(std::cin, line)) {
            // EOF
            return 0;
        }
        std::istringstream iss(line);
        if (iss >> choice && choice >= 1 && choice <= static_cast<int>(options.size())) {
            return choice;
        }
        std::cout << "输入无效，请重新输入。" << std::endl;
    }
}

std::string MenuBase::readLine(const std::string &prompt)
{
    std::cout << prompt;
    std::string line;
    if (!std::getline(std::cin, line)) {
        return "";
    }
    // 去除首尾空白
    size_t start = line.find_first_not_of(" \t\r\n");
    if (start == std::string::npos)
        return "";
    size_t end = line.find_last_not_of(" \t\r\n");
    return line.substr(start, end - start + 1);
}

int MenuBase::readInt(const std::string &prompt)
{
    while (true) {
        std::string line = readLine(prompt);
        if (line.empty())
            return 0;
        std::istringstream iss(line);
        int val;
        if (iss >> val) {
            return val;
        }
        std::cout << "输入无效，请输入数字。" << std::endl;
    }
}

void MenuBase::pause()
{
    std::cout << "\n按回车键继续...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void MenuBase::clearScreen()
{
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void MenuBase::printSeparator(char ch, int count)
{
    std::string sep(count, ch);
    std::cout << sep << std::endl;
}
