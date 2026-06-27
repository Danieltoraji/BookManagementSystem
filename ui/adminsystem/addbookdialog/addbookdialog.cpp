#include "addbookdialog.h"
#include "ui_addbookdialog.h"

#include <QMessageBox>
#include <QString>
#include "services/bookservice.h"
#include "model/book.h"

AddBookDialog::AddBookDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddBookDialog)
{
    ui->setupUi(this);
}

AddBookDialog::~AddBookDialog()
{
    delete ui;
}

void AddBookDialog::on_buttonBox_accepted()
{

    QString isbn = ui->isbnline->text().trimmed();
    QString title = ui->nameline->text().trimmed();
    QString author = ui->authorline->text().trimmed();
    QString publisher = ui->publisherline->text().trimmed();
    QString yearStr = ui->yearline->text().trimmed();
    QString category = ui->categoryline->text().trimmed();
    QString remarks = ui->remarksarea->toPlainText().trimmed();

    // 校验
    if (isbn.isEmpty()) {
        QMessageBox::warning(this, tr("输入错误"), tr("ISBN 不能为空！"));
        return;
    }
    if (title.isEmpty()) {
        QMessageBox::warning(this, tr("输入错误"), tr("书名不能为空！"));
        return;
    }

    bool ok = false;
    int year = yearStr.isEmpty() ? 0 : yearStr.toInt(&ok);
    if (!ok && !yearStr.isEmpty()) {
        QMessageBox::warning(this, tr("输入错误"), tr("出版年份必须为数字！"));
        return;
    }

    Book book(isbn.toStdString(),title.toStdString(),author.toStdString(),
        publisher.toStdString(),year,category.toStdString(),remarks.toStdString());

    // 调用服务层添加图书
    if (BookService::getInstance().addBook(book)) {
        BookService::getInstance().writeBooksToFile();
        QMessageBox::information(this, tr("成功"), tr("图书添加成功！"));
    } else {
        QMessageBox::warning(this, tr("失败"), tr("该 ISBN 已存在，添加失败！"));
    }
}
