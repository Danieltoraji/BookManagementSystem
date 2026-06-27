#include "bookmanagementsystem.h"
#include "ui_bookmanagementsystem.h"
#include "ui/usersystem/usersystem.h"
#include "ui/adminsystem/adminsystem.h"

BookManagementSystem::BookManagementSystem(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BookManagementSystem)
{
    ui->setupUi(this);
}

BookManagementSystem::~BookManagementSystem()
{
    delete ui;
}

void BookManagementSystem::on_pushButton_2_clicked()
{
    static UserSystem *userSystem = nullptr;
    if (!userSystem) {
        userSystem = new UserSystem;
        userSystem->setAttribute(Qt::WA_DeleteOnClose, false);
    }
    userSystem->show();
    hide();
}


void BookManagementSystem::on_pushButton_clicked()
{
    static AdminSystem *adminSystem = nullptr;
    if (!adminSystem) {
        adminSystem = new AdminSystem;
        adminSystem->setAttribute(Qt::WA_DeleteOnClose, false);
    }
    adminSystem->show();
    hide();
}

