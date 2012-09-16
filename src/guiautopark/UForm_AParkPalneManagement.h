//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл декларації класу вікна реєстрації користувача
//
// Створений програмістами Компанії "Утех" 07.06.2011р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#ifndef UFORM_APARKPALNEMANAGEMENT_H
#define UFORM_APARKPALNEMANAGEMENT_H

#include <QtGui>
#include <QSettings>
#include <QDir>
#include <QtSql>

#include "UAutoParkMeneger_APark.h"
#include "ui_UForm_AParkPalneManagement.h"

#include <UTableWidgetSqlExt>
//--------------------utech--------------------utech--------------------utech--------------------

//--------------------utech--------------------utech--------------------utech--------------------
class UForm_AParkPalneManagement : public UAParkTabWidget
{
  Q_OBJECT

  public:
		UForm_AParkPalneManagement(int tWType, QWidget *parent = 0);
		~UForm_AParkPalneManagement();
		
		void populateToolBar(QToolBar * tBar);
  public slots:
		void populateZvitKupivliPalnogo();
		void createZvitKupivliPalnogo();
		void deleteZvitKupivliPalnogo();
		
		void populateZvitKupivliPalnogoOrders();
		void createZvitKupivliPalnogoOrders();
		void deleteZvitKupivliPalnogoOrders();
		
		void calcOrdersSummary();
		
		void printZvitVykorystannyaKoshtivPalne();
		
		void action_printReyestrChekivGAZ_activated();
		void action_printReyestrChekivDailyGAZ_activated();
		void action_printReyestrChekivPALNE_activated();
                void action_printReyestrChekivVidPostachalnykaPALNE_activated();
		void action_printVidomistZakupivliPalnogoPoVodiyahZaMisyac_activated();
		void action_printVidomistZakupivliPalnogoPoVodiyahZaMisyacVRozriziRahunkiv_activated();
		void action_printReyestrChekivVidPostachalnykaPoVyduPalnogo_activated();
		void action_exportInformaciiVExcel_activated();
  private:
		Ui::UForm_AParkPalneManagement ui;
		
		UTableWidgetSqlExt *twExtZvity;
		UTableWidgetSqlExt *twExtOrders;
};
//--------------------utech--------------------utech--------------------utech--------------------
#endif
