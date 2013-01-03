//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл виконання класу вікна налаштування програми
//
// Створений програмістами Компанії "Утех" 29.03.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------
#include "UForm_AParkPracivnyky.h"

#include "UDifFunc_APark.h"
#include "UPrintDocs_APark.h"
#include <UStandardDelegate>
#include "UDialog_AParkDateFilter.h"
#include "UDialogYMFilter.h"

#include <QtDebug>
//--------------------utech--------------------utech--------------------utech--------------------
UForm_AParkPracivnyky::UForm_AParkPracivnyky(int tWType, QWidget *parent)
        : UAParkTabWidget(tWType, parent)
{
	ui.setupUi(this);
	
	twExt = new UDataFormView(ui.tableWidget_PerelikPracivnykiv, "npr");
	twExt->setSortingEnabled(true);
	twExt->colNamesList << "Id"
						<< "Id"
						<< "Prizv"
						<< "Imia"
						<< "Pobatk"
						<< "Data_nar"
						<< "Posada_id"
						<< "TypRoboty"
						<< "TypOplaty"
						<< "Iden_kod"
						<< "Tel"
						<< "Rozryad"
						<< "Stavka"
						<< "Pidrozdil_id"
						<< "Num_dit"
						<< "Ozn_pilgy"
						<< "Data_pruin_na_rob"
						<< "data_zvilnenia"
						<< "Klasnist_vodiya"
						<< "VidsDoplaty"
						<< "Alimenty"
						<< "Pensioner"
						<< "ChlenProfspilky"
						<< "Invalid"
						<< "Pracuye"
						<< "Buh_rahunok"
						<< "BrygadaNum"
						<< "KlasVodiya"
						<< "IsBrygadyr"
						<< "Naparnyky";
	
	twExt->addColAlignment("Id", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("Prizv", Qt::AlignVCenter | Qt::AlignLeft);
	twExt->addColAlignment("Imia", Qt::AlignVCenter | Qt::AlignLeft);
	twExt->addColAlignment("Pobatk", Qt::AlignVCenter | Qt::AlignLeft);
	twExt->addColAlignment("Data_nar", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("Posada_id", Qt::AlignVCenter | Qt::AlignLeft);
	twExt->addColAlignment("TypRoboty", Qt::AlignVCenter | Qt::AlignLeft);
	twExt->addColAlignment("TypOplaty", Qt::AlignVCenter | Qt::AlignLeft);
	twExt->addColAlignment("Iden_kod", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("Tel", Qt::AlignVCenter | Qt::AlignLeft);
	twExt->addColAlignment("Rozryad", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("Stavka", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("Pidrozdil_id", Qt::AlignVCenter | Qt::AlignLeft);
	twExt->addColAlignment("Num_dit", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("Ozn_pilgy", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("Data_pruin_na_rob", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("data_zvilnenia", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("Klasnist_vodiya", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("VidsDoplaty", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("Alimenty", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("Pensioner", Qt::AlignVCenter | Qt::AlignLeft);
	twExt->addColAlignment("ChlenProfspilky", Qt::AlignVCenter | Qt::AlignLeft);
	twExt->addColAlignment("Invalid", Qt::AlignVCenter | Qt::AlignLeft);
	twExt->addColAlignment("Pracuye", Qt::AlignVCenter | Qt::AlignLeft);
	twExt->addColAlignment("Buh_rahunok", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("BrygadaNum", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("KlasVodiya", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("IsBrygadyr", Qt::AlignVCenter | Qt::AlignLeft);
	twExt->addColAlignment("Naparnyky", Qt::AlignVCenter | Qt::AlignRight);
	
	ui.spinBox_TabNumber->setReadOnly(true);
	ui.dateEdit_dataZvilnenia->setReadOnly(true);
	twExt->insertWidget(ui.spinBox_TabNumber, "Id");
	twExt->insertWidget(ui.lineEdit_prizv, "Prizv");
	twExt->insertWidget(ui.lineEdit_imya, "Imia");
	twExt->insertWidget(ui.lineEdit_poBatk, "Pobatk");
	twExt->insertWidget(ui.dateEdit_dataNar, "Data_nar");
	twExt->insertWidget(ui.comboBox_posadaId, "Posada_id");
	twExt->insertWidget(ui.comboBox_typRoboty, "TypRoboty");
	twExt->insertWidget(ui.comboBox_typOplaty, "TypOplaty");
	twExt->insertWidget(ui.lineEdit_idenKod, "Iden_kod");
	twExt->insertWidget(ui.lineEdit_tel, "Tel");
	twExt->insertWidget(ui.spinBox_rozryad, "Rozryad");
	twExt->insertWidget(ui.doubleSpinBox_stavka, "Stavka");
	twExt->insertWidget(ui.comboBox_pidrozdil_id, "Pidrozdil_id");
	twExt->insertWidget(ui.spinBox_kilkistDitey, "Num_dit");
	twExt->insertWidget(ui.spinBox_oznakaPilgy, "Ozn_pilgy");
	twExt->insertWidget(ui.dateEdit_dataPryinyattyaNaRobotu, "Data_pruin_na_rob");
	twExt->insertWidget(ui.dateEdit_dataZvilnenia, "data_zvilnenia");
	twExt->insertWidget(ui.doubleSpinBox_klasnistVodiya, "Klasnist_vodiya");
	twExt->insertWidget(ui.doubleSpinBox_vidsDoplaty, "VidsDoplaty");
	twExt->insertWidget(ui.doubleSpinBox_alimenty, "Alimenty");
	twExt->insertWidget(ui.checkBox_pensioner, "Pensioner");
	twExt->insertWidget(ui.spinBox_buhRahunok, "Buh_rahunok");
	twExt->insertWidget(ui.checkBox_chlenPrifspilky, "ChlenProfspilky");
	twExt->insertWidget(ui.checkBox_invalid, "Invalid");
	twExt->insertWidget(ui.checkBox_pracuye, "Pracuye");
	twExt->insertWidget(ui.spinBox_brygada, "BrygadaNum");
	twExt->insertWidget(ui.spinBox_klasVodiya, "KlasVodiya");
	twExt->insertWidget(ui.checkBox_brygadyr, "IsBrygadyr");
	
	
	//Ініціалізація делегатів для колонок таблиці
	QSqlQuery query;
	UIntStringList delegateList;
		//Делегат Посада
	delegateList.clear();
	delegateList.insert(0, "");
	query.exec("SELECT id, Posada FROM taryfni_sitky");
	while (query.next()){
		delegateList.insert(query.value(0).toInt(), "["+query.value(0).toString()+"] - "+query.value(1).toString());
	}
	twExt->setItemDelegateForColumn("Posada_id", delegateList);
	
	//Делегат Підрозділ
	delegateList.clear();
	delegateList.insert(0, "");
	query.exec("SELECT id, Name FROM pidrozdily_salary ORDER BY Name");
	while (query.next()){
		delegateList.insert(query.value(0).toInt(), "["+query.value(0).toString()+"] - "+query.value(1).toString());
	}
	twExt->setItemDelegateForColumn("Pidrozdil_id", delegateList);
	
		//Делегат Тип роботи
	delegateList.clear();
	delegateList.insert(0, "[0]-У штаті");
	delegateList.insert(1, "[1]-По договору");
	delegateList.insert(1, "[2]-По сумісництву");
	twExt->setItemDelegateForColumn("TypRoboty", delegateList);
	
		//Делегат Тип оплати
	delegateList.clear();
	delegateList.insert(0, "[0]-Помісячна");
	delegateList.insert(1, "[1]-Погодинна");
	twExt->setItemDelegateForColumn("TypOplaty", delegateList);
	
	twExt->setItemDelegateForColumn(1, new USpinBoxDelegate(1,999999, ui.tableWidget_PerelikPracivnykiv));
	
	twExt->setItemDelegateForColumn("Data_nar", new UDateTimeDelegate(ui.tableWidget_PerelikPracivnykiv, "dd.MM.yyyy"));
	twExt->setItemDelegateForColumn("Data_pruin_na_rob", new UDateTimeDelegate(ui.tableWidget_PerelikPracivnykiv, "dd.MM.yyyy"));
	twExt->setItemDelegateForColumn("data_zvilnenia", new UDateTimeDelegate(ui.tableWidget_PerelikPracivnykiv, "dd.MM.yyyy"));
		
	twExt->setItemDelegateForColumn("Rozryad", new USpinBoxDelegate(0,5, ui.tableWidget_PerelikPracivnykiv));
	twExt->setItemDelegateForColumn("Ozn_pilgy", new USpinBoxDelegate(0,5, ui.tableWidget_PerelikPracivnykiv));
	twExt->setItemDelegateForColumn("KlasVodiya", new USpinBoxDelegate(0,5, ui.tableWidget_PerelikPracivnykiv));
	twExt->setItemDelegateForColumn("Num_dit", new USpinBoxDelegate(0,20, ui.tableWidget_PerelikPracivnykiv));
	twExt->setItemDelegateForColumn("Buh_rahunok", new USpinBoxDelegate(0,99999, ui.tableWidget_PerelikPracivnykiv));
	twExt->setItemDelegateForColumn("BrygadaNum", new USpinBoxDelegate(0,99999, ui.tableWidget_PerelikPracivnykiv));
	twExt->setItemDelegateForColumn("Naparnyky", new USpinBoxDelegate(0,99999, ui.tableWidget_PerelikPracivnykiv));
	
	twExt->setItemDelegateForColumn("Stavka", new UDoubleSpinBoxDelegate(0,100000, 2, ui.tableWidget_PerelikPracivnykiv));
	twExt->setItemDelegateForColumn("Klasnist_vodiya", new UDoubleSpinBoxDelegate(0,100000, 2, ui.tableWidget_PerelikPracivnykiv));
	twExt->setItemDelegateForColumn("VidsDoplaty", new UDoubleSpinBoxDelegate(0,100000, 2, ui.tableWidget_PerelikPracivnykiv));
	twExt->setItemDelegateForColumn("Alimenty", new UDoubleSpinBoxDelegate(0,100000, 2, ui.tableWidget_PerelikPracivnykiv));
	
	twExt->setItemDelegateForColumn("Pensioner", new UCheckBoxDelegate(ui.tableWidget_PerelikPracivnykiv));
	twExt->setItemDelegateForColumn("ChlenProfspilky", new UCheckBoxDelegate(ui.tableWidget_PerelikPracivnykiv));
	twExt->setItemDelegateForColumn("Invalid", new UCheckBoxDelegate(ui.tableWidget_PerelikPracivnykiv));
	twExt->setItemDelegateForColumn("Pracuye", new UCheckBoxDelegate(ui.tableWidget_PerelikPracivnykiv));
	twExt->setItemDelegateForColumn("IsBrygadyr", new UCheckBoxDelegate(ui.tableWidget_PerelikPracivnykiv));
	
	twExt->setColumnHidden(0);
	twExt->setColumnWidth("Prizv", 100);
	twExt->setColumnWidth("Imia", 100);
	twExt->setColumnWidth("Pobatk", 100);
	twExt->setColumnWidth("Data_nar", 80);
	twExt->setColumnWidth("Posada_id", 130);
	twExt->setColumnWidth("TypRoboty", 90);
	twExt->setColumnWidth("TypOplaty", 80);
	twExt->setColumnWidth("Iden_kod", 70);
	twExt->setColumnWidth("Tel", 80);
	twExt->setColumnWidth("Rozryad", 50);
	twExt->setColumnWidth("Stavka", 80);
	twExt->setColumnWidth("Pidrozdil_id", 120);
	twExt->setColumnWidth("Num_dit", 80);
	twExt->setColumnWidth("Ozn_pilgy", 50);
	twExt->setColumnWidth("Data_pruin_na_rob", 80);
	twExt->setColumnWidth("data_zvilnenia", 1);
	twExt->setColumnWidth("Klasnist_vodiya", 90);
	twExt->setColumnWidth("VidsDoplaty", 80);
	twExt->setColumnWidth("Alimenty", 80);
	twExt->setColumnWidth("Pensioner", 80);
	twExt->setColumnWidth("Buh_rahunok", 80);
	twExt->setColumnWidth("ChlenProfspilky", 80);
	twExt->setColumnWidth("Invalid", 80);
	twExt->setColumnWidth("Pracuye", 80);
	twExt->setColumnWidth("BrygadaNum", 60);
	twExt->setColumnWidth("KlasVodiya", 70);
	twExt->setColumnWidth("IsBrygadyr", 70);
	twExt->setColumnWidth("Naparnyky", 55);
	
	twExt->populateTable();
	
	connect(ui.pushButton_create, SIGNAL(clicked()), this, SLOT(pushButton_create_clicked()));
	connect(ui.pushButton_delete, SIGNAL(clicked()), this, SLOT(pushButton_delete_clicked()));
	connect(ui.pushButton_reload, SIGNAL(clicked()), twExt, SLOT(populateTable()));
	connect(ui.pushButton_zvilnyty, SIGNAL(clicked()), this, SLOT(pushButton_zvilnyty_pracivnyka()));
	connect(ui.lineEdit_search, SIGNAL(textChanged(QString)), this, SLOT(filtr_po_prizvyshchu()));
	connect(ui.pushButton_clearFiltr, SIGNAL(clicked(bool)), this, SLOT(clearFiltr()));
	
	connect(twExt, SIGNAL(tableItemEdited(QTableWidgetItem *)), this, SLOT(populateDovidnykValues(QTableWidgetItem *)));
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkPracivnyky::pushButton_create_clicked()
{
	if (!twExt->addRow())
		QMessageBox::critical(0,"Помилка створення запису","Запис шляхового листа не створено не створено");
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkPracivnyky::pushButton_delete_clicked()
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
void UForm_AParkPracivnyky::pushButton_zvilnyty_pracivnyka()
{
	if	( QMessageBox::question(
                this,
                "!!! Звільнення працівника !!!",
                "Ви дійсно бажаєте звільнити працівника?",
                "Так",
				"Ні-ні-ні",
                QString(), 0, 1)
		)
		return;
	UDialog_AParkDateFilter *d = new UDialog_AParkDateFilter((QDate::currentDate()), "Дата звільнення", "dd.MM.yyyy");
	if (d->exec()){
		QDate vDate = d->date();
		QSqlQuery query;
		if (!query.exec("UPDATE npr SET data_zvilnenia = '"+vDate.toString("yyyy-MM-dd")+"',\
						Pracuye = 0\
						WHERE id= "+sqlStr(ui.spinBox_TabNumber->value())+"")) 
		QMessageBox::critical(0,"Помикла звільнення працівника","Працівник не звільнений");
		query.next();
		twExt->populateTable();
	}
	delete d;
		
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkPracivnyky::filtr_po_prizvyshchu()
{
	if (ui.lineEdit_search->text().size() > 0)
		twExt->setSqlFilter("CONCAT(if(Prizv is NULL,'',Prizv),' ' , if(Imia is NULL,'',Imia), ' ' , if(Pobatk is NULL,'',Pobatk)) LIKE '%"+(ui.lineEdit_search->text())+"%'");
	else
		twExt->clearSqlFilter();
	twExt->populateTable();
		
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkPracivnyky::clearFiltr()
{
	ui.lineEdit_search->blockSignals(true);
	ui.lineEdit_search->clear();
	twExt->clearSqlFilter();
	twExt->populateTable();
	ui.lineEdit_search->blockSignals(false);
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkPracivnyky::populateDovidnykValues(QTableWidgetItem *item)
{
	
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkPracivnyky::populateToolBar(QToolBar * tBar)
{
	
}
//--------------------utech--------------------utech--------------------utech--------------------
UForm_AParkPracivnyky::~UForm_AParkPracivnyky()
{
	
}
//--------------------utech--------------------utech--------------------utech--------------------
