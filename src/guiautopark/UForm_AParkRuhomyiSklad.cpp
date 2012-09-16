//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл виконання класу вікна налаштування програми
//
// Створений програмістами Компанії "Утех" 29.03.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------
#include "UForm_AParkRuhomyiSklad.h"

#include "UDifFunc_APark.h"
#include <UStandardDelegate>

#include <QtDebug>
//--------------------utech--------------------utech--------------------utech--------------------
UForm_AParkRuhomyiSklad::UForm_AParkRuhomyiSklad(int tWType, QWidget *parent)
        : UAParkTabWidget(tWType, parent)
{
	ui.setupUi(this);
	
	twExt = new UDataFormView(ui.tableWidget_ruhomyiSklad, "ruhomyiSklad");
	twExt->setSortingEnabled(true);
	twExt->colNamesList << "Id"
						<< "Id"
						<< "GarajNumber" 
						<< "NomernyiZnak" 
						<< "MarkaAuto_Id" 
						<< "TO1" 
						<< "TO2" 
						<< "KilkSydMisc" 
						<< "VvedenoVEkspluataciyu" 
						<< "MarkaPalnogo_Id"
						<< "RozhidPalnogo" 
						<< "Brygada_Id";
	
	ui.spinBox_id->setReadOnly(true);
	twExt->insertWidget(ui.spinBox_id, "Id");
	twExt->insertWidget(ui.spinBox_GarajNumber, "GarajNumber");
	twExt->insertWidget(ui.lineEdit_NomernyiZnak, "NomernyiZnak");
	twExt->insertWidget(ui.comboBox_MarkaAuto_Id, "MarkaAuto_Id");
	twExt->insertWidget(ui.spinBox_TO1, "TO1");
	twExt->insertWidget(ui.spinBox_TO2, "TO2");
	twExt->insertWidget(ui.spinBox_KilkSydMisc, "KilkSydMisc");
	twExt->insertWidget(ui.dateEdit_VvedenoVEkspluataciyu, "VvedenoVEkspluataciyu");
	twExt->insertWidget(ui.comboBox_MarkaPalnogo_Id, "MarkaPalnogo_Id");
	twExt->insertWidget(ui.doubleSpinBox_RozhidPalnogo, "RozhidPalnogo");
	twExt->insertWidget(ui.spinBox_Brygada_Id, "Brygada_Id");
	
	//Ініціалізація делегатів для колонок таблиці
	QSqlQuery query;
	UIntStringList delegateList;
		//Делегат марки авто
	delegateList.clear();
	delegateList.insert(0, "");
	query.exec("SELECT Id, concat('/',MarkaName,'/ ', MarkaShyfr)  FROM markaauto");
	while (query.next()){
		delegateList.insert(query.value(0).toInt(), query.value(1).toString());
	}
	twExt->setItemDelegateForColumn("MarkaAuto_Id", delegateList);
		//Делегат марки пального
	delegateList.clear();
	delegateList.insert(0, "");
	query.exec("SELECT id, MarkaName FROM markapalnogo");
	while (query.next()){
		delegateList.insert(query.value(0).toInt(), query.value(1).toString());
	}
	twExt->setItemDelegateForColumn("MarkaPalnogo_Id", delegateList);
	
	twExt->setItemDelegateForColumn(1, new USpinBoxDelegate(0,100,ui.tableWidget_ruhomyiSklad));
	twExt->setItemDelegateForColumn("RozhidPalnogo", new UDoubleSpinBoxDelegate(0,100,2,ui.tableWidget_ruhomyiSklad));
	
	twExt->setColumnHidden(0, true);
	twExt->setColumnWidth("Id", 40);
	twExt->setColumnWidth("GarajNumber", 90);
	twExt->setColumnWidth("NomernyiZnak", 90);
	twExt->setColumnWidth("MarkaAuto_Id" , 200);
	twExt->setColumnWidth("TO1", 60);
	twExt->setColumnWidth("TO2", 60);
	twExt->setColumnWidth("KilkSydMisc", 80);
	twExt->setColumnWidth("VvedenoVEkspluataciyu", 120);
	twExt->setColumnWidth("MarkaPalnogo_Id", 80);
	twExt->setColumnWidth("RozhidPalnogo", 80);
	twExt->setColumnWidth("Brygada_Id", 80);
	
	twExt->addColAlignment("Id", Qt::AlignRight | Qt::AlignVCenter);
	twExt->addColAlignment("GarajNumber", Qt::AlignRight | Qt::AlignVCenter);
	twExt->addColAlignment("NomernyiZnak", Qt::AlignLeft | Qt::AlignVCenter);
	twExt->addColAlignment("MarkaAuto_Id", Qt::AlignLeft | Qt::AlignVCenter);
	twExt->addColAlignment("TO1", Qt::AlignRight | Qt::AlignVCenter);
	twExt->addColAlignment("TO2", Qt::AlignRight | Qt::AlignVCenter);
	twExt->addColAlignment("KilkSydMisc", Qt::AlignRight | Qt::AlignVCenter);
	twExt->addColAlignment("VvedenoVEkspluataciyu", Qt::AlignRight | Qt::AlignVCenter);
	twExt->addColAlignment("RozhidPalnogo", Qt::AlignRight | Qt::AlignVCenter);
	twExt->addColAlignment("MarkaPalnogo_Id", Qt::AlignLeft | Qt::AlignVCenter);
	twExt->addColAlignment("Brygada_Id", Qt::AlignLeft | Qt::AlignVCenter);
	
	twExt->populateTable();
	
	connect(ui.pushButton_create, SIGNAL(clicked()), this, SLOT(pushButton_create_clicked()));
	connect(ui.pushButton_delete, SIGNAL(clicked()), this, SLOT(pushButton_delete_clicked()));
	connect(ui.pushButton_reload, SIGNAL(clicked()), twExt, SLOT(populateTable()));
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkRuhomyiSklad::pushButton_create_clicked()
{
	if (!twExt->addRow())
		QMessageBox::critical(0,"Помилка створення запису","Запис автобуса не створено");
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkRuhomyiSklad::pushButton_delete_clicked()
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
void UForm_AParkRuhomyiSklad::populateToolBar(QToolBar * tBar)
{
	
}
//--------------------utech--------------------utech--------------------utech--------------------
UForm_AParkRuhomyiSklad::~UForm_AParkRuhomyiSklad()
{
	
}
//--------------------utech--------------------utech--------------------utech--------------------
