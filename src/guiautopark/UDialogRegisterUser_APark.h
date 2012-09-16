//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл декларації класу вікна реєстрації користувача
//
// Створений програмістами Компанії "Утех" 29.03.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#ifndef UDIALOGREGISTERUSER_APark_H
#define UDIALOGREGISTERUSER_APark_H

#include <QDialog>
#include <QSettings>
#include <QDir>
#include <QSqlQuery>

#include "UAutoParkMeneger_APark.h"
#include "UDifFunc_APark.h"
#include "ui_UDialogRegisterUser_APark.h"
//--------------------utech--------------------utech--------------------utech--------------------
class UDialogRegisterUser : public QDialog
{
  Q_OBJECT

  public:
	UDialogRegisterUser(QWidget *parent = 0);
	~UDialogRegisterUser();
	static int registeredUserId();
	static int registeredUserGroupId();
	static int registeredUserAccessPower();
	static int registeredUserProgram();
	static bool userHasAccessToWidget(int widgetId);
	static QString registeredUserName();
	bool tryRegister();
	void saveCurUserState();
		
  public slots:
	void populateUsers();
	void pushButton_enter_clicked();
	void pushButton_changePassword_clicked();
	void pushButton_close_clicked();
  signals:
		
  private:
	Ui::UDialogRegisterUser ui;
		
	static int __registeredUserId;
	static int __registeredUserGroupId;
	static int __registeredUserAccessPower;
	static int __registeredUserProgram;
};
//--------------------utech--------------------utech--------------------utech--------------------
#endif
