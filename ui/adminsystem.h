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

private:
    Ui::AdminSystem *ui;
};

#endif // ADMINSYSTEM_H
