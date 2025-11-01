#ifndef SETPASSWORDDIALOG_H
#define SETPASSWORDDIALOG_H

#include <QDialog>
#include <QAbstractButton>
#include "../head/generalvariables.h"

namespace Ui {
class SetPasswordDialog;
}

class SetPasswordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetPasswordDialog(QWidget *parent = 0);
    ~SetPasswordDialog();

signals:
    void sendKey(const std::string &master_key);

private slots:
    void on_SetBTN_clicked();

    void on_ExitBTN_clicked();

private:
    Ui::SetPasswordDialog *ui;
    int isNewPasswdAcceptable(const QString &_p1, const QString &_p2);
};

#endif // SETPASSWORDDIALOG_H
