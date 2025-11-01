#include "../head/newcontactdialog.h"
#include "ui_newcontactdialog.h"
#include <regex>
#include <fstream>


NewContactDialog::NewContactDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewContactDialog)
{
    ui->setupUi(this);
    connect(this, SIGNAL(sendNewContactInfo(std::string, std::string)), parent, SLOT(ReceiveNewContactInfo(std::string, std::string)) );
}

NewContactDialog::~NewContactDialog()
{
    delete ui;
}

/**
   Gdy zostanie podjęta próba dodania nowego kontaktu
 * @brief NewContactDialog::on_add_clicked
 */
void NewContactDialog::on_add_clicked()
{
    auto name = ui->nameTXT->toPlainText();
    auto ID = ui->ipTXT->toPlainText();

    if( name.length() < 1 ){
        ui->label_name->setStyleSheet("QLabel { color : red; }");
        return;
    }

    ui->label_name->setStyleSheet("QLabel { color : green; }");

    if( ID.length() < 1 ){
        ui->label_ip->setStyleSheet("QLabel { color : red; }");
        return;
    }

    ui->label_ip->setStyleSheet("QLabel { color : green; }");

    // Gdy dane są w poprawnym formacie:

    emit sendNewContactInfo(name.toUtf8().constData(), ID.toUtf8().constData());
    this->accept();
}


void NewContactDialog::on_cancel_clicked()
{
    this->reject();
}
