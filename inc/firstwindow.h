#ifndef FIRSTWINDOW_H
#define FIRSTWINDOW_H
#include "login.h"
#include <QWidget>
#include "login2.h"
namespace Ui {
class FirstWindow;
}

class FirstWindow : public QWidget
{
    Q_OBJECT

public:
    explicit FirstWindow(QWidget *parent = 0);
    ~FirstWindow();
    Login  *login;
    login2 *log;

private slots:
    void on_pushButton_clicked();

private:
    Ui::FirstWindow *ui;
};

#endif // FIRSTWINDOW_H
