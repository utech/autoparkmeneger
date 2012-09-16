//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл виконання класу вікна налаштування програми
//
// Створений програмістами Компанії "Утех" 25.03.2010р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------
#include "UForm_AParkKartkyRobotyVodiyiv.h"

#include "UDifFunc_APark.h"
#include "UPrintDocs_APark.h"
#include <UStandardDelegate>

#include <QtDebug>

#define FIRST_PALNE_COLUMN 1
//--------------------utech--------------------utech--------------------utech--------------------
UForm_AParkKartkyRobotyVodiyiv::UForm_AParkKartkyRobotyVodiyiv(int tWType, QWidget *parent)
        : UAParkTabWidget(tWType, parent)
{
	ui.setupUi(this);
	ui.dateEdit_monthFilter->setDate(QDate::currentDate());
	ui.tableWidget_vidiyi->setColumnCount(3);
	QTableWidgetItem *item;
	item = new QTableWidgetItem();
	item->setData(Qt::DisplayRole, "Таб.номер");
	ui.tableWidget_vidiyi->setHorizontalHeaderItem(0, item);
	item = new QTableWidgetItem();
	item->setData(Qt::DisplayRole, "ПІБ");
	ui.tableWidget_vidiyi->setHorizontalHeaderItem(1, item);
	item = new QTableWidgetItem();
	item->setData(Qt::DisplayRole, "К-сть записів");
	ui.tableWidget_vidiyi->setHorizontalHeaderItem(2, item);
	ui.tableWidget_vidiyi->setColumnWidth(0, 70);
	ui.tableWidget_vidiyi->setColumnWidth(1, 250);
	ui.tableWidget_vidiyi->setColumnWidth(2, 100);
	
	ui.tableWidget_vidiyi->addAction(ui.action_printKartkyRobotyVodiyiv);
	ui.tableWidget_vidiyi->setContextMenuPolicy(Qt::ActionsContextMenu);
	
	populateTable();
	
	connect(ui.dateEdit_monthFilter, SIGNAL(dateChanged(const QDate &)), this,SLOT(populateTable()));
	connect(ui.pushButton_reload, SIGNAL(clicked()), this,SLOT(populateTable()));
	connect(ui.action_printKartkyRobotyVodiyiv, SIGNAL(activated()), this,SLOT(action_printKartkyRobotyVodiyiv_activated()));
	connect(ui.tableWidget_vidiyi, SIGNAL(itemDoubleClicked(QTableWidgetItem *)), this,SLOT(tableWidget_vidiyi_itemDoubleClicked(QTableWidgetItem *)));
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkKartkyRobotyVodiyiv::populateToolBar(QToolBar * tBar)
{
	tBar->addAction(ui.action_printKartkyRobotyVodiyiv);
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkKartkyRobotyVodiyiv::populateTable()
{
	ui.tableWidget_vidiyi->setSortingEnabled(false);
	
	UWorkMonth wMonth(ui.dateEdit_monthFilter->date().year(), ui.dateEdit_monthFilter->date().month());
	QSqlQuery query;
	QTableWidgetItem *item;
	query.exec("SELECT count(*) FROM npr WHERE Posada_id=10");
	query.next();
	int rowCount = query.value(0).toInt(), row;
	ui.tableWidget_vidiyi->setRowCount(rowCount);
	
	query.exec("SELECT npr.id, npr.Prizv, npr.Imia, npr.Pobatk, s.shlahLystCount FROM npr \
				LEFT JOIN (SELECT VodiyTabelNum_id, count(*) AS shlahLystCount FROM shlyahovyiLyst \
							WHERE ToZvitDate BETWEEN date("+sqlStr(wMonth.begDate())+") \
								AND date("+sqlStr(wMonth.endDate())+") \
							GROUP BY VodiyTabelNum_id) AS s \
				ON s.VodiyTabelNum_id=npr.id \
				WHERE npr.Posada_id=10\
				ORDER BY npr.Prizv, npr.Imia, npr.Pobatk");
	for (row=0; row<rowCount && query.next(); ++row){
		//Таб. номер
		item = new QTableWidgetItem();
		item->setData(Qt::DisplayRole, query.value(0));
		item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
		ui.tableWidget_vidiyi->setItem(row, 0, item);
		//ПІБ
		item = new QTableWidgetItem();
		item->setData(Qt::DisplayRole, query.value(1).toString()+" "+query.value(2).toString()+" "+query.value(3).toString());
		item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
		ui.tableWidget_vidiyi->setItem(row, 1, item);
		//Кількість шляхових листів
		item = new QTableWidgetItem();
		item->setData(Qt::DisplayRole, query.value(4).toString());
		item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
		ui.tableWidget_vidiyi->setItem(row, 2, item);
	}
	ui.tableWidget_vidiyi->resizeRowsToContents();
	
	ui.tableWidget_vidiyi->setSortingEnabled(true);
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkKartkyRobotyVodiyiv::action_printKartkyRobotyVodiyiv_activated()
{
	QModelIndexList list = ui.tableWidget_vidiyi->selectionModel()->selectedRows(0);
	if (list.count() == 0){
		QMessageBox::critical(0,"Помилка", "Для друку карток Вам необхідно обрати\nперелік працівників у таблиці");
		return;
	}
	
	QList<int> vodiyiList;
	foreach (QModelIndex ind, list){
		vodiyiList.append(ind.data().toInt());
	}
	
	UPrintDocs_APark *printDocs = new UPrintDocs_APark();
	printDocs->print_KartkyRobotyVodiyiv(ui.dateEdit_monthFilter->date(), vodiyiList);
	connect(this, SIGNAL(mainWindowClosed()), printDocs->printform, SLOT(close()));
	delete printDocs;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkKartkyRobotyVodiyiv::tableWidget_vidiyi_itemDoubleClicked(QTableWidgetItem *item)
{
	UPrintDocs_APark *printDocs = new UPrintDocs_APark();
	QList<int> vodiyiList;
	vodiyiList.append(ui.tableWidget_vidiyi->item(item->row(), 0)->data(Qt::DisplayRole).toInt());
	
	printDocs->print_KartkyRobotyVodiyiv(ui.dateEdit_monthFilter->date(), vodiyiList);
	connect(this, SIGNAL(mainWindowClosed()), printDocs->printform, SLOT(close()));
	delete printDocs;
}
//--------------------utech--------------------utech--------------------utech--------------------
UForm_AParkKartkyRobotyVodiyiv::~UForm_AParkKartkyRobotyVodiyiv()
{
	
}
//--------------------utech--------------------utech--------------------utech--------------------
