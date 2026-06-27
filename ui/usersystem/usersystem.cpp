#include "usersystem.h"
#include "ui_usersystem.h"
#include "services/bookservice.h"
#include <QStandardItemModel>
#include <QMessageBox>

UserSystem::UserSystem(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UserSystem)
{
    ui->setupUi(this);
}

UserSystem::~UserSystem()
{
    delete ui;
}

//辅助函数

void UserSystem::refreshBookTable(const auto &books)
{
    auto *model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels({"ISBN", "标题", "作者", "出版社", "出版年份", "分类", "副本列表", "备注"});

    for (size_t row = 0; row < books.size(); ++row) {
        const auto &b = books[row];
        auto copies = b.getCopies();
        QString copiesStr;
        for (auto it = copies.begin(); it != copies.end(); ++it) {
            if (it != copies.begin())
                copiesStr += ", ";
            copiesStr += QString::fromStdString(*it);
        }

        model->setItem(row, 0, new QStandardItem(QString::fromStdString(b.getISBN())));
        model->setItem(row, 1, new QStandardItem(QString::fromStdString(b.getTitle())));
        model->setItem(row, 2, new QStandardItem(QString::fromStdString(b.getAuthor())));
        model->setItem(row, 3, new QStandardItem(QString::fromStdString(b.getPublisher())));
        model->setItem(row, 4, new QStandardItem(QString::number(b.getPublishingYear())));
        model->setItem(row, 5, new QStandardItem(QString::fromStdString(b.getCategory())));
        model->setItem(row, 6, new QStandardItem(copiesStr));
        model->setItem(row, 7, new QStandardItem(QString::fromStdString(b.getRemarks())));
    }

    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
}

//槽函数

void UserSystem::on_pushButton_clicked()
{
    searchQuery query;

    // 字段1
    switch (ui->f1->currentIndex()) {
        case 1:  query.field1 = searchQuery::Field::ISBN;   break;
        case 2:  query.field1 = searchQuery::Field::Title;  break;
        case 3:  query.field1 = searchQuery::Field::Author; break;
        default: query.field1 = searchQuery::Field::Empty;  break;
    }

    // 条件1
    switch (ui->c1->currentIndex()) {
        case 1:  query.condition1 = searchQuery::Condition::Contains;   break;
        case 2:  query.condition1 = searchQuery::Condition::StartsWith; break;
        default: query.condition1 = searchQuery::Condition::Equals;     break;
    }

    query.value1 = ui->value1->text().toStdString();

    // 逻辑
    query.logic = (ui->logic->currentIndex() == 1)
                      ? searchQuery::Logic::Or
                      : searchQuery::Logic::And;

    // 字段2
    switch (ui->f2->currentIndex()) {
        case 1:  query.field2 = searchQuery::Field::ISBN;   break;
        case 2:  query.field2 = searchQuery::Field::Title;  break;
        case 3:  query.field2 = searchQuery::Field::Author; break;
        default: query.field2 = searchQuery::Field::Empty;  break;
    }

    // 条件2
    switch (ui->c2->currentIndex()) {
        case 1:  query.condition2 = searchQuery::Condition::Contains;   break;
        case 2:  query.condition2 = searchQuery::Condition::StartsWith; break;
        default: query.condition2 = searchQuery::Condition::Equals;     break;
    }

    query.value2 = ui->value2->text().toStdString();

    auto results = BookService::getInstance().searchBooks(query);
    std::vector<Book> books;
    books.reserve(results.size());
    for (const Book *b : results) {
        if (b) books.push_back(*b);
    }
    refreshBookTable(books);
}


void UserSystem::on_getbooks_clicked()
{
    if(BookService::getInstance().readBooksFromFile()){
        QMessageBox::information(this, "Success", "图书数据已成功加载！");
        refreshBookTable(BookService::getInstance().getAllBooks());
    }
    else{
        QMessageBox::warning(this, "Error", "图书数据加载失败，请检查文件是否为空！");
    }
}

