//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл декларації класу вікна реєстрації користувача
//
// Створений програмістами Компанії "Утех" 29.03.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#ifndef UFORM_APARKMARSHRUTY_H
#define UFORM_APARKMARSHRUTY_H

#include <QtGui>
#include <QSettings>
#include <QDir>
#include <QtSql>

#include "UAutoParkMeneger_APark.h"
#include "ui_UForm_AParkMarshruty.h"

#include <UTableWidgetSqlExt>
//--------------------utech--------------------utech--------------------utech--------------------

//--------------------utech--------------------utech--------------------utech--------------------
class UForm_AParkMarshruty : public UAParkTabWidget
{
  Q_OBJECT

  public:
		UForm_AParkMarshruty(int tWType, QWidget *parent = 0);
		~UForm_AParkMarshruty();
		
		void populateToolBar(QToolBar * tBar);
		
  public slots:
		void pushButton_create_clicked();
		void pushButton_delete_clicked();
  signals:
		
	  private:
		Ui::UForm_AParkMarshruty ui;
		
		UDataFormView *twExt;
};
//--------------------utech--------------------utech--------------------utech--------------------
#endif
