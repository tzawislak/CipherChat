#include "../head/contact.h"
#include <QMessageBox>

/**
  Klasa tworząca nowy kontakt

  Klasa tworzy nowy kontakt, ustala secred shared key, który zna jedynie użytkownik i kontakt, który dodaje.
  W oknie konwersacji dodawany jest komunikat o nazwie kontaktu, jego id oraz współdzielonym kluczu,
  czego warto by jednak nie pokazywać

 * @brief Contact::Contact
 * @param _name  nazwa nowego kontaktu
 * @param _id    id nowego kontaktu
 * @param _privDH  prywatny klucz użytkownika
 * @param _dh       parametry protokołu Diffie-Hellmana
 */
Contact::Contact(QString _name, std::string _id, CryptoPP::Integer _privDH, CryptoPP::DH _dh)
{
    this->conv = new QListWidget();
    this->name = _name;
    // ustal wspolny klucz DH:
    CryptoPP::SecByteBlock SBBsharedDH( _dh.AgreedValueLength() );

    CryptoPP::SecByteBlock priv(_dh.PrivateKeyLength());
    _privDH.Encode(priv, _dh.PrivateKeyLength());

    CryptoPP::Integer pubRecv(_id.c_str());
    id = IntegerTostring(pubRecv).substr(0, 6).c_str();

    CryptoPP::SecByteBlock pub(_dh.PublicKeyLength());
    pubRecv.Encode(pub, _dh.PublicKeyLength());


    if(!_dh.Agree(SBBsharedDH, priv, pub))
        QMessageBox::warning(NULL, "Błąd DH", "Błąd podczas ustalania wspólnego klucza" );

    this->shared.Decode(SBBsharedDH.BytePtr(), SBBsharedDH.SizeInBytes());

    // zrzutuj shared na 256 bitowy klucz do AES, druga osoba będzie miała identyczny
    std::stringstream sshared;
    sshared << std::hex << shared;
    std::string aes_shared_str = sshared.str();
    aes_shared = CalcSHA256( aes_shared_str );
    std::cout << b32byteToString(aes_shared) << std::endl;
    // klucz ustalony
    QString text2 = name;
    QListWidgetItem* powitanie = new QListWidgetItem( text2.append(" - nowa konwersacja"));
    powitanie->setTextColor(Qt::green);
    powitanie->setBackground(Qt::white);
    powitanie->setTextAlignment(Qt::AlignLeft);
    this->conv->addItem( powitanie );

    QListWidgetItem* idInfo = new QListWidgetItem( QString::fromStdString( id.c_str()) );
    idInfo->setTextColor(Qt::green);
    idInfo->setBackground(Qt::white);
    idInfo->setTextAlignment(Qt::AlignLeft);
    this->conv->addItem( idInfo );

    QListWidgetItem* kluczc = new QListWidgetItem( QString::fromStdString( b32byteToString( aes_shared ) ) );
    kluczc->setTextColor(Qt::green);
    kluczc->setBackground(Qt::white);
    kluczc->setTextAlignment(Qt::AlignLeft);
    this->conv->addItem( kluczc );

}
/**
  konstruktor kopiujący
 * @brief Contact::Contact
 * @param ct
 */
Contact::Contact(const Contact& ct){
    std::cout << "Copy constr\n";
    name = ct.name;
    shared = ct.shared;
    conv = ct.conv;
}
/**
   przeciążony operator przypisania
 * @brief Contact::operator =
 * @param ct
 * @return obiekt skopiowany
 */
Contact Contact::operator=(const Contact& ct){
    std::cout << "operator = \n";
    if( this != &ct){
        name = ct.name;
        shared = ct.shared;
        conv = ct.conv;
    }
    return *this;
}
/**
   dodaje wiadomość wysłaną przez użytkownika do listy wiadomości
 * @brief Contact::addSent
 * @param _data
 */
void Contact::addSent(QListWidgetItem *_data){
    this->conv->addItem( _data );
    this->conv->scrollToBottom();
}
/**
   dodaje wiadomość otrzymaną przez użytkownika do listy wiadomości
 * @brief Contact::addRecv
 * @param _data
 */
void Contact::addRecv(QListWidgetItem *_data){
    this->conv->addItem( _data );
    this->conv->scrollToBottom();
}
