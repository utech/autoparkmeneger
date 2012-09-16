//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл виконання класу вікна налаштування програми
//
// Створений програмістами Компанії "Утех" 29.03.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------
#include "UForm_AParkRozrahSumyKompensPoPilgah.h"

#include "UDifFunc_APark.h"
#include "UPrintDocs_APark.h"
#include <UStandardDelegate>
#include "UDialog_AParkDateFilter.h"

#include <QtDebug>
//--------------------utech--------------------utech--------------------utech--------------------
UForm_AParkRozrahSumyKompensPoPilgah::UForm_AParkRozrahSumyKompensPoPilgah(int tWType, QWidget *parent)
        : UAParkTabWidget(tWType, parent)
{
	ui.setupUi(this);
	
	twExt = new UDataFormView(ui.tableWidget_RozrahSumyKompens, "pilgyAParkPokazn");
	twExt->setSortingEnabled(true);
	twExt->colNamesList << "Id"
						<< "CurDate"
						<< "VyruchkaZagalna"
						<< "TaryfZaPasajKm"
						<< "KilkistPlatnPasaj"
						<< "Koef"
						<< "KilkistPilgovykiv"
						<< "KilkistVrahPilgovykiv"
						<< "Prymitka";
	
	twExt->addColAlignment("CurDate", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("VyruchkaZagalna", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("TaryfZaPasajKm", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("KilkistPlatnPasaj", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("Koef", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("KilkistPilgovykiv", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("KilkistVrahPilgovykiv", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("Prymitka", Qt::AlignVCenter | Qt::AlignLeft);
	
	twExt->insertWidget(ui.dateEdit_date, "CurDate");
	twExt->insertWidget(ui.doubleSpinBox_vyruchka, "VyruchkaZagalna");
	twExt->insertWidget(ui.doubleSpinBox_taryf, "TaryfZaPasajKm");
	twExt->insertWidget(ui.spinBox_kilkPerevezPlatnPasaj, "KilkistPlatnPasaj");
	twExt->insertWidget(ui.doubleSpinBox_koef, "Koef");
	twExt->insertWidget(ui.spinBox_kilkPilgovykiv, "KilkistPilgovykiv");
	twExt->insertWidget(ui.spinBox_kilkVrahPilgovykiv, "KilkistVrahPilgovykiv");
	twExt->insertWidget(ui.lineEdit_prymitka, "Prymitka");
	
	
	ui.tableWidget_RozrahSumyKompens->setItemDelegateForColumn(twExt->columnNumber("CurDate"), new UDateTimeDelegate(ui.tableWidget_RozrahSumyKompens, "MM.yyyy"));
	
	ui.tableWidget_RozrahSumyKompens->setItemDelegateForColumn(twExt->columnNumber("VyruchkaZagalna"), new UDoubleSpinBoxDelegate(0,100000, 2, ui.tableWidget_RozrahSumyKompens));
	ui.tableWidget_RozrahSumyKompens->setItemDelegateForColumn(twExt->columnNumber("TaryfZaPasajKm"), new UDoubleSpinBoxDelegate(0,100000, 2, ui.tableWidget_RozrahSumyKompens));
	ui.tableWidget_RozrahSumyKompens->setItemDelegateForColumn(twExt->columnNumber("Koef"), new UDoubleSpinBoxDelegate(0,100000, 4, ui.tableWidget_RozrahSumyKompens));
	
	ui.tableWidget_RozrahSumyKompens->setItemDelegateForColumn(twExt->columnNumber("KilkistPlatnPasaj"), new USpinBoxDelegate(0,100000, ui.tableWidget_RozrahSumyKompens));
	ui.tableWidget_RozrahSumyKompens->setItemDelegateForColumn(twExt->columnNumber("KilkistPilgovykiv"), new USpinBoxDelegate(0,100000, ui.tableWidget_RozrahSumyKompens));
	ui.tableWidget_RozrahSumyKompens->setItemDelegateForColumn(twExt->columnNumber("KilkistVrahPilgovykiv"), new USpinBoxDelegate(0,100000, ui.tableWidget_RozrahSumyKompens));
	
	ui.tableWidget_RozrahSumyKompens->setColumnHidden(0, true);
	twExt->setColumnWidth("CurDate", 90);
	twExt->setColumnWidth("VyruchkaZagalna", 90);
	twExt->setColumnWidth("TaryfZaPasajKm", 90);
	twExt->setColumnWidth("KilkistPlatnPasaj", 90);
	twExt->setColumnWidth("Koef", 90);
	twExt->setColumnWidth("KilkistPilgovykiv", 90);
	twExt->setColumnWidth("KilkistVrahPilgovykiv", 90);
	twExt->setColumnWidth("Prymitka", 300);
	
	twExt->populateTable();
	
	connect(ui.pushButton_create, SIGNAL(clicked()), this, SLOT(pushButton_create_clicked()));
	connect(ui.pushButton_delete, SIGNAL(clicked()), this, SLOT(pushButton_delete_clicked()));
	connect(ui.pushButton_reload, SIGNAL(clicked()), twExt, SLOT(populateTable()));
	
	connect(ui.pushButton_avtozapovn, SIGNAL(clicked()), this, SLOT(pushButton_avtozapovn_clicked()));
	
	connect(twExt, SIGNAL(tableItemEdited(QTableWidgetItem *)), this, SLOT(populateDovidnykValues(QTableWidgetItem *)));
	
	connect(ui.action_printSumaKompensPoPilgah, SIGNAL(activated()), this, SLOT(action_printSumaKompensPoPilgah_activated()));
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkRozrahSumyKompensPoPilgah::pushButton_create_clicked()
{
	if (!twExt->addRow("INSERT INTO pilgyAParkPokazn (CurDate) VALUES ('"+QDate::currentDate().toString("yyyy-MM-")+"01')"))
		QMessageBox::critical(0,"Помилка створення запису","Запис шляхового листа не створено не створено");
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkRozrahSumyKompensPoPilgah::pushButton_delete_clicked()
{
	if	( QMessageBox::question(
                this,
                "!!! Видалення стрічки !!!",
                "Ви дійсно бажаєте видалити стрічку?",
                "Так",
				"Ні-ні-ні",
                QString(), 0, 1)
		)
		return;
	if (!twExt->deleteRow())
		QMessageBox::critical(0,"Помикла видалення запису","Запис не видалено");
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkRozrahSumyKompensPoPilgah::pushButton_avtozapovn_clicked()
{
	if	( QMessageBox::question(
                this,
                "Автозаповнення стрічки",
                "Ви дійсно бажаєте здійснити автозаповнення стрічки?\nПри цьому, старі дані будуть змінені на нові.",
                "Так",
				"Ні-ні-ні",
                QString(), 0, 1)
		)
		return;
	
	QSqlQuery query;
	UWorkMonth wMonth(twExt->currentItemData("CurDate").toDate());
	query.exec("SELECT sum(KilkProdKvytkiv), sum(KilkProdKvytkivAutoStat), \
						sum(VartProdKvytkiv), sum(VartProdKvytkivAutoStat), \
						sum(PilgoviPasajyry) \
				FROM shlyahovyiLyst \
				WHERE date(ToZvitDate) BETWEEN date("+sqlStr(wMonth.begDate())+") \
					AND date("+sqlStr(wMonth.endDate())+")");
	if (query.next()){
		twExt->setCurrentItemData("VyruchkaZagalna", query.value(2).toDouble()+query.value(3).toDouble());
		twExt->setCurrentItemData("KilkistPlatnPasaj", query.value(0).toDouble()+query.value(1).toDouble());
		twExt->setCurrentItemData("KilkistPilgovykiv", query.value(4).toDouble());
	}
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkRozrahSumyKompensPoPilgah::populateDovidnykValues(QTableWidgetItem *item)
{

}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkRozrahSumyKompensPoPilgah::populateToolBar(QToolBar * tBar)
{
	tBar->addAction(ui.action_printSumaKompensPoPilgah);
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkRozrahSumyKompensPoPilgah::action_printSumaKompensPoPilgah_activated()
{
	UPrintDocs_APark *printDocs = new UPrintDocs_APark();
	printDocs->print_RozrahSumyKompensPoPilgah(ui.tableWidget_RozrahSumyKompens->item(ui.tableWidget_RozrahSumyKompens->currentRow(),0)->data(Qt::DisplayRole).toInt());
	connect(this, SIGNAL(mainWindowClosed()), printDocs->printform, SLOT(close()));
	delete printDocs;
}
//--------------------utech--------------------utech--------------------utech--------------------
UForm_AParkRozrahSumyKompensPoPilgah::~UForm_AParkRozrahSumyKompensPoPilgah()
{
	
}
//--------------------utech--------------------utech--------------------utech--------------------
