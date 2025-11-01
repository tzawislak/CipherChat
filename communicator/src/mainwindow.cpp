#include "../head/mainwindow.h"
#include <functional>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    //      Unlock messenger
    if ( this->ReadKey() < 0 ) std::exit(1);

    //      Create DH priv-pub key pair
    CryptoPP::Integer p("0xB10B8F96A080E01DDE92DE5EAE5D54EC52C99FBCFB06A3C6"
    "9A6A9DCA52D23B616073E28675A23D189838EF1E2EE652C0"
    "13ECB4AEA906112324975C3CD49B83BFACCBDD7D90C4BD70"
    "98488E9C219A73724EFFD6FAE5644738FAA31A4FF55BCCC0"
    "A151AF5F0DC8B4BD45BF37DF365C1A65E68CFDA76D4DA708"
    "DF1FB2BC2E4A4371");

    CryptoPP::Integer g("0xA4D1CBD5C3FD34126765A442EFB99905F8104DD258AC507F"
      "D6406CFF14266D31266FEA1E5C41564B777E690F5504F213"
      "160217B4B01B886A5E91547F9E2749F4D7FBD7D3B9A92EE1"
      "909D0D2263F80A76A6A24C087A091F531DBF0A0169B6A28A"
      "D662A4D18E73AFA32D779D5918D08BC8858F4DCEF97C2A24"
      "855E6EEB22B3B2E5");

    CryptoPP::Integer q("0xF518AA8781A8DF278ABA4E7D64B7CB9D49462353");

    CryptoPP::AutoSeededRandomPool rnd;


    dh.AccessGroupParameters().Initialize(p, q, g);
    if(!dh.GetGroupParameters().ValidateGroup(rnd, 3))
        std::cerr << "Błąd ustalania parametrów DH" ;

    CryptoPP::SecByteBlock SBBprivDH( dh.PrivateKeyLength() );
    CryptoPP::SecByteBlock SBBpubDH( dh.PublicKeyLength() );

    dh.GenerateKeyPair(rnd, SBBprivDH, SBBpubDH);

    this->pubDH.Decode(SBBpubDH.BytePtr(), SBBpubDH.SizeInBytes());
    this->privDH.Decode(SBBprivDH.BytePtr(), SBBprivDH.SizeInBytes());



    //      TCP connection
    std::cout << " Master Key: "<< master_key << std::endl;
    std::cout << " ID:         "<<IntegerTostring(pubDH).substr(0, 6).c_str()<<std::endl;
    my_id = IntegerTostring(pubDH).substr(0, 6).c_str();
    try{
        socket = std::make_unique<TCPConnector>();
        // podaj swój identyfikator (pierwsze 6 znaków klucza publicznego DH)
        socket->Write( IntegerTostring(pubDH).substr(0, 6) );


    }catch(TCPException &tcpe){
        QMessageBox::warning(this, "Błąd połączenia", tcpe.opis );
    }



    ui->setupUi(this);
    connect(ui->ListaKontaktow, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onListKONT_clicked(QListWidgetItem*)) );

}

MainWindow::~MainWindow()
{
    delete ui;
}



/**
 * Prosi o podanie hasła lub ustawia hasło gdy nie jest ustawione (plik ../.txt/password.txt nie istnieje)
 * @brief MainWindow::ReadKey
 * @return kod poprawnosci
 */
int MainWindow::ReadKey()
{
    std::ifstream passwordFile("../communicator/.txt/password.txt");
    if( !passwordFile.good() ){
        // Ustaw hasło i wygeneruj klucz jeśli nie istnieje
        SetPasswordDialog spd(this);
        spd.setModal(true);
        int spd_result = spd.exec();

        if(spd_result == QDialog::Accepted) {  }
        if(spd_result == QDialog::Rejected) {
            std::cerr << "Nie ustawiono hasła. " << std::endl;
            return -1;
        }
    }else{
        // wczytaj klucz
        std::string hashed_phrase;
        passwordFile >> hashed_phrase;
        passwordFile.close();
        // obsłuż odblokowanie komunikatora
        CheckPasswordDialog cpd( hashed_phrase, this );
        cpd.setModal(true);
        int cpd_result = cpd.exec();


        if(cpd_result == QDialog::Accepted) {  }
        if(cpd_result == QDialog::Rejected) {
            std::cerr << "Nie podano poprawnego hasła. " << std::endl;
            return -2;
        }
    }

    return 0;
}



