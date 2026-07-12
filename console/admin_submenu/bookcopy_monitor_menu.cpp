#include "bookcopy_monitor_menu.h"
#include "services/bookcopyservice.h"
#include <iostream>
#include <iomanip>

void BookCopyMonitorMenu::show()
{
    std::vector<std::string> options = {
        "查看所有副本",
        "按ISBN查询副本",
        "按馆藏号查询副本",
        "按位置查询副本",
        "添加副本",
        "修改副本",
        "删除副本",
        "从文件读取副本",
        "保存副本到文件",
        "返回上级菜单"
    };

    while (true) {
        int choice = displayMenu("图书副本监控", options);
        switch (choice) {
            case 1: displayAllBookCopies(); break;
            case 2: searchByISBN(); break;
            case 3: searchByLibCode(); break;
            case 4: searchByLocation(); break;
            case 5: addBookCopy(); break;
            case 6: updateBookCopy(); break;
            case 7: removeBookCopy(); break;
            case 8: readFromFile(); break;
            case 9: saveToFile(); break;
            case 10: return;
            default: std::cout << "无效的选择，请重新输入。" << std::endl; break;
        }
    }
}

void BookCopyMonitorMenu::displayAllBookCopies()
{
    std::cout << "\n=== 查看所有副本 ===" << std::endl;
    std::cout << "此功能待实现。" << std::endl;
    pause();
}

void BookCopyMonitorMenu::searchByISBN()
{
    std::cout << "\n=== 按ISBN查询副本 ===" << std::endl;
    std::cout << "此功能待实现。" << std::endl;
    pause();
}

void BookCopyMonitorMenu::searchByLibCode()
{
    std::cout << "\n=== 按馆藏号查询副本 ===" << std::endl;
    std::cout << "此功能待实现。" << std::endl;
    pause();
}

void BookCopyMonitorMenu::searchByLocation()
{
    std::cout << "\n=== 按位置查询副本 ===" << std::endl;
    std::cout << "此功能待实现。" << std::endl;
    pause();
}

void BookCopyMonitorMenu::addBookCopy()
{
    std::cout << "\n=== 添加副本 ===" << std::endl;
    std::cout << "此功能待实现。" << std::endl;
    pause();
}

void BookCopyMonitorMenu::updateBookCopy()
{
    std::cout << "\n=== 修改副本 ===" << std::endl;
    std::cout << "此功能待实现。" << std::endl;
    pause();
}

void BookCopyMonitorMenu::removeBookCopy()
{
    std::cout << "\n=== 删除副本 ===" << std::endl;
    std::cout << "此功能待实现。" << std::endl;
    pause();
}

void BookCopyMonitorMenu::readFromFile()
{
    std::cout << "\n=== 从文件读取副本 ===" << std::endl;
    std::cout << "此功能待实现。" << std::endl;
    pause();
}

void BookCopyMonitorMenu::saveToFile()
{
    std::cout << "\n=== 保存副本到文件 ===" << std::endl;
    std::cout << "此功能待实现。" << std::endl;
    pause();
}

void BookCopyMonitorMenu::printBookCopies(const std::vector<BookCopy> &copies)
{
    (void)copies; // 框架阶段暂不使用
    std::cout << "此功能待实现。" << std::endl;
}
