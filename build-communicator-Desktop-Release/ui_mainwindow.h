/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExit;
    QWidget *centralWidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *sendBTN;
    QTextEdit *sendTXT;
    QListWidget *listCONV;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QListWidget *ListaKontaktow;
    QPushButton *BTNdodajKontakt;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(957, 500);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(900, 500));
        MainWindow->setMaximumSize(QSize(5000, 5000));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(9, 409, 941, 52));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        sendBTN = new QPushButton(horizontalLayoutWidget);
        sendBTN->setObjectName(QStringLiteral("sendBTN"));

        horizontalLayout->addWidget(sendBTN);

        sendTXT = new QTextEdit(horizontalLayoutWidget);
        sendTXT->setObjectName(QStringLiteral("sendTXT"));
        sendTXT->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(sendTXT->sizePolicy().hasHeightForWidth());
        sendTXT->setSizePolicy(sizePolicy1);
        sendTXT->setMaximumSize(QSize(16777215, 50));

        horizontalLayout->addWidget(sendTXT);

        listCONV = new QListWidget(centralWidget);
        listCONV->setObjectName(QStringLiteral("listCONV"));
        listCONV->setGeometry(QRect(270, 0, 671, 401));
        sizePolicy1.setHeightForWidth(listCONV->sizePolicy().hasHeightForWidth());
        listCONV->setSizePolicy(sizePolicy1);
        listCONV->setMinimumSize(QSize(400, 0));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(11, 1, 258, 401));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        ListaKontaktow = new QListWidget(widget);
        ListaKontaktow->setObjectName(QStringLiteral("ListaKontaktow"));

        verticalLayout_2->addWidget(ListaKontaktow);

        BTNdodajKontakt = new QPushButton(widget);
        BTNdodajKontakt->setObjectName(QStringLiteral("BTNdodajKontakt"));

        verticalLayout_2->addWidget(BTNdodajKontakt);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 957, 19));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Super tajny komunikator", 0));
        actionExit->setText(QApplication::translate("MainWindow", "dodaj kontakt", 0));
        sendBTN->setText(QApplication::translate("MainWindow", "Wy\305\233lij", 0));
        BTNdodajKontakt->setText(QApplication::translate("MainWindow", "Dodaj kontakt", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
