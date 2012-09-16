//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл декларації класу вікна реєстрації користувача
//
// Створений програмістами Компанії "Утех" 23.03.2010р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#ifndef UForm_AParkEditSumTabelWidget_H
#define UForm_AParkEditSumTabelWidget_H

#include <QtGui>
#include <QSettings>
#include <QDir>
#include <QtSql>
#include <QTime>
#include <QDate>

#include "UAutoParkMeneger_APark.h"
#include "ui_UFormSalaryTabelSumWidget.h"

//--------------------utech--------------------utech--------------------utech--------------------
// Через проблему наслідування від QObject з двох гілок ієрархії класів (Через QWidget), 
// прийнято рішення простого копіювання
//функцій класу UFormSalaryTabelSumWidget з програми зарплати


class UForm_AParkEditSumTabelWidget : public UAParkTabWidget
{
  Q_OBJECT

  public:
	UForm_AParkEditSumTabelWidget(int tWType, QWidget *parent = 0, QDate dt=QDate::currentDate());
	~UForm_AParkEditSumTabelWidget();
	
	void populateToolBar(QToolBar * tBar);
  public slots:
	void populateSumTabel();
	void sumTabelCurRowChanged( const QModelIndex & curIndex, const QModelIndex & prevIndex);
	void updateSumTabelSQLRows(int row, int column);
	void showOnlyWorkWorkersChanged(int state);
  signals:
	void mainWindowClosed();
	void currentWorkerChanged(int NprId);
  private:
	Ui::UFormSalaryTabelSumWidget ui;
	bool showOnlyWorkWorkers;
};
//--------------------utech--------------------utech--------------------utech--------------------
#endif
