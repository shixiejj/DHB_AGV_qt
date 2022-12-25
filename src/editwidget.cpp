#include "editwidget.h"
#include "ui_editwidget.h"
#include <QPainter>

editWidget::editWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::editWidget)
{
    ui->setupUi(this);
    this->setWindowTitle("任务配置");
}

//窗口显示背景图片要用paintEvent将样式表绘制到窗口中
void editWidget::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

editWidget::~editWidget()
{
    delete ui;
}
