#ifndef BOOKMANAGEMENTSYSTEM_H
#define BOOKMANAGEMENTSYSTEM_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class BookManagementSystem;
}
QT_END_NAMESPACE

class UserSystem;

class UserSystem;

class BookManagementSystem : public QMainWindow
{
    Q_OBJECT

public:
    explicit BookManagementSystem(QWidget *parent = nullptr);
    ~BookManagementSystem() override;

private slots:
    void on_pushButton_2_clicked();


    void on_pushButton_clicked();

private:
    Ui::BookManagementSystem *ui;
    UserSystem *m_userSystem = nullptr;

};
#endif // BOOKMANAGEMENTSYSTEM_H
