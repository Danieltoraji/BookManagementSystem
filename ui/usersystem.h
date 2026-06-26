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

private:
    Ui::UserSystem *ui;
};

#endif // USERSYSTEM_H
