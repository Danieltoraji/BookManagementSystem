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
        "按位置查询副本（查看本馆书架）",
        "添加副本",
        "修改副本",
        "注销副本",
        "删除副本（不建议使用）",
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
            case 7: cancelBookCopy(); break;
            case 8: removeBookCopy(); break;
            case 9: readFromFile(); break;
            case 10: saveToFile(); break;
            case 11: return;
            default: std::cout << "无效的选择，请重新输入。" << std::endl; break;
        }
    }
}

void BookCopyMonitorMenu::displayAllBookCopies()
{
    std::cout << "\n=== 查看所有副本 ===" << std::endl;
    std::vector<BookCopy> copies = bookCopyService::getInstance().getAllBookCopies();
    printBookCopies(copies);
    pause();
}

void BookCopyMonitorMenu::searchByISBN()
{
    std::cout << "\n=== 按ISBN查询副本 ===" << std::endl;
    std::string isbn = readLine("请输入图书ISBN: ");
    auto copies = bookCopyService::getInstance().getBookCopiesByISBN(isbn);
    if (copies.empty()) {
        std::cout << "没有找到该ISBN的图书副本。" << std::endl;
    } else {
        std::cout << "书名: " << BookService::getInstance().getBookTitleByISBN(isbn) << std::endl;
        std::cout << "找到 " << copies.size() << " 个副本：" << std::endl;
        for (const auto &copy : copies) {
            std::string statusStr;
            switch (copy.getStatus()) {
                case available:  statusStr = "可用";  break;
                case borrowed:   statusStr = "借阅中";   break;
                case cancelled:  statusStr = "已注销";  break;
                default:         statusStr = "未知";    break;
            }
            std::cout << "副本编号: " << copy.getLibCode() 
                      << ", 位置: " << copy.getBookLocation() 
                      << ", 状态: " << statusStr 
                      << std::endl;
        }
    }
    pause();
}

void BookCopyMonitorMenu::searchByLibCode()
{
    std::cout << "\n=== 按馆藏号查询副本 ===" << std::endl;
    std::string libCode = readLine("请输入馆藏号: ");
    BookCopy* copy = bookCopyService::getInstance().getBookCopyByLibCode(libCode);
    if (!copy) {
        std::cout << "没有找到该馆藏号的图书副本。" << std::endl;
    } else {
        printBookCopies({*copy});
    }
}

void BookCopyMonitorMenu::searchByLocation()
{
    std::cout << "\n=== 按位置查询副本 ===" << std::endl;
    std::cout << "任一项不输入则代表不指定该项以及后续项" << std::endl;
    std::string lib = "";
    short floor = 0;
    short row = 0;
    short unit = 0;
    short level = 0;
    lib = readLine("请输入图书馆代码: ");
    if (!lib.empty()) {
        floor = readInt("请输入楼层号: ");
        if (floor){
            row = readInt("请输入书架号: ");
            if (row){
                unit = readInt("请输入单元号: ");
                if (unit){
                    level = readInt("请输入层号: ");
                }
            }
        }
    }
    auto copies = bookCopyService::getInstance().getBookCopiesByLocation(lib, floor, row, unit, level);
    printSeparator('=');
    std::cout << "找到 " << copies.size() << " 个副本：" << std::endl;
    printBookCopies(copies);
    pause();
}

void BookCopyMonitorMenu::addBookCopy()
{
    std::cout << "\n=== 添加副本 ===" << std::endl;
    std::string isbn = readLine("请输入图书ISBN: ");
    if(!BookService::getInstance().isBookValid(isbn)) {
        std::cout << "图书ISBN无效，请先添加图书信息。" << std::endl;
        pause();
        return;
    }
    std::string libCode = readLine("请输入馆藏号: ");
    if (!bookCopyService::getInstance().isLibCodeAvailable(libCode)) {
        std::cout << "馆藏号已存在，请重新输入。" << std::endl;
        pause();
        return;
    }
    std::string lib = readLine("请输入图书馆代码: ");
    short floor = readInt("请输入楼层号: ");
    short row = readInt("请输入书架号: ");
    short unit = readInt("请输入单元号: ");
    short level = readInt("请输入层号: ");

    Location loc(lib, floor, row, unit, level);
    if (bookCopyService::getInstance().addBookCopy(BookCopy(isbn, libCode, loc))) {
        std::cout << "副本添加成功。" << std::endl;
    } else {
        std::cout << "副本添加失败。" << std::endl;
    }
    pause();
}

