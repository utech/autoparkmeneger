//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл декларації класу вікна реєстрації користувача
//
// Створений програмістами Компанії "Утех" 29.03.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#ifndef UForm_AParkPlanNaZminu_APARK_H
#define UForm_AParkPlanNaZminu_APARK_H

#include <QtGui>
#include <QSettings>
#include <QDir>
#include <QtSql>

#include "UAutoParkMeneger_APark.h"
#include "ui_UForm_AParkPlanNaZminu.h"

#include <UTableWidgetSqlExt>
//--------------------utech--------------------utech--------------------utech--------------------
class UForm_AParkPlanNaZminu : public UAParkTabWidget
{
  Q_OBJECT

  public:
		UForm_AParkPlanNaZminu(int tWType, QWidget *parent = 0);
		~UForm_AParkPlanNaZminu();
		
		void populateToolBar(QToolBar * tBar);
  public slots:
		void populatePlanNaZminuTable();
		void pushButton_create_clicked();
		void pushButton_delete_clicked();
		void saveItem(QTableWidgetItem *item);
		
		void action_printPlanyValovyhDohodiv_activated();
  private:
		Ui::UForm_AParkPlanNaZminu ui;
		
		QHash<int, int> marshrutIdHash; //marshrutIdHash<col, Id>
};
//--------------------utech--------------------utech--------------------utech--------------------
#endif
