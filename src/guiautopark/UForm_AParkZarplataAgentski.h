//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл декларації класу вікна реєстрації користувача
//
// Створений програмістами Компанії "Утех" 29.03.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#ifndef UFORM_APARKZARPLATAAGENTSKI_H
#define UForm_AParkZarplataAgentski_H

#include <QtGui>
#include <QSettings>
#include <QDir>
#include <QtSql>

#include "UAutoParkMeneger_APark.h"
#include "ui_UForm_AParkZarplataAgentski.h"

#include <UTableWidgetSqlExt>
//--------------------utech--------------------utech--------------------utech--------------------

//--------------------utech--------------------utech--------------------utech--------------------
class UForm_AParkZarplataAgentski : public UAParkTabWidget
{
  Q_OBJECT

  public:
	UForm_AParkZarplataAgentski(int tWType, QWidget *parent = 0);
	~UForm_AParkZarplataAgentski();
	
	void populateToolBar(QToolBar * tBar);
  public slots:
	void pushButton_create_clicked();
	void pushButton_delete_clicked();
  private:
	Ui::UForm_AParkZarplataAgentski ui;
	
	UDataFormView *twExt;
};
//--------------------utech--------------------utech--------------------utech--------------------
#endif
