/********************************************************************************
** Form generated from reading UI file 'login2.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN2_H
#define UI_LOGIN2_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_login2
{
public:
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer_6;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QSpacerItem *verticalSpacer;
    QLabel *label_2;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_2;
    QComboBox *comboBox;
    QSpacerItem *verticalSpacer_3;
    QLineEdit *lineEdit_user;
    QSpacerItem *verticalSpacer_4;
    QLineEdit *lineEdit_passward;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *verticalSpacer_7;

    void setupUi(QDialog *login2)
    {
        if (login2->objectName().isEmpty())
            login2->setObjectName(QStringLiteral("login2"));
        login2->resize(445, 406);
        QIcon icon;
        icon.addFile(QStringLiteral(":/res/1.png"), QSize(), QIcon::Normal, QIcon::Off);
        login2->setWindowIcon(icon);
        login2->setStyleSheet(QStringLiteral("QDialog{background-image: url(:/res/back5.jpg);}"));
        verticalLayout_3 = new QVBoxLayout(login2);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_6);

        widget_3 = new QWidget(login2);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        horizontalLayout = new QHBoxLayout(widget_3);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_3 = new QSpacerItem(80, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        widget = new QWidget(widget_3);
        widget->setObjectName(QStringLiteral("widget"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(label);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(label_2);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(label_3);


        horizontalLayout->addWidget(widget);

        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        widget_2 = new QWidget(widget_3);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        verticalLayout_2 = new QVBoxLayout(widget_2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        comboBox = new QComboBox(widget_2);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy1);
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font.setPointSize(10);
        font.setBold(false);
        font.setWeight(50);
        comboBox->setFont(font);
        comboBox->setLayoutDirection(Qt::LeftToRight);
        comboBox->setEditable(false);
        comboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        verticalLayout_2->addWidget(comboBox);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_3);

        lineEdit_user = new QLineEdit(widget_2);
        lineEdit_user->setObjectName(QStringLiteral("lineEdit_user"));
        lineEdit_user->setFont(font);
        lineEdit_user->setLayoutDirection(Qt::LeftToRight);
        lineEdit_user->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(lineEdit_user);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_4);

        lineEdit_passward = new QLineEdit(widget_2);
        lineEdit_passward->setObjectName(QStringLiteral("lineEdit_passward"));
        sizePolicy.setHeightForWidth(lineEdit_passward->sizePolicy().hasHeightForWidth());
        lineEdit_passward->setSizePolicy(sizePolicy);
        lineEdit_passward->setFont(font);
        lineEdit_passward->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(lineEdit_passward);


        horizontalLayout->addWidget(widget_2);

        horizontalSpacer_4 = new QSpacerItem(80, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        verticalLayout_3->addWidget(widget_3);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_3->addItem(verticalSpacer_5);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_5 = new QSpacerItem(90, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);

        pushButton = new QPushButton(login2);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        pushButton->setFont(font1);
        pushButton->setStyleSheet(QLatin1String("background-color: rgb(255, 154, 252);\n"
"background-color: rgb(109, 192, 232);"));

        horizontalLayout_2->addWidget(pushButton);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_6);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 2);
        horizontalLayout_2->setStretch(2, 1);

        verticalLayout_3->addLayout(horizontalLayout_2);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_7);


        retranslateUi(login2);

        QMetaObject::connectSlotsByName(login2);
    } // setupUi

    void retranslateUi(QDialog *login2)
    {
        login2->setWindowTitle(QApplication::translate("login2", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("login2", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:700; color:#ffffff;\">\347\231\273\345\275\225\346\235\203\351\231\220\357\274\232</span></p></body></html>", Q_NULLPTR));
        label_2->setText(QApplication::translate("login2", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:700; color:#ffffff;\">\347\231\273\345\275\225\350\264\246\345\217\267\357\274\232</span></p></body></html>", Q_NULLPTR));
        label_3->setText(QApplication::translate("login2", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:700; color:#ffffff;\">\347\231\273\345\275\225\345\257\206\347\240\201\357\274\232</span></p></body></html>", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("login2", "\346\223\215\344\275\234\345\221\230", Q_NULLPTR)
         << QApplication::translate("login2", "\347\256\241\347\220\206\345\221\230", Q_NULLPTR)
        );
        lineEdit_user->setText(QApplication::translate("login2", "20000001", Q_NULLPTR));
        lineEdit_passward->setText(QApplication::translate("login2", "1111", Q_NULLPTR));
        pushButton->setText(QApplication::translate("login2", "\347\231\273\345\275\225", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class login2: public Ui_login2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN2_H
