/********************************************************************************
** Form generated from reading UI file 'newcontactdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWCONTACTDIALOG_H
#define UI_NEWCONTACTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NewContactDialog
{
public:
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QTextEdit *nameTXT;
    QLabel *label_name;
    QLabel *label_ip;
    QTextEdit *ipTXT;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *add;
    QPushButton *cancel;

    void setupUi(QDialog *NewContactDialog)
    {
        if (NewContactDialog->objectName().isEmpty())
            NewContactDialog->setObjectName(QStringLiteral("NewContactDialog"));
        NewContactDialog->resize(510, 109);
        formLayoutWidget = new QWidget(NewContactDialog);
        formLayoutWidget->setObjectName(QStringLiteral("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(9, 9, 491, 61));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        nameTXT = new QTextEdit(formLayoutWidget);
        nameTXT->setObjectName(QStringLiteral("nameTXT"));
        nameTXT->setLayoutDirection(Qt::LeftToRight);
        nameTXT->setAutoFillBackground(false);

        formLayout->setWidget(0, QFormLayout::FieldRole, nameTXT);

        label_name = new QLabel(formLayoutWidget);
        label_name->setObjectName(QStringLiteral("label_name"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_name);

        label_ip = new QLabel(formLayoutWidget);
        label_ip->setObjectName(QStringLiteral("label_ip"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_ip);

        ipTXT = new QTextEdit(formLayoutWidget);
        ipTXT->setObjectName(QStringLiteral("ipTXT"));
        ipTXT->setLayoutDirection(Qt::LeftToRight);

        formLayout->setWidget(1, QFormLayout::FieldRole, ipTXT);

        widget = new QWidget(NewContactDialog);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(330, 80, 168, 24));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        add = new QPushButton(widget);
        add->setObjectName(QStringLiteral("add"));

        horizontalLayout->addWidget(add);

        cancel = new QPushButton(widget);
        cancel->setObjectName(QStringLiteral("cancel"));

        horizontalLayout->addWidget(cancel);


        retranslateUi(NewContactDialog);

        QMetaObject::connectSlotsByName(NewContactDialog);
    } // setupUi

    void retranslateUi(QDialog *NewContactDialog)
    {
        NewContactDialog->setWindowTitle(QApplication::translate("NewContactDialog", "Dialog", 0));
        label_name->setText(QApplication::translate("NewContactDialog", "Nazwa", 0));
        label_ip->setText(QApplication::translate("NewContactDialog", "ip", 0));
        add->setText(QApplication::translate("NewContactDialog", "Dodaj", 0));
        cancel->setText(QApplication::translate("NewContactDialog", "Cofnij", 0));
    } // retranslateUi

};

namespace Ui {
    class NewContactDialog: public Ui_NewContactDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWCONTACTDIALOG_H
