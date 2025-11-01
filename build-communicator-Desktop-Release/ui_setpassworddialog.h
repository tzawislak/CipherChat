/********************************************************************************
** Form generated from reading UI file 'setpassworddialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETPASSWORDDIALOG_H
#define UI_SETPASSWORDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SetPasswordDialog
{
public:
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QLabel *label_2;
    QPlainTextEdit *noweHaslo;
    QPlainTextEdit *noweHaslo2;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *SetBTN;
    QPushButton *ExitBTN;

    void setupUi(QDialog *SetPasswordDialog)
    {
        if (SetPasswordDialog->objectName().isEmpty())
            SetPasswordDialog->setObjectName(QStringLiteral("SetPasswordDialog"));
        SetPasswordDialog->resize(480, 143);
        formLayoutWidget = new QWidget(SetPasswordDialog);
        formLayoutWidget->setObjectName(QStringLiteral("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(20, 10, 441, 61));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(formLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        label_2 = new QLabel(formLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        noweHaslo = new QPlainTextEdit(formLayoutWidget);
        noweHaslo->setObjectName(QStringLiteral("noweHaslo"));
        noweHaslo->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(noweHaslo->sizePolicy().hasHeightForWidth());
        noweHaslo->setSizePolicy(sizePolicy);
        noweHaslo->setMaximumSize(QSize(400, 25));

        formLayout->setWidget(0, QFormLayout::FieldRole, noweHaslo);

        noweHaslo2 = new QPlainTextEdit(formLayoutWidget);
        noweHaslo2->setObjectName(QStringLiteral("noweHaslo2"));
        noweHaslo2->setEnabled(true);
        sizePolicy.setHeightForWidth(noweHaslo2->sizePolicy().hasHeightForWidth());
        noweHaslo2->setSizePolicy(sizePolicy);
        noweHaslo2->setMaximumSize(QSize(400, 25));

        formLayout->setWidget(1, QFormLayout::FieldRole, noweHaslo2);

        horizontalLayoutWidget = new QWidget(SetPasswordDialog);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(250, 80, 201, 51));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        SetBTN = new QPushButton(horizontalLayoutWidget);
        SetBTN->setObjectName(QStringLiteral("SetBTN"));

        horizontalLayout->addWidget(SetBTN);

        ExitBTN = new QPushButton(horizontalLayoutWidget);
        ExitBTN->setObjectName(QStringLiteral("ExitBTN"));

        horizontalLayout->addWidget(ExitBTN);


        retranslateUi(SetPasswordDialog);

        QMetaObject::connectSlotsByName(SetPasswordDialog);
    } // setupUi

    void retranslateUi(QDialog *SetPasswordDialog)
    {
        SetPasswordDialog->setWindowTitle(QApplication::translate("SetPasswordDialog", "Set Password", 0));
        label->setText(QApplication::translate("SetPasswordDialog", "Nowe has\305\202o", 0));
        label_2->setText(QApplication::translate("SetPasswordDialog", "Powt\303\263rz", 0));
        SetBTN->setText(QApplication::translate("SetPasswordDialog", "Dalej", 0));
        ExitBTN->setText(QApplication::translate("SetPasswordDialog", "Koniec", 0));
    } // retranslateUi

};

namespace Ui {
    class SetPasswordDialog: public Ui_SetPasswordDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETPASSWORDDIALOG_H
