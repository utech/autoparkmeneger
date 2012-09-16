//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл виконання класу вікна налаштування програми
//
// Створений програмістами Компанії "Утех" 29.03.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------
#include "UForm_AParkCinaPalnogo.h"

#include "UDifFunc_APark.h"
#include <UStandardDelegate>

#include <QtDebug>

#define FIRST_PALNE_COLUMN 1
//--------------------utech--------------------utech--------------------utech--------------------
UForm_AParkCinaPalnogo::UForm_AParkCinaPalnogo(int tWType, QWidget *parent)
        : UAParkTabWidget(tWType, parent)
{
	ui.setupUi(this);
	ui.spinBox_yearFilter->setValue(QDate::currentDate().year());
	
	
	populateCinaPalnogoTable();
	
	connect(ui.spinBox_yearFilter, SIGNAL(valueChanged(int)), this,SLOT(populateCinaPalnogoTable()));
	connect(ui.pushButton_reload, SIGNAL(clicked()), this,SLOT(populateCinaPalnogoTable()));
	connect(ui.pushButton_create, SIGNAL(clicked()), this,SLOT(pushButton_create_clicked()));
	connect(ui.pushButton_delete, SIGNAL(clicked()), this,SLOT(pushButton_delete_clicked()));
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkCinaPalnogo::populateToolBar(QToolBar * tBar)
{

}
//--------------------utech--------------------utech--------------------utech--------------------
/*
Ціни на пальне відображаються у зведеній таблиці, де по вертикалі іде динаміка в часі,
  а по горизонталі перелік марок пального.
Вертикальна заголовкова комірка містить ідентифікатор дати.
Горизонтальна заголовкова комірка містить ідентифікатор пального в UserRole і 
  назву пального в DisplayRole
Для визначення номера стовбця з певним ідентифікатором пального використовується
  хеш palneIdHash<col, id>
*/
void UForm_AParkCinaPalnogo::populateCinaPalnogoTable()
{
	disconnect(ui.tableWidget_cinaPalnogo, SIGNAL(itemChanged(QTableWidgetItem *)), this,SLOT(saveItem(QTableWidgetItem *)));
	
	QTableWidgetItem *item;
	QSqlQuery query, cinaQuery;
	int iter;
	
	//горизонтальні заголовки, заповнення palneIdHash
	ui.tableWidget_cinaPalnogo->clear();
	palneIdHash.clear();
	query.exec("SELECT Id, MarkaName FROM markapalnogo ORDER BY Id");
	for (iter = FIRST_PALNE_COLUMN; query.next(); iter++)
		palneIdHash.insert(iter, query.value(0).toInt());
	ui.tableWidget_cinaPalnogo->setColumnCount(palneIdHash.count() + FIRST_PALNE_COLUMN + 1);
	query.seek(-1);
	for (iter = FIRST_PALNE_COLUMN; query.next(); iter++){
		item = new QTableWidgetItem();
		item->setData(Qt::UserRole, query.value(0).toInt());
		item->setData(Qt::DisplayRole, query.value(1).toString());
		ui.tableWidget_cinaPalnogo->setHorizontalHeaderItem(iter, item);
	}
	item = new QTableWidgetItem();
	item->setData(Qt::DisplayRole, "Дата");
	ui.tableWidget_cinaPalnogo->setHorizontalHeaderItem(FIRST_PALNE_COLUMN-1, item);
	item = new QTableWidgetItem();
	item->setData(Qt::DisplayRole, "Примітка");
	ui.tableWidget_cinaPalnogo->setHorizontalHeaderItem(palneIdHash.count() + FIRST_PALNE_COLUMN, item);
	
	//Заповнення по датах
	query.exec("SELECT count(*) FROM cinaPalnogoDate WHERE year(CDate)="+sqlStr(ui.spinBox_yearFilter->value()));
	query.next();
	ui.tableWidget_cinaPalnogo->setRowCount(query.value(0).toInt());
	query.exec("SELECT id, CDate, Prymitka FROM cinaPalnogoDate \
				WHERE year(CDate)="+sqlStr(ui.spinBox_yearFilter->value())+" ORDER BY CDate");
	for (int row=0; row<ui.tableWidget_cinaPalnogo->rowCount() && query.next(); row++){
		item = new QTableWidgetItem();
		item->setData(Qt::UserRole, query.value(0));
		ui.tableWidget_cinaPalnogo->setVerticalHeaderItem(row, item);
		item = new QTableWidgetItem();
		item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
		item->setData(Qt::EditRole, query.value(1));
		ui.tableWidget_cinaPalnogo->setItem(row, FIRST_PALNE_COLUMN-1,item);
		item = new QTableWidgetItem();
		item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
		item->setData(Qt::EditRole, query.value(2));
		ui.tableWidget_cinaPalnogo->setItem(row, palneIdHash.count() + FIRST_PALNE_COLUMN, item);
		
		for (iter = 0; iter<palneIdHash.count(); iter++){
			item = new QTableWidgetItem();
			item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
			ui.tableWidget_cinaPalnogo->setItem(row, iter+FIRST_PALNE_COLUMN,item);
		}
		
		cinaQuery.exec("SELECT Palne_id, Cina FROM cinaPalnogo \
						WHERE CinaPalnogoDate_id="+query.value(0).toString());
		while (cinaQuery.next())
			ui.tableWidget_cinaPalnogo->item(row, palneIdHash.key(cinaQuery.value(0).toInt()))->
						setData(Qt::EditRole, cinaQuery.value(1).toDouble());	
	}
	
	//Заповнення делегатів
	ui.tableWidget_cinaPalnogo->setItemDelegateForColumn(FIRST_PALNE_COLUMN-1, 
				new UDateEditDelegate(QDate(2005,01,01), QDate(2100,12,31), ui.tableWidget_cinaPalnogo));
	//ширина дати
	ui.tableWidget_cinaPalnogo->setColumnWidth(FIRST_PALNE_COLUMN-1, 70);
	for (iter=0; iter<palneIdHash.count(); iter++){
		ui.tableWidget_cinaPalnogo->setItemDelegateForColumn(FIRST_PALNE_COLUMN+iter, 
				new UDoubleSpinBoxDelegate(0,1000,2, ui.tableWidget_cinaPalnogo));
		//ширина ціни
		ui.tableWidget_cinaPalnogo->setColumnWidth(FIRST_PALNE_COLUMN+iter, 60);
	}
	//ширина Примітки
	ui.tableWidget_cinaPalnogo->setColumnWidth(FIRST_PALNE_COLUMN+palneIdHash.count(), 130);
	
	ui.tableWidget_cinaPalnogo->resizeRowsToContents();
	
	connect(ui.tableWidget_cinaPalnogo, SIGNAL(itemChanged(QTableWidgetItem *)), this,SLOT(saveItem(QTableWidgetItem *)));
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkCinaPalnogo::pushButton_create_clicked()
{
	disconnect(ui.tableWidget_cinaPalnogo, SIGNAL(itemChanged(QTableWidgetItem *)), this,SLOT(saveItem(QTableWidgetItem *)));
	
	QSqlQuery query;
	if (!query.exec("INSERT INTO cinaPalnogoDate(CDate) VALUES("+sqlStr(QDate::currentDate())+")")){
		QMessageBox::critical(this, "Помилка", "Помилка створення стрічки цін на пальне");
		connect(ui.tableWidget_cinaPalnogo, SIGNAL(itemChanged(QTableWidgetItem *)), this,SLOT(saveItem(QTableWidgetItem *)));
		return;
	}
	query.exec("SELECT last_insert_id()");
	query.next();
	int dateId = query.value(0).toInt();
	int row = ui.tableWidget_cinaPalnogo->rowCount();
	ui.tableWidget_cinaPalnogo->setRowCount(row+1);
	QTableWidgetItem * item = new QTableWidgetItem();
	item->setData(Qt::UserRole, dateId);
	ui.tableWidget_cinaPalnogo->setVerticalHeaderItem(row, item);
	item = new QTableWidgetItem();
	item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
	item->setData(Qt::EditRole, QDate::currentDate());
	ui.tableWidget_cinaPalnogo->setItem(row,FIRST_PALNE_COLUMN-1,item);
	
	//вирівнювання для цін
	for (int iter = 0; iter<palneIdHash.count(); iter++){
		item = new QTableWidgetItem();
		item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
		ui.tableWidget_cinaPalnogo->setItem(row, iter+FIRST_PALNE_COLUMN,item);
	}
	
	ui.tableWidget_cinaPalnogo->resizeRowToContents(row);
	item = ui.tableWidget_cinaPalnogo->item(row, FIRST_PALNE_COLUMN -1);
	ui.tableWidget_cinaPalnogo->setCurrentItem(item);
	ui.tableWidget_cinaPalnogo->scrollToItem(item);
	ui.tableWidget_cinaPalnogo->editItem(item);
	
	connect(ui.tableWidget_cinaPalnogo, SIGNAL(itemChanged(QTableWidgetItem *)), this,SLOT(saveItem(QTableWidgetItem *)));
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkCinaPalnogo::pushButton_delete_clicked()
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
	
	QModelIndexList selList = ui.tableWidget_cinaPalnogo->selectionModel()->selectedRows();
	if (!selList.count()){
		QMessageBox::information(this, "Порада", "Ви не обрали жодної стрічки для видалення.\nОберіть хоч одну стрічку для видалення");
		return;
	}
	disconnect(ui.tableWidget_cinaPalnogo, SIGNAL(itemChanged(QTableWidgetItem *)), this,SLOT(saveItem(QTableWidgetItem *)));
	
	int dateId, row;
	bool doneOkCur;
	bool doneOkAll=true;
	QSqlQuery query;
	QList<int> idList;
	foreach(QModelIndex index, selList){
		row = index.row();
		dateId = ui.tableWidget_cinaPalnogo->verticalHeaderItem(row)->data(Qt::UserRole).toInt();
		doneOkCur = query.exec("DELETE FROM cinaPalnogoDate WHERE id="+sqlStr(dateId));
		query.exec("DELETE FROM cinaPalnogo WHERE cinaPalnogoDate_id="+sqlStr(dateId));
		if (doneOkCur)
			idList << dateId;
		else
			doneOkAll = false;
		//ui.tableWidget_cinaPalnogo->removeRow(row);
	}
	for (row=0; row<ui.tableWidget_cinaPalnogo->rowCount(); row++){
		dateId = ui.tableWidget_cinaPalnogo->verticalHeaderItem(row)->data(Qt::UserRole).toInt();
		if (idList.contains(dateId)){
			ui.tableWidget_cinaPalnogo->removeRow(row);
			--row;
			if (!idList.removeOne(dateId))
				doneOkAll = false;
		}
	}
	if (!doneOkAll)
		QMessageBox::critical(this, "Помилка", "Програма не змогла видалити одну або декілька стрічок");
	
	connect(ui.tableWidget_cinaPalnogo, SIGNAL(itemChanged(QTableWidgetItem *)), this,SLOT(saveItem(QTableWidgetItem *)));
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkCinaPalnogo::saveItem(QTableWidgetItem *item)
{
	disconnect(ui.tableWidget_cinaPalnogo, SIGNAL(itemChanged(QTableWidgetItem *)), this,SLOT(saveItem(QTableWidgetItem *)));
	
	int col = item->column();
	int row = item->row();
	QSqlQuery query;
	
	if (col == FIRST_PALNE_COLUMN-1){ // збереження дати цін на пальне
		query.exec("UPDATE cinaPalnogoDate SET CDate="+sqlStr(item->data(Qt::EditRole).toDate())+" \
					WHERE id="+ui.tableWidget_cinaPalnogo->verticalHeaderItem(row)->data(Qt::UserRole).toString());
		query.exec("SELECT CDate FROM cinaPalnogoDate \
					WHERE id="+ui.tableWidget_cinaPalnogo->verticalHeaderItem(row)->data(Qt::UserRole).toString());
		query.next();
		item->setData(Qt::EditRole, query.value(0));
	}
	else if (col >= FIRST_PALNE_COLUMN 
			&& col<=(FIRST_PALNE_COLUMN+palneIdHash.count()-1)){ // збереження цін на пальне
		
		query.exec("SELECT id FROM CinaPalnogo \
					WHERE Palne_id="+sqlStr(ui.tableWidget_cinaPalnogo->horizontalHeaderItem(col)->data(Qt::UserRole).toInt())+" \
						and CinaPalnogoDate_id="+sqlStr(ui.tableWidget_cinaPalnogo->verticalHeaderItem(row)->data(Qt::UserRole).toInt())+"");
		int cinaId = query.next()?query.value(0).toInt():0;
		if (cinaId){ //зміна запису
			query.exec("UPDATE CinaPalnogo SET Cina="+sqlStr(item->data(Qt::EditRole).toDouble())+" \
						WHERE id="+sqlStr(cinaId));
		}
		else{ //створення запису
			bool ok = query.exec("INSERT INTO CinaPalnogo(Palne_id, CinaPalnogoDate_id, Cina) \
						VALUES ( "+sqlStr(ui.tableWidget_cinaPalnogo->horizontalHeaderItem(col)->data(Qt::UserRole).toInt())+", \
								"+sqlStr(ui.tableWidget_cinaPalnogo->verticalHeaderItem(row)->data(Qt::UserRole).toInt())+", \
								"+sqlStr(item->data(Qt::EditRole).toDouble())+")");
			if (ok){
				query.exec("SELECT last_insert_id()");
				query.next();
				cinaId = query.value(0).toInt();
			}
		}
		//зворотній зв'язок
		query.exec("SELECT Cina FROM CinaPalnogo WHERE id="+sqlStr(cinaId));
		query.next();
		item->setData(Qt::EditRole, query.value(0).toDouble());
	}
	else if (col == FIRST_PALNE_COLUMN+palneIdHash.count()){ //збереження примітка
		query.exec("UPDATE cinaPalnogoDate SET Prymitka="+sqlStr(item->data(Qt::EditRole).toString())+" \
					WHERE id="+ui.tableWidget_cinaPalnogo->verticalHeaderItem(row)->data(Qt::UserRole).toString());
		query.exec("SELECT Prymitka FROM cinaPalnogoDate \
					WHERE id="+ui.tableWidget_cinaPalnogo->verticalHeaderItem(row)->data(Qt::UserRole).toString());
		query.next();
		item->setData(Qt::EditRole, query.value(0));
	}
	
	connect(ui.tableWidget_cinaPalnogo, SIGNAL(itemChanged(QTableWidgetItem *)), this,SLOT(saveItem(QTableWidgetItem *)));
}
//--------------------utech--------------------utech--------------------utech--------------------
UForm_AParkCinaPalnogo::~UForm_AParkCinaPalnogo()
{
	
}
//--------------------utech--------------------utech--------------------utech--------------------
