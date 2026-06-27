#ifndef USERSYSTEM_H
#define USERSYSTEM_H

#include <QMainWindow>

namespace Ui {
class UserSystem;
}

class UserSystem : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserSystem(QWidget *parent = nullptr);
    ~UserSystem();

private slots:
    void on_pushButton_clicked();
    void on_getbooks_clicked();

private:
    void refreshBookTable(const auto &books);//用来显示搜索结果的函数
    Ui::UserSystem *ui;
};

#endif // USERSYSTEM_H
