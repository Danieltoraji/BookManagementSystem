#ifndef ADMINSYSTEM_H
#define ADMINSYSTEM_H

#include <QMainWindow>

namespace Ui {
class AdminSystem;
}

class AdminSystem : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminSystem(QWidget *parent = nullptr);
    ~AdminSystem();

private slots:
    void on_pushButton_clicked();

    void on_readFromFileButton_clicked();

    void on_save_clicked();

private:
    void refreshBookTable(const auto &books);
    void convertTableBackToBooks();
    Ui::AdminSystem *ui;
};

#endif // ADMINSYSTEM_H
