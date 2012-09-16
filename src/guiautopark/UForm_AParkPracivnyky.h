//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл декларації класу вікна реєстрації користувача
//
// Створений програмістами Компанії "Утех" 29.03.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#ifndef UForm_AParkPracivnyky_H
#define UForm_AParkPracivnyky_H

#include <QtGui>
#include <QSettings>
#include <QDir>
#include <QtSql>

#include "UAutoParkMeneger_APark.h"
#include "ui_UForm_AParkPracivnyky.h"

#include <UTableWidgetSqlExt>
//--------------------utech--------------------utech--------------------utech--------------------

//--------------------utech--------------------utech--------------------utech--------------------
class UForm_AParkPracivnyky : public UAParkTabWidget
{
  Q_OBJECT

  public:
		UForm_AParkPracivnyky(int tWType, QWidget *parent = 0);
		~UForm_AParkPracivnyky();
		
		void populateToolBar(QToolBar * tBar);
  public slots:
		void pushButton_create_clicked();
		void pushButton_delete_clicked();
		void populateDovidnykValues(QTableWidgetItem *item);
  private:
		Ui::UForm_AParkPracivnyky ui;
		
		UDataFormView *twExt;
};
//--------------------utech--------------------utech--------------------utech--------------------
#endif
