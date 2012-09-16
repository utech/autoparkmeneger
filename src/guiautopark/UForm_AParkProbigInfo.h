//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл декларації класу вікна реєстрації користувача
//
// Створений програмістами Компанії "Утех" 29.03.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#ifndef UFORM_APARKPROBIGINFO_H
#define UFORM_APARKPROBIGINFO_H

#include <QtGui>
#include <QSettings>
#include <QDir>
#include <QtSql>

#include "UAutoParkMeneger_APark.h"
#include "ui_UForm_AParkProbigInfo.h"

#include <UTableWidgetSqlExt>
//--------------------utech--------------------utech--------------------utech--------------------
class UForm_AParkProbigInfo : public UAParkTabWidget
{
  Q_OBJECT

  public:
	UForm_AParkProbigInfo(int tWType, QWidget *parent = 0);
	~UForm_AParkProbigInfo();
		
	void populateToolBar(QToolBar * tBar);
	void setItemData(int row, int col, QVariant data);
  public slots:
	void populateTableWidget();
	
	void action_PrintMisyachnyiProbigUsihAvtobusiv_activated();
	void action_PrintMisyachnyiProbigOneAvtobus_activated();
	void action_PrintPerelikAvtobusivNaTO_activated();
  signals:
	
  private:
	Ui::UForm_AParkProbigInfo ui;
};
//--------------------utech--------------------utech--------------------utech--------------------
#endif
