//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл виконання класу вікна налаштування програми
//
// Створений програмістами Компанії "Утех" 29.03.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------
#include "UForm_AParkKartkyOblikuVykonannyaPlanu.h"

#include "UDifFunc_APark.h"
#include "UPrintDocs_APark.h"

#include <QtDebug>
//--------------------utech--------------------utech--------------------utech--------------------
UForm_AParkKartkyOblikuVykonannyaPlanu::UForm_AParkKartkyOblikuVykonannyaPlanu(int tWType, QWidget *parent)
        : UAParkTabWidget(tWType, parent)
{
	ui.setupUi(this);
	ui.dateEdit_endMonth->setDate(QDate::currentDate());
	
	ui.tableWidget_vodiiPidpryemstva->setColumnWidth(0,60);
	ui.tableWidget_vodiiPidpryemstva->setColumnWidth(1,230);
	
	populateVodiyiTable();
	
	connect(ui.action_printKartkyOblikuVykonPlanu, SIGNAL(activated()), this, SLOT(action_printKartkyOblikuVykonPlanu_activated()));
	connect(ui.tableWidget_vodiiPidpryemstva, SIGNAL(itemDoubleClicked(QTableWidgetItem *)), this, SLOT(action_printKartkyOblikuVykonPlanu_activated()));
	connect(ui.pushButton_printCards, SIGNAL(clicked(bool)), this, SLOT(action_printKartkyOblikuVykonPlanu_activated()));
	connect(ui.pushButton_reload, SIGNAL(clicked(bool)), this, SLOT(populateVodiyiTable()));
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkKartkyOblikuVykonannyaPlanu::populateVodiyiTable()
{
	QSqlQuery query;
	query.exec("SELECT Znach FROM progOptionsAPark WHERE id=1");
	query.seek(0);
	int vodoyiId = query.value(0).toInt();
	query.exec("SELECT count(*) FROM npr WHERE posada_id="+QString::number(vodoyiId));
	query.seek(0);
	int rowCount = query.value(0).toInt();
	ui.tableWidget_vodiiPidpryemstva->setRowCount(rowCount);
	query.exec("SELECT id, Prizv, Imia, Pobatk FROM npr WHERE posada_id="+QString::number(vodoyiId)+" ORDER BY Prizv, Imia, Pobatk");
	for (int row=0; row<rowCount && query.next(); ++row){
		QTableWidgetItem *item = new QTableWidgetItem();
		item->setData(Qt::DisplayRole, query.value(0));
		item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
		ui.tableWidget_vodiiPidpryemstva->setItem(row, 0, item);
		item = new QTableWidgetItem();
		item->setText(query.value(1).toString()+" "+query.value(2).toString()+" "+query.value(3).toString());
		item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
		ui.tableWidget_vodiiPidpryemstva->setItem(row, 1, item);
	}
	ui.tableWidget_vodiiPidpryemstva->resizeRowsToContents();
	if (rowCount>0)
		ui.tableWidget_vodiiPidpryemstva->setCurrentCell(0,0);
	
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkKartkyOblikuVykonannyaPlanu::populateToolBar(QToolBar * tBar)
{
	tBar->addAction(ui.action_printKartkyOblikuVykonPlanu);
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkKartkyOblikuVykonannyaPlanu::action_printKartkyOblikuVykonPlanu_activated()
{
	QModelIndexList list = ui.tableWidget_vodiiPidpryemstva->selectionModel()->selectedRows(0);
	if (list.count() == 0){
		QMessageBox::critical(0,"Помилка", "Для друку карток Вам необхідно обрати перелік працівників\nу таблиці \"Водії підприємства\"");
		return;
	}
	
	QList<int> vodiyiList;
	foreach (QModelIndex ind, list){
		vodiyiList.append(ind.data().toInt());
	}
	
	UPrintDocs_APark *printDocs = new UPrintDocs_APark();
	printDocs->print_KartkyOblikuVykonPlanu(ui.dateEdit_endMonth->date(), vodiyiList);
	connect(this, SIGNAL(mainWindowClosed()), printDocs->printform, SLOT(close()));
	delete printDocs;
}
//--------------------utech--------------------utech--------------------utech--------------------
UForm_AParkKartkyOblikuVykonannyaPlanu::~UForm_AParkKartkyOblikuVykonannyaPlanu()
{
	
}
//--------------------utech--------------------utech--------------------utech--------------------
