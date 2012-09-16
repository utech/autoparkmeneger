//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл декларації класу вікна реєстрації користувача
//
// Створений програмістами Компанії "Утех" 29.03.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#ifndef UForm_AParkDocumentsView_H
#define UForm_AParkDocumentsView_H

#include <QtGui>
#include <QSettings>
#include <QDir>
#include <QtSql>

#include "UAutoParkMeneger_APark.h"
#include "ui_UForm_AParkDocumentsView.h"

#include <UTableWidgetSqlExt>
//--------------------utech--------------------utech--------------------utech--------------------

//--------------------utech--------------------utech--------------------utech--------------------
class UForm_AParkDocumentsView : public UAParkTabWidget
{
  Q_OBJECT

  public:
	UForm_AParkDocumentsView(int tWType, QWidget *parent = 0);
	~UForm_AParkDocumentsView();
	
	void populateToolBar(QToolBar * tBar);
  public slots:
	void action_printPlanyValovyhDohodiv_activated();
	void action_printVidomistVykonannyaPlanuVDen_activated();
	void action_printZvedenaVidomistPoDorojnihLystahZaMisyac_activated();
	void action_printZvedenaVidomistPoTupahMarshrutivZaMisyac_activated();
	void action_printZvitProZdanuVyruchkuGotivkoyu_activated();
	void action_printZvitProPerevezPilgPasajyriv_activated();
	void action_printTabelVodoyiv();
	void action_print_perelik_pracivnykiv_activated();
	void action_print_vidomist_narah_zarplaty_activated();
	void action_print_month_cards_activated();
	void action_print_month_card_for_current_worker_activated();
	void action_print_year_cards_activated();
	void action_print_year_card_for_current_worker_activated();
	void action_print_utrymannya_activated();
	void action_print_vidrahuvannya_activated();
	void action_printOplataZaborgovanist_activated();
	void action_printVidomistNarahuvannyaIVidrahuvannya_activated();
  private:
	Ui::UForm_AParkDocumentsView ui;
};
//--------------------utech--------------------utech--------------------utech--------------------
#endif
