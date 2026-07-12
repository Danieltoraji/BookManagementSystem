#include "admin_menu.h"
#include "services/bookservice.h"
#include <iostream>
#include <iomanip>
#include <sstream>

void AdminMenu::show()
{
    std::vector<std::string> options = {
        "搜索图书",
        "显示所有图书",
        "从文件读取图书",
        "保存图书到文件",
        "添加图书",
        "删除图书",
        "退出登录"
    };

    while (true) {
        int choice = displayMenu("管理员系统", options);
        switch (choice) {
            case 1: searchBooks(); break;
            case 2: displayAllBooks(); break;
            case 3: readFromFile(); break;
            case 4: saveToFile(); break;
            case 5: addBook(); break;
            case 6: deleteBook(); break;
            case 7: return;
        }
    }
}

void AdminMenu::buildSearchQuery(searchQuery &query)
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

void AdminMenu::printBooks(const std::vector<Book> &books)
{
    if (books.empty()) {
        std::cout << "没有找到图书。" << std::endl;
        return;
    }

    printSeparator('=');
    std::cout << std::left
              << std::setw(15) << "ISBN"
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
        auto copies = bookCopyService::getInstance().getBookCopiesByISBN(b.getISBN());
        for (auto it = copies.begin(); it != copies.end(); ++it) {
            if (it != copies.begin())
                copiesStr += ", ";
            copiesStr += it->getLibCode();
        }

        std::cout << std::left
                  << std::setw(15) << b.getISBN()
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

void AdminMenu::searchBooks()
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

void AdminMenu::displayAllBooks()
{
    std::cout << "\n=== 所有图书 ===" << std::endl;
    printBooks(BookService::getInstance().getAllBooks());
    pause();
}

void AdminMenu::readFromFile()
{
    std::cout << "\n=== 从文件读取图书 ===" << std::endl;
    if (BookService::getInstance().readBooksFromFile()) {
        std::cout << "成功从文件读取图书信息！" << std::endl;
    } else {
        std::cout << "从文件读取图书信息失败！请检查文件是否为空。" << std::endl;
    }
    pause();
}

void AdminMenu::saveToFile()
{
    std::cout << "\n=== 保存图书到文件 ===" << std::endl;
    if (BookService::getInstance().writeBooksToFile()) {
        std::cout << "成功将图书信息保存到文件！" << std::endl;
    } else {
        std::cout << "将图书信息保存到文件失败！" << std::endl;
    }
    pause();
}

void AdminMenu::addBook()
{
    std::cout << "\n=== 添加图书 ===" << std::endl;
    std::string isbn = readLine("请输入ISBN: ");
    std::string title = readLine("请输入书名: ");
    std::string author = readLine("请输入作者: ");
    std::string publisher = readLine("请输入出版社: ");
    int year = readInt("请输入出版年份: ");
    std::string category = readLine("请输入分类: ");
    std::string remarks = readLine("请输入备注: ");

    if (isbn.empty()) {
        std::cout << "ISBN 不能为空！" << std::endl;
        pause();
        return;
    }
    if (title.empty()) {
        std::cout << "书名不能为空！" << std::endl;
        pause();
        return;
    }

    Book book(isbn, title, author, publisher, year, category, remarks);

    if (BookService::getInstance().addBook(book)) {
        BookService::getInstance().writeBooksToFile();
        std::cout << "图书添加成功！" << std::endl;
    } else {
        std::cout << "该 ISBN 已存在，添加失败！" << std::endl;
    }
    pause();
}

void AdminMenu::deleteBook()
{
    std::cout << "\n=== 删除图书 ===" << std::endl;
    std::string isbn = readLine("请输入要删除的ISBN: ");
    if (isbn.empty()) {
        std::cout << "ISBN 不能为空！" << std::endl;
        pause();
        return;
    }
    if (BookService::getInstance().removeBook(isbn)) {
        BookService::getInstance().writeBooksToFile();
        std::cout << "图书删除成功！" << std::endl;
    } else {
        std::cout << "该 ISBN 不存在，删除失败！" << std::endl;
    }
    pause();
}