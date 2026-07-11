#include "user_menu.h"
#include "services/bookservice.h"
#include <iostream>
#include <iomanip>
#include <sstream>

void UserMenu::show()
{
    std::vector<std::string> options = {
        "搜索图书",
        "显示所有图书",
        "搜索图书副本",
        "借阅指定图书",
        "归还指定图书",
        "退出登录"
    };

    while (true) {
        int choice = displayMenu("用户系统", options);
        switch (choice) {
            case 1: searchBooks(); break;
            case 2: displayAllBooks(); break;
            case 3: searchCopies(); break;
            case 4: borrowBook(); break;
            case 5: returnBook(); break;
            case 6: return; // 退出登录
            default: std::cout << "无效的选择，请重新输入。" << std::endl;break;
        }
    }
}

void UserMenu::buildSearchQuery(searchQuery &query)
{
    // 字段1
    std::cout << "\n--- 搜索条件1 ---" << std::endl;
    std::cout << "  1. ISBN" << std::endl;
    std::cout << "  2. 标题" << std::endl;
    std::cout << "  3. 作者" << std::endl;
    std::cout << "  0. 跳过（不设条件1）" << std::endl;
    int f1 = readInt("请选择搜索字段: ");
    switch (f1) {
        case 1:  query.field1 = searchQuery::Field::ISBN;   break;
        case 2:  query.field1 = searchQuery::Field::Title;  break;
        case 3:  query.field1 = searchQuery::Field::Author; break;
        default: query.field1 = searchQuery::Field::Empty;  break;
    }

    if (query.field1 != searchQuery::Field::Empty) {
        std::cout << "  1. 等于" << std::endl;
        std::cout << "  2. 包含" << std::endl;
        std::cout << "  3. 开头匹配" << std::endl;
        int c1 = readInt("请选择匹配方式: ");
        switch (c1) {
            case 2:  query.condition1 = searchQuery::Condition::Contains;   break;
            case 3:  query.condition1 = searchQuery::Condition::StartsWith; break;
            default: query.condition1 = searchQuery::Condition::Equals;     break;
        }
        query.value1 = readLine("请输入搜索内容: ");
    }

    // 字段2
    std::cout << "\n--- 搜索条件2 ---" << std::endl;
    std::cout << "  1. ISBN" << std::endl;
    std::cout << "  2. 标题" << std::endl;
    std::cout << "  3. 作者" << std::endl;
    std::cout << "  0. 跳过（不设条件2）" << std::endl;
    int f2 = readInt("请选择搜索字段: ");
    switch (f2) {
        case 1:  query.field2 = searchQuery::Field::ISBN;   break;
        case 2:  query.field2 = searchQuery::Field::Title;  break;
        case 3:  query.field2 = searchQuery::Field::Author; break;
        default: query.field2 = searchQuery::Field::Empty;  break;
    }

    if (query.field2 != searchQuery::Field::Empty) {
        std::cout << "  1. 与（AND）" << std::endl;
        std::cout << "  2. 或（OR）" << std::endl;
        int logic = readInt("请选择逻辑关系: ");
        query.logic = (logic == 2) ? searchQuery::Logic::Or : searchQuery::Logic::And;

        std::cout << "  1. 等于" << std::endl;
        std::cout << "  2. 包含" << std::endl;
        std::cout << "  3. 开头匹配" << std::endl;
        int c2 = readInt("请选择匹配方式: ");
        switch (c2) {
            case 2:  query.condition2 = searchQuery::Condition::Contains;   break;
            case 3:  query.condition2 = searchQuery::Condition::StartsWith; break;
            default: query.condition2 = searchQuery::Condition::Equals;     break;
        }
        query.value2 = readLine("请输入搜索内容: ");
    }
}

void UserMenu::printBooks(const std::vector<Book> &books)
{
    if (books.empty()) {
        std::cout << "没有找到图书。" << std::endl;
        return;
    }

    printSeparator('=');
    std::cout << std::left
              << std::setw(18) << "ISBN"
              << std::setw(25) << "标题"
              << std::setw(15) << "作者"
              << std::setw(20) << "出版社"
              << std::setw(8)  << "年份"
              << std::setw(12) << "分类"
              << std::setw(20) << "副本列表"
              << "备注" << std::endl;
    printSeparator('-');

    for (const auto &b : books) {
        std::string copiesStr;
        auto copies = b.getCopies();
        for (auto it = copies.begin(); it != copies.end(); ++it) {
            if (it != copies.begin())
                copiesStr += ", ";
            copiesStr += *it;
        }

        std::cout << std::left
                  << std::setw(18) << b.getISBN()
                  << std::setw(25) << b.getTitle()
                  << std::setw(15) << b.getAuthor()
                  << std::setw(20) << b.getPublisher()
                  << std::setw(8)  << b.getPublishingYear()
                  << std::setw(12) << b.getCategory()
                  << std::setw(20) << copiesStr
                  << b.getRemarks() << std::endl;
    }
    printSeparator('=');
    std::cout << "共 " << books.size() << " 本图书。" << std::endl;
}

void UserMenu::searchBooks()
{
    std::cout << "\n=== 搜索图书 ===" << std::endl;
    searchQuery query;
    query.field1 = searchQuery::Field::Empty;
    query.condition1 = searchQuery::Condition::Equals;
    query.logic = searchQuery::Logic::And;
    query.field2 = searchQuery::Field::Empty;
    query.condition2 = searchQuery::Condition::Equals;

    buildSearchQuery(query);

    auto results = BookService::getInstance().searchBooks(query);
    std::vector<Book> books;
    books.reserve(results.size());
    for (const Book *b : results) {
        if (b)
            books.push_back(*b);
    }
    printBooks(books);
    pause();
}

void UserMenu::displayAllBooks()
{
    std::cout << "\n=== 所有图书 ===" << std::endl;
    printBooks(BookService::getInstance().getAllBooks());
    pause();
}

void UserMenu::readFromFile()
{
    std::cout << "\n=== 从文件读取图书 ===" << std::endl;
    if (BookService::getInstance().readBooksFromFile()) {
        std::cout << "图书数据已成功加载！" << std::endl;
    } else {
        std::cout << "图书数据加载失败，请检查文件是否为空！" << std::endl;
    }
    pause();
}