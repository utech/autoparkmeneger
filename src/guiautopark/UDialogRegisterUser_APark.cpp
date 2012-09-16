//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл виконання класу вікна налаштування програми
//
// Створений програмістами Компанії "Утех" 29.03.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------
#include "UDialogRegisterUser_APark.h"
#include "UDialogChangePassword_APark.h"

#include <USqlAccessible>
#include <QtDebug>

int UDialogRegisterUser::__registeredUserId=0;
int UDialogRegisterUser::__registeredUserGroupId=0;
int UDialogRegisterUser::__registeredUserAccessPower=0;
int UDialogRegisterUser::__registeredUserProgram=0;

//--------------------utech--------------------utech--------------------utech--------------------
UDialogRegisterUser::UDialogRegisterUser(QWidget *parent)
        : QDialog(parent)
{
	ui.setupUi(this);
	ui.label_versionInfo->setText("\"Автопарк менеджер\" в."+QString(UAutoPark::version()));
	
	setMinimumSize(size());
	setMaximumSize(size());
	
	UAutoParkPrograms *apPr = new UAutoParkPrograms();
	for (int iter=0; iter<apPr->ProgramsList.size(); iter++)
		ui.listWidget_subprogs->addItem(apPr->ProgramsList[iter]);
	ui.listWidget_subprogs->setCurrentRow(readSetting("Register_Dialog", "Default_Program").toInt());
	delete apPr;
	
	populateUsers();
	
	ui.lineEdit_password->setFocus( Qt::MouseFocusReason );
	
	connect(ui.pushButton_enter, SIGNAL(clicked()), this, SLOT(pushButton_enter_clicked()));
	connect(ui.pushButton_changePassword, SIGNAL(clicked()), this, SLOT(pushButton_changePassword_clicked()));
	connect(ui.pushButton_close, SIGNAL(clicked()), this, SLOT(pushButton_close_clicked()));
}
//--------------------utech--------------------utech--------------------utech--------------------
void UDialogRegisterUser::populateUsers()
{
	QSqlQuery query;
	int defaultUserId = readSetting("Register_Dialog", "Default_User_Id").toInt();
	query.exec("SELECT Id, Imya, Pobatk, Prizv FROM users WHERE Active=true ORDER BY Login, id");
	ui.listWidget_users->clear();
	QListWidgetItem * lwItem;
	while (query.next()){
		lwItem = new QListWidgetItem(query.value(1).toString()+" "+query.value(2).toString()+" "+query.value(3).toString());
		lwItem->setData(Qt::UserRole, query.value(0).toInt());
		
		ui.listWidget_users->addItem(lwItem);
		if (defaultUserId == query.value(0).toInt()){
			lwItem->setSelected(true);
			ui.listWidget_users->setCurrentItem(lwItem);
		}
	}
}
//--------------------utech--------------------utech--------------------utech--------------------
void UDialogRegisterUser::pushButton_enter_clicked()
{
	if (tryRegister()){
		saveCurUserState();
		accept();
	}
}
//--------------------utech--------------------utech--------------------utech--------------------
void UDialogRegisterUser::pushButton_changePassword_clicked()
{
	if (tryRegister()){
		UDialogChangePassword * dChPswrd = new UDialogChangePassword(__registeredUserId);
		dChPswrd->exec();
		delete dChPswrd;
		saveCurUserState();
		accept();
	}
}
//--------------------utech--------------------utech--------------------utech--------------------
void UDialogRegisterUser::pushButton_close_clicked()
{
	reject();
}
//--------------------utech--------------------utech--------------------utech--------------------
int UDialogRegisterUser::registeredUserId()
{
	return __registeredUserId;
}
//--------------------utech--------------------utech--------------------utech--------------------
int UDialogRegisterUser::registeredUserGroupId()
{
	return __registeredUserGroupId;
}
//--------------------utech--------------------utech--------------------utech--------------------
int UDialogRegisterUser::registeredUserAccessPower()
{
	return __registeredUserAccessPower;
}
//--------------------utech--------------------utech--------------------utech--------------------
int UDialogRegisterUser::registeredUserProgram()
{
	return __registeredUserProgram;
}
//--------------------utech--------------------utech--------------------utech--------------------
bool UDialogRegisterUser::userHasAccessToWidget(int widgetId)
{
	QSqlQuery query;
	query.exec("SELECT PerevezAccessDif FROM users WHERE id="+QString::number(registeredUserId()));
	if (!query.next())
		return false;
	QString s = query.value(0).toString().trimmed().simplified().remove(' ');
	if (s.contains(QRegExp("^\\*"))){
		if (!s.contains(QRegExp("^\\*\\^")))
			return true;
		else{
			if (!s.contains(QRegExp("\\b"+QString::number(widgetId)+"\\b"))){
				return true;
			}
			return false;
		}
		return false;
	}
	//без знаку усі віджети (*)
	if (s.contains(QRegExp("\\b"+QString::number(widgetId)+"\\b")))
		return true;
	return false;
}
//--------------------utech--------------------utech--------------------utech--------------------
QString UDialogRegisterUser::registeredUserName()
{
	QSqlQuery query;
	query.exec("SELECT Login FROM users WHERE id="+QString::number(__registeredUserId));
	if (query.next())
		return query.value(0).toString();
	return "";
}
//--------------------utech--------------------utech--------------------utech--------------------
bool UDialogRegisterUser::tryRegister()
{
	QSqlQuery query;
	short userId = ui.listWidget_users->currentItem()->data(Qt::UserRole).toInt();
	short subProg = ui.listWidget_subprogs->currentRow() + 1;
	query.exec("SELECT PerevezAccess, ZarplataAccess, SkladAccess FROM users \
				WHERE active=true and Id="+sqlStr(userId)+" and PassWord=md5('"+ui.lineEdit_password->text()+"')");
	if (query.seek(0)){
		short access = query.value(subProg - 1).toInt();
		if (access == UAutoPark::AccessDenyed){
			QMessageBox::critical(0, "Доступ заборонено", "Вибачте, але Вам заборонено доступ до цього розділу.\nОберіть підпрограму, з якою ви уповноважені працювати і зареєструйтесь.");
			writeUserLog(userId, subProg, UAutoPark::ProgramAccessDenyed);
			ui.lineEdit_password->clear();
			return false;
		}
		query.exec("SELECT Group_id FROM users WHERE Id="+sqlStr(userId));
		query.seek(0);
		__registeredUserId = userId;
		__registeredUserGroupId = query.value(0).toInt();
		__registeredUserAccessPower = access;
		__registeredUserProgram = subProg;
		writeUserLog(userId, subProg, UAutoPark::LoginSuccessful);
		return true;
	}
	else{
		QMessageBox::critical(0, "Помилка реєстрації", "Ви внесли невірний пароль, або Ваш акаунт було заблоковано.\nСпробуйте ще раз уважно внести реєстраційні дані.");
		ui.lineEdit_password->clear();
		writeUserLog(userId, subProg, UAutoPark::WrongPassword);
		return false;
	}
}
//--------------------utech--------------------utech--------------------utech--------------------
void UDialogRegisterUser::saveCurUserState()
{
	writeSetting(ui.listWidget_users->currentItem()->data(Qt::UserRole).toInt(), "Register_Dialog", "Default_User_Id");
	writeSetting(ui.listWidget_subprogs->currentRow(),"Register_Dialog", "Default_Program");
}
//--------------------utech--------------------utech--------------------utech--------------------
UDialogRegisterUser::~UDialogRegisterUser()
{
	
}
//--------------------utech--------------------utech--------------------utech--------------------
