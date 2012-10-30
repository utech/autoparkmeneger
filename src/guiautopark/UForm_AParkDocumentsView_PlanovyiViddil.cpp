//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл виконання класу вікна налаштування програми
//
// Створений програмістами Компанії "Утех" 29.03.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------
#include "UForm_AParkDocumentsView_PlanovyiViddil.h"

#include "UDifFunc_APark.h"
#include "UPrintDocs_APark.h"
#include "UPrintDocs.h"
#include "UDialogYMFilter.h"
#include "UDialog_AParkDateFilter.h"
#include "UDialog_AParkMarshrutTypeDateFilter.h"
#include "UDialog_AParkAutobusDateFilter.h"
#include <UStandardDelegate>

#include <QtDebug>
//--------------------utech--------------------utech--------------------utech--------------------
UForm_AParkDocumentsView_PlanovyiViddil::UForm_AParkDocumentsView_PlanovyiViddil(int tWType, QWidget *parent)
        : UAParkTabWidget(tWType, parent)
{
	ui.setupUi(this);
	
	ui.dateEdit_filtr->setDate(QDate::currentDate());
	
	connect(ui.pushButton_printPlanyValovyhDohodiv, SIGNAL(clicked()), 
			this, SLOT(action_printPlanyValovyhDohodiv_activated()));
	connect(ui.pushButton_printVidomistVykonannyaPlanuVDen, SIGNAL(clicked()), 
			this, SLOT(action_printVidomistVykonannyaPlanuVDen_activated()));
	connect(ui.pushButton_printZvedenaVidomistPoDorojnihLystahZaMisyac, SIGNAL(clicked()), 
			this, SLOT(action_printZvedenaVidomistPoDorojnihLystahZaMisyac_activated()));
	connect(ui.pushButton_printZvedenaVidomistPoTupahMarshrutivZaMisyac, SIGNAL(clicked()), 
			this, SLOT(action_printZvedenaVidomistPoTupahMarshrutivZaMisyac_activated()));
	connect(ui.pushButton_printZvitProZdanuVyruchkuGotivkoyu, SIGNAL(clicked()), 
			this, SLOT(action_printZvitProZdanuVyruchkuGotivkoyu_activated()));
	connect(ui.pushButton_printZvitProPerevezPilgPasajyriv, SIGNAL(clicked()), 
			this, SLOT(action_printZvitProPerevezPilgPasajyriv_activated()));
	
	connect(ui.pushButton_print_perelik_pracivnykiv, SIGNAL(clicked()), 
			this, SLOT(action_print_perelik_pracivnykiv_activated()));
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkDocumentsView_PlanovyiViddil::populateToolBar(QToolBar * tBar)
{
	
}
//--------------------utech--------------------utech--------------------utech--------------------
UForm_AParkDocumentsView_PlanovyiViddil::~UForm_AParkDocumentsView_PlanovyiViddil()
{
	
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkDocumentsView_PlanovyiViddil::action_printPlanyValovyhDohodiv_activated()
{
	UDialog_AParkDateFilter *d = new UDialog_AParkDateFilter(ui.dateEdit_filtr->date(), "Дата Планів", "dd.MM.yyyy");
	if (d->exec()){
		UPrintDocs_APark *printDocs = new UPrintDocs_APark();
		printDocs->print_planyValovyhDohodiv(d->date());
		connect(this, SIGNAL(mainWindowClosed()), printDocs->printform, SLOT(close()));
		delete printDocs;
	}
	delete d;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkDocumentsView_PlanovyiViddil::action_printVidomistVykonannyaPlanuVDen_activated()
{
	UDialog_AParkDateFilter *d = new UDialog_AParkDateFilter(ui.dateEdit_filtr->date(), "Дата для відомості");
	if (d->exec()){
		UPrintDocs_APark *printDocs = new UPrintDocs_APark();
		printDocs->print_vidomistVykonannyaPlanuVDen(d->date());
		connect(this, SIGNAL(mainWindowClosed()), printDocs->printform, SLOT(close()));
		delete printDocs;
	}
	delete d;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkDocumentsView_PlanovyiViddil::action_printZvedenaVidomistPoDorojnihLystahZaMisyac_activated()
{
	UDialog_AParkMarshrutTypeDateFilter *d = new UDialog_AParkMarshrutTypeDateFilter(ui.dateEdit_filtr->date(), "Дата для відомості", "MM.yyyy");
	if (d->exec()){
		UPrintDocs_APark *printDocs = new UPrintDocs_APark();
		printDocs->print_zvedenaVidomistPoDorojnihLystahZaMisyac(d->date(), d->marshrutType());
		connect(this, SIGNAL(mainWindowClosed()), printDocs->printform, SLOT(close()));
		delete printDocs;
	}
	delete d;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkDocumentsView_PlanovyiViddil::action_printZvedenaVidomistPoTupahMarshrutivZaMisyac_activated()
{
	UDialog_AParkMarshrutTypeDateFilter *d = new UDialog_AParkMarshrutTypeDateFilter(ui.dateEdit_filtr->date(), "Дата для відомості", "MM.yyyy");
	if (d->exec()){
		UPrintDocs_APark *printDocs = new UPrintDocs_APark();
		printDocs->print_zvedenaVidomistPoTupahMarshrutivZaMisyac(d->date(), d->marshrutType());
		connect(this, SIGNAL(mainWindowClosed()), printDocs->printform, SLOT(close()));
		delete printDocs;
	}
	delete d;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkDocumentsView_PlanovyiViddil::action_printZvitProZdanuVyruchkuGotivkoyu_activated()
{
	UDialog_AParkDateFilter *d = new UDialog_AParkDateFilter(ui.dateEdit_filtr->date(), "Дата для відомості", "MM.yyyy");
	if (d->exec()){
		UPrintDocs_APark *printDocs = new UPrintDocs_APark();
		printDocs->print_zvitProZdanuVyruchkuGotivkoyuZaMisyac(d->date());
		connect(this, SIGNAL(mainWindowClosed()), printDocs->printform, SLOT(close()));
		delete printDocs;
	}
	delete d;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkDocumentsView_PlanovyiViddil::action_printZvitProPerevezPilgPasajyriv_activated()
{
	UDialog_AParkDateFilter *d = new UDialog_AParkDateFilter(ui.dateEdit_filtr->date(), "Дата для відомості", "MM.yyyy");
	if (d->exec()){
		UPrintDocs_APark *printDocs = new UPrintDocs_APark();
		printDocs->print_zvitProPerevezPilgPasajyriv(d->date());
		connect(this, SIGNAL(mainWindowClosed()), printDocs->printform, SLOT(close()));
		delete printDocs;
	}
	delete d;
}
//--------------------utech--------------------utech--------------------utech--------------------

void UForm_AParkDocumentsView_PlanovyiViddil::action_print_perelik_pracivnykiv_activated()
{
	UPrintDocs *printDocs = new UPrintDocs();
	printDocs->perelik_pracivnykiv(0, false);
	connect(this, SIGNAL(closeLoginSignal()), printDocs->printform, SLOT(close()));
	connect(this, SIGNAL(mainWindowClosed()), printDocs->printform, SLOT(close()));
	delete printDocs;
}
//--------------------utech--------------------utech--------------------utech--------------------
