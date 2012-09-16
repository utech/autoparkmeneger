//--------------------utech--------------------utech--------------------utech--------------------
//
// ���� ��������� ����� ���� ������������ ��������
//
// ��������� ������������ ������ "����" 29.03.2009�.
// � ���� ���������������� ���������� �������� QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#include "UDifFunc_APark.h"
#include <QDebug>

#include <QDateTime>
#include <USqlAccessible>

//--------------------utech--------------------utech--------------------utech--------------------
bool connectToDB()
{
	QSqlDatabase pdb = QSqlDatabase::addDatabase("QMYSQL");
	QDir::setCurrent(QCoreApplication::applicationDirPath());
	QSettings *settings = new QSettings("./autopark.ini", QSettings::IniFormat);
    pdb.setDatabaseName(settings->value("dataBase/Database").toString());
    pdb.setUserName(settings->value("dataBase/User").toString());
	pdb.setPassword(settings->value("dataBase/Password").toString());
    pdb.setHostName(settings->value("dataBase/Host").toString());
	pdb.setPort(settings->value("dataBase/Port").toInt());
	delete settings;
    if (!pdb.open()){
			QMessageBox::critical(0, "������� ��'������� �� ���� �����", 
								"������� �������, ����������� ���������:\n"
								+ pdb.lastError().text() 
								+ "\n\n�������� �� ������ ��'�������� �� ���� �����.\n\
								\n������ �������:\
								\n 1. ��������� ��������� ����'����.\
								\n 2. �� ����������� ����'���� �� ������� ������������� �������� �����.\
								\n 3. ������ ���������� (����) ������� ����� ODBC.\
								\n 4. ��������� � �������.\n\
								\n������ - ! 1 ! �����, ��� ������� ��������� ����'���� � ��������� ���� �� �������������.\
								\n������ - !2-3! ��������� �� ������� � �������� �������� ��������.\
								\n������ - ! 4 ! �������� �� ��'������� ��������� ������ ������ ����'����� �� ����������.\
								\n                 � �� ��������� ��� ���������.\
								\n������ - ��������� ���������� � ������� �� ��������.\
								\n���� ����������� ��� �� �������, �� ����������� �� ������������.\n\
								\n                            ������� �� ����������.");
        return false;
    }
    return true;
}
//--------------------utech--------------------utech--------------------utech--------------------
QVariant readSetting(QString settingPath, QString settingName, QString iniFileName)
{
	QDir::setCurrent(QCoreApplication::applicationDirPath());
	QSettings settings("./"+iniFileName, QSettings::IniFormat);
	return settings.value(settingPath+"/"+settingName);
}
//--------------------utech--------------------utech--------------------utech--------------------
void writeSetting(QVariant val, QString settingPath, QString settingName, QString iniFileName)
{
	QDir::setCurrent(QCoreApplication::applicationDirPath());
        QSettings settings("./"+iniFileName, QSettings::IniFormat);file:///mnt/win_d/devel/autoparkmeneger/src/guiautopark/UDifFunc_APark.h
	settings.beginGroup(settingPath);
	settings.setValue(settingName, val);
	settings.endGroup();
}
//--------------------utech--------------------utech--------------------utech--------------------
QString encrypt(QString str)
{
	return str.toLocal8Bit().toBase64();
}
//--------------------utech--------------------utech--------------------utech--------------------
QString decrypt(QString str)
{
	return QByteArray::fromBase64(str.toLocal8Bit());
}
//--------------------utech--------------------utech--------------------utech--------------------
bool writeUserLog(int userId, int ProgramId, int UserOperId, QString prymitka)
{
	QSqlQuery query;
	if (prymitka.size()>10)
		prymitka.truncate(10);
	bool doneOk = query.exec("INSERT INTO logUserOperations (User_id, Program_Id, UserOper_Id, HostName, Prymitka) \
							VALUES ("+sqlStr(userId)+", "+sqlStr(ProgramId)+", "+sqlStr(UserOperId)+", SUBSTRING_INDEX(CURRENT_USER(),'@',-1),"+sqlStr(prymitka)+")");
	return doneOk;
}
//--------------------utech--------------------utech--------------------utech--------------------
void castControls(QObject *obj, bool isAct)
{
	QAction *action = qobject_cast<QAction *>(obj);
	if (action){
		action->setEnabled(isAct);
		return;
	}
	
	QComboBox *comboBox = qobject_cast<QComboBox *>(obj);
	if (comboBox){
		comboBox->setEnabled(isAct);
		return;
	}
	
	QSpinBox *spinBox = qobject_cast<QSpinBox *>(obj);
	if (spinBox){
		spinBox->setReadOnly(!isAct);
		return;
	}
	
	QLineEdit *lineEdit = qobject_cast<QLineEdit *>(obj);
	if (lineEdit){
		lineEdit->setReadOnly(!isAct);
		return;
	}
	
	QDoubleSpinBox *doubleSpinBox = qobject_cast<QDoubleSpinBox *>(obj);
	if (doubleSpinBox){
		doubleSpinBox->setReadOnly(!isAct);
		return;
	}
	
	QCheckBox *checkBox = qobject_cast<QCheckBox *>(obj);
	if (checkBox){
		checkBox->setEnabled(isAct);
		return;
	}
	
	QToolButton *toolButton = qobject_cast<QToolButton *>(obj);
	if (toolButton){
		toolButton->setEnabled(isAct);
		return;
	}
	
	QDateEdit *dateEdit = qobject_cast<QDateEdit *>(obj);
	if (dateEdit){
		dateEdit->setEnabled(isAct);
		return;
	}
	
	QPushButton *pushButton = qobject_cast<QPushButton *>(obj);
	if (pushButton){
		pushButton->setEnabled(isAct);
		return;
	}
	
	QGroupBox *groupBox = qobject_cast<QGroupBox *>(obj);
	if (groupBox){
		groupBox->setEnabled(isAct);
		return;
	}
	
	QTableWidget *tableWidget = qobject_cast<QTableWidget *>(obj);
	if (tableWidget){
		tableWidget->blockSignals(!isAct);
		return;
	}
	
	QTableView *tableView = qobject_cast<QTableView *>(obj);
	if (tableView){
		tableView->setEnabled(isAct);
		return;
	}
	
	QWidget *widget = qobject_cast<QWidget *>(obj);
	if (widget){
		widget->setEnabled(isAct);
		return;
	}
}
//--------------------utech--------------------utech--------------------utech--------------------
