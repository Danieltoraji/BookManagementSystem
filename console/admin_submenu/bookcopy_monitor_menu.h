#ifndef BOOKCOPY_MONITOR_MENU_H
#define BOOKCOPY_MONITOR_MENU_H

#include "../menu_base.h"
#include <vector>
#include "model/bookcopy.h"

// 图书副本监控菜单：查看、搜索、增删改副本，文件读写
class BookCopyMonitorMenu : public MenuBase
{
public:
    void show();

private:
    // 菜单操作
    void displayAllBookCopies();
    void searchByISBN();
    void searchByLibCode();
    void searchByLocation();
    void addBookCopy();
    void updateBookCopy();
    void removeBookCopy();
    void readFromFile();
    void saveToFile();

    // 辅助：打印副本列表
    void printBookCopies(const std::vector<BookCopy> &copies);
};

#endif // BOOKCOPY_MONITOR_MENU_H
