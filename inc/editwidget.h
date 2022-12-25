#ifndef EDITWIDGET_H
#define EDITWIDGET_H

#include <QWidget>

namespace Ui {
class editWidget;
}

class editWidget : public QWidget
{
    Q_OBJECT

public:
    explicit editWidget(QWidget *parent = nullptr);
    ~editWidget();
void paintEvent(QPaintEvent *event);

private:
    Ui::editWidget *ui;
};

#endif // EDITWIDGET_H