void MainWindow::on_sendBTN_clicked()
{
    // poaz na gui
    QListWidgetItem* sent = new QListWidgetItem(ui->sendTXT->toPlainText());
    sent->setTextColor(Qt::blue);
    sent->setBackground(Qt::white);
    sent->setTextAlignment(Qt::AlignRight);

    QListWidgetItem* sent2 = new QListWidgetItem( *sent);
    ui->listCONV->addItem(sent2);
    ui->listCONV->scrollToBottom();
    // dodaj tez do pamieci kontktu
    auto currentConvName = ui->ListaKontaktow->currentItem()->text();
    auto id_number = contactIDs.find( currentConvName )->second;

    contacts[id_number]->addSent( sent );

    // wyślij do servera
    // ale najpierw zaszyfruj
    std::string wiad = ui->sendTXT->toPlainText().toUtf8().constData();
    byte iv[ CryptoPP::AES::BLOCKSIZE ];
    memset( iv, 0x00, CryptoPP::AES::BLOCKSIZE );
    std::string ciphertext = b32AESEncrypted( contacts[id_number]->aes_shared, iv, wiad );
    std::cout << std::endl << "szyfr: "<< ciphertext << std::endl << std::endl;



    std::string odszyfrowana = b32AESDecrypted( contacts[id_number]->aes_shared, iv, ciphertext);
    std::cout << std::endl << "odszy: "<< odszyfrowana << std::endl << std::endl;

    try{
        std::string msg = contacts[ id_number ]->id;
        msg.append(my_id);
        msg.append(ciphertext);
        std::cout << "Cipher text : " << ciphertext<< std::endl;
        // uwaga! jesli string ma wiecej niz 32 bajty, to koncowka zostanie pominieta! Szyfrowanie odbywa sie na danych do 32 bajtow!
        socket->Write( msg );
    }catch(TCPException &tcpe){
        QMessageBox::warning(this, "Błąd połączenia", tcpe.opis );
    }catch(...){
        std::cerr << "Other error while sending text... " << std::endl;
    }
//5cc5e00f919faf56f92af28d0d051e50792356137e131fc9b62a4e3acff490f150d542057a174c6903a75dff7244e3cfac9d7b71aae60dc273db2ece1aa89c7af73913799f6bc93e3464db8afa75cfe3e8f47c3b80624918f3eb83a6be4598783e818bfbcf1a804163398d8237485511f37fa39c778463b4846c7f204efbc281h


}


void MainWindow::on_BTNdodajKontakt_clicked()
{
    NewContactDialog ncd(this);
    ncd.setModal(true);
    ncd.exec();
}


/*
 *
 *
 *  slots
 *
 *
 */

void MainWindow::ReceiveMasterKey(const std::string &_mk){
    master_key = _mk;
}

void MainWindow::ReceiveNewContactInfo(std::__cxx11::string _name, std::__cxx11::string _id){
    std::cout << "Nowy kontakt: " << _name << " " << _id << std::endl;
    QListWidgetItem* nc = new QListWidgetItem( QString::fromUtf8(_name.c_str()));
    nc->setTextColor(Qt::green);
    nc->setBackground(Qt::black);
    nc->setTextAlignment(Qt::AlignLeft);
    this->contactIDs[ QString::fromUtf8(_name.c_str()) ] = contacts.size();

    this->contacts.push_back( new Contact( QString::fromUtf8(_name.c_str()), _id, this->privDH, this->dh ) );

    ui->ListaKontaktow->addItem(nc);


}

