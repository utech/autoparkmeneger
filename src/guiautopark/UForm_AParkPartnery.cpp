//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл виконання класу вікна налаштування програми
//
// Створений програмістами Компанії "Утех" 29.03.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------
#include "UForm_AParkPartnery.h"

#include "UDifFunc_APark.h"
#include <UStandardDelegate>

#include <QtDebug>
//--------------------utech--------------------utech--------------------utech--------------------
UForm_AParkPartnery::UForm_AParkPartnery(int tWType, QWidget *parent)
        : UAParkTabWidget(tWType, parent)
{
	ui.setupUi(this);
	
	ui.tableWidget_partnery->setColumnCount(5);
	twExt = new UDataFormView(ui.tableWidget_partnery, "dovPartners");
	twExt->setSortingEnabled(true);
	
	ui.tableWidget_partnery->setHorizontalHeaderLabels( QStringList() 
															<< "id"
															<< "Назва"
															<< "ЄДРПОУ"
															<< "Адреса"
															<< "Тел.");
	
	twExt->colNamesList << "Id"
						<< "Name"
						<< "EDRPOU"
						<< "Adresa"
						<< "Tel";
	
	twExt->addColAlignment("Id", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("Name", Qt::AlignVCenter | Qt::AlignLeft);
	twExt->addColAlignment("EDRPOU", Qt::AlignVCenter | Qt::AlignLeft);
	twExt->addColAlignment("Adresa", Qt::AlignVCenter | Qt::AlignLeft);
	twExt->addColAlignment("Tel", Qt::AlignVCenter | Qt::AlignLeft);
	
	twExt->setColumnHidden(0);
	twExt->setColumnWidth("Id", 40);
	twExt->setColumnWidth("Name", 250);
	twExt->setColumnWidth("EDRPOU", 80);
	twExt->setColumnWidth("Adresa", 200);
	twExt->setColumnWidth("Tel", 100);
	
	twExt->populateTable();
	
	connect(ui.pushButton_reload, SIGNAL(clicked()), twExt,SLOT(populateTable()));
	connect(ui.pushButton_create, SIGNAL(clicked()), this, SLOT(pushButton_create_clicked()));
	connect(ui.pushButton_delete, SIGNAL(clicked()), this, SLOT(pushButton_delete_clicked()));
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkPartnery::populateToolBar(QToolBar * tBar)
{
	
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkPartnery::pushButton_create_clicked()
{
	if (!twExt->addRow("INSERT INTO dovPartners (IsPostach) VALUES (1)"))
		QMessageBox::critical(0,"Помилка створення запису","Запис партнера не створено");
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkPartnery::pushButton_delete_clicked()
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
UForm_AParkPartnery::~UForm_AParkPartnery()
{
	
}
//--------------------utech--------------------utech--------------------utech--------------------
