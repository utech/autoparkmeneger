//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл декларації класу вікна реєстрації користувача
//
// Створений програмістами Компанії "Утех" 29.03.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#ifndef UForm_AParkCloseMonthes_APARK_H
#define UForm_AParkCloseMonthes_APARK_H

#include <QtGui>
#include <QSettings>
#include <QDir>
#include <QtSql>

#include "UAutoParkMeneger_APark.h"
#include "ui_UForm_AParkCloseMonthes.h"

#include <UTableWidgetSqlExt>
//--------------------utech--------------------utech--------------------utech--------------------
class UForm_AParkCloseMonthes : public UAParkTabWidget
{
  Q_OBJECT

  public:
		UForm_AParkCloseMonthes(int tWType, QWidget *parent = 0);
		~UForm_AParkCloseMonthes();
		
		void populateToolBar(QToolBar * tBar);
  public slots:
		void pushButton_create_clicked();
		void pushButton_delete_clicked();
	  private:
		Ui::UForm_AParkCloseMonthes ui;
		UTableWidgetSqlExt *twExt;
};
//--------------------utech--------------------utech--------------------utech--------------------
#endif
