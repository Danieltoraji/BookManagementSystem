#include "adminsystem.h"
#include "ui_adminsystem.h"
#include "services/bookservice.h"
#include "addbookdialog/addbookdialog.h"
#include "delbookdialog/delbookdialog.h"
#include <QMessageBox>
#include <QStandardItemModel>
#include <algorithm>


AdminSystem::AdminSystem(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AdminSystem)
{
    ui->setupUi(this);
}

AdminSystem::~AdminSystem()
{
    delete ui;
}

//辅助函数

void AdminSystem::refreshBookTable(const auto &books)
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

    ui->booklist->setModel(model);
    ui->booklist->horizontalHeader()->setStretchLastSection(true);
}

bool AdminSystem::convertTableBackToBooks()
{
    auto *model = qobject_cast<QStandardItemModel *>(ui->booklist->model());
    if (!model) {
        QMessageBox::warning(this, "Error", "表格模型无效！");
        return false;
    }

    // 按ISBN合并更新：仅更新表格中有的书。
    auto &allBooks = BookService::getInstance().books;

    for (int row = 0; row < model->rowCount(); ++row) {
        std::string isbn = model->item(row, 0)->text().toStdString();

        // 在主存中按ISBN查找对应图书
        auto it = std::find_if(allBooks.begin(), allBooks.end(),
            [&](const Book &b) { return b.getISBN() == isbn; });

        if (it != allBooks.end()) {
            it->setTitle(model->item(row, 1)->text().toStdString());
            it->setAuthor(model->item(row, 2)->text().toStdString());
            it->setPublisher(model->item(row, 3)->text().toStdString());
            it->setPublishingYear(model->item(row, 4)->text().toInt());
            it->setCategory(model->item(row, 5)->text().toStdString());

            QString copiesStr = model->item(row, 6)->text();
            std::list<std::string> copies;
            for (const auto &copy : copiesStr.split(',')) {
                copies.push_back(copy.trimmed().toStdString());
            }
            it->setCopies(copies);

            it->setRemarks(model->item(row, 7)->text().toStdString());
        }
    }
    return true;
}

//槽函数

void AdminSystem::on_pushButton_clicked()
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

void AdminSystem::on_readFromFileButton_clicked()
{
    if (BookService::getInstance().readBooksFromFile()) {
        QMessageBox::information(this, "Success", "成功从文件读取书籍信息！");
        refreshBookTable(BookService::getInstance().getAllBooks());
    } else {
        QMessageBox::warning(this, "Error", "从文件读取书籍信息失败！检查是否为空");
    }
}

void AdminSystem::on_save_clicked()
{
    if (!convertTableBackToBooks()) {
        QMessageBox::warning(this, "Error", "转换表格数据到书籍对象失败！");
        return;
    }
    if (BookService::getInstance().writeBooksToFile()) {
        QMessageBox::information(this, "Success", "成功将书籍信息保存到文件！");
        refreshBookTable(BookService::getInstance().getAllBooks());
    } else {
        QMessageBox::warning(this, "Error", "将书籍信息保存到文件失败！");
    }
}

void AdminSystem::on_addbook_clicked()
{
    AddBookDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        refreshBookTable(BookService::getInstance().getAllBooks());
    }
}

void AdminSystem::on_delbook_clicked()
{
    DelBookDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        refreshBookTable(BookService::getInstance().getAllBooks());
    }
}

