//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл виконання класу вікна налаштування програми
//
// Створений програмістами Компанії "Утех" 29.03.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------
#include "UForm_AParkPlanNaZminu.h"

#include "UDifFunc_APark.h"
#include "UDialog_AParkDateFilter.h"
#include "UPrintDocs_APark.h"
#include <UStandardDelegate>

#include <QtDebug>

#define FIRST_MARSHRUT_ROW 1
//--------------------utech--------------------utech--------------------utech--------------------
UForm_AParkPlanNaZminu::UForm_AParkPlanNaZminu(int tWType, QWidget *parent)
        : UAParkTabWidget(tWType, parent)
{
	ui.setupUi(this);
	ui.spinBox_yearFilter->setValue(QDate::currentDate().year());
	
	
	populatePlanNaZminuTable();
	
	connect(ui.spinBox_yearFilter, SIGNAL(valueChanged(int)), this,SLOT(populatePlanNaZminuTable()));
	connect(ui.pushButton_reload, SIGNAL(clicked()), this,SLOT(populatePlanNaZminuTable()));
	connect(ui.pushButton_create, SIGNAL(clicked()), this,SLOT(pushButton_create_clicked()));
	connect(ui.pushButton_delete, SIGNAL(clicked()), this,SLOT(pushButton_delete_clicked()));
	connect(ui.action_printPlanyValovyhDohodiv, SIGNAL(activated()), this,SLOT(action_printPlanyValovyhDohodiv_activated()));
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkPlanNaZminu::populateToolBar(QToolBar * tBar)
{
	tBar->addAction(ui.action_printPlanyValovyhDohodiv);
}
//--------------------utech--------------------utech--------------------utech--------------------
/*
План на зміну відображаються у зведеній таблиці, де по вертикалі іде перелік
марштурів, а по горизонталі - дати.
Горизонтальна заголовкова комірка містить ідентифікатор дати.
Вертикальна заголовкова комірка містить ідентифікатор маршруту в UserRole і
номер маршруту - номер графіка - номер зміни  - в DisplayRole
Для визначення номера рядка (маршруту) з певним ідентифікатором пального використовується
  хеш marshrutIdHash<col, id>
*/
void UForm_AParkPlanNaZminu::populatePlanNaZminuTable()
{
	disconnect(ui.tableWidget_PlanNaZminu, SIGNAL(itemChanged(QTableWidgetItem *)), this,SLOT(saveItem(QTableWidgetItem *)));
	
	QTableWidgetItem *item;
	QSqlQuery query, planQuery;
	int iter;
	int col;
	
	//горизонтальні заголовки, заповнення marshrutIdHash
	ui.tableWidget_PlanNaZminu->clear();
	marshrutIdHash.clear();
	query.exec("SELECT id, KodMarshrutu, MarshrutNapryamok, GrafikNum, ZminaNum \
				FROM marshruty \
				ORDER BY KodMarshrutu, GrafikNum, ZminaNum");
	for (iter = FIRST_MARSHRUT_ROW; query.next(); iter++)
		marshrutIdHash.insert(iter, query.value(0).toInt());
	ui.tableWidget_PlanNaZminu->setRowCount(marshrutIdHash.count() + FIRST_MARSHRUT_ROW);
	query.seek(-1);
	for (iter = FIRST_MARSHRUT_ROW; query.next(); iter++){
		item = new QTableWidgetItem();
		item->setData(Qt::UserRole, query.value(0).toInt());
		item->setData(Qt::DisplayRole, query.value(1).toString()+"."+query.value(3).toString()
									+"."+query.value(4).toString()+" "+query.value(2).toString());
		ui.tableWidget_PlanNaZminu->setVerticalHeaderItem(iter, item);
	}
	item = new QTableWidgetItem();
	item->setData(Qt::DisplayRole, "Дата");
	ui.tableWidget_PlanNaZminu->setVerticalHeaderItem(FIRST_MARSHRUT_ROW-1, item);
	
	//Заповнення по датах
	query.exec("SELECT count(*) FROM planNaZminuDate WHERE year(CDate)="+sqlStr(ui.spinBox_yearFilter->value()));
	query.next();
	ui.tableWidget_PlanNaZminu->setColumnCount(query.value(0).toInt());
	query.exec("SELECT id, CDate FROM PlanNaZminuDate \
				WHERE year(CDate)="+sqlStr(ui.spinBox_yearFilter->value())+" ORDER BY CDate");
	for (col=0; col<ui.tableWidget_PlanNaZminu->columnCount() && query.next(); col++){
		item = new QTableWidgetItem();
		item->setData(Qt::UserRole, query.value(0));
		item->setData(Qt::DisplayRole, query.value(1).toDate().toString("dd.MM.yyyy"));
		ui.tableWidget_PlanNaZminu->setHorizontalHeaderItem(col, item);
		item = new QTableWidgetItem();
		item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
		item->setData(Qt::EditRole, query.value(1));
		ui.tableWidget_PlanNaZminu->setItem(FIRST_MARSHRUT_ROW-1, col,item);
		
		for (iter = 0; iter<marshrutIdHash.count(); iter++){
			item = new QTableWidgetItem();
			item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
			ui.tableWidget_PlanNaZminu->setItem(iter+FIRST_MARSHRUT_ROW, col, item);
		}
		
		planQuery.exec("SELECT Marshrut_id, Plan FROM planNaZminu \
						WHERE PlanNaZminuDate_id="+query.value(0).toString());
		while (planQuery.next())
			ui.tableWidget_PlanNaZminu->item(marshrutIdHash.key(planQuery.value(0).toInt()), col)->
						setData(Qt::EditRole, planQuery.value(1).toDouble());	
	}
	
	//Заповнення делегатів
	ui.tableWidget_PlanNaZminu->setItemDelegateForRow(FIRST_MARSHRUT_ROW-1, 
				new UDateEditDelegate(QDate(2005,01,01), QDate(2100,12,31), ui.tableWidget_PlanNaZminu));
	for (iter=0; iter<marshrutIdHash.count(); iter++)
		ui.tableWidget_PlanNaZminu->setItemDelegateForRow(FIRST_MARSHRUT_ROW+iter, 
				new UDoubleSpinBoxDelegate(0,100000,2, ui.tableWidget_PlanNaZminu));
	
	//Налаштування ширини
	for (col = 0; col<ui.tableWidget_PlanNaZminu->columnCount(); col++)
		ui.tableWidget_PlanNaZminu->setColumnWidth(col, 75);
	ui.tableWidget_PlanNaZminu->resizeRowsToContents();
	
	connect(ui.tableWidget_PlanNaZminu, SIGNAL(itemChanged(QTableWidgetItem *)), this,SLOT(saveItem(QTableWidgetItem *)));
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkPlanNaZminu::pushButton_create_clicked()
{
	disconnect(ui.tableWidget_PlanNaZminu, SIGNAL(itemChanged(QTableWidgetItem *)), this,SLOT(saveItem(QTableWidgetItem *)));
	
	QSqlQuery query;
	if (!query.exec("INSERT INTO PlanNaZminuDate(CDate) VALUES("+sqlStr(QDate::currentDate())+")")){
		QMessageBox::critical(this, "Помилка", "Помилка створення стовбця Плану на зміну");
		connect(ui.tableWidget_PlanNaZminu, SIGNAL(itemChanged(QTableWidgetItem *)), this,SLOT(saveItem(QTableWidgetItem *)));
		return;
	}
	query.exec("SELECT last_insert_id()");
	query.next();
	int dateId = query.value(0).toInt();
	int col = ui.tableWidget_PlanNaZminu->columnCount();
	ui.tableWidget_PlanNaZminu->setColumnCount(col+1);
	QTableWidgetItem * item = new QTableWidgetItem();
	item->setData(Qt::UserRole, dateId);
	item->setData(Qt::DisplayRole, QDate::currentDate().toString("dd.MM.yyyy"));
	ui.tableWidget_PlanNaZminu->setHorizontalHeaderItem(col, item);
	item = new QTableWidgetItem();
	item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
	item->setData(Qt::EditRole, QDate::currentDate());
	ui.tableWidget_PlanNaZminu->setItem(FIRST_MARSHRUT_ROW-1,col,item);
	
	//вирівнювання для цін
	for (int iter = 0; iter<marshrutIdHash.count(); iter++){
		item = new QTableWidgetItem();
		item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
		ui.tableWidget_PlanNaZminu->setItem(iter+FIRST_MARSHRUT_ROW, col,item);
	}
	
	ui.tableWidget_PlanNaZminu->setColumnWidth(col, 75);
	item = ui.tableWidget_PlanNaZminu->item(FIRST_MARSHRUT_ROW-1, col);
	ui.tableWidget_PlanNaZminu->setCurrentItem(item);
	ui.tableWidget_PlanNaZminu->scrollToItem(item);
	ui.tableWidget_PlanNaZminu->editItem(item);
	
	connect(ui.tableWidget_PlanNaZminu, SIGNAL(itemChanged(QTableWidgetItem *)), this,SLOT(saveItem(QTableWidgetItem *)));
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkPlanNaZminu::pushButton_delete_clicked()
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
	
	QModelIndexList selList = ui.tableWidget_PlanNaZminu->selectionModel()->selectedColumns();
	if (!selList.count()){
		QMessageBox::information(this, "Порада", "Ви не обрали жодної стрічки для видалення.\nОберіть хоч одну стрічку для видалення");
		return;
	}
	disconnect(ui.tableWidget_PlanNaZminu, SIGNAL(itemChanged(QTableWidgetItem *)), this,SLOT(saveItem(QTableWidgetItem *)));
	
	int dateId, col;
	bool doneOkCur;
	bool doneOkAll=true;
	QSqlQuery query;
	QList<int> idList;
	foreach(QModelIndex index, selList){
		col = index.column();
		dateId = ui.tableWidget_PlanNaZminu->horizontalHeaderItem(col)->data(Qt::UserRole).toInt();
		doneOkCur = query.exec("DELETE FROM PlanNaZminuDate WHERE id="+sqlStr(dateId));
		query.exec("DELETE FROM PlanNaZminu WHERE PlanNaZminuDate_id="+sqlStr(dateId));
		if (doneOkCur)
			idList << dateId;
		else
			doneOkAll = false;
		//ui.tableWidget_PlanNaZminu->removeRow(row);
	}
	for (col=0; col<ui.tableWidget_PlanNaZminu->columnCount(); col++){
		dateId = ui.tableWidget_PlanNaZminu->horizontalHeaderItem(col)->data(Qt::UserRole).toInt();
		if (idList.contains(dateId)){
			ui.tableWidget_PlanNaZminu->removeColumn(col);
			--col;
			if (!idList.removeOne(dateId))
				doneOkAll = false;
		}
	}
	if (!doneOkAll)
		QMessageBox::critical(this, "Помилка", "Програма не змогла видалити одну або декілька стрічок");
	
	connect(ui.tableWidget_PlanNaZminu, SIGNAL(itemChanged(QTableWidgetItem *)), this,SLOT(saveItem(QTableWidgetItem *)));
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkPlanNaZminu::action_printPlanyValovyhDohodiv_activated()
{
	UDialog_AParkDateFilter *d = new UDialog_AParkDateFilter(QDate::currentDate(), "Дата Планів", "dd.MM.yyyy");
	if (d->exec()){
		UPrintDocs_APark *printDocs = new UPrintDocs_APark();
		printDocs->print_planyValovyhDohodiv(d->date());
		connect(this, SIGNAL(mainWindowClosed()), printDocs->printform, SLOT(close()));
		delete printDocs;
	}
	delete d;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkPlanNaZminu::saveItem(QTableWidgetItem *item)
{
	disconnect(ui.tableWidget_PlanNaZminu, SIGNAL(itemChanged(QTableWidgetItem *)), this,SLOT(saveItem(QTableWidgetItem *)));
	
	int col = item->column();
	int row = item->row();
	int planNaZminuDateId = ui.tableWidget_PlanNaZminu->horizontalHeaderItem(col)->data(Qt::UserRole).toInt();
	QSqlQuery query;
	
	if (row == FIRST_MARSHRUT_ROW-1){ // збереження дати Плану на зміну
		query.exec("UPDATE PlanNaZminuDate SET CDate="+sqlStr(item->data(Qt::EditRole).toDate())+" \
					WHERE id="+sqlStr(planNaZminuDateId));
		query.exec("SELECT CDate FROM PlanNaZminuDate \
					WHERE id="+sqlStr(planNaZminuDateId));
		query.next();
		item->setData(Qt::EditRole, query.value(0));
		ui.tableWidget_PlanNaZminu->horizontalHeaderItem(col)->setData(Qt::DisplayRole, query.value(0).toDate().toString("dd.MM.yyyy"));
	}
	else if (row >= FIRST_MARSHRUT_ROW){ // збереження ПЛАНУ НА ЗМІНУ
		query.exec("SELECT id FROM PlanNaZminu \
					WHERE Marshrut_id="+sqlStr(ui.tableWidget_PlanNaZminu->verticalHeaderItem(row)->data(Qt::UserRole).toInt())+" \
						and PlanNaZminuDate_id="+sqlStr(planNaZminuDateId)+"");
		int planId = query.next()?query.value(0).toInt():0;
		if (planId){ //зміна запису
			query.exec("UPDATE PlanNaZminu SET Plan="+sqlStr(item->data(Qt::EditRole).toDouble())+" \
						WHERE id="+sqlStr(planId));
		}
		else{ //створення запису
			bool ok = query.exec("INSERT INTO PlanNaZminu (Marshrut_id, PlanNaZminuDate_id, Plan) \
						VALUES ( "+sqlStr(ui.tableWidget_PlanNaZminu->verticalHeaderItem(row)->data(Qt::UserRole).toInt())+", \
								"+sqlStr(planNaZminuDateId)+", \
								"+sqlStr(item->data(Qt::EditRole).toDouble())+")");
			if (ok){
				query.exec("SELECT last_insert_id()");
				query.next();
				planId = query.value(0).toInt();
			}
		}
		//зворотній зв'язок
		query.exec("SELECT Plan FROM PlanNaZminu WHERE id="+sqlStr(planId));
		query.next();
		item->setData(Qt::EditRole, query.value(0).toDouble());
	}
	
	connect(ui.tableWidget_PlanNaZminu, SIGNAL(itemChanged(QTableWidgetItem *)), this,SLOT(saveItem(QTableWidgetItem *)));
}
//--------------------utech--------------------utech--------------------utech--------------------
UForm_AParkPlanNaZminu::~UForm_AParkPlanNaZminu()
{
	
}
//--------------------utech--------------------utech--------------------utech--------------------
