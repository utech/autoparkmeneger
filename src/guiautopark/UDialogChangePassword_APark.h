//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл декларації класу вікна реєстрації користувача
//
// Створений програмістами Компанії "Утех" 29.03.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#ifndef UDIALOGCHANGEPASSWORD_APark_H
#define UDIALOGCHANGEPASSWORD_APark_H

#include <QDialog>
#include <QtDebug>
#include <QSqlQuery>
#include <QMessageBox>

#include "ui_UDialogChangePassword_APark.h"

//--------------------utech--------------------utech--------------------utech--------------------
class UDialogChangePassword : public QDialog
{
        Q_OBJECT

    public:
        UDialogChangePassword(int user_id, QWidget *parent = 0);
		
		bool new_password_is_valid();
		QString newPassword();
		
		~UDialogChangePassword();
    public slots:
		void okButton_login_clicked();

    private:
		Ui::UDialogChangePassword ui;
		int usId;

};
//--------------------utech--------------------utech--------------------utech--------------------
#endif