void MainWindow::ReceiveNewMsg(){
    std::string wiadomosci = socket->Read(my_id);
    std::cout << wiadomosci << std::endl;

    size_t position = wiadomosci.find("\t");
    size_t last_pos = 0;
    while( position != std::string::npos){
        // wiad składa się z identyfikatora i właściwej informacji. Oddziel ID i informację
        std::string wiad = wiadomosci.substr(last_pos, position-last_pos );
        std::string ID = wiad.substr(0, 6);
        std::string msg = wiad.substr(6);
        std::cout << ":" << ID << '=' << msg << std::endl;
        last_pos = position+1;
        position = wiadomosci.find("\t", position+1);


        QListWidgetItem* recv = new QListWidgetItem(QString::fromStdString(msg));
        recv->setTextColor(Qt::red);
        recv->setBackground(Qt::white);
        recv->setTextAlignment(Qt::AlignLeft);


        contacts[ contactIDs[QString::fromStdString(ID)] ]->addRecv( recv );
        if( ui->ListaKontaktow->currentItem()->text().toUtf8().constData() == ID ){
            QListWidgetItem* recv2 = new QListWidgetItem( *recv);
            ui->listCONV->addItem(recv2);
            ui->listCONV->scrollToBottom();
        }


    }
}





void MainWindow::on_actionPoka_m_j_ID_triggered()
{
    std::stringstream ss;
    ss << std::hex << this->pubDH;
    std::string pubKey = ss.str();
    QMessageBox::about( this, "Moje ID" , QString::fromUtf8(pubKey.c_str()) );

}

/** Gdy naciśnięto kontakt
 * @brief MainWindow::onListKONT_clicked
 * @param _item
 */
void MainWindow::onListKONT_clicked(QListWidgetItem* _item){
    ui->listCONV->clear();
    // znajdz Contact o nazwie _item->text()
    Contact* c = contacts[ contactIDs[_item->text()] ];
    std::cout << " Kontakt: " << c->name.toUtf8().constData() << std::endl;
    for( int i=0; i < c->conv->count(); i++ ){
        std::cout << i << "   "  << c->conv->item(i)->text().toUtf8().constData() << std::endl;
        QListWidgetItem* nc = new QListWidgetItem (*c->conv->item(i));
        ui->listCONV->addItem( nc );
        ui->listCONV->scrollToBottom();
    }
}





/**
   Gdy naciśnięty, odpytuję serwer o dane
 * @brief MainWindow::on_pushButton_clicked
 */
void MainWindow::on_pushButton_clicked()
{
    std::string wiadomosci = socket->Read(my_id);
    std::cout << wiadomosci << std::endl;

    size_t position = wiadomosci.find("\t");
    size_t last_pos = 0;
    while( position != std::string::npos){
        // wiad składa się z identyfikatora i właściwej informacji. Oddziel ID i informację
        std::string wiad = wiadomosci.substr(last_pos, position-last_pos );
        std::string ID = wiad.substr(0, 6);
        std::string msg = wiad.substr(6);
        std::cout << ":" << ID << '=' << msg << std::endl;
        last_pos = position+1;
        position = wiadomosci.find("\t", position+1);

        // poszukaj kontaktu o tym ID
        const byte* key;
        QString name = "haha";
        for(auto &it : contacts ){
            std::cout << "." << it->id << std::endl;
            if( it->id == ID ){
                key = it->aes_shared;
                name = it->name;
            }
        }
        std::cout << "Żyję!" << std::endl;
        std::cout <<  name.toUtf8().constData()  << std::endl;

        std::cout <<  b32byteToString(key)  << std::endl;


        // Odszyfruj
        byte iv[ CryptoPP::AES::BLOCKSIZE ];
        memset( iv, 0x00, CryptoPP::AES::BLOCKSIZE );

        std::string odszyfrowana = b32AESDecrypted( key, iv, msg);
        std::cout << "Żyję!!" << std::endl;

        QListWidgetItem* recv = new QListWidgetItem(QString::fromStdString(odszyfrowana));
        recv->setTextColor(Qt::red);
        recv->setBackground(Qt::white);
        recv->setTextAlignment(Qt::AlignLeft);
        std::cout << "Żyję!!!" << std::endl;


        contacts[ contactIDs[name] ]->addRecv( recv );
        std::cout << "LK: " << ui->ListaKontaktow->currentItem()->text().toUtf8().constData() << "\nID: " << name.toUtf8().constData() << std::endl;
        if( ui->ListaKontaktow->currentItem()->text().toUtf8().constData() == name ){
            QListWidgetItem* recv2 = new QListWidgetItem( *recv);
            ui->listCONV->addItem(recv2);
            ui->listCONV->scrollToBottom();
        }
    }
}
