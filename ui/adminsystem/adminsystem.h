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

    void on_addbook_clicked();

private:
    void refreshBookTable(const auto &books);//用来显示的函数
    bool convertTableBackToBooks();//同步表格信息更新
    Ui::AdminSystem *ui;
};

#endif // ADMINSYSTEM_H
