//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл декларації класу вікна реєстрації користувача
//
// Створений програмістами Компанії "Утех" 29.03.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#ifndef UForm_AParkCinaPalnogo_APARK_H
#define UForm_AParkCinaPalnogo_APARK_H

#include <QtGui>
#include <QSettings>
#include <QDir>
#include <QtSql>

#include "UAutoParkMeneger_APark.h"
#include "ui_UForm_AParkCinaPalnogo.h"

#include <UTableWidgetSqlExt>
//--------------------utech--------------------utech--------------------utech--------------------
class UForm_AParkCinaPalnogo : public UAParkTabWidget
{
  Q_OBJECT

  public:
		UForm_AParkCinaPalnogo(int tWType, QWidget *parent = 0);
		~UForm_AParkCinaPalnogo();
		
		void populateToolBar(QToolBar * tBar);
  public slots:
		void populateCinaPalnogoTable();
		void pushButton_create_clicked();
		void pushButton_delete_clicked();
		void saveItem(QTableWidgetItem *item);
  private:
		Ui::UForm_AParkCinaPalnogo ui;
		
		QHash<int, int> palneIdHash; //palneIdHash<col, Id>
};
//--------------------utech--------------------utech--------------------utech--------------------
#endif
