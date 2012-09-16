//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл декларації класу вікна реєстрації користувача
//
// Створений програмістами Компанії "Утех" 29.03.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#ifndef UFORM_APARKLYSTOKREGULYARNOSTIRUHU_APARK_H
#define UFORM_APARKLYSTOKREGULYARNOSTIRUHU_APARK_H

#include <QtGui>
#include <QSettings>
#include <QDir>
#include <QtSql>

#include "UAutoParkMeneger_APark.h"
#include "ui_UForm_AParkLystokRegulyarnostiRuhu.h"

#include <UTableWidgetSqlExt>
//--------------------utech--------------------utech--------------------utech--------------------
class UForm_AParkLystokRegulyarnostiRuhu : public UAParkTabWidget
{
  Q_OBJECT

  public:
		UForm_AParkLystokRegulyarnostiRuhu(int tWType, QWidget *parent = 0);
		~UForm_AParkLystokRegulyarnostiRuhu();
		
		void populateToolBar(QToolBar * tBar);
		void showFilterString();
  public slots:
		void toolButton_avtoZapovn_clicked();
		void pushButton_create_clicked();
		void pushButton_delete_clicked();
		
		void setDateFilter();
		void populateDovidnykValues(QTableWidgetItem *item);
		void calcVartistPalnogoZaZminu();
		
		void action_printLystkyRegulyarnostiRuhu_activated();
		void action_printBackSideOfLystokRegulyarnosti_activated();
		void action_printPustogrLystkaRegulRuhu_activated();
		
		void pushButton_showHideExtSearch_clicked();
		void groupBox_extFilter_toggled();
		void pushButton_execFilter_clicked();
  private:
		Ui::UForm_AParkLystokRegulyarnostiRuhu ui;
		UDataFormView *twExt;
		
		//Редаговані комбобокси для розширеного фільтрування
		UIntEditingComboBox * autoFilterCB;
		UIntEditingComboBox * vodiyFilterCB;
		UIntEditingComboBox * marshrutFilterCB;
		UIntEditingComboBox * nochivlyaFilterCB;
};
//--------------------utech--------------------utech--------------------utech--------------------
#endif
