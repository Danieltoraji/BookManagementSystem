#include "search_info_menu.h"


void SearchInfoMenu::show()
{
    std::vector<std::string> options = {
        "显示所有图书",
        "搜索馆藏图书",
        "搜索图书副本",
        "查看本馆书架",
        "返回上级菜单"
    };

    while (true) {
        int choice = displayMenu("搜索图书", options);
        switch (choice) {
            case 1: displayAllBooks(); break;
            case 2: searchBooks(); break;
            case 3: searchCopies(); break;
            case 4: viewShelves(); break;
            case 5: return; // 返回上级菜单
            default: std::cout << "无效的选择，请重新输入。" << std::endl;break;
        }
    }
}

//功能函数
void SearchInfoMenu::displayAllBooks(){
    std::cout << "\n=== 显示所有图书 ===" << std::endl;
    auto books = BookService::getInstance().getAllBooks();
    printBooks(books);
}

void SearchInfoMenu::searchBooks()
{
    std::cout << "\n=== 搜索图书 ===" << std::endl;
    searchQuery query;
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

void SearchInfoMenu::searchCopies()
{
    std::cout << "\n=== 搜索图书副本 ===" << std::endl;
    std::string isbn = readLine("请输入图书ISBN: ");
    auto copies = bookCopyService::getInstance().getBookCopiesByISBN(isbn);
    if (copies.empty()) {
        std::cout << "没有找到该ISBN的图书副本。" << std::endl;
    } else {
        std::cout << "找到 " << copies.size() << " 个副本：" << std::endl;
        for (const auto &copy : copies) {
            std::cout << "副本编号: " << copy.getLibCode() 
                      << ", 位置: " << copy.getBookLocation() 
                      << ", 状态: " << copy.getStatus() 
                      << std::endl;
        }
    }
    pause();
}

void SearchInfoMenu::viewShelves()
{
    std::cout << "\n=== 查看本馆书架 ===" << std::endl;
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
}

//辅助函数
void SearchInfoMenu::buildSearchQuery(searchQuery &query)
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

void SearchInfoMenu::printBooks(const std::vector<Book> &books)
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

void SearchInfoMenu::printBookCopies(const std::vector<BookCopy> &bookCopies)
{
    if (bookCopies.empty()) {
        std::cout << "没有找到图书副本。" << std::endl;
        return;
    }

    printSeparator('=');
    std::cout << std::left
              << std::setw(18) << "ISBN"
              << std::setw(12) << "副本编号"
              << std::setw(20) << "位置"
              << "状态" << std::endl;
    printSeparator('-');

    for (const auto &copy : bookCopies) {
        std::cout << std::left
                  << std::setw(18) << copy.getISBN()
                  << std::setw(12) << copy.getLibCode()
                  << std::setw(20) << copy.getBookLocation()
                  << copy.getStatus() << std::endl;
    }
    printSeparator('=');
    std::cout << "共 " << bookCopies.size() << " 个副本。" << std::endl;
}