//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл декларації класу вікна реєстрації користувача
//
// Створений програмістами Компанії "Утех" 23.03.2010р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#ifndef UFORM_APARKEDITTABELWIDGET_H
#define UFORM_APARKEDITTABELWIDGET_H

#include <QtGui>
#include <QSettings>
#include <QDir>
#include <QtSql>
#include <QTime>

#include "UAutoParkMeneger_APark.h"
#include "ui_UForm_AParkEditTabelWidget.h"

//--------------------utech--------------------utech--------------------utech--------------------
class UForm_AParkEditTabelWidget : public UAParkTabWidget
{
  Q_OBJECT

  public:
	UForm_AParkEditTabelWidget(int tWType, QWidget *parent = 0);
	~UForm_AParkEditTabelWidget();
	
	void populateToolBar(QToolBar * tBar);
	void fillTabelCell(int row, int col);
  public slots:
	void populateTabel();
	void tableWidget_tabel_itemDoubleClicked(QTableWidgetItem *item);
	void fillTabelFromDb();
	void fillCurrentCell();
	void fillCurrentRow();
	void printTabel();
	void pushButton_findCell_clicked();
  private:
	Ui::UForm_AParkEditTabelWidget ui;
};
//--------------------utech--------------------utech--------------------utech--------------------
#endif
