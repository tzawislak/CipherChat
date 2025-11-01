#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <fstream>
#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <vector>
#include <QDebug>
#include <QMessageBox>
#include "../head/tcpconnector.h"
#include "../head/setpassworddialog.h"
#include "../head/checkpassworddialog.h"
#include "../head/newcontactdialog.h"
#include "../head/cryptography.h"
#include "../head/contact.h"
#include "ui_mainwindow.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int ReadKey();
    int ReadContacts();



private slots:
    void on_sendBTN_clicked();
    void onListKONT_clicked(QListWidgetItem* _item);
    void on_BTNdodajKontakt_clicked();

    void on_actionPoka_m_j_ID_triggered();

    void on_pushButton_clicked();

public slots:
    void ReceiveMasterKey(const std::string &_mk);
    void ReceiveNewContactInfo(std::string _name, std::string _id);
    void ReceiveNewMsg();

private:
    Ui::MainWindow *ui;
    std::map<QString, unsigned> contactIDs;
    std::vector<Contact*> contacts;
    // cryptography
    CryptoPP::DH dh;
    std::string master_key;
    CryptoPP::Integer privDH;
    CryptoPP::Integer pubDH;
    CryptoPP::Integer sharedDH;
    std::string my_id;
    // tcp
    std::unique_ptr<TCPConnector> socket;
};

#endif // MAINWINDOW_H
