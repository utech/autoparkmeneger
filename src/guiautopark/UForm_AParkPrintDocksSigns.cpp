//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл виконання класу вікна налаштування програми
//
// Створений програмістами Компанії "Утех" 19.07.2010р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------
#include "UForm_AParkPrintDocksSigns.h"

#include "UDifFunc_APark.h"
#include <UStandardDelegate>
#include <UMath>

#include <QtDebug>
//--------------------utech--------------------utech--------------------utech--------------------
UForm_AParkPrintDocksSigns::UForm_AParkPrintDocksSigns(int tWType, QWidget *parent)
        : UAParkTabWidget(tWType, parent)
{
	ui.setupUi(this);
	
	//Надаштуваня таблиці документи для друку
	ui.tableWidget_doksEnum->setColumnCount(3);
	twExtDocks = new UTableWidgetSqlExt(ui.tableWidget_doksEnum, "printdocsenum");
	twExtDocks->setSortingEnabled(true);
	
	ui.tableWidget_doksEnum->setHorizontalHeaderLabels( QStringList() 
															<< "id"
															<< "Назва документа"
															<< "Примітка");
	twExtDocks->colNamesList << "Id"
						<< "Name"
						<< "Prymitka";
						
	twExtDocks->addColAlignment("Name", Qt::AlignVCenter | Qt::AlignLeft);
	twExtDocks->addColAlignment("Prymitka", Qt::AlignVCenter | Qt::AlignLeft);
	
	ui.tableWidget_doksEnum->setColumnHidden(0, true);
	twExtDocks->setColumnWidth("Name", 380);
	twExtDocks->setColumnWidth("Prymitka", 100);
	
	twExtDocks->populateTable();
	
	//Налаштування таблиці користувачів
	ui.tableWidget_user->setColumnCount(5);
	twExtUsers = new UTableWidgetSqlExt(ui.tableWidget_user, "users");
	twExtUsers->setSortingEnabled(true);
	
	ui.tableWidget_user->setHorizontalHeaderLabels( QStringList() 
															<< "id"
															<< "Прізвище"
															<< "Ім'я"
															<< "По-батькові"
															<< "Посада для друку");
	twExtUsers->colNamesList << "Id"
						<< "Prizv"
						<< "Imya"
						<< "Pobatk"
						<< "PosadaName";
	
	twExtUsers->addColAlignment("Prizv", Qt::AlignVCenter | Qt::AlignLeft);
	twExtUsers->addColAlignment("Imya", Qt::AlignVCenter | Qt::AlignLeft);
	twExtUsers->addColAlignment("Pobatk", Qt::AlignVCenter | Qt::AlignLeft);
	twExtUsers->addColAlignment("PosadaName", Qt::AlignVCenter | Qt::AlignLeft);
	
	ui.tableWidget_user->setColumnHidden(0, true);
	twExtUsers->setColumnWidth("Prizv", 100);
	twExtUsers->setColumnWidth("Imya", 100);
	twExtUsers->setColumnWidth("Pobatk", 100);
	twExtUsers->setColumnWidth("PosadaName", 150);
	
	twExtUsers->populateTable();
	
	ui.tableWidget_singns->setColumnHidden(0,true);
	ui.tableWidget_singns->setHorizontalHeaderLabels( QStringList() << "" << "" << "" << "" << "");
	ui.label_curDocument->setText("Відомість нарахування");
	ui.tableWidget_singns->setColumnWidth(1, 50);
	ui.tableWidget_singns->setColumnWidth(2, 200);
	ui.tableWidget_singns->setColumnWidth(3, 100);
	ui.tableWidget_singns->setColumnWidth(4, 200);
	populatePrintDockSigns();
	
	connect(ui.toolButton_addUserSign, SIGNAL(clicked()), this, SLOT(toolButton_addUserSign_clicked()));
	connect(ui.toolButton_signUp, SIGNAL(clicked()), this, SLOT(toolButton_signUp_clicked()));
	connect(ui.toolButton_signDown, SIGNAL(clicked()), this, SLOT(toolButton_signDown_clicked()));
	connect(ui.toolButton_saveSigns, SIGNAL(clicked()), this, SLOT(toolButton_saveSigns_clicked()));
	connect(ui.toolButton_deleteSign, SIGNAL(clicked()), this, SLOT(toolButton_deleteSign_clicked()));
	
	connect(ui.tableWidget_doksEnum->selectionModel(), SIGNAL(currentRowChanged(const QModelIndex &,const QModelIndex &)), 
					this, SLOT(populatePrintDockSigns()));
}
//--------------------utech--------------------utech--------------------utech--------------------
UForm_AParkPrintDocksSigns::~UForm_AParkPrintDocksSigns()
{
	
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkPrintDocksSigns::populateToolBar(QToolBar * tBar)
{
	
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkPrintDocksSigns::toolButton_addUserSign_clicked()
{
	int userId = twExtUsers->currentItemData("id").toInt();
	if (userId == 0)
		return;
	QTableWidgetItem *item;
	int row = ui.tableWidget_singns->rowCount();
	ui.tableWidget_singns->setRowCount(row+1);
	//User.id
	item = new QTableWidgetItem();
	item->setData(Qt::EditRole, userId);
	ui.tableWidget_singns->setItem(row, 0, item);
	//Посада
	item = new QTableWidgetItem(twExtUsers->currentItemData("PosadaName").toString());
	ui.tableWidget_singns->setItem(row, 2, item);
	//Піб
	item = new QTableWidgetItem(uPrizvIB(twExtUsers->currentItemData("Prizv").toString(),
											twExtUsers->currentItemData("Imya").toString(),
											twExtUsers->currentItemData("Pobatk").toString()));
	ui.tableWidget_singns->setItem(row, 4, item);
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkPrintDocksSigns::toolButton_signUp_clicked()
{
	int cRow = ui.tableWidget_singns->currentRow();
	int cCol = ui.tableWidget_singns->currentColumn();
	if (cRow == 0)
		return;
	
	QTableWidgetItem *item1;
	QTableWidgetItem *item2;
	
	for (int col=0; col<ui.tableWidget_singns->columnCount(); col++){
		item1 = ui.tableWidget_singns->takeItem(cRow, col);
		item2 = ui.tableWidget_singns->takeItem(cRow-1, col);
		ui.tableWidget_singns->setItem(cRow-1, col, item1);
		ui.tableWidget_singns->setItem(cRow, col, item2);
	}
	ui.tableWidget_singns->setCurrentCell(cRow-1, cCol);
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkPrintDocksSigns::toolButton_signDown_clicked()
{
	int cRow = ui.tableWidget_singns->currentRow();
	int cCol = ui.tableWidget_singns->currentColumn();
	if (cRow == ui.tableWidget_singns->rowCount()-1)
		return;
	
	QTableWidgetItem *item1;
	QTableWidgetItem *item2;
	
	for (int col=0; col<ui.tableWidget_singns->columnCount(); col++){
		item1 = ui.tableWidget_singns->takeItem(cRow, col);
		item2 = ui.tableWidget_singns->takeItem(cRow+1, col);
		ui.tableWidget_singns->setItem(cRow+1, col, item1);
		ui.tableWidget_singns->setItem(cRow, col, item2);
	}
	ui.tableWidget_singns->setCurrentCell(cRow+1, cCol);
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkPrintDocksSigns::toolButton_saveSigns_clicked()
{
	int docId = twExtDocks->currentItemData("id").toInt();
	if (docId == 0){
		QMessageBox::critical(0,"Помилка","Помилка запису підписів у документі");
		return;
	}
	
	QSqlQuery query;
	query.exec("DELETE FROM printDocsSigns WHERE PrintDoc_id="+sqlStr(docId));
	int sortOrder = 0;
	for (int row=0; row<ui.tableWidget_singns->rowCount(); row++){
		query.exec("INSERT INTO printDocsSigns (PrintDoc_id, User_id, SortOrder) VALUES \
						("+sqlStr(docId)+", \
						"+sqlStr(ui.tableWidget_singns->item(row,0)->data(Qt::EditRole).toInt())+", \
						"+sqlStr(sortOrder++)+")");
	}
	QMessageBox::information(0,"Успішний запис","Підписи для документа успішно записано");
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkPrintDocksSigns::toolButton_deleteSign_clicked()
{
	if (ui.tableWidget_singns->rowCount() == 0)
		return;
	int cRow = ui.tableWidget_singns->currentRow();
	int cCol = ui.tableWidget_singns->currentColumn();
	ui.tableWidget_singns->removeRow(cRow);
	if (cRow == ui.tableWidget_singns->rowCount())
		ui.tableWidget_singns->setCurrentCell(cRow-1, cCol);
	else
		ui.tableWidget_singns->setCurrentCell(cRow, cCol);
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkPrintDocksSigns::populatePrintDockSigns()
{
	ui.tableWidget_singns->setRowCount(0);
	int docId = twExtDocks->currentItemData("id").toInt();
	if (docId == 0)
		return;
	
	QTableWidgetItem *item;
	ui.label_curDocument->setText(twExtDocks->currentItemData("Name").toString());
	
	QSqlQuery query("SELECT printDocsSigns.User_id, users.Prizv, users.Imya, users.PoBatk, users.PosadaName \
					FROM printDocsSigns \
					LEFT JOIN users ON printDocsSigns.User_id=users.id \
					WHERE PrintDoc_id="+sqlStr(docId)+" \
					ORDER BY SortOrder");
	while (query.next()){
		int row = ui.tableWidget_singns->rowCount();
		ui.tableWidget_singns->insertRow(row);
		
		//User.id
		item = new QTableWidgetItem();
		item->setData(Qt::EditRole, query.value(0).toInt());
		ui.tableWidget_singns->setItem(row, 0, item);
		//Посада
		item = new QTableWidgetItem(query.value(4).toString());
		ui.tableWidget_singns->setItem(row, 2, item);
		//Піб
		item = new QTableWidgetItem(uPrizvIB(query.value(1).toString(),
											query.value(2).toString(),
											query.value(3).toString()));
		ui.tableWidget_singns->setItem(row, 4, item);
	}
	
	if (ui.tableWidget_singns->rowCount() == 0)
		return;
	ui.tableWidget_singns->setCurrentCell(0, 1);
}
//--------------------utech--------------------utech--------------------utech--------------------
