#include "../head/checkpassworddialog.h"
#include "../head/cryptography.h"
#include "ui_checkpassworddialog.h"

CheckPasswordDialog::CheckPasswordDialog(std::__cxx11::string _hashed_phrase, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CheckPasswordDialog),
    hashed_phrase(_hashed_phrase)
{
    ui->setupUi(this);
    ui->passwordTXT->setTabChangesFocus(true);

    connect(this, SIGNAL(sendKey(std::string)), parent, SLOT(ReceiveMasterKey(const std::string)) );

}

CheckPasswordDialog::~CheckPasswordDialog()
{
    delete ui;
}



void CheckPasswordDialog::on_checkPSWDbutton_clicked()
{
    // pobierz hasło od użytkownika
    std::string typed_in = ui->passwordTXT->toPlainText().toUtf8().constData();
    auto key =  CalcSHA256 ( typed_in) ;

    //
    //std::cout << b32byteToString( key ) << std::endl;

    // szyfruje CRYPT_PHRASE kluczem key
    // iv nie został jeszcze zaimplementowany, dlatego jest zerem;
    byte iv[ CryptoPP::AES::BLOCKSIZE ];
    memset( iv, 0x00, CryptoPP::AES::BLOCKSIZE );

    auto AES_ciphertext = b32AESEncrypted( key, iv, CRYPT_PHRASE );



    if( hashed_phrase == AES_ciphertext ) {
        emit sendKey( b32byteToString(key) ); // przeslij poprawny klucz do klasy MainWindow
        this->accept();
    }else{
        ui->labelMSG->setText("Niepoprawne hasło");
    }
}
