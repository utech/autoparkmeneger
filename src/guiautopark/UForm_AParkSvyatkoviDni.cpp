//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл виконання класу вікна налаштування програми
//
// Створений програмістами Компанії "Утех" 29.03.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------
#include "UForm_AParkSvyatkoviDni.h"

#include "UDifFunc_APark.h"
#include <UStandardDelegate>
#include <USqlAccessible>
#include <QtDebug>
//--------------------utech--------------------utech--------------------utech--------------------
UForm_AParkSvyatkoviDni::UForm_AParkSvyatkoviDni(int tWType, QWidget *parent)
        : UAParkTabWidget(tWType, parent)
{
	ui.setupUi(this);
	ui.spinBox_yearFilter->setValue(QDate::currentDate().year());
	
	twExt = new UDataFormView(ui.tableWidget_svyatkoviDni, "svyatkoviDni");
	twExt->setSortingEnabled(true);
	
	ui.tableWidget_svyatkoviDni->setColumnCount(3);
	ui.tableWidget_svyatkoviDni->setHorizontalHeaderLabels( QStringList() 
															<< "id"
															<< "Свято"
															<< "Дата");
	
	twExt->colNamesList << "Id" 
					<< "SvyatoName"
					<< "CDate";
	
	twExt->addColAlignment("SvyatoName", Qt::AlignLeft | Qt::AlignVCenter);
	twExt->addColAlignment("CDate", Qt::AlignRight | Qt::AlignVCenter);
	
	
	twExt->setItemDelegateForColumn("CDate", new UDateEditDelegate(QDate(2000,01,01), QDate(2100,12,31), ui.tableWidget_svyatkoviDni));
	
	twExt->setColumnHidden("id", true);
	twExt->setColumnWidth("SvyatoName", 250);
	twExt->setColumnWidth("CDate", 100);
	
	populateTable();
	
	connect(ui.pushButton_create, SIGNAL(clicked()), this, SLOT(pushButton_create_clicked()));
	connect(ui.pushButton_delete, SIGNAL(clicked()), this, SLOT(pushButton_delete_clicked()));
	connect(ui.pushButton_reload, SIGNAL(clicked()), this, SLOT(populateTable()));
	connect(ui.spinBox_yearFilter, SIGNAL(valueChanged(int)), this, SLOT(populateTable()));
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkSvyatkoviDni::pushButton_create_clicked()
{
	if (!twExt->addRow("INSERT INTO svyatkoviDni (CDate) VALUES (date('"
						+QDate(ui.spinBox_yearFilter->value(),12,1).toString("yyyy-MM-dd")+"'))"))
		QMessageBox::critical(0,"Помилка створення запису","Запис святкового дня не створено");
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkSvyatkoviDni::pushButton_delete_clicked()
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
void UForm_AParkSvyatkoviDni::populateTable()
{
	twExt->setSqlFilter("year(CDate)="+sqlStr(ui.spinBox_yearFilter->value()));
	twExt->populateTable();
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkSvyatkoviDni::populateToolBar(QToolBar * tBar)
{
	
}
//--------------------utech--------------------utech--------------------utech--------------------
UForm_AParkSvyatkoviDni::~UForm_AParkSvyatkoviDni()
{
	
}
//--------------------utech--------------------utech--------------------utech--------------------
