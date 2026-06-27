#include "delbookdialog.h"
#include "ui_delbookdialog.h"
#include "services/bookservice.h"
#include <QMessageBox>
#include <QString>

DelBookDialog::DelBookDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DelBookDialog)
{
    ui->setupUi(this);
}

DelBookDialog::~DelBookDialog()
{
    delete ui;
}

void DelBookDialog::on_buttonBox_accepted()
{
    QString isbn = ui->isbnline->text().trimmed();
    if (isbn.isEmpty()) {
        QMessageBox::warning(this, tr("输入错误"), tr("ISBN 不能为空！"));
        return;
    }
    if(BookService::getInstance().removeBook(isbn.toStdString())){
        BookService::getInstance().writeBooksToFile();
        QMessageBox::information(this, tr("成功"), tr("图书删除成功！"));
    } else {
        QMessageBox::warning(this, tr("失败"), tr("该 ISBN 不存在，删除失败！"));
    }
}

