//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл виконання класу вікна налаштування програми
//
// Створений програмістами Компанії "Утех" 29.03.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------
#include "UForm_AParkMarkyAuto.h"

#include "UDifFunc_APark.h"
#include <UStandardDelegate>

#include <QtDebug>
//--------------------utech--------------------utech--------------------utech--------------------
UForm_AParkMarkyAuto::UForm_AParkMarkyAuto(int tWType, QWidget *parent)
        : UAParkTabWidget(tWType, parent)
{
	ui.setupUi(this);
	
	twExt = new UDataFormView(ui.tableWidget_markaAuto, "markaAuto");
	twExt->setSortingEnabled(true);
	
	twExt->colNamesList << "Id"
						<< "Id"
						<< "MarkaName"
						<< "MarkaShyfr";
	
	twExt->addColAlignment("Id", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("MarkaName", Qt::AlignVCenter | Qt::AlignLeft);
	twExt->addColAlignment("MarkaShyfr", Qt::AlignVCenter | Qt::AlignLeft);
	
	twExt->setColumnHidden(0);
	twExt->setColumnWidth("Id", 40);
	twExt->setColumnWidth("MarkaName", 140);
	twExt->setColumnWidth("MarkaShyfr", 230);
	
	twExt->setItemDelegateForColumn(1, new USpinBoxDelegate(1,1000000000, twExt));
	
	twExt->populateTable();
	
	connect(ui.pushButton_reload, SIGNAL(clicked()), twExt,SLOT(populateTable()));
	connect(ui.pushButton_create, SIGNAL(clicked()), this, SLOT(pushButton_create_clicked()));
	connect(ui.pushButton_delete, SIGNAL(clicked()), this, SLOT(pushButton_delete_clicked()));
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkMarkyAuto::populateToolBar(QToolBar * tBar)
{
	
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkMarkyAuto::pushButton_create_clicked()
{
	if (!twExt->addRow())
		QMessageBox::critical(0,"Помилка створення запису","Запис марки автобуса не створено");
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkMarkyAuto::pushButton_delete_clicked()
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
UForm_AParkMarkyAuto::~UForm_AParkMarkyAuto()
{
	
}
//--------------------utech--------------------utech--------------------utech--------------------