void BookCopyMonitorMenu::updateBookCopy()
{
    std::cout << "\n=== 修改副本 ===" << std::endl;
    std::string isbn = readLine("请输入图书ISBN: ");
    if (!BookService::getInstance().isBookValid(isbn)) {
        std::cout << "图书ISBN无效，请先添加图书信息。" << std::endl;
        pause();
        return;
    }
    std::string libCode = readLine("请输入要修改的副本的馆藏号: ");
    if (!bookCopyService::getInstance().getBookCopyByLibCode(libCode)) {
        std::cout << "馆藏号不存在，请重新输入。" << std::endl;
        pause();
        return;
    }
    std::cout << "请输入新的副本信息。注意只能修改地点信息。留空表示不变。" << std::endl;
    std::string lib = readLine("请输入新的图书馆代码: ");
    short floor = readInt("请输入新的楼层号: ");
    short row = readInt("请输入新的书架号: ");
    short unit = readInt("请输入新的单元号: ");
    short level = readInt("请输入新的层号: ");
    Location loc(lib, floor, row, unit, level);
    bookCopyService::getInstance().updateBookCopy(isbn, libCode, BookCopy(isbn, libCode, loc));
    std::cout << "副本修改成功。" << std::endl;
    pause();
}

void BookCopyMonitorMenu::cancelBookCopy()
{
    std::cout << "\n=== 注销副本 ===" << std::endl;
    std::string isbn = readLine("请输入图书ISBN: ");
    if (!BookService::getInstance().isBookValid(isbn)) {
        std::cout << "图书ISBN无效，请先添加图书信息。" << std::endl;
        pause();
        return;
    }
    std::string libCode = readLine("请输入要注销的副本的馆藏号: ");
    if (!bookCopyService::getInstance().getBookCopyByLibCode(libCode)) {
        std::cout << "馆藏号不存在，请重新输入。" << std::endl;
        pause();
        return;
    }
    bookCopyService::getInstance().cancelBookCopy(isbn, libCode);
    pause();
}

void BookCopyMonitorMenu::removeBookCopy()
{
    std::cout << "\n=== 删除副本 ===" << std::endl;
    std::string confirmation = readLine("不建议删除副本，因为可能会影响借阅等功能。建议使用注销副本功能。请确认是否继续删除？(y/n): ");
    if (confirmation != "y" && confirmation != "Y") {
        std::cout << "操作已取消。" << std::endl;
        pause();
        return;
    }
    std::string isbn = readLine("请输入图书ISBN: ");
    if (!BookService::getInstance().isBookValid(isbn)) {
        std::cout << "图书ISBN无效，请先添加图书信息。" << std::endl;
        pause();
        return;
    }
    std::string libCode = readLine("请输入要删除的副本的馆藏号: ");
    if (!bookCopyService::getInstance().isLibCodeAvailable(libCode)) {
        std::cout << "馆藏号不存在，请重新输入。" << std::endl;
        pause();
        return;
    }
    if (bookCopyService::getInstance().removeBookCopy(isbn, libCode)) {
        std::cout << "副本删除成功。" << std::endl;
    } else {
        std::cout << "副本删除失败。" << std::endl;
    }
    pause();
}

void BookCopyMonitorMenu::readFromFile()
{
    std::cout << "\n=== 从文件读取副本 ===" << std::endl;
    bookCopyService::getInstance().readBookCopiesFromFile();
    std::cout << "副本已从文件读取。" << std::endl;
    pause();
}

void BookCopyMonitorMenu::saveToFile()
{
    std::cout << "\n=== 保存副本到文件 ===" << std::endl;
    bookCopyService::getInstance().writeBookCopiesToFile();
    std::cout << "副本已保存到文件。" << std::endl;
    pause();
}

void BookCopyMonitorMenu::printBookCopies(const std::vector<BookCopy> &copies)
{
    std::cout<< std::left << std::setw(20) << "ISBN"
              << std::setw(30) << "书名"
              << std::setw(15) << "馆藏号"
              << std::setw(20) << "位置"
              << std::setw(10) << "状态" << std::endl;
    std::string statusStr;
    for (const auto &copy : copies) {
        switch (copy.getStatus()) {
            case available:  statusStr = "可用";  break;
            case borrowed:   statusStr = "借阅中";   break;
            case cancelled:  statusStr = "已注销";  break;
            default:         statusStr = "未知";    break;
        }
        std::cout << std::left << std::setw(20) << copy.getISBN()
                  << std::setw(30) << BookService::getInstance().getBookTitleByISBN(copy.getISBN())
                  << std::setw(15) << copy.getLibCode()
                  << std::setw(20) << copy.getBookLocation()
                  << std::setw(10) << statusStr << std::endl;
    }
}
