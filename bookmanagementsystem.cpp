#include "bookmanagementsystem.h"
#include "ui_bookmanagementsystem.h"

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
