//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл виконання класу вікна налаштування програми
//
// Створений програмістами Компанії "Утех" 21.01.2012р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------
#include "UForm_AParkEditTabelPidrozdilivWidget.h"

#include "UDifFunc_APark.h"
#include "UDialog_AParkEditTabelCell.h"
#include "UPrintDocs_APark.h"
#include "UTabelDayDelegate.h"
#include <UStandardDelegate>
#include <UPostupForm>
#include <UTableWidgetSqlExt>

#include <QtDebug>
//--------------------utech--------------------utech--------------------utech--------------------
UForm_AParkEditTabelPidrozdilivWidget::UForm_AParkEditTabelPidrozdilivWidget(int tWType, QWidget *parent)
        : UAParkTabWidget(tWType, parent)
{
	ui.setupUi(this);
	ui.tableWidget_tabel->addAction(ui.action_reloadTabel);
	ui.tableWidget_tabel->addAction(ui.action_printTabel);
	ui.tableWidget_tabel->setContextMenuPolicy(Qt::ActionsContextMenu);
	ui.tableWidget_tabel->setItemDelegate(new UTabelDayDelegate(ui.tableWidget_tabel));
	
	QSqlQuery query;
	
	new UIntEditingComboBox(ui.comboBox_pidrozdil);
	ui.comboBox_pidrozdil->addItem("Без підрозділу",0);
	query.exec("SELECT id, Name FROM pidrozdily_salary ORDER BY id");
	while (query.next())
		ui.comboBox_pidrozdil->addItem("["+query.value(0).toString()+"] "+query.value(1).toString(), query.value(0).toInt());
	ui.comboBox_pidrozdil->setCurrentIndex(0);
	
	new UIntEditingComboBox(ui.comboBox_vodiyFilter);
	
	ui.dateEdit_tabelDate->setDate(QDate::currentDate());
	
	populateTabel();
	
	connect(ui.dateEdit_tabelDate, SIGNAL(dateChanged(const QDate &)), this,SLOT(populateTabel()));
	connect(ui.comboBox_pidrozdil, SIGNAL(currentIndexChanged(int)), this,SLOT(populateTabel()));
	connect(ui.action_reloadTabel, SIGNAL(activated()), this,SLOT(populateTabel()));
	connect(ui.action_printTabel, SIGNAL(activated()), this,SLOT(printTabel()));
	connect(ui.pushButton_findCell, SIGNAL(clicked()), this,SLOT(pushButton_findCell_clicked()));
	connect(ui.tableWidget_tabel, SIGNAL(itemDoubleClicked(QTableWidgetItem *)), this,SLOT(tableWidget_tabel_itemDoubleClicked(QTableWidgetItem *)));
}
//--------------------utech--------------------utech--------------------utech--------------------
UForm_AParkEditTabelPidrozdilivWidget::~UForm_AParkEditTabelPidrozdilivWidget()
{
	
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkEditTabelPidrozdilivWidget::populateToolBar(QToolBar * tBar)
{
	tBar->addAction(ui.action_printTabel);
}
//--------------------utech--------------------utech--------------------utech--------------------
int UForm_AParkEditTabelPidrozdilivWidget::currentPidrozdilId()
{
	return ui.comboBox_pidrozdil->itemData(ui.comboBox_pidrozdil->currentIndex()).toInt(); 
}
//--------------------utech--------------------utech--------------------utech--------------------
//Заповнює поля таблиці табеля з таблиці табеля бази даних 
void UForm_AParkEditTabelPidrozdilivWidget::populateTabel()
{
	QTableWidgetItem *item;
	QSqlQuery query;
	QString str;
	UWorkMonth wMonth(ui.dateEdit_tabelDate->date().year(), ui.dateEdit_tabelDate->date().month());
	ui.dateEdit_dateFilter->setDate(wMonth.begDate());
	//створення переліку індексів святкових днів
	QSet<int> svIndex;
	query.exec("SELECT CDate FROM svyatkovidni \
				WHERE CDate BETWEEN date("+sqlStr(wMonth.begDate())+") \
					and date("+sqlStr(wMonth.endDate())+")");
	while (query.next())
		svIndex << wMonth.begDate().daysTo(query.value(0).toDate());
	
	ui.comboBox_vodiyFilter->clear();
	ui.comboBox_vodiyFilter->addItem("", 0);
	
	// Заповнення вертикального заголовка
	query.exec("SELECT count(*) FROM npr WHERE Pidrozdil_id="+sqlStr(currentPidrozdilId()));
	query.next();
	int rowCount = query.value(0).toInt(), row;
	ui.tableWidget_tabel->setRowCount(rowCount);
	query.exec("SELECT id, Prizv, Imia, Pobatk FROM npr WHERE Pidrozdil_id="+sqlStr(currentPidrozdilId())+" \
				ORDER BY Naparnyky, Prizv, Imia, Pobatk");
	for (row=0; row<rowCount && query.next(); row++){
		// Populate filter combobox
		ui.comboBox_vodiyFilter->addItem("["+query.value(0).toString()+"] "+query.value(1).toString()+" "+
					query.value(2).toString()+" "+query.value(3).toString(), query.value(0));
		
		str = query.value(1).toString();
		if (query.value(2).toString().size()>0){
			str += QString(" ") + query.value(2).toString().at(0) + QString(".");
			if (query.value(3).toString().size()>0)
				str += QString(" ") + query.value(3).toString().at(0) + QString(".");
		}
		str += " ["+query.value(0).toString()+"]";
		item = new QTableWidgetItem();
		item->setData(Qt::DisplayRole, str);
		item->setData(Qt::UserRole, query.value(0));
		ui.tableWidget_tabel->setVerticalHeaderItem(row, item);
	}
	// Заповнення горизонтального заголовка
	ui.tableWidget_tabel->setColumnCount(wMonth.begDate().daysTo(wMonth.endDate())+1);
	int col=0;
	for (QDate xDate=wMonth.begDate(); xDate<=wMonth.endDate(); xDate=xDate.addDays(1)){
		item = new QTableWidgetItem();
		item->setData(Qt::DisplayRole, xDate.toString("dd.MM,ddd"));
		item->setData(Qt::UserRole, xDate);
		ui.tableWidget_tabel->setHorizontalHeaderItem(col, item);
		col++;
	}
	
	//створення усіх QTableWidgetItem
	for (row=0; row<rowCount; row++)
		for (col=0; col<ui.tableWidget_tabel->columnCount(); col++){
			item = new QTableWidgetItem();
			if (svIndex.contains(col))
				item->setData(Qt::BackgroundRole, QBrush(QColor("#e6ffa8")));
			ui.tableWidget_tabel->setItem(row,col, item);
			
		}
	
	UTabelDay tabDay;
	QVariant variant;
	for (row=0; row<rowCount; row++){
		query.exec("SELECT Cur_Date, Pracivn_status_ID, God_zag, God_nichni, God_sv FROM tabel \
					WHERE Npr_id="+sqlStr(ui.tableWidget_tabel->verticalHeaderItem(row)->data(Qt::UserRole).toInt())+" \
						and (Cur_Date BETWEEN date("+sqlStr(wMonth.begDate())+") \
							AND date("+sqlStr(wMonth.endDate())+"))");
		while (query.next()){
			col = wMonth.begDate().daysTo(query.value(0).toDate());
			tabDay.workType = query.value(1).toInt();
			tabDay.rob = query.value(2).toTime();
			tabDay.nich = query.value(3).toTime();
			tabDay.sv = query.value(4).toTime();
			item = ui.tableWidget_tabel->item(row, col);
			variant.setValue(tabDay);
			item->setData(Qt::EditRole, variant);
		}
	}
	
	ui.tableWidget_tabel->resizeColumnsToContents();
	ui.tableWidget_tabel->resizeRowsToContents();
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkEditTabelPidrozdilivWidget::tableWidget_tabel_itemDoubleClicked(QTableWidgetItem *item)
{
	UDialog_AParkEditTabelCell d(ui.tableWidget_tabel->verticalHeaderItem(item->row())->data(Qt::UserRole).toInt(),
								ui.tableWidget_tabel->horizontalHeaderItem(item->column())->data(Qt::UserRole).toDate(),
								item,
								0);
	d.exec();
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkEditTabelPidrozdilivWidget::printTabel()
{
	UPrintDocs_APark *printDocs = new UPrintDocs_APark();
	printDocs->print_monthTabel(ui.dateEdit_tabelDate->date().year(), 
								ui.dateEdit_tabelDate->date().month(),
								currentPidrozdilId());
	connect(this, SIGNAL(mainWindowClosed()), printDocs->printform, SLOT(close()));
	delete printDocs;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkEditTabelPidrozdilivWidget::pushButton_findCell_clicked()
{
	UWorkMonth wMonth(ui.dateEdit_tabelDate->date().year(), ui.dateEdit_tabelDate->date().month());
	int vId = ui.comboBox_vodiyFilter->itemData(ui.comboBox_vodiyFilter->currentIndex(), Qt::UserRole).toInt();
	ui.comboBox_vodiyFilter->setCurrentIndex(0);
	int col = wMonth.begDate().daysTo(ui.dateEdit_dateFilter->date());
	if (col < 0)
		col = 0;
	if (col > ui.tableWidget_tabel->columnCount()-1)
		col = ui.tableWidget_tabel->columnCount()-1;
	
	for (int row=0; row<ui.tableWidget_tabel->rowCount(); row++){
		if (ui.tableWidget_tabel->verticalHeaderItem(row)->data(Qt::UserRole).toInt() == vId){
			QTableWidgetItem *item = ui.tableWidget_tabel->item(row, col);
			ui.tableWidget_tabel->setCurrentItem(item);
			ui.tableWidget_tabel->scrollToItem(item);
			ui.tableWidget_tabel->setFocus();
			return;
		}
	}
	QMessageBox::information(0,"Пошук завершено","Програмі не вдалося знайти працівника з табельним номером "+QString::number(vId));
}
//--------------------utech--------------------utech--------------------utech--------------------
