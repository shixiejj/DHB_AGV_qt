/********************************************************************************
** Form generated from reading UI file 'editdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITDIALOG_H
#define UI_EDITDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_editDialog
{
public:
    QGroupBox *groupBox_51;
    QLabel *title;
    QLineEdit *showOffer;
    QPushButton *editCancel;
    QPushButton *editSave;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_327;
    QComboBox *editPriority;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_378;
    QComboBox *comboBox_209;
    QWidget *layoutWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_379;
    QComboBox *comboBox_210;
    QWidget *layoutWidget_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_377;
    QComboBox *comboBox_207;
    QComboBox *comboBox_208;
    QWidget *layoutWidget_5;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_380;
    QComboBox *comboBox_211;
    QComboBox *comboBox_212;

    void setupUi(QDialog *editDialog)
    {
        if (editDialog->objectName().isEmpty())
            editDialog->setObjectName(QStringLiteral("editDialog"));
        editDialog->resize(756, 478);
        editDialog->setStyleSheet(QStringLiteral("#editDialog{background-image: url(:/res/backtee.jpg);}"));
        groupBox_51 = new QGroupBox(editDialog);
        groupBox_51->setObjectName(QStringLiteral("groupBox_51"));
        groupBox_51->setGeometry(QRect(-10, 0, 771, 481));
        groupBox_51->setStyleSheet(QStringLiteral("color:transparent;"));
        title = new QLabel(groupBox_51);
        title->setObjectName(QStringLiteral("title"));
        title->setGeometry(QRect(320, 40, 101, 41));
        showOffer = new QLineEdit(groupBox_51);
        showOffer->setObjectName(QStringLiteral("showOffer"));
        showOffer->setGeometry(QRect(280, 90, 181, 31));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        showOffer->setFont(font);
        showOffer->setStyleSheet(QStringLiteral("color: rgb(0, 0, 0);"));
        editCancel = new QPushButton(groupBox_51);
        editCancel->setObjectName(QStringLiteral("editCancel"));
        editCancel->setGeometry(QRect(250, 360, 97, 29));
        editCancel->setStyleSheet(QLatin1String("background-color: rgb(56, 56, 56);\n"
"color: rgb(200, 200, 200);"));
        editSave = new QPushButton(groupBox_51);
        editSave->setObjectName(QStringLiteral("editSave"));
        editSave->setGeometry(QRect(390, 360, 97, 29));
        editSave->setStyleSheet(QLatin1String("background-color: rgb(56, 56, 56);\n"
"color: rgb(200, 200, 200);"));
        layoutWidget = new QWidget(groupBox_51);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(70, 160, 271, 22));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(30);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_327 = new QLabel(layoutWidget);
        label_327->setObjectName(QStringLiteral("label_327"));

        horizontalLayout->addWidget(label_327);

        editPriority = new QComboBox(layoutWidget);
        editPriority->setObjectName(QStringLiteral("editPriority"));
        editPriority->setStyleSheet(QLatin1String("background-color: rgb(55, 111, 167);\n"
"color: rgb(255, 255, 255);"));
        editPriority->setEditable(true);

        horizontalLayout->addWidget(editPriority);

        horizontalLayout->setStretch(0, 2);
        horizontalLayout->setStretch(1, 5);
        layoutWidget_2 = new QWidget(groupBox_51);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(70, 210, 271, 22));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget_2);
        horizontalLayout_2->setSpacing(30);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_378 = new QLabel(layoutWidget_2);
        label_378->setObjectName(QStringLiteral("label_378"));

        horizontalLayout_2->addWidget(label_378);

        comboBox_209 = new QComboBox(layoutWidget_2);
        comboBox_209->setObjectName(QStringLiteral("comboBox_209"));
        comboBox_209->setStyleSheet(QLatin1String("background-color: rgb(55, 111, 167);\n"
"color: rgb(255, 255, 255);"));
        comboBox_209->setEditable(true);

        horizontalLayout_2->addWidget(comboBox_209);

        horizontalLayout_2->setStretch(0, 2);
        horizontalLayout_2->setStretch(1, 5);
        layoutWidget_3 = new QWidget(groupBox_51);
        layoutWidget_3->setObjectName(QStringLiteral("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(70, 270, 271, 22));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget_3);
        horizontalLayout_3->setSpacing(30);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_379 = new QLabel(layoutWidget_3);
        label_379->setObjectName(QStringLiteral("label_379"));

        horizontalLayout_3->addWidget(label_379);

        comboBox_210 = new QComboBox(layoutWidget_3);
        comboBox_210->setObjectName(QStringLiteral("comboBox_210"));
        comboBox_210->setStyleSheet(QLatin1String("background-color: rgb(55, 111, 167);\n"
"color: rgb(255, 255, 255);"));
        comboBox_210->setEditable(true);

        horizontalLayout_3->addWidget(comboBox_210);

        horizontalLayout_3->setStretch(0, 2);
        horizontalLayout_3->setStretch(1, 5);
        layoutWidget_4 = new QWidget(groupBox_51);
        layoutWidget_4->setObjectName(QStringLiteral("layoutWidget_4"));
        layoutWidget_4->setGeometry(QRect(390, 210, 291, 22));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget_4);
        horizontalLayout_4->setSpacing(20);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_377 = new QLabel(layoutWidget_4);
        label_377->setObjectName(QStringLiteral("label_377"));

        horizontalLayout_4->addWidget(label_377);

        comboBox_207 = new QComboBox(layoutWidget_4);
        comboBox_207->setObjectName(QStringLiteral("comboBox_207"));
        comboBox_207->setStyleSheet(QLatin1String("background-color: rgb(55, 111, 167);\n"
"color: rgb(255, 255, 255);"));
        comboBox_207->setEditable(true);

        horizontalLayout_4->addWidget(comboBox_207);

        comboBox_208 = new QComboBox(layoutWidget_4);
        comboBox_208->setObjectName(QStringLiteral("comboBox_208"));
        comboBox_208->setStyleSheet(QLatin1String("background-color: rgb(55, 111, 167);\n"
"color: rgb(255, 255, 255);"));
        comboBox_208->setEditable(true);

        horizontalLayout_4->addWidget(comboBox_208);

        horizontalLayout_4->setStretch(0, 2);
        horizontalLayout_4->setStretch(1, 3);
        horizontalLayout_4->setStretch(2, 3);
        layoutWidget_5 = new QWidget(groupBox_51);
        layoutWidget_5->setObjectName(QStringLiteral("layoutWidget_5"));
        layoutWidget_5->setGeometry(QRect(390, 270, 291, 22));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget_5);
        horizontalLayout_5->setSpacing(20);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        label_380 = new QLabel(layoutWidget_5);
        label_380->setObjectName(QStringLiteral("label_380"));

        horizontalLayout_5->addWidget(label_380);

        comboBox_211 = new QComboBox(layoutWidget_5);
        comboBox_211->setObjectName(QStringLiteral("comboBox_211"));
        comboBox_211->setStyleSheet(QLatin1String("background-color: rgb(55, 111, 167);\n"
"color: rgb(255, 255, 255);"));
        comboBox_211->setEditable(true);

        horizontalLayout_5->addWidget(comboBox_211);

        comboBox_212 = new QComboBox(layoutWidget_5);
        comboBox_212->setObjectName(QStringLiteral("comboBox_212"));
        comboBox_212->setStyleSheet(QLatin1String("background-color: rgb(55, 111, 167);\n"
"color: rgb(255, 255, 255);"));
        comboBox_212->setEditable(true);

        horizontalLayout_5->addWidget(comboBox_212);

        horizontalLayout_5->setStretch(0, 2);
        horizontalLayout_5->setStretch(1, 3);
        horizontalLayout_5->setStretch(2, 3);

        retranslateUi(editDialog);
        QObject::connect(editSave, SIGNAL(clicked()), editDialog, SLOT(accept()));
        QObject::connect(editCancel, SIGNAL(clicked()), editDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(editDialog);
    } // setupUi

    void retranslateUi(QDialog *editDialog)
    {
        editDialog->setWindowTitle(QApplication::translate("editDialog", "Dialog", Q_NULLPTR));
        groupBox_51->setTitle(QString());
        title->setText(QApplication::translate("editDialog", "<html><head/><body><p><span style=\" font-size:18pt; font-weight:600; color:#ffffff;\">\344\273\273\345\212\241\351\205\215\347\275\256</span></p></body></html>", Q_NULLPTR));
        showOffer->setText(QApplication::translate("editDialog", "20221120-020103-0102", Q_NULLPTR));
        editCancel->setText(QApplication::translate("editDialog", "\345\217\226\346\266\210", Q_NULLPTR));
        editSave->setText(QApplication::translate("editDialog", "\347\241\256\345\256\232", Q_NULLPTR));
        label_327->setText(QApplication::translate("editDialog", "<html><head/><body><p><span style=\" font-size:12pt; color:#ffffff;\">\344\274\230\345\205\210\347\272\247</span></p></body></html>", Q_NULLPTR));
        editPriority->clear();
        editPriority->insertItems(0, QStringList()
         << QApplication::translate("editDialog", "\344\274\230\345\205\210", Q_NULLPTR)
         << QApplication::translate("editDialog", "\346\234\200\351\253\230", Q_NULLPTR)
         << QApplication::translate("editDialog", "\351\241\272\345\272\217", Q_NULLPTR)
        );
        label_378->setText(QApplication::translate("editDialog", "<html><head/><body><p><span style=\" font-size:12pt; color:#ffffff;\">\344\277\256\346\224\271\350\265\267\347\202\271</span></p></body></html>", Q_NULLPTR));
        comboBox_209->clear();
        comboBox_209->insertItems(0, QStringList()
         << QApplication::translate("editDialog", "\344\270\215\344\277\256\346\224\271", Q_NULLPTR)
         << QApplication::translate("editDialog", "\344\277\256\346\224\271", Q_NULLPTR)
        );
        label_379->setText(QApplication::translate("editDialog", "<html><head/><body><p><span style=\" font-size:12pt; color:#ffffff;\">\344\277\256\346\224\271\350\265\267\347\202\271</span></p></body></html>", Q_NULLPTR));
        comboBox_210->clear();
        comboBox_210->insertItems(0, QStringList()
         << QApplication::translate("editDialog", "\344\270\215\344\277\256\346\224\271", Q_NULLPTR)
         << QApplication::translate("editDialog", "\344\277\256\346\224\271", Q_NULLPTR)
        );
        label_377->setText(QApplication::translate("editDialog", "<html><head/><body><p><span style=\" font-size:12pt; color:#ffffff;\">\346\226\260\350\256\276\350\265\267\347\202\271</span></p></body></html>", Q_NULLPTR));
        comboBox_207->clear();
        comboBox_207->insertItems(0, QStringList()
         << QApplication::translate("editDialog", "\344\274\230\345\205\210", Q_NULLPTR)
         << QApplication::translate("editDialog", "\344\270\215\344\274\230\345\205\210", Q_NULLPTR)
        );
        comboBox_208->clear();
        comboBox_208->insertItems(0, QStringList()
         << QApplication::translate("editDialog", "01", Q_NULLPTR)
         << QApplication::translate("editDialog", "02", Q_NULLPTR)
        );
        label_380->setText(QApplication::translate("editDialog", "<html><head/><body><p><span style=\" font-size:12pt; color:#ffffff;\">\346\226\260\350\256\276\347\273\210\347\202\271</span></p></body></html>", Q_NULLPTR));
        comboBox_211->clear();
        comboBox_211->insertItems(0, QStringList()
         << QApplication::translate("editDialog", "\344\274\230\345\205\210", Q_NULLPTR)
         << QApplication::translate("editDialog", "\344\270\215\344\274\230\345\205\210", Q_NULLPTR)
        );
        comboBox_212->clear();
        comboBox_212->insertItems(0, QStringList()
         << QApplication::translate("editDialog", "01", Q_NULLPTR)
         << QApplication::translate("editDialog", "02", Q_NULLPTR)
        );
    } // retranslateUi

};

namespace Ui {
    class editDialog: public Ui_editDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITDIALOG_H
