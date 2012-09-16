//--------------------utech--------------------utech--------------------utech--------------------
//
// Створений програмістами Компанії "Утех" 24.03.2010р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#ifndef UDIALOG_APARKEDITTABELCELL_H
#define UDIALOG_APARKEDITTABELCELL_H

#include <QDialog>
#include <QDate>
#include <QtDebug>
#include <QTableWidgetItem>

#include "UAutoParkMeneger_APark.h"

#include "ui_UDialog_AParkEditTabelCell.h"
//--------------------utech--------------------utech--------------------utech--------------------
class UDialog_AParkEditTabelCell : public QDialog
{
	Q_OBJECT

  public:
	UDialog_AParkEditTabelCell(int nprId, QDate dt, QTableWidgetItem* item, QWidget *parent = 0);
		
	~UDialog_AParkEditTabelCell();
  public slots:
	void pushButton_accept_clicked();
	void checkRobTime();
  private:
	Ui::UDialog_AParkEditTabelCell ui;
		
	QDate _dt;
	int _nprId;
	QTableWidgetItem *_item;
};
//--------------------utech--------------------utech--------------------utech--------------------
#endif
