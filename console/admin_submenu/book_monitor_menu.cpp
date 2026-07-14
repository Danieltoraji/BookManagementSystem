#include "book_monitor_menu.h"
#include "services/bookservice.h"
#include <iostream>
#include <iomanip>
#include <sstream>

void BookMonitorMenu::show()
{
    std::vector<std::string> options = {
        "搜索图书",
        "显示所有图书",
        "按ISBN查询图书",
        "添加图书",
        "修改图书",
        "删除图书",
        "从文件读取图书",
        "保存图书到文件",
        "返回上级菜单"
    };

    while (true) {
        int choice = displayMenu("图书监控", options);
        switch (choice) {
            case 1: searchBooks(); break;
            case 2: displayAllBooks(); break;
            case 3: searchByISBN(); break;
            case 4: addBook(); break;
            case 5: updateBook(); break;
            case 6: deleteBook(); break;
            case 7: readFromFile(); break;
            case 8: saveToFile(); break;
            case 9: return;
            default: std::cout << "无效的选择，请重新输入。" << std::endl; break;
        }
    }
}

void BookMonitorMenu::buildSearchQuery(searchQuery &query)
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

void BookMonitorMenu::printBooks(const std::vector<Book> &books)
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

void BookMonitorMenu::searchBooks()
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

void BookMonitorMenu::displayAllBooks()
{
    std::cout << "\n=== 所有图书 ===" << std::endl;
    printBooks(BookService::getInstance().getAllBooks());
    pause();
}

void BookMonitorMenu::searchByISBN()
{
    std::cout << "\n=== 按ISBN查询图书 ===" << std::endl;
    std::string isbn = readLine("请输入ISBN: ");
    Book book = BookService::getInstance().getBookByISBN(isbn);
    if (book.getISBN().empty()) {
        std::cout << "未找到该ISBN的图书。" << std::endl;
    } else {
        printBooks({book});
    }
    pause();
}

void BookMonitorMenu::addBook()
{
    std::cout << "\n=== 添加图书 ===" << std::endl;
    std::string isbn = readLine("请输入ISBN: ");
    std::string title = readLine("请输入书名: ");
    std::string author = readLine("请输入作者(可选): ");
    std::string publisher = readLine("请输入出版社(可选): ");
    int year = readInt("请输入出版年份(可选): ");
    std::string category = readLine("请输入分类(可选): ");
    std::string remarks = readLine("请输入备注(可选): ");

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

void BookMonitorMenu::updateBook()
{
    std::cout << "\n=== 修改图书 ===" << std::endl;
    std::string isbn = readLine("请输入要修改的图书的ISBN: ");
    if (isbn.empty()) {
        std::cout << "ISBN 不能为空！" << std::endl;
        pause();
        return;
    }
    Book existingBook = BookService::getInstance().getBookByISBN(isbn);
    if (existingBook.getISBN().empty()) {
        std::cout << "该 ISBN 不存在，修改失败！" << std::endl;
        pause();
        return;
    }
    std::string title = readLine("请输入新的书名（留空代表不修改）: ");
    title = title.empty() ? existingBook.getTitle() : title;
    std::string author = readLine("请输入新的作者（留空代表不修改）: ");
    author = author.empty() ? existingBook.getAuthor() : author;
    std::string publisher = readLine("请输入新的出版社（留空代表不修改）: ");
    publisher = publisher.empty() ? existingBook.getPublisher() : publisher;
    int year = readInt("请输入新的出版年份（留空代表不修改）: ");
    year = (year == 0) ? existingBook.getPublishingYear() : year;
    std::string category = readLine("请输入新的分类（留空代表不修改）: ");
    category = category.empty() ? existingBook.getCategory() : category;
    std::string remarks = readLine("请输入新的备注（留空代表不修改）: ");
    remarks = remarks.empty() ? existingBook.getRemarks() : remarks;

    Book book(isbn, title, author, publisher, year, category, remarks);
    if (BookService::getInstance().updateBook(isbn, book)) {
        BookService::getInstance().writeBooksToFile();
        std::cout << "图书修改成功！" << std::endl;
    } else {
        std::cout << "该 ISBN 不存在，修改失败！" << std::endl;
    }
    pause();
}

void BookMonitorMenu::deleteBook()
{
    std::cout << "\n=== 删除图书 ===" << std::endl;
    std::string isbn = readLine("请输入要删除的ISBN: ");
    if (isbn.empty()) {
        std::cout << "ISBN 不能为空！" << std::endl;
        pause();
        return;
    }
    Book existingBook = BookService::getInstance().getBookByISBN(isbn);
    std::cout << "您确定要删除图书: " << existingBook.getTitle() << " (ISBN: " << isbn << ") 吗？这将会注销所有的副本。" << std::endl;
    std::string confirmation = readLine("输入 'yes' 确认删除");
    if (confirmation != "yes") {
        std::cout << "删除操作已取消。" << std::endl;
        pause();
        return;
    }
    if (BookService::getInstance().removeBook(isbn)) {
        std::cout << "图书删除成功！" << std::endl;
        std::cout << "该图书的所有副本已注销，相关借阅记录已标记为已归还。" << std::endl;
    } else {
        std::cout << "该 ISBN 不存在，删除失败！" << std::endl;
    }
    pause();
}

void BookMonitorMenu::readFromFile()
{
    std::cout << "\n=== 从文件读取图书 ===" << std::endl;
    if (BookService::getInstance().readBooksFromFile()) {
        std::cout << "成功从文件读取图书信息！" << std::endl;
    } else {
        std::cout << "从文件读取图书信息失败！请检查文件是否为空。" << std::endl;
    }
    pause();
}

void BookMonitorMenu::saveToFile()
{
    std::cout << "\n=== 保存图书到文件 ===" << std::endl;
    if (BookService::getInstance().writeBooksToFile()) {
        std::cout << "成功将图书信息保存到文件！" << std::endl;
    } else {
        std::cout << "将图书信息保存到文件失败！" << std::endl;
    }
    pause();
}
