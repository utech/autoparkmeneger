//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл декларації класу вікна реєстрації користувача
//
// Створений програмістами Компанії "Утех" 29.03.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#ifndef UForm_AParkDocumentsView_PlanovyiViddil_H
#define UForm_AParkDocumentsView_PlanovyiViddil_H

#include <QtGui>
#include <QSettings>
#include <QDir>
#include <QtSql>

#include "UAutoParkMeneger_APark.h"
#include "ui_UForm_AParkDocumentsView_PlanovyiViddil.h"

#include <UTableWidgetSqlExt>
//--------------------utech--------------------utech--------------------utech--------------------

//--------------------utech--------------------utech--------------------utech--------------------
class UForm_AParkDocumentsView_PlanovyiViddil : public UAParkTabWidget
{
  Q_OBJECT

  public:
	UForm_AParkDocumentsView_PlanovyiViddil(int tWType, QWidget *parent = 0);
	~UForm_AParkDocumentsView_PlanovyiViddil();
	
	void populateToolBar(QToolBar * tBar);
  public slots:
	void action_printPlanyValovyhDohodiv_activated();
	void action_printVidomistVykonannyaPlanuVDen_activated();
	void action_printZvedenaVidomistPoDorojnihLystahZaMisyac_activated();
	void action_printZvedenaVidomistPoTupahMarshrutivZaMisyac_activated();
	void action_printZvitProZdanuVyruchkuGotivkoyu_activated();
	void action_printZvitProPerevezPilgPasajyriv_activated();
	void action_print_perelik_pracivnykiv_activated();
  private:
	Ui::UForm_AParkDocumentsView_PlanovyiViddil ui;
};
//--------------------utech--------------------utech--------------------utech--------------------
#endif
