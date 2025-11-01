/********************************************************************************
** Form generated from reading UI file 'checkpassworddialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHECKPASSWORDDIALOG_H
#define UI_CHECKPASSWORDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_CheckPasswordDialog
{
public:
    QPushButton *checkPSWDbutton;
    QPlainTextEdit *passwordTXT;
    QLabel *labelMSG;

    void setupUi(QDialog *CheckPasswordDialog)
    {
        if (CheckPasswordDialog->objectName().isEmpty())
            CheckPasswordDialog->setObjectName(QStringLiteral("CheckPasswordDialog"));
        CheckPasswordDialog->resize(459, 120);
        checkPSWDbutton = new QPushButton(CheckPasswordDialog);
        checkPSWDbutton->setObjectName(QStringLiteral("checkPSWDbutton"));
        checkPSWDbutton->setGeometry(QRect(330, 80, 111, 22));
        passwordTXT = new QPlainTextEdit(CheckPasswordDialog);
        passwordTXT->setObjectName(QStringLiteral("passwordTXT"));
        passwordTXT->setGeometry(QRect(20, 40, 421, 31));
        passwordTXT->setAutoFillBackground(false);
        passwordTXT->setInputMethodHints(Qt::ImhNone);
        labelMSG = new QLabel(CheckPasswordDialog);
        labelMSG->setObjectName(QStringLiteral("labelMSG"));
        labelMSG->setGeometry(QRect(20, 10, 411, 16));
        QFont font;
        font.setStyleStrategy(QFont::PreferAntialias);
        labelMSG->setFont(font);
        labelMSG->setInputMethodHints(Qt::ImhHiddenText|Qt::ImhSensitiveData);

        retranslateUi(CheckPasswordDialog);

        QMetaObject::connectSlotsByName(CheckPasswordDialog);
    } // setupUi

    void retranslateUi(QDialog *CheckPasswordDialog)
    {
        CheckPasswordDialog->setWindowTitle(QApplication::translate("CheckPasswordDialog", "Podaj has\305\202o", 0));
        checkPSWDbutton->setText(QApplication::translate("CheckPasswordDialog", "Dalej", 0));
        passwordTXT->setPlainText(QString());
        labelMSG->setText(QApplication::translate("CheckPasswordDialog", "Podaj has\305\202o:", 0));
    } // retranslateUi

};

namespace Ui {
    class CheckPasswordDialog: public Ui_CheckPasswordDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHECKPASSWORDDIALOG_H
