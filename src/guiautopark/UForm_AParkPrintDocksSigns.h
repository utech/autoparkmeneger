//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл декларації класу вікна реєстрації користувача
//
// Створений програмістами Компанії "Утех" 19.07.2010р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#ifndef UForm_AParkPrintDocksSigns_APARK_H
#define UForm_AParkPrintDocksSigns_APARK_H

#include <QtGui>
#include <QSettings>
#include <QDir>
#include <QtSql>

#include "UAutoParkMeneger_APark.h"
#include "ui_UForm_AParkPrintDocksSigns.h"

#include <UTableWidgetSqlExt>

//--------------------utech--------------------utech--------------------utech--------------------
class UForm_AParkPrintDocksSigns : public UAParkTabWidget
{
  Q_OBJECT

  public:
	UForm_AParkPrintDocksSigns(int tWType, QWidget *parent = 0);
	~UForm_AParkPrintDocksSigns();
		
	void populateToolBar(QToolBar * tBar);
  public slots:
		void toolButton_addUserSign_clicked();
		void toolButton_signUp_clicked();
		void toolButton_signDown_clicked();
		void toolButton_saveSigns_clicked();
		void toolButton_deleteSign_clicked();
		void populatePrintDockSigns();
  private:
	Ui::UForm_AParkPrintDocksSigns ui;
	
	UTableWidgetSqlExt *twExtDocks;
	UTableWidgetSqlExt *twExtUsers;
};
//--------------------utech--------------------utech--------------------utech--------------------
#endif
