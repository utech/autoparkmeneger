//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл виконання класу вікна налаштування програми
//
// Створений програмістами Компанії "Утех" 29.03.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------
#include "UForm_AParkTOLog.h"

#include "UDifFunc_APark.h"
#include <UStandardDelegate>

#include <QtDebug>
//--------------------utech--------------------utech--------------------utech--------------------
UForm_AParkTOLog::UForm_AParkTOLog(int tWType, QWidget *parent)
        : UAParkTabWidget(tWType, parent)
{
	ui.setupUi(this);
	ui.dateEdit_DateFilter->setDate(QDate::currentDate());
	populateAutosListWidget();
	
	twExt = new UDataFormView(ui.tableWidget_TOLog, "TOLog");
	twExt->colNamesList << "Id"
						<< "GarajNum_id"
						<< "TONum"
						<< "TODate"
						<< "TOProbig";
	
	twExt->addColAlignment("GarajNum_id", Qt::AlignVCenter | Qt::AlignLeft);
	twExt->addColAlignment("TONum", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("TODate", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("TOProbig", Qt::AlignVCenter | Qt::AlignRight);
	
	twExt->insertWidget(ui.comboBox_auto, "GarajNum_id");
	twExt->insertWidget(ui.spinBox_TONum, "TONum");
	twExt->insertWidget(ui.dateEdit_zaizdDate, "TODate");
	twExt->insertWidget(ui.doubleSpinBox_NulyovyiProbig, "TOProbig");
	
	//Ініціалізація делегатів для колонок таблиці
	QSqlQuery query;
	UIntStringList delegateList;
		//Делегат Гаражний номер
	delegateList.clear();
	delegateList.insert(0, "");
	query.exec("SELECT ruhomyiSklad.GarajNumber, ruhomyiSklad.NomernyiZnak, \
						markaAuto.MarkaShyfr \
				FROM ruhomyiSklad \
				LEFT JOIN markaauto ON markaAuto.id=ruhomyiSklad.MarkaAuto_id \
				ORDER BY ruhomyiSklad.NomernyiZnak");
	while (query.next()){
		delegateList.insert(query.value(0).toInt(), "№"+query.value(0).toString()+" ["+query.value(1).toString()+"] - "+query.value(2).toString());
	}
	twExt->setItemDelegateForColumn("GarajNum_id", delegateList);
	
	ui.tableWidget_TOLog->setItemDelegateForColumn(twExt->columnNumber("TODate"), new UDateEditDelegate(QDate(2000,1,1),QDate(2100,12,31),ui.tableWidget_TOLog));
	ui.tableWidget_TOLog->setItemDelegateForColumn(twExt->columnNumber("TOProbig"), new UDoubleSpinBoxDelegate(0,100000, 2, ui.tableWidget_TOLog));
	ui.tableWidget_TOLog->setItemDelegateForColumn(twExt->columnNumber("TONum"), new USpinBoxDelegate(0,2, ui.tableWidget_TOLog));
	
	ui.tableWidget_TOLog->setColumnHidden(0, true);
	twExt->setColumnWidth("GarajNum_id", 250);
	
	setTOLogFilterFilter();
	
	connect(ui.pushButton_create, SIGNAL(clicked()), this, SLOT(pushButton_create_clicked()));
	connect(ui.pushButton_delete, SIGNAL(clicked()), this, SLOT(pushButton_delete_clicked()));
	connect(ui.pushButton_reload, SIGNAL(clicked()), twExt, SLOT(populateTable()));
	
	connect(ui.toolBox_TOLogFilter, SIGNAL(currentChanged(int)), this, SLOT(setTOLogFilterFilter()));
	connect(ui.listWidget_AutosFilter, SIGNAL(currentRowChanged(int)), this, SLOT(setTOLogFilterFilter()));
	connect(ui.dateEdit_DateFilter, SIGNAL(dateChanged(const QDate &)), this, SLOT(setTOLogFilterFilter()));
	
	connect(twExt, SIGNAL(tableItemEdited(QTableWidgetItem *)), this, SLOT(populateDovidnykValues(QTableWidgetItem *)));
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkTOLog::pushButton_create_clicked()
{
	QString sqlStr;
	if (ui.toolBox_TOLogFilter->currentIndex()==0) //фільтр по гаражному номеру
		sqlStr = "INSERT INTO TOLog (GarajNum_id, TODate) \
				VALUES ("+ui.listWidget_AutosFilter->currentItem()->data(Qt::UserRole).toString()+", \
					'"+QDate::currentDate().toString("yyyy-MM-dd")+"')";
	else if (ui.toolBox_TOLogFilter->currentIndex()==1) //фільтр по даті
		sqlStr = "INSERT INTO TOLog (TODate) VALUES ('"+ui.dateEdit_DateFilter->date().toString("yyyy-MM-dd")+"')";
	
	if (!twExt->addRow(sqlStr))
		QMessageBox::critical(0,"Помилка створення запису","Запис шляхового листа не створено не створено");
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkTOLog::pushButton_delete_clicked()
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
void UForm_AParkTOLog::setTOLogFilterFilter()
{
	if (ui.toolBox_TOLogFilter->currentIndex() == 0){
		twExt->setSqlFilter("GarajNum_id="+ui.listWidget_AutosFilter->currentItem()->data(Qt::UserRole).toString());
	}
	else{
		twExt->setSqlFilter("TODate='"+ui.dateEdit_DateFilter->date().toString("yyyy-MM-dd")+"'");
	}
	twExt->populateTable();
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkTOLog::populateDovidnykValues(QTableWidgetItem *item)
{
	
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkTOLog::populateToolBar(QToolBar * tBar)
{
	
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkTOLog::populateAutosListWidget()
{
	QSqlQuery query;
	QListWidgetItem * item;
	ui.listWidget_AutosFilter->clear();
	query.exec("SELECT ruhomyiSklad.GarajNumber, ruhomyiSklad.NomernyiZnak, \
						markaAuto.MarkaShyfr \
				FROM ruhomyiSklad \
				LEFT JOIN markaauto ON markaAuto.id=ruhomyiSklad.MarkaAuto_id \
				ORDER BY ruhomyiSklad.NomernyiZnak");
	while (query.next()){
		item = new QListWidgetItem("№"+query.value(0).toString()+" ["+query.value(1).toString()+"] - "+query.value(2).toString());
		item->setData(Qt::UserRole, query.value(0).toInt());
		ui.listWidget_AutosFilter->addItem(item);
	}
	if (ui.listWidget_AutosFilter->count()>0){
		item = ui.listWidget_AutosFilter->item(0);
		ui.listWidget_AutosFilter->setCurrentItem(item);
		ui.listWidget_AutosFilter->scrollToItem(item);
	}
}
//--------------------utech--------------------utech--------------------utech--------------------
UForm_AParkTOLog::~UForm_AParkTOLog()
{
	
}
//--------------------utech--------------------utech--------------------utech--------------------
