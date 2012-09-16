//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл декларації класу вікна реєстрації користувача
//
// Створений програмістами Компанії "Утех" 21.01.2012р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#ifndef UFORM_APARKEDITTABELPIDROZDILIVWIDGET_H
#define UFORM_APARKEDITTABELPIDROZDILIVWIDGET_H

#include <QtGui>
#include <QSettings>
#include <QDir>
#include <QtSql>
#include <QTime>

#include "UAutoParkMeneger_APark.h"
#include "ui_UForm_AParkEditTabelPidrozdilivWidget.h"

//--------------------utech--------------------utech--------------------utech--------------------
class UForm_AParkEditTabelPidrozdilivWidget : public UAParkTabWidget
{
  Q_OBJECT

  public:
	UForm_AParkEditTabelPidrozdilivWidget(int tWType, QWidget *parent = 0);
	~UForm_AParkEditTabelPidrozdilivWidget();
	
	void populateToolBar(QToolBar * tBar);
	int currentPidrozdilId();
  public slots:
	void populateTabel();
	void tableWidget_tabel_itemDoubleClicked(QTableWidgetItem *item);
	void printTabel();
	void pushButton_findCell_clicked();
  private:
	Ui::UForm_AParkEditTabelPidrozdilivWidget ui;
};
#endif
