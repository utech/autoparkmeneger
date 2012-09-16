//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл декларації класу вікна реєстрації користувача
//
// Створений програмістами Компанії "Утех" 29.03.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#ifndef UForm_AParkPartnery_APARK_H
#define UForm_AParkPartnery_APARK_H

#include <QtGui>
#include <QSettings>
#include <QDir>
#include <QtSql>

#include "UAutoParkMeneger_APark.h"
#include "ui_UForm_AParkPartnery.h"

#include <UTableWidgetSqlExt>
//--------------------utech--------------------utech--------------------utech--------------------
class UForm_AParkPartnery : public UAParkTabWidget
{
  Q_OBJECT

  public:
		UForm_AParkPartnery(int tWType, QWidget *parent = 0);
		~UForm_AParkPartnery();
		
		void populateToolBar(QToolBar * tBar);
  public slots:
		void pushButton_create_clicked();
		void pushButton_delete_clicked();
	  private:
		Ui::UForm_AParkPartnery ui;
		UTableWidgetSqlExt *twExt;
};
//--------------------utech--------------------utech--------------------utech--------------------
#endif
