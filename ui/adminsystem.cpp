#include "adminsystem.h"
#include "ui_adminsystem.h"
#include "services/bookservice.h"
#include <QMessageBox>
#include <QStandardItemModel>


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

void AdminSystem::on_pushButton_clicked()
{
}

void AdminSystem::on_readFromFileButton_clicked()
{
    if (BookService::getInstance().readBooksFromFile()) {
        QMessageBox::information(this, "Success", "成功从文件读取书籍信息！");
        refreshBookTable(BookService::getInstance().getAllBooks());
    } else {
        QMessageBox::warning(this, "Error", "从文件读取书籍信息失败！");
    }
}

void AdminSystem::on_save_clicked()
{
    convertTableBackToBooks();
    if (BookService::getInstance().writeBooksToFile()) {
        QMessageBox::information(this, "Success", "成功从文件读取书籍信息！");
        refreshBookTable(BookService::getInstance().getAllBooks());
    } else {
        QMessageBox::warning(this, "Error", "从文件读取书籍信息失败！");
    }
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

void AdminSystem::convertTableBackToBooks()
{
    auto *model = qobject_cast<QStandardItemModel *>(ui->booklist->model());
    if (!model) {
        QMessageBox::warning(this, "Error", "表格模型无效！");
        return;
    }

    std::vector<Book> books;
    for (int row = 0; row < model->rowCount(); ++row) {
        Book b;
        b.setISBN(model->item(row, 0)->text().toStdString());
        b.setTitle(model->item(row, 1)->text().toStdString());
        b.setAuthor(model->item(row, 2)->text().toStdString());
        b.setPublisher(model->item(row, 3)->text().toStdString());
        b.setPublishingYear(model->item(row, 4)->text().toInt());
        b.setCategory(model->item(row, 5)->text().toStdString());

        QString copiesStr = model->item(row, 6)->text();
        std::list<std::string> copies;
        for (const auto &copy : copiesStr.split(',')) {
            copies.push_back(copy.trimmed().toStdString());
        }
        b.setCopies(copies);

        b.setRemarks(model->item(row, 7)->text().toStdString());

        books.push_back(b);
    }

    // 更新BookService中的数据
    BookService::getInstance().books = books;
}

