//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл декларації класу вікна реєстрації користувача
//
// Створений програмістами Компанії "Утех" 25.03.2010р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#ifndef UFORM_APARKKARTKYROBOTYVODIYIV_APARK_H
#define UFORM_APARKKARTKYROBOTYVODIYIV_APARK_H

#include <QtGui>
#include <QtSql>

#include "UAutoParkMeneger_APark.h"
#include "ui_UForm_AParkKartkyRobotyVodiyiv.h"

#include <UTableWidgetSqlExt>
//--------------------utech--------------------utech--------------------utech--------------------
class UForm_AParkKartkyRobotyVodiyiv : public UAParkTabWidget
{
  Q_OBJECT

  public:
	UForm_AParkKartkyRobotyVodiyiv(int tWType, QWidget *parent = 0);
	~UForm_AParkKartkyRobotyVodiyiv();
	
	void populateToolBar(QToolBar * tBar);
  public slots:
	void populateTable();
	void action_printKartkyRobotyVodiyiv_activated();
	void tableWidget_vidiyi_itemDoubleClicked(QTableWidgetItem *item);
  private:
	Ui::UForm_AParkKartkyRobotyVodiyiv ui;
};
//--------------------utech--------------------utech--------------------utech--------------------
#endif
