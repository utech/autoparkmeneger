//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл декларації класу вікна реєстрації користувача
//
// Створений програмістами Компанії "Утех" 29.03.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#ifndef UFORM_APARKSVYATKOVIDNI_H
#define UFORM_APARKSVYATKOVIDNI_H

#include <QtGui>
#include <QSettings>
#include <QDir>
#include <QtSql>

#include "UAutoParkMeneger_APark.h"
#include "ui_UForm_AParkSvyatkoviDni.h"

#include <UTableWidgetSqlExt>
//--------------------utech--------------------utech--------------------utech--------------------

//--------------------utech--------------------utech--------------------utech--------------------
class UForm_AParkSvyatkoviDni : public UAParkTabWidget
{
  Q_OBJECT

  public:
		UForm_AParkSvyatkoviDni(int tWType, QWidget *parent = 0);
		~UForm_AParkSvyatkoviDni();
		
		void populateToolBar(QToolBar * tBar);
		
  public slots:
		void pushButton_create_clicked();
		void pushButton_delete_clicked();
		void populateTable();
  signals:
		
	  private:
		Ui::UForm_AParkSvyatkoviDni ui;
		
		UTableWidgetSqlExt *twExt;
};
//--------------------utech--------------------utech--------------------utech--------------------
#endif
