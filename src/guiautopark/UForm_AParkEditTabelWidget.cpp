//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл виконання класу вікна налаштування програми
//
// Створений програмістами Компанії "Утех" 23.03.2010р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------
#include "UForm_AParkEditTabelWidget.h"

#include "UDifFunc_APark.h"
#include "UDialog_AParkEditTabelCell.h"
#include "UPrintDocs_APark.h"
#include "UTabelDayDelegate.h"
#include <UStandardDelegate>
#include <UPostupForm>
#include <UTableWidgetSqlExt>

#include <QtDebug>
//--------------------utech--------------------utech--------------------utech--------------------
UForm_AParkEditTabelWidget::UForm_AParkEditTabelWidget(int tWType, QWidget *parent)
        : UAParkTabWidget(tWType, parent)
{
	ui.setupUi(this);
	ui.tableWidget_tabel->addAction(ui.action_reloadTabel);
	ui.tableWidget_tabel->addAction(ui.action_printTabel);
	ui.tableWidget_tabel->addAction(ui.action_fillTabelFromDb);
	ui.tableWidget_tabel->addAction(ui.action_fillRowFromDb);
	ui.tableWidget_tabel->addAction(ui.action_fillCellFromDb);
	ui.tableWidget_tabel->setContextMenuPolicy(Qt::ActionsContextMenu);
	ui.tableWidget_tabel->setItemDelegate(new UTabelDayDelegate(ui.tableWidget_tabel));
	
	new UIntEditingComboBox(ui.comboBox_vodiyFilter);
	ui.comboBox_vodiyFilter->addItem("",0);
	QSqlQuery q("SELECT id, Prizv, Imia, Pobatk FROM npr WHERE Posada_id=10 ORDER BY Prizv, Imia, Pobatk");
	while (q.next())
		ui.comboBox_vodiyFilter->addItem("["+q.value(0).toString()+"] "+q.value(1).toString()+" "+
					q.value(2).toString()+" "+q.value(3).toString(), q.value(0));
	
	ui.dateEdit_tabelDate->setDate(QDate::currentDate());
	
	populateTabel();
	
	connect(ui.dateEdit_tabelDate, SIGNAL(dateChanged(const QDate &)), this,SLOT(populateTabel()));
	connect(ui.action_reloadTabel, SIGNAL(activated()), this,SLOT(populateTabel()));
	connect(ui.action_fillTabelFromDb, SIGNAL(activated()), this,SLOT(fillTabelFromDb()));
	connect(ui.action_fillRowFromDb, SIGNAL(activated()), this,SLOT(fillCurrentRow()));
	connect(ui.action_fillCellFromDb, SIGNAL(activated()), this,SLOT(fillCurrentCell()));
	connect(ui.action_printTabel, SIGNAL(activated()), this,SLOT(printTabel()));
	connect(ui.pushButton_findCell, SIGNAL(clicked()), this,SLOT(pushButton_findCell_clicked()));
	connect(ui.tableWidget_tabel, SIGNAL(itemDoubleClicked(QTableWidgetItem *)), this,SLOT(tableWidget_tabel_itemDoubleClicked(QTableWidgetItem *)));
}
//--------------------utech--------------------utech--------------------utech--------------------
UForm_AParkEditTabelWidget::~UForm_AParkEditTabelWidget()
{
	
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkEditTabelWidget::populateToolBar(QToolBar * tBar)
{
	tBar->addAction(ui.action_printTabel);
	tBar->addAction(ui.action_fillTabelFromDb);
	tBar->addAction(ui.action_fillRowFromDb);
	tBar->addAction(ui.action_fillCellFromDb);
}
//--------------------utech--------------------utech--------------------utech--------------------
//Заповнює поля таблиці табеля з таблиці табеля бази даних 
void UForm_AParkEditTabelWidget::populateTabel()
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
	
	// Заповнення вертикального заголовка
	query.exec("SELECT count(*) FROM npr WHERE Posada_id=10");
	query.next();
	int rowCount = query.value(0).toInt(), row;
	ui.tableWidget_tabel->setRowCount(rowCount);
	query.exec("SELECT id, Prizv, Imia, Pobatk FROM npr WHERE Posada_id=10 \
				ORDER BY Naparnyky, Prizv, Imia, Pobatk");
	for (row=0; row<rowCount && query.next(); row++){
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
void UForm_AParkEditTabelWidget::tableWidget_tabel_itemDoubleClicked(QTableWidgetItem *item)
{
	UDialog_AParkEditTabelCell d(ui.tableWidget_tabel->verticalHeaderItem(item->row())->data(Qt::UserRole).toInt(),
								ui.tableWidget_tabel->horizontalHeaderItem(item->column())->data(Qt::UserRole).toDate(),
								item,
								0);
	d.exec();
}
//--------------------utech--------------------utech--------------------utech--------------------
//заповнює комірку табеля з шляхових листів
void UForm_AParkEditTabelWidget::fillTabelCell(int row, int col)
{
	const QDate dt = ui.tableWidget_tabel->horizontalHeaderItem(col)->data(Qt::UserRole).toDate();
	const int nprId = ui.tableWidget_tabel->verticalHeaderItem(row)->data(Qt::UserRole).toInt();
	
	unsigned char dayInWorkMonthType = 0; //0 - звичний день; 1 - початок місяця; 2 - кінець місяця
	UWorkMonth wMonth(dt);
	if (dt == wMonth.begDate())
		dayInWorkMonthType = 1;
	else if (dt == wMonth.endDate())
		dayInWorkMonthType = 2;
	
	QSqlQuery query;
	int workMinutes=0;
	int xMinutes;
	bool isShlyahLysty=false;
	QTime xTime, robTime, svTime(0,0);
	query.exec("SELECT ChasVRezervi, ChasVNaryadi, TypPoNochivli_id  \
				FROM shlyahovyiLyst \
				WHERE VodiyTabelNum_id="+sqlStr(nprId)+" \
					and date(ToZvitDate)=date("+sqlStr(dt)+")");
	while (query.next()){
		if (query.value(2).toInt() != 2){ //без ночівлі, поточний день
			xTime = query.value(0).toTime();
			workMinutes = xTime.hour() * 60 + xTime.minute();
			xTime = query.value(1).toTime();
			workMinutes += xTime.hour() * 60 + xTime.minute();
		}
		else{ //з ночівлею поточний день
			xTime = query.value(0).toTime();
			xMinutes = xTime.hour() * 60 + xTime.minute();
			xTime = query.value(1).toTime();
			xMinutes += xTime.hour() * 60 + xTime.minute();
			if (dayInWorkMonthType == 2)
				workMinutes += xMinutes;
			else
				workMinutes += xMinutes/2;
		}
		isShlyahLysty = true;
	}
	
	if (dayInWorkMonthType != 1){
		query.exec("SELECT ChasVRezervi, ChasVNaryadi  \
					FROM shlyahovyiLyst \
					WHERE TypPoNochivli_id=2 and VodiyTabelNum_id="+sqlStr(nprId)+" \
						and date(ToZvitDate)=date("+sqlStr(dt.addDays(-1))+")");
		while (query.next()){ //попередній день - путівки з ночівлею
			xTime = query.value(0).toTime();
			xMinutes = xTime.hour() * 60 + xTime.minute();
			xTime = query.value(1).toTime();
			xMinutes += xTime.hour() * 60 + xTime.minute();
			workMinutes += xMinutes/2;
			
			isShlyahLysty = true;
		}
	}
	
	robTime.setHMS(workMinutes/60, fmod(workMinutes,60), 0);
	
	//перевірка на святковість
	/*if (dt.dayOfWeek()==7) //неділя
		svTime = robTime;
	else{*/
		query.exec("SELECT true FROM svyatkoviDni WHERE CDate=date("+sqlStr(dt)+")");
		if (query.next()) //святковий день
			svTime = robTime;
	//}
	
	query.exec("SELECT id FROM tabel WHERE Npr_ID="+sqlStr(nprId)+" and Cur_date="+sqlStr(dt));
	if (!query.next()){
		if (!isShlyahLysty) //Вихід, якщо немає шляхових листів і немає запису в табелі
			return;
		query.exec("INSERT INTO tabel (Npr_ID, Cur_date) VALUES ("+sqlStr(nprId)+","+sqlStr(dt)+")");
		query.exec("SELECT last_insert_id()");
		query.next();
	}
	else if (!isShlyahLysty) //Занулення статусу працівника коли стічка була створена до того, а шляхових листів немає
		QSqlQuery q("UPDATE tabel SET Pracivn_status_ID=0 \
					WHERE id="+query.value(0).toString()+" and Pracivn_status_ID=1");
	int id = query.value(0).toInt();
	query.exec("UPDATE tabel SET \
					"+(isShlyahLysty?QString("Pracivn_status_ID=1,"):QString(""))+" \
					God_zag = "+sqlStr(robTime)+", \
					God_nichni = 0, \
					God_sv = "+sqlStr(svTime)+" \
				WHERE id="+sqlStr(id));
	query.exec("SELECT Pracivn_status_ID, God_zag, God_nichni, God_sv FROM tabel WHERE id="+sqlStr(id));
	query.next();
	UTabelDay tabelDay;
	tabelDay.workType = query.value(0).toInt();
	tabelDay.rob = query.value(1).toTime();
	tabelDay.nich = query.value(2).toTime();
	tabelDay.sv = query.value(3).toTime();
	QVariant var;
	var.setValue(tabelDay);
	ui.tableWidget_tabel->item(row,col)->setData(Qt::EditRole, var);
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkEditTabelWidget::fillTabelFromDb()
{
	if	( QMessageBox::question(
                this,
                "Автозаповнення табеля",
                "Ви дійсно бажаєте здійснити автозаповнення табеля значеннями \nз шляхових листів для УСІХ працівників за весь місяць?\nПри цьому, старі дані будуть змінені на нові.",
                "Так",
				"Ні-ні-ні",
                QString(), 0, 1)
		)
		return;
	
	UPostupForm postup(0, ui.tableWidget_tabel->rowCount());
	postup.show();
	
	for (int row=0; row<ui.tableWidget_tabel->rowCount(); row++){
		for (int col=0; col<ui.tableWidget_tabel->columnCount(); col++)
			fillTabelCell(row, col);
		postup.incPos();
	}
	postup.hide();
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkEditTabelWidget::fillCurrentCell()
{
	if (ui.tableWidget_tabel->rowCount()==0)
		return;
	if (ui.tableWidget_tabel->selectionModel()->hasSelection())
		fillTabelCell(ui.tableWidget_tabel->currentRow(), ui.tableWidget_tabel->currentColumn());
	else
		QMessageBox::information(0,"Необхідне позначення","Позначте будь-ласка комірку для заповнення");
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkEditTabelWidget::fillCurrentRow()
{
	if	( QMessageBox::question(
                this,
                "Автозаповнення табеля",
                "Ви дійсно бажаєте здійснити автозаповнення табеля значеннями \nз шляхових листів для ПОТОЧНОГО працівника за весь місяць?\nПри цьому, старі дані будуть змінені на нові.",
                "Так",
				"Ні-ні-ні",
                QString(), 0, 1)
		)
		return;
	
	if (ui.tableWidget_tabel->rowCount()==0)
		return;
	
	if (ui.tableWidget_tabel->selectionModel()->hasSelection()){
		UPostupForm postup(0, ui.tableWidget_tabel->columnCount());
		postup.show();
		for (int col=0; col<ui.tableWidget_tabel->columnCount(); col++){
			fillTabelCell(ui.tableWidget_tabel->currentRow(), col);
			postup.incPos();
		}
		postup.hide();
	}
	else
		QMessageBox::information(0,"Необхідне позначення","Позначте будь-ласка комірку для заповнення");
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkEditTabelWidget::printTabel()
{
	UPrintDocs_APark *printDocs = new UPrintDocs_APark();
	printDocs->print_monthTabel(ui.dateEdit_tabelDate->date().year(), ui.dateEdit_tabelDate->date().month());
	connect(this, SIGNAL(mainWindowClosed()), printDocs->printform, SLOT(close()));
	delete printDocs;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkEditTabelWidget::pushButton_findCell_clicked()
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
