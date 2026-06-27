#include "usersystem.h"
#include "ui_usersystem.h"

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

void UserSystem::on_pushButton_clicked()
{

}

