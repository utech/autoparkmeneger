//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл декларації класу вікна реєстрації користувача
//
// Створений програмістами Компанії "Утех" 29.03.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#ifndef UFORM_APARKTOLOG_H
#define UFORM_APARKTOLOG_H

#include <QtGui>
#include <QSettings>
#include <QDir>
#include <QtSql>

#include "UAutoParkMeneger_APark.h"
#include "ui_UForm_AParkTOLog.h"

#include <UTableWidgetSqlExt>
//--------------------utech--------------------utech--------------------utech--------------------

//--------------------utech--------------------utech--------------------utech--------------------
class UForm_AParkTOLog : public UAParkTabWidget
{
  Q_OBJECT

  public:
		UForm_AParkTOLog(int tWType, QWidget *parent = 0);
		~UForm_AParkTOLog();
		
		void populateToolBar(QToolBar * tBar);
		void populateAutosListWidget();
  public slots:
		void pushButton_create_clicked();
		void pushButton_delete_clicked();
		
		void setTOLogFilterFilter();
		void populateDovidnykValues(QTableWidgetItem *item);
  private:
		Ui::UForm_AParkTOLog ui;
		
		UDataFormView *twExt;
};
//--------------------utech--------------------utech--------------------utech--------------------
#endif
