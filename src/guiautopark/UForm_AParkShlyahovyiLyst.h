//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл декларації класу вікна реєстрації користувача
//
// Створений програмістами Компанії "Утех" 29.03.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#ifndef UFORM_APARKSHLYAHOVYILYST_H
#define UFORM_APARKSHLYAHOVYILYST_H

#include <QtGui>
#include <QSettings>
#include <QDir>
#include <QtSql>

#include "UAutoParkMeneger_APark.h"
#include "ui_UForm_AParkShlyahovyiLyst.h"

#include <UTableWidgetSqlExt>
//--------------------utech--------------------utech--------------------utech--------------------

//--------------------utech--------------------utech--------------------utech--------------------
class UForm_AParkShlyahovyiLyst : public UAParkTabWidget
{
  Q_OBJECT

  public:
		UForm_AParkShlyahovyiLyst(int tWType, QWidget *parent = 0);
		~UForm_AParkShlyahovyiLyst();
		
		void populateToolBar(QToolBar * tBar);
		void showFilterString();
  public slots:
		void pushButton_create_clicked();
		void pushButton_delete_clicked();
		void populateDovidnykValues(QTableWidgetItem *item);
		void populateDefaultMarshrutZnach();
		
		void setDateFilter();
		
		void action_printVidomistVykonannyaPlanuVDen_activated();
		void action_printZvedenaVidomistPoDorojnihLystahZaMisyac_activated();
		void action_printZvedenaVidomistPoTupahMarshrutivZaMisyac_activated();
		void action_printZvitProZdanuVyruchkuGotivkoyu_activated();
		void action_printZvitProPerevezPilgPasajyriv_activated();
		void action_printVidomistMarshrutivVDen_activated();
		
		void pushButton_showHideExtSearch_clicked();
		void groupBox_extFilter_toggled();
		void pushButton_execFilter_clicked();
  private:
		Ui::UForm_AParkShlyahovyiLyst ui;
		
		UDataFormView *twExt;
		
		//Редаговані комбобокси для розширеного фільтрування
		UIntEditingComboBox * autoFilterCB;
		UIntEditingComboBox * vodiyFilterCB;
		UIntEditingComboBox * marshrutFilterCB;
		UIntEditingComboBox * nochivlyaFilterCB;
};
//--------------------utech--------------------utech--------------------utech--------------------
#endif
