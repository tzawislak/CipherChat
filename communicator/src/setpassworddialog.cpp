#include "../head/setpassworddialog.h"
#include "ui_setpassworddialog.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <unistd.h>
#include "../head/cryptography.h"




SetPasswordDialog::SetPasswordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetPasswordDialog)
{
    ui->setupUi(this);
    connect(this, SIGNAL(sendKey(std::string)), parent, SLOT(ReceiveMasterKey(const std::string)) );
}

SetPasswordDialog::~SetPasswordDialog()
{
    delete ui;
}

void SetPasswordDialog::on_SetBTN_clicked()
{
    auto np1 = ui->noweHaslo->toPlainText();
    auto np2 = ui->noweHaslo2->toPlainText();

    if( !isNewPasswdAcceptable(np1, np2) )
    {

        std::ofstream passwordFile("../communicator/.txt/password.txt");
        if( passwordFile.good() ){
            //
            auto key = CalcSHA256(np1.toUtf8().constData()); // nowy klucz
            //std::cout << b32byteToString( key ) << std::endl;

            // szyfruje CRYPT_PHRASE kluczem key
            // iv nie został jeszcze zaimplementowany, dlatego jest zerem;
            byte iv[ CryptoPP::AES::BLOCKSIZE ];
            memset( iv, 0x00, CryptoPP::AES::BLOCKSIZE );

            auto AES_ciphertext = b32AESEncrypted( key, iv, CRYPT_PHRASE );

            // zapisz zaszyfrowany CRYPT_PHRASE
            passwordFile  << AES_ciphertext;


            std::cout << "Password set" << std::endl;
            emit sendKey( b32byteToString(key));
            passwordFile.close();
        }
        else{
            std::cout << "Cannot save new key to communicator/.txt/password.txt" << std::endl;
            this->reject();
        }


        this->accept();
    }
}

void SetPasswordDialog::on_ExitBTN_clicked()
{
   exit(0);
}


int SetPasswordDialog::isNewPasswdAcceptable(const QString &_p1, const QString &_p2){
    if(_p1 != _p2)  return 1;
    if(_p1.length() < 8) return 2;
    /*

    kolejne warunki

    */
    return 0;
}
