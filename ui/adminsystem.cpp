#include "adminsystem.h"
#include "ui_adminsystem.h"
#include "services/bookservice.h"
#include <QMessageBox>


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
    } else {
        QMessageBox::warning(this, "Error", "从文件读取书籍信息失败！");
    }
}

