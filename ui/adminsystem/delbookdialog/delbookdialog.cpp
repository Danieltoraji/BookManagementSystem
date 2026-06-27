#include "delbookdialog.h"
#include "ui_delbookdialog.h"

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
