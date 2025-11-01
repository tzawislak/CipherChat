#ifndef NEWCONTACTDIALOG_H
#define NEWCONTACTDIALOG_H

#include <QDialog>

namespace Ui {
class NewContactDialog;
}

class NewContactDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewContactDialog(QWidget *parent = 0);
    ~NewContactDialog();
signals:
    void sendNewContactInfo(std::string name, std::string id);

private slots:


    void on_add_clicked();

    void on_cancel_clicked();

private:
    Ui::NewContactDialog *ui;
};

#endif // NEWCONTACTDIALOG_H
