#ifndef CheckPasswordDialog_H
#define CheckPasswordDialog_H

#include <QDialog>
#include "../head/mainwindow.h"
#include "../head/generalvariables.h"


namespace Ui {
class CheckPasswordDialog;
}

class CheckPasswordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CheckPasswordDialog(std::string _hashed_phrase, QWidget *parent = 0);
    ~CheckPasswordDialog();
signals:
    void sendKey(const std::string &master_key);

public slots:
    void on_checkPSWDbutton_clicked();

private:
    Ui::CheckPasswordDialog *ui;
    std::string hashed_phrase;
};

#endif // CheckPasswordDialog_H
