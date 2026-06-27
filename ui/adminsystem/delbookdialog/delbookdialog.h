#ifndef DELBOOKDIALOG_H
#define DELBOOKDIALOG_H

#include <QDialog>

namespace Ui {
class DelBookDialog;
}

class DelBookDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DelBookDialog(QWidget *parent = nullptr);
    ~DelBookDialog();

private:
    Ui::DelBookDialog *ui;
};

#endif // DELBOOKDIALOG_H
