//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл виконання класу вікна налаштування програми
//
// Створений програмістами Компанії "Утех" 29.03.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------
#include "UForm_AParkDocumentsView.h"

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
UForm_AParkDocumentsView::UForm_AParkDocumentsView(int tWType, QWidget *parent)
        : UAParkTabWidget(tWType, parent)
{
	ui.setupUi(this);
	
	ui.dateEdit_filtr->setDate(QDate::currentDate());
	
	QSqlQuery query;
	query.exec("SELECT id, Prizv, Imia, Pobatk FROM npr WHERE Posada_id=10 ORDER BY Prizv, Imia, Pobatk");
	while (query.next()){
		ui.comboBox_nprId->addItem(query.value(1).toString()+" "+query.value(2).toString()
				+" "+query.value(3).toString()+" ["+query.value(0).toString()+"]",
				query.value(0).toInt());
	}
	new UIntEditingComboBox(ui.comboBox_nprId);
	
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
	connect(ui.pushButton_printTabelVodoyiv, SIGNAL(clicked()), 
			this, SLOT(action_printTabelVodoyiv()));
	
	connect(ui.pushButton_print_perelik_pracivnykiv, SIGNAL(clicked()), 
			this, SLOT(action_print_perelik_pracivnykiv_activated()));
	connect(ui.pushButton_print_vidomist_narah_zarplaty, SIGNAL(clicked()), 
			this, SLOT(action_print_vidomist_narah_zarplaty_activated()));
	connect(ui.pushButton_print_month_cards, SIGNAL(clicked()), 
			this, SLOT(action_print_month_cards_activated()));
	connect(ui.pushButton_print_year_cards, SIGNAL(clicked()), 
			this, SLOT(action_print_year_cards_activated()));
	connect(ui.pushButton_print_utrymannya, SIGNAL(clicked()), 
			this, SLOT(action_print_utrymannya_activated()));
	connect(ui.pushButton_print_vidrahuvannya, SIGNAL(clicked()), 
			this, SLOT(action_print_vidrahuvannya_activated()));
	connect(ui.pushButton_printOplataZaborgovanist, SIGNAL(clicked()), 
			this, SLOT(action_printOplataZaborgovanist_activated()));
	connect(ui.pushButton_printVidomistNarahuvannyaIVidrahuvannya, SIGNAL(clicked()), 
			this, SLOT(action_printVidomistNarahuvannyaIVidrahuvannya_activated()));
	
	connect(ui.pushButton_print_month_card_for_current_worker, SIGNAL(clicked()), 
			this, SLOT(action_print_month_card_for_current_worker_activated()));
	connect(ui.pushButton_print_year_card_for_current_worker, SIGNAL(clicked()), 
			this, SLOT(action_print_year_card_for_current_worker_activated()));
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkDocumentsView::populateToolBar(QToolBar * tBar)
{
	
}
//--------------------utech--------------------utech--------------------utech--------------------
UForm_AParkDocumentsView::~UForm_AParkDocumentsView()
{
	
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkDocumentsView::action_printPlanyValovyhDohodiv_activated()
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
void UForm_AParkDocumentsView::action_printVidomistVykonannyaPlanuVDen_activated()
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
void UForm_AParkDocumentsView::action_printZvedenaVidomistPoDorojnihLystahZaMisyac_activated()
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
void UForm_AParkDocumentsView::action_printZvedenaVidomistPoTupahMarshrutivZaMisyac_activated()
{
	UDialog_AParkDateFilter *d = new UDialog_AParkDateFilter(ui.dateEdit_filtr->date(), "Дата для відомості", "MM.yyyy");
	if (d->exec()){
		UPrintDocs_APark *printDocs = new UPrintDocs_APark();
		printDocs->print_zvedenaVidomistPoTupahMarshrutivZaMisyac(d->date());
		connect(this, SIGNAL(mainWindowClosed()), printDocs->printform, SLOT(close()));
		delete printDocs;
	}
	delete d;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkDocumentsView::action_printZvitProZdanuVyruchkuGotivkoyu_activated()
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
void UForm_AParkDocumentsView::action_printZvitProPerevezPilgPasajyriv_activated()
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


void UForm_AParkDocumentsView::action_printTabelVodoyiv()
{
	UPrintDocs_APark *printDocs = new UPrintDocs_APark();
	printDocs->print_monthTabel(ui.dateEdit_filtr->date().year(), ui.dateEdit_filtr->date().month());
	connect(this, SIGNAL(mainWindowClosed()), printDocs->printform, SLOT(close()));
	delete printDocs;
}
//--------------------utech--------------------utech--------------------utech--------------------

void UForm_AParkDocumentsView::action_print_perelik_pracivnykiv_activated()
{
	UPrintDocs *printDocs = new UPrintDocs();
	printDocs->perelik_pracivnykiv(0, false);
	connect(this, SIGNAL(closeLoginSignal()), printDocs->printform, SLOT(close()));
	connect(this, SIGNAL(mainWindowClosed()), printDocs->printform, SLOT(close()));
	delete printDocs;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkDocumentsView::action_print_vidomist_narah_zarplaty_activated()
{
	UDialogYMFilter *filterDialog = new UDialogYMFilter(0,"Друк відомості нарахування зарплати", ui.dateEdit_filtr->date().year(), ui.dateEdit_filtr->date().month());
	if (filterDialog->exec()==1){
		UPrintDocs *printDocs = new UPrintDocs();
		printDocs->print_narahuvannya_za_misac(filterDialog->get_Year(),filterDialog->get_Month(),0,false);
		connect(this, SIGNAL(closeLoginSignal()), printDocs->printform, SLOT(close()));
		connect(this, SIGNAL(mainWindowClosed()), printDocs->printform, SLOT(close()));
		delete printDocs;
	}
	delete filterDialog;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkDocumentsView::action_print_month_cards_activated()
{
	UDialogYMFilter *filterDialog = new UDialogYMFilter(0,"Друк карточок по зарплаті", ui.dateEdit_filtr->date().year(), ui.dateEdit_filtr->date().month());
	if (filterDialog->exec()==1){
		UPrintDocs *printDocs = new UPrintDocs();
		printDocs->print_worker_cards(filterDialog->get_Year(),filterDialog->get_Month(),0, false);
		connect(this, SIGNAL(closeLoginSignal()), printDocs->printform, SLOT(close()));
		connect(this, SIGNAL(mainWindowClosed()), printDocs->printform, SLOT(close()));
		delete printDocs;
	}
	delete filterDialog;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkDocumentsView::action_print_month_card_for_current_worker_activated()
{
	UDialogYMFilter *filterDialog = new UDialogYMFilter(0,"Друк картки по зарплаті для поточного працівника", ui.dateEdit_filtr->date().year(), ui.dateEdit_filtr->date().month());
	if (filterDialog->exec()==1){
		UPrintDocs *printDocs = new UPrintDocs();
		printDocs->print_cur_worker_card(filterDialog->get_Year(),filterDialog->get_Month(), 
				ui.comboBox_nprId->itemData(ui.comboBox_nprId->currentIndex(),Qt::UserRole).toInt());
		connect(this, SIGNAL(closeLoginSignal()), printDocs->printform, SLOT(close()));
		connect(this, SIGNAL(mainWindowClosed()), printDocs->printform, SLOT(close()));
		delete printDocs;
	}
	delete filterDialog;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkDocumentsView::action_print_year_cards_activated()
{
	UDialogYMFilter *filterDialog = new UDialogYMFilter(0,"Друк річних карток по зарплаті", ui.dateEdit_filtr->date().year(), ui.dateEdit_filtr->date().month());
	if (filterDialog->exec()==1){
		UPrintDocs *printDocs = new UPrintDocs();
		printDocs->print_year_cards(filterDialog->get_Year(),0,false);
		connect(this, SIGNAL(closeLoginSignal()), printDocs->printform, SLOT(close()));
		connect(this, SIGNAL(mainWindowClosed()), printDocs->printform, SLOT(close()));
		delete printDocs;
	}
	delete filterDialog;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkDocumentsView::action_print_year_card_for_current_worker_activated()
{
	UDialogYMFilter *filterDialog = new UDialogYMFilter(0,"Друк річної картки по зарплаті для поточного працівника", ui.dateEdit_filtr->date().year(), ui.dateEdit_filtr->date().month());
	if (filterDialog->exec()==1){
		UPrintDocs *printDocs = new UPrintDocs();
		printDocs->print_year_cur_worker_card(filterDialog->get_Year(),
			ui.comboBox_nprId->itemData(ui.comboBox_nprId->currentIndex(),Qt::UserRole).toInt());
		connect(this, SIGNAL(closeLoginSignal()), printDocs->printform, SLOT(close()));
		connect(this, SIGNAL(mainWindowClosed()), printDocs->printform, SLOT(close()));
		delete printDocs;
	}
	delete filterDialog;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkDocumentsView::action_print_utrymannya_activated()
{
	UDialogYMFilter *filterDialog = new UDialogYMFilter(0,"Друк нарахованих утримань із зарплати", ui.dateEdit_filtr->date().year(), ui.dateEdit_filtr->date().month());
	if (filterDialog->exec()==1){
		UPrintDocs *printDocs = new UPrintDocs();
		printDocs->print_vidomist_utrymannya(filterDialog->get_Year(),filterDialog->get_Month(),0, false);
		connect(this, SIGNAL(closeLoginSignal()), printDocs->printform, SLOT(close()));
		connect(this, SIGNAL(mainWindowClosed()), printDocs->printform, SLOT(close()));
		delete printDocs;
	}
	delete filterDialog;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkDocumentsView::action_print_vidrahuvannya_activated()
{
	UDialogYMFilter *filterDialog = new UDialogYMFilter(0,"Друк нарахованих відрахувань на зарплату", ui.dateEdit_filtr->date().year(), ui.dateEdit_filtr->date().month());
	if (filterDialog->exec()==1){
		UPrintDocs *printDocs = new UPrintDocs();
		printDocs->print_vidomist_vidrahuvannya(filterDialog->get_Year(),filterDialog->get_Month(),0, false);
		connect(this, SIGNAL(closeLoginSignal()), printDocs->printform, SLOT(close()));
		connect(this, SIGNAL(mainWindowClosed()), printDocs->printform, SLOT(close()));
		delete printDocs;
	}
	delete filterDialog;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkDocumentsView::action_printOplataZaborgovanist_activated()
{
	UDialogYMFilter *filterDialog = new UDialogYMFilter(0,"Друк нарахованих відрахувань на зарплату", ui.dateEdit_filtr->date().year(), ui.dateEdit_filtr->date().month());
	if (filterDialog->exec()==1){
		UPrintDocs *printDocs = new UPrintDocs();
		printDocs->print_vidomist_oplaty_i_zaborgovanosti(filterDialog->get_Year(),filterDialog->get_Month(),0, false);
		connect(this, SIGNAL(closeLoginSignal()), printDocs->printform, SLOT(close()));
		connect(this, SIGNAL(mainWindowClosed()), printDocs->printform, SLOT(close()));
		delete printDocs;
	}
	delete filterDialog;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkDocumentsView::action_printVidomistNarahuvannyaIVidrahuvannya_activated()
{
	UDialogYMFilter *filterDialog = new UDialogYMFilter(0,"Друк нарахованих відрахувань на зарплату", ui.dateEdit_filtr->date().year(), ui.dateEdit_filtr->date().month());
	if (filterDialog->exec()==1){
		UPrintDocs *printDocs = new UPrintDocs();
		printDocs->print_vidomist_narah_i_vidrah_by_buhrahunok(filterDialog->get_Year(),filterDialog->get_Month(), false);
		connect(this, SIGNAL(closeLoginSignal()), printDocs->printform, SLOT(close()));
		connect(this, SIGNAL(mainWindowClosed()), printDocs->printform, SLOT(close()));
		delete printDocs;
	}
	delete filterDialog;
}
//--------------------utech--------------------utech--------------------utech--------------------
