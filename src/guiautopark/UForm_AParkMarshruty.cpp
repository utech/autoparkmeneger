//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл виконання класу вікна налаштування програми
//
// Створений програмістами Компанії "Утех" 29.03.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------
#include "UForm_AParkMarshruty.h"

#include "UDifFunc_APark.h"
#include <UStandardDelegate>
#include <USqlAccessible>
#include <QtDebug>
//--------------------utech--------------------utech--------------------utech--------------------
UForm_AParkMarshruty::UForm_AParkMarshruty(int tWType, QWidget *parent)
        : UAParkTabWidget(tWType, parent)
{
	ui.setupUi(this);
	
	
	twExt = new UDataFormView(ui.tableWidget_marshruty, "marshruty");
	twExt->setSortingEnabled(true);
	
	ui.tableWidget_marshruty->setColumnCount(22);
	ui.tableWidget_marshruty->setHorizontalHeaderLabels( QStringList() 
															<< "id"
															<< "Код марш."
															<< "Напрямок"
															<< "№ граф."
															<< "№ зміни"
															<< "Довж."
															<< "Тип"
															<< "Пальне"
															<< "Виїзд"
															<< "Заїзд"
															<< "Ноч."
															<< "Дн.в роб."
															<< "Ч.в Нар."
															<< "Ч.в Марш."
															<< "Ч.з Розр."
															<< "Ч. Нічн."
															<< "Ч.на Рейс"
															<< "К-сть рейсів"
															<< "Проб.нул."
															<< "Проб.заг."
															<< "Витр.безд."
															<< "Автобус");
	
	twExt->colNamesList << "Id" 
					<< "KodMarshrutu"
					<< "MarshrutNapryamok"
					<< "GrafikNum"
					<< "ZminaNum"
					<< "DovjynaMarshrutu"
					<< "TypMarshrutu_Id"
					<< "TypVytratyPalnogo"
					<< "ChasVyizdu"
					<< "ChasZaizdu"
					<< "TypPoNochivli"
					<< "DniVRoboti"
					<< "ChasVNaryadi"
					<< "ChasVMarshruti"
					<< "ChasZRozryvom"
					<< "ChasNichnyi"
					<< "ChasNaReis"
					<< "KilkReisiv"
					<< "ProbigNulovyi"
					<< "ProbigZagalnyi"
					<< "VytrPalnNaBezdor"
					<< "RuhomyiSkald_garNum";
	
	twExt->insertWidget(ui.spinBox_KodMarshrutu, "KodMarshrutu");
	twExt->insertWidget(ui.lineEdit_MarshrutNapryamok, "MarshrutNapryamok");
	twExt->insertWidget(ui.spinBox_GrafikNum, "GrafikNum");
	twExt->insertWidget(ui.spinBox_ZminaNum, "ZminaNum");
	twExt->insertWidget(ui.doubleSpinBox_DovjynaMarshrutu, "DovjynaMarshrutu");
	twExt->insertWidget(ui.comboBox_TypMarshrutu_Id, "TypMarshrutu_Id");
	twExt->insertWidget(ui.comboBox_TypVytratyPalnogo, "TypVytratyPalnogo");
	twExt->insertWidget(ui.timeEdit_ChasVyizdu, "ChasVyizdu");
	twExt->insertWidget(ui.timeEdit_ChasZaizdu, "ChasZaizdu");
	twExt->insertWidget(ui.comboBox_TypPoNochivli, "TypPoNochivli");
	twExt->insertWidget(ui.spinBox_DniVRoboti, "DniVRoboti");
	twExt->insertWidget(ui.timeEdit_ChasVNaryadi, "ChasVNaryadi");
	twExt->insertWidget(ui.timeEdit_ChasVMarshruti, "ChasVMarshruti");
	twExt->insertWidget(ui.checkBox_ChasZRozryvom, "ChasZRozryvom");
	twExt->insertWidget(ui.timeEdit_ChasNichnyi, "ChasNichnyi");
	twExt->insertWidget(ui.timeEdit_ChasNaReis, "ChasNaReis");
	twExt->insertWidget(ui.spinBox_KilkReisiv, "KilkReisiv");
	twExt->insertWidget(ui.doubleSpinBox_ProbigNulovyi, "ProbigNulovyi");
	twExt->insertWidget(ui.doubleSpinBox_ProbigZagalnyi, "ProbigZagalnyi");
	twExt->insertWidget(ui.doubleSpinBox_VytrPalnNaBezdor, "VytrPalnNaBezdor");
	twExt->insertWidget(ui.comboBox_GarajNum, "RuhomyiSkald_garNum");
	
	twExt->addColAlignment("KodMarshrutu", Qt::AlignRight | Qt::AlignVCenter);
	twExt->addColAlignment("MarshrutNapryamok", Qt::AlignLeft | Qt::AlignVCenter);
	twExt->addColAlignment("GrafikNum", Qt::AlignRight | Qt::AlignVCenter);
	twExt->addColAlignment("ZminaNum", Qt::AlignRight | Qt::AlignVCenter);
	twExt->addColAlignment("DovjynaMarshrutu", Qt::AlignRight | Qt::AlignVCenter);
	twExt->addColAlignment("TypMarshrutu_Id", Qt::AlignLeft | Qt::AlignVCenter);
	twExt->addColAlignment("TypVytratyPalnogo", Qt::AlignLeft | Qt::AlignVCenter);
	twExt->addColAlignment("ChasVyizdu", Qt::AlignRight | Qt::AlignVCenter);
	twExt->addColAlignment("ChasZaizdu", Qt::AlignRight | Qt::AlignVCenter);
	twExt->addColAlignment("TypPoNochivli", Qt::AlignLeft | Qt::AlignVCenter);
	twExt->addColAlignment("DniVRoboti", Qt::AlignRight | Qt::AlignVCenter);
	twExt->addColAlignment("ChasVNaryadi", Qt::AlignRight | Qt::AlignVCenter);
	twExt->addColAlignment("ChasVMarshruti", Qt::AlignRight | Qt::AlignVCenter);
	twExt->addColAlignment("ChasZRozryvom", Qt::AlignRight | Qt::AlignVCenter);
	twExt->addColAlignment("ChasNichnyi", Qt::AlignRight | Qt::AlignVCenter);
	twExt->addColAlignment("ChasNaReis", Qt::AlignRight | Qt::AlignVCenter);
	twExt->addColAlignment("KilkReisiv", Qt::AlignRight | Qt::AlignVCenter);
	twExt->addColAlignment("ProbigNulovyi", Qt::AlignRight | Qt::AlignVCenter);
	twExt->addColAlignment("ProbigZagalnyi", Qt::AlignRight | Qt::AlignVCenter);
	twExt->addColAlignment("VytrPalnNaBezdor", Qt::AlignRight | Qt::AlignVCenter);
	twExt->addColAlignment("RuhomyiSkald_garNum", Qt::AlignLeft | Qt::AlignVCenter);
	
	//Ініціалізація делегатів для колонок таблиці
	QSqlQuery query;
	UIntStringList delegateList;
	
		//Делегат Тип місський, міжміський
	delegateList.clear();
	delegateList.insert(0, "");
	query.exec("SELECT id, TypName FROM typmarshrutu");
	while (query.next()){
		delegateList.insert(query.value(0).toInt(), query.value(1).toString());
	}
	twExt->setItemDelegateForColumn("TypMarshrutu_Id",  delegateList);
		//Делегат Тип по зимі
	delegateList.clear();
	delegateList.insert(0, "");
	query.exec("SELECT id, ShortTypName FROM typvytratypalnogo");
	while (query.next()){
		delegateList.insert(query.value(0).toInt(), query.value(1).toString());
	}
	twExt->setItemDelegateForColumn("TypVytratyPalnogo", delegateList);
	
		//Делегат Признаку ночівлі
	delegateList.clear();
	delegateList.insert(0, "");
	query.exec("SELECT id, ShortTypName FROM typponochivli");
	while (query.next()){
		delegateList.insert(query.value(0).toInt(), query.value(1).toString());
	}
	twExt->setItemDelegateForColumn("TypPoNochivli", delegateList);
		//Делегат Рухомого складу
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
	twExt->setItemDelegateForColumn("RuhomyiSkald_garNum",  delegateList);
	
	twExt->setItemDelegateForColumn("KodMarshrutu",  new USpinBoxDelegate(0,10000,ui.tableWidget_marshruty));
	twExt->setItemDelegateForColumn("GrafikNum",  new USpinBoxDelegate(0,10000,ui.tableWidget_marshruty));
	twExt->setItemDelegateForColumn("ZminaNum",  new USpinBoxDelegate(0,10000,ui.tableWidget_marshruty));
	twExt->setItemDelegateForColumn("KilkReisiv",  new USpinBoxDelegate(0,100,ui.tableWidget_marshruty));
	
	twExt->setItemDelegateForColumn("DovjynaMarshrutu",  new UDoubleSpinBoxDelegate(0,10000,1,ui.tableWidget_marshruty));
	twExt->setItemDelegateForColumn("ProbigNulovyi", new UDoubleSpinBoxDelegate(0,10000,1,ui.tableWidget_marshruty));
	twExt->setItemDelegateForColumn("ProbigZagalnyi", new UDoubleSpinBoxDelegate(0,10000,1,ui.tableWidget_marshruty));
	twExt->setItemDelegateForColumn("VytrPalnNaBezdor", new UDoubleSpinBoxDelegate(0,10000,1,ui.tableWidget_marshruty));
	
	twExt->setItemDelegateForColumn("ChasVyizdu", new UTimeDelegate(ui.tableWidget_marshruty, "H:mm"));
	twExt->setItemDelegateForColumn("ChasZaizdu", new UTimeDelegate(ui.tableWidget_marshruty, "H:mm"));
	twExt->setItemDelegateForColumn("ChasVNaryadi", new UTimeDelegate(ui.tableWidget_marshruty, "H:mm"));
	twExt->setItemDelegateForColumn("ChasVMarshruti", new UTimeDelegate(ui.tableWidget_marshruty, "H:mm"));
	twExt->setItemDelegateForColumn("ChasNichnyi", new UTimeDelegate(ui.tableWidget_marshruty, "H:mm"));
	twExt->setItemDelegateForColumn("ChasNaReis", new UTimeDelegate(ui.tableWidget_marshruty, "H:mm"));
	
	twExt->setItemDelegateForColumn("ChasZRozryvom", new UCheckBoxDelegate(ui.tableWidget_marshruty, "Так", "Ні"));
	
	twExt->setColumnHidden("id", true);
	twExt->setColumnWidth("KodMarshrutu", 70);
	twExt->setColumnWidth("MarshrutNapryamok", 130);
	twExt->setColumnWidth("GrafikNum", 57);
	twExt->setColumnWidth("ZminaNum", 57);
	twExt->setColumnWidth("DovjynaMarshrutu", 50);
	twExt->setColumnWidth("TypMarshrutu_Id", 75);
	twExt->setColumnWidth("TypVytratyPalnogo", 52);
	twExt->setColumnWidth("ChasVyizdu", 50);
	twExt->setColumnWidth("ChasZaizdu", 50);
	twExt->setColumnWidth("TypPoNochivli", 33);
	twExt->setColumnWidth("DniVRoboti", 58);
	twExt->setColumnWidth("ChasVNaryadi", 55);
	twExt->setColumnWidth("ChasVMarshruti", 63);
	twExt->setColumnWidth("ChasZRozryvom", 58);
	twExt->setColumnWidth("ChasNichnyi", 55);
	twExt->setColumnWidth("ChasNaReis", 63);
	twExt->setColumnWidth("KilkReisiv", 80);
	twExt->setColumnWidth("ProbigNulovyi", 65);
	twExt->setColumnWidth("ProbigZagalnyi", 65);
	twExt->setColumnWidth("VytrPalnNaBezdor", 75);
	twExt->setColumnWidth("RuhomyiSkald_garNum", 100);
	
	twExt->populateTable();
	
	connect(ui.pushButton_create, SIGNAL(clicked()), this, SLOT(pushButton_create_clicked()));
	connect(ui.pushButton_delete, SIGNAL(clicked()), this, SLOT(pushButton_delete_clicked()));
	connect(ui.pushButton_reload, SIGNAL(clicked()), twExt, SLOT(populateTable()));
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkMarshruty::pushButton_create_clicked()
{
	if (!twExt->addRow())
		QMessageBox::critical(0,"Помилка створення запису","Запис маршруту не створено");
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkMarshruty::pushButton_delete_clicked()
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
void UForm_AParkMarshruty::populateToolBar(QToolBar * tBar)
{
	
}
//--------------------utech--------------------utech--------------------utech--------------------
UForm_AParkMarshruty::~UForm_AParkMarshruty()
{
	
}
//--------------------utech--------------------utech--------------------utech--------------------
