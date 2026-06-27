#ifndef ADDBOOKDIALOG_H
#define ADDBOOKDIALOG_H

#include <QDialog>

namespace Ui {
class AddBookDialog;
}

class AddBookDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddBookDialog(QWidget *parent = nullptr);
    ~AddBookDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddBookDialog *ui;
};

#endif // ADDBOOKDIALOG_H
