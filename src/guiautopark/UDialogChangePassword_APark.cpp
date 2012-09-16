//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл виконання класу вікна налаштування програми
//
// Створений програмістами Компанії "Утех" 29.03.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#include "UDialogChangePassword_APark.h"

//--------------------utech--------------------utech--------------------utech--------------------
UDialogChangePassword::UDialogChangePassword(int user_id, QWidget *parent)
        : QDialog(parent)
{
    ui.setupUi(this);
	
	usId = user_id;
		//Connectors
	connect(ui.okButton_login, SIGNAL(clicked()), this, SLOT(okButton_login_clicked()));
}
//--------------------utech--------------------utech--------------------utech--------------------
bool UDialogChangePassword::new_password_is_valid()
{
	if (ui.lineEdit_new_password_1->text() == ui.lineEdit_new_password_2->text())
		return true;
	else
		return false;
}
//--------------------utech--------------------utech--------------------utech--------------------
QString UDialogChangePassword::newPassword()
{
	return ui.lineEdit_new_password_2->text();
}
//---------------------slots---------------------------------
void UDialogChangePassword::okButton_login_clicked()
{
	if ( new_password_is_valid() ){
		QSqlQuery query;
		bool doneOk = query.exec("UPDATE users SET password=md5('"+ui.lineEdit_new_password_2->text()+"') WHERE id="+QVariant(usId).toString());
		if (doneOk)
			accept();
		else
			QMessageBox::critical(
                this,
                "!!! Помилка зміни пароля !!!",
                "Система не змогла змінити Ваш пароль.\nСпробуйте ще раз.",
                QMessageBox::Ok);
	}
	else{
		QMessageBox::critical(
                this,
                "!!! Неспівпадіння паролів !!!",
                "Паролі не співпадають.\nСпробуйте ще раз.",
                QMessageBox::Ok);
		ui.lineEdit_new_password_1->clear();
		ui.lineEdit_new_password_2->clear();
	}
}
//--------------------utech--------------------utech--------------------utech--------------------
UDialogChangePassword::~UDialogChangePassword()
{

}
//--------------------utech--------------------utech--------------------utech--------------------
