//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл виконання класу вікна налаштування програми
//
// Створений програмістами Компанії "Утех" 29.03.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------
#include "UForm_AParkZarplataAgentski.h"

#include "UDifFunc_APark.h"
#include <UStandardDelegate>

#include <QtDebug>
//--------------------utech--------------------utech--------------------utech--------------------
UForm_AParkZarplataAgentski::UForm_AParkZarplataAgentski(int tWType, QWidget *parent)
        : UAParkTabWidget(tWType, parent)
{
	ui.setupUi(this);
	
	twExt = new UDataFormView(ui.tableWidget, "agentski");
	twExt->setSortingEnabled(true);
	
	ui.tableWidget->setColumnCount(3);
	ui.tableWidget->setHorizontalHeaderLabels( QStringList() 
															<< "id"
															<< "Табельний номер працівника"
															<< "Сума");
	
	twExt->colNamesList << "Id" 
					<< "TabelNum_id"
					<< "Suma";
	
	twExt->insertWidget(ui.comboBox_tabNomer, "TabelNum_id");
	twExt->insertWidget(ui.doubleSpinBox_suma, "Suma");
	
	twExt->addColAlignment("TabelNum_id", Qt::AlignLeft | Qt::AlignVCenter);
	twExt->addColAlignment("Suma", Qt::AlignRight | Qt::AlignVCenter);
	
	//Ініціалізація делегатів для колонок таблиці
	QSqlQuery query;
	UIntStringList delegateList;
		//Делегат Піб водія + Табельний номер
	delegateList.clear();
	delegateList.insert(0, "");
	query.exec("SELECT id, Prizv, Imia, PoBatk FROM npr ORDER BY Prizv, Imia, PoBatk");
	while (query.next()){
		delegateList.insert(query.value(0).toInt(), "["+query.value(0).toString()+"] "+query.value(1).toString()+" "+query.value(2).toString()+" "+query.value(3).toString());
	}
	twExt->setItemDelegateForColumn("TabelNum_id", delegateList);
	twExt->setItemDelegateForColumn("Suma",  new UDoubleSpinBoxDelegate(0,1000000,2,ui.tableWidget));
	
	twExt->setColumnHidden("id", true);
	twExt->setColumnWidth("TabelNum_id", 300);
	twExt->setColumnWidth("Suma", 70);
	
	twExt->populateTable();
	
	connect(ui.pushButton_create, SIGNAL(clicked()), this, SLOT(pushButton_create_clicked()));
	connect(ui.pushButton_delete, SIGNAL(clicked()), this, SLOT(pushButton_delete_clicked()));
	connect(ui.pushButton_reload, SIGNAL(clicked()), twExt, SLOT(populateTable()));
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkZarplataAgentski::pushButton_create_clicked()
{
	if (!twExt->addRow())
		QMessageBox::critical(0,"Помилка створення запису","Запис нарахування агентських не створено");
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkZarplataAgentski::pushButton_delete_clicked()
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
void UForm_AParkZarplataAgentski::populateToolBar(QToolBar * tBar)
{
	
}
//--------------------utech--------------------utech--------------------utech--------------------
UForm_AParkZarplataAgentski::~UForm_AParkZarplataAgentski()
{
	
}
//--------------------utech--------------------utech--------------------utech--------------------
