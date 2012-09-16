//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл виконання класу вікна налаштування програми
//
// Створений програмістами Компанії "Утех" 29.03.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------
#include "UForm_AParkProbigInfo.h"

#include "UDifFunc_APark.h"
#include "UPrintDocs_APark.h"
#include "UDialog_AParkDateFilter.h"
#include "UDialog_AParkAutobusDateFilter.h"
#include <UStandardDelegate>

#include <QtDebug>
//--------------------utech--------------------utech--------------------utech--------------------
UForm_AParkProbigInfo::UForm_AParkProbigInfo(int tWType, QWidget *parent)
        : UAParkTabWidget(tWType, parent)
{
	ui.setupUi(this);
	
	ui.radioButton_NeedTO->setChecked(true);
	ui.radioButton_TO1_TO2->setChecked(true);
	
	ui.tableWidget_ProbigInfo->setColumnWidth(0, 250);
	
	populateTableWidget();
	
	connect(ui.pushButton_reload, SIGNAL(clicked()), this, SLOT(populateTableWidget()));
	
	connect(ui.radioButton_NeedTO, SIGNAL(released()), this, SLOT(populateTableWidget()));
	connect(ui.radioButton_NotFarTo, SIGNAL(released()), this, SLOT(populateTableWidget()));
	connect(ui.radioButton_TO1_TO2, SIGNAL(released()), this, SLOT(populateTableWidget()));
	connect(ui.radioButton_TO1, SIGNAL(released()), this, SLOT(populateTableWidget()));
	connect(ui.radioButton_TO2, SIGNAL(released()), this, SLOT(populateTableWidget()));
	
	connect(ui.action_PrintMisyachnyiProbigUsihAvtobusiv, SIGNAL(activated()), this, SLOT(action_PrintMisyachnyiProbigUsihAvtobusiv_activated())); 
	connect(ui.action_PrintMisyachnyiProbigOneAvtobus, SIGNAL(activated()), this, SLOT(action_PrintMisyachnyiProbigOneAvtobus_activated())); 
	connect(ui.action_PrintPerelikAvtobusivNaTO, SIGNAL(activated()), this, SLOT(action_PrintPerelikAvtobusivNaTO_activated())); 
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkProbigInfo::populateToolBar(QToolBar * tBar)
{
	tBar->addAction(ui.action_PrintMisyachnyiProbigUsihAvtobusiv);
	tBar->addAction(ui.action_PrintMisyachnyiProbigOneAvtobus);
	tBar->addAction(ui.action_PrintPerelikAvtobusivNaTO);
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkProbigInfo::populateTableWidget()
{
	QString autoTOFiltr;
	if (ui.radioButton_NeedTO->isChecked())
		autoTOFiltr = " WHERE IF(autoTONum.PrevTONum=1,ruhomyiSklad.TO2,ruhomyiSklad.TO1)<=autoProbig.ZagProbig ";
	else
		autoTOFiltr = " WHERE IF(autoTONum.PrevTONum=1,ruhomyiSklad.TO2,ruhomyiSklad.TO1)-autoProbig.ZagProbig < 500 \
					AND IF(autoTONum.PrevTONum=1,ruhomyiSklad.TO2,ruhomyiSklad.TO1)-autoProbig.ZagProbig > 0 ";
	
	if (ui.radioButton_TO1->isChecked())
		autoTOFiltr += " AND IF(autoTONum.PrevToNum=1,2,1)=1 ";
	else if (ui.radioButton_TO2->isChecked())
		autoTOFiltr += " AND IF(autoTONum.PrevToNum=1,2,1)=2 ";
	
	QSqlQuery query;
	query.exec("SELECT count(*)	FROM ((ruhomyiSklad \
				LEFT JOIN (SELECT GarajNum_Id, sum(ZagalnProbig) AS ZagProbig FROM shlyahovyiLyst \
						WHERE DATE(DataVyizdu)>=(SELECT max(TOLog.TODate) FROM TOLog WHERE TOLog.GarajNum_id=shlyahovyiLyst.GarajNum_Id) \
							OR (SELECT max(TOLog.TODate) FROM TOLog WHERE TOLog.GarajNum_id=shlyahovyiLyst.GarajNum_Id) IS NULL \
						GROUP BY GarajNum_Id) AS autoProbig \
					ON autoProbig.GarajNum_Id=ruhomyiSklad.GarajNumber) \
				LEFT JOIN (SELECT GarajNum_id, TONum AS PrevToNum FROM TOLog t \
						WHERE TODate=(SELECT max(TOLog.TODate) FROM TOLog WHERE TOLog.GarajNum_id=t.GarajNum_Id)) AS autoTONum \
					ON autoTONum.GarajNum_id=ruhomyiSklad.GarajNumber) \
				LEFT JOIN MarkaAuto ON MarkaAuto.id=ruhomyiSklad.MarkaAuto_Id "+autoTOFiltr);
	query.seek(0);
	int rowCount = query.value(0).toInt();
	ui.tableWidget_ProbigInfo->setRowCount(rowCount);
	query.exec("SELECT ruhomyiSklad.GarajNumber, IF(autoTONum.PrevToNum=1,ruhomyiSklad.TO2,ruhomyiSklad.TO1) AS probigForTO, \
					autoProbig.ZagProbig, autoTONum.PrevTONum, IF(autoTONum.PrevToNum=1,2,1) AS needToNum, \
					MarkaAuto.MarkaName, MarkaAuto.MarkaShyfr, ruhomyiSklad.NomernyiZnak \
				FROM ((ruhomyiSklad \
				LEFT JOIN (SELECT GarajNum_Id, sum(ZagalnProbig) AS ZagProbig FROM shlyahovyiLyst \
						WHERE DATE(DataVyizdu)>=(SELECT max(TOLog.TODate) FROM TOLog WHERE TOLog.GarajNum_id=shlyahovyiLyst.GarajNum_Id) \
							OR (SELECT max(TOLog.TODate) FROM TOLog WHERE TOLog.GarajNum_id=shlyahovyiLyst.GarajNum_Id) IS NULL \
						GROUP BY GarajNum_Id) AS autoProbig \
					ON autoProbig.GarajNum_Id=ruhomyiSklad.GarajNumber) \
				LEFT JOIN (SELECT GarajNum_id, TONum AS PrevToNum FROM TOLog t \
						WHERE TODate=(SELECT max(TOLog.TODate) FROM TOLog WHERE TOLog.GarajNum_id=t.GarajNum_Id)) AS autoTONum \
					ON autoTONum.GarajNum_id=ruhomyiSklad.GarajNumber) \
				LEFT JOIN MarkaAuto ON MarkaAuto.id=ruhomyiSklad.MarkaAuto_Id "+autoTOFiltr);
	
	for (int row=0; row<rowCount && query.next(); ++row){
		setItemData(row, 0, "№"+query.value(0).toString()+" ["+query.value(7).toString()+"] - "+query.value(6).toString());
		setItemData(row, 1, query.value(4));
		setItemData(row, 2, query.value(2));
		setItemData(row, 3, query.value(1));
		setItemData(row, 4, query.value(2).toDouble() - query.value(1).toDouble());
		ui.tableWidget_ProbigInfo->resizeRowToContents(row);
	}
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkProbigInfo::setItemData(int row, int col, QVariant data)
{
	QTableWidgetItem *item = new QTableWidgetItem();
	item->setData(Qt::EditRole, data);
	item->setTextAlignment(Qt::AlignVCenter | Qt::AlignRight);
	ui.tableWidget_ProbigInfo->setItem(row, col, item);
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkProbigInfo::action_PrintMisyachnyiProbigUsihAvtobusiv_activated()
{
	QDate cDate = QDate::currentDate();
	UDialog_AParkDateFilter *dialog = new UDialog_AParkDateFilter(cDate.year(), cDate.month(), "Вибір місяця", this);
	if (dialog->exec()){
		UPrintDocs_APark *printDocs = new UPrintDocs_APark();
		printDocs->print_misyachnyiProbigUsihAvtobusiv(dialog->year(), dialog->month());
		connect(this, SIGNAL(mainWindowClosed()), printDocs->printform, SLOT(close()));
		delete printDocs;
	}
	delete dialog;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkProbigInfo::action_PrintMisyachnyiProbigOneAvtobus_activated()
{
	QDate cDate = QDate::currentDate();
	UDialog_AParkAutobusDateFilter *dialog = new UDialog_AParkAutobusDateFilter(cDate.year(), cDate.month(), "Вибір місяця", this);
	if (dialog->exec()){
		UPrintDocs_APark *printDocs = new UPrintDocs_APark();
		printDocs->print_misyachnyiProbigOdnogoAvtobusa(dialog->year(), dialog->month(), dialog->garajNumber());
		connect(this, SIGNAL(mainWindowClosed()), printDocs->printform, SLOT(close()));
		delete printDocs;
	}
	delete dialog;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkProbigInfo::action_PrintPerelikAvtobusivNaTO_activated()
{
	UPrintDocs_APark *printDocs = new UPrintDocs_APark();
	short TONum=0;
	if (ui.radioButton_TO1->isChecked())
		TONum = 1;
	else if (ui.radioButton_TO2->isChecked())
		TONum = 2;
	printDocs->print_perelikAvtobusivNaTO(TONum);
	connect(this, SIGNAL(mainWindowClosed()), printDocs->printform, SLOT(close()));
	delete printDocs;
}
//--------------------utech--------------------utech--------------------utech--------------------
UForm_AParkProbigInfo::~UForm_AParkProbigInfo()
{
	
}
//--------------------utech--------------------utech--------------------utech--------------------
