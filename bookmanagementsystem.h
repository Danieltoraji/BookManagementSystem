#ifndef BOOKMANAGEMENTSYSTEM_H
#define BOOKMANAGEMENTSYSTEM_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class BookManagementSystem;
}
QT_END_NAMESPACE

class BookManagementSystem : public QMainWindow
{
    Q_OBJECT

public:
    explicit BookManagementSystem(QWidget *parent = nullptr);
    ~BookManagementSystem() override;

private:
    Ui::BookManagementSystem *ui;
};
#endif // BOOKMANAGEMENTSYSTEM_H
