//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл виконання класу вікна налаштування програми
//
// Створений програмістами Компанії "Утех" 29.03.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------
#include "UForm_AParkShlyahovyiLyst.h"

#include "UDifFunc_APark.h"
#include "UPrintDocs_APark.h"
#include <UStandardDelegate>
#include "UDialog_AParkDateFilter.h"
#include "UDialog_AParkMarshrutTypeDateFilter.h"
#include "UAutoParkMeneger_APark.h"

#include <U2List>

#include <QtDebug>
//--------------------utech--------------------utech--------------------utech--------------------
UForm_AParkShlyahovyiLyst::UForm_AParkShlyahovyiLyst(int tWType, QWidget *parent)
        : UAParkTabWidget(tWType, parent)
{
	ui.setupUi(this);
	autoFilterCB = new UIntEditingComboBox(ui.comboBox_autoFilter);
	vodiyFilterCB = new UIntEditingComboBox(ui.comboBox_vodiyFilter);
	marshrutFilterCB = new UIntEditingComboBox(ui.comboBox_marshrutFilter);
	nochivlyaFilterCB = new UIntEditingComboBox(ui.comboBox_nochivlyaFilter);
	
	ui.groupBox_extFilter->setChecked(false);
	ui.groupBox_shyahLystNumberFilter->setChecked(false);
	ui.groupBox_autoFilter->setChecked(false);
	ui.groupBox_vodiyFilter->setChecked(false);
	ui.groupBox_marshrutFilter->setChecked(false);
	ui.groupBox_dataVyizduFilter->setChecked(false);
	ui.groupBox_monthVyizduFilter->setChecked(false);
	ui.groupBox_nochivlyaFilter->setChecked(false);
	ui.groupBox_extFilter->setVisible(false);
	ui.groupBox_korygFilter->setChecked(false);
	ui.pushButton_showHideExtSearch->setIcon(QIcon(":/icontexto_webdev_pack/icontexto_webdev_pack/icontexto-webdev-arrow-up-016x016.png"));
	
	ui.dateEdit_filtr->setDate(QDate::currentDate());
	ui.dateEdit_dataVyizduFilter->setDate(QDate::currentDate());
	ui.dateEdit_monthVyizduFilter->setDate(QDate::currentDate());
	
	ui.tableWidget_ShlyahovyiLyst->setColumnCount(28);
	twExt = new UDataFormView(ui.tableWidget_ShlyahovyiLyst, "shlyahovyiLyst");
	twExt->setSortingEnabled(true);
	
	ui.tableWidget_ShlyahovyiLyst->setHorizontalHeaderLabels( QStringList() 
															<< "id"
															<< "№ Шл.л."
															<< "Автоб."
															<< "Водій"
															<< "Маршрут."
															<< "№ граф."
															<< "№ зміни"
															<< "Кориг.."
															<< "Ніч."
															<< "Виїзд"
															<< "Заїзд"
															<< "Д.Звітн."
															<< "Заг.Проб."
															<< "Запр.гот."
															<< "План"
															<< "№ ЛОРО"
															<< "К-сть квт."
															<< "Сума"
															<< "А.К-сть квт."
															<< "А.сума"
															<< "Пільг."
															<< "Ч.в Нар."
															<< "Ч.в Рез."
															<< "Ч.в Мар."
															<< "Пл.к-сть.рейс."
															<< "Фк.к-сть.рейс."
															<< "Пл.розх.пальн."
															<< "Фк.розх.пальн.");
	
	twExt->colNamesList << "Id"
						<< "ShlyahovyiLystNum_id"
						<< "GarajNum_id"
						<< "VodiyTabelNum_id"
						<< "KodMarshrutu_id"
						<< "GrafikNum"
						<< "ZminaNum"
						<< "IsKoryguv"
						<< "TypPoNochivli_id"
						<< "DataVyizdu"
						<< "DataZaizdu"
						<< "ToZvitDate"
						<< "ZagalnProbig"
						<< "ZapravkaZaGotivku"
						<< "PlanNaZminu"
						<< "LORONumber"
						<< "KilkProdKvytkiv"
						<< "VartProdKvytkiv"
						<< "KilkProdKvytkivAutoStat"
						<< "VartProdKvytkivAutoStat"
						<< "PilgoviPasajyry"
						<< "ChasVNaryadi"
						<< "ChasVRezervi"
						<< "ChasVMarshruti"
						<< "PlanKilkReisiv"
						<< "FaktKilkReisiv"
						<< "PlanRozhidPalnogo"
						<< "FactRozhidPalnogo";
	
	twExt->addColAlignment("ShlyahovyiLystNum_id", Qt::AlignVCenter | Qt::AlignLeft);
	twExt->addColAlignment("KodMarshrutu_id", Qt::AlignVCenter | Qt::AlignLeft);
	twExt->addColAlignment("GrafikNum", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("ZminaNum", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("TypPoNochivli_id", Qt::AlignVCenter | Qt::AlignLeft);
	twExt->addColAlignment("VodiyTabelNum_id", Qt::AlignVCenter | Qt::AlignLeft);
	twExt->addColAlignment("GarajNum_id", Qt::AlignVCenter | Qt::AlignLeft);
	twExt->addColAlignment("DataVyizdu", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("DataZaizdu", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("ToZvitDate", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("IsKoryguv", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("ChasVNaryadi", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("ChasVRezervi", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("ChasVMarshruti", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("KilkProdKvytkiv", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("VartProdKvytkiv", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("KilkProdKvytkivAutoStat", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("VartProdKvytkivAutoStat", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("PlanNaZminu", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("LORONumber", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("ZapravkaZaGotivku", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("PilgoviPasajyry", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("ZagalnProbig", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("PlanKilkReisiv", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("FaktKilkReisiv", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("PlanRozhidPalnogo", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("FactRozhidPalnogo", Qt::AlignVCenter | Qt::AlignRight);
	
	twExt->insertWidget(ui.spinBox_ShlyahovyiLystNumber, "ShlyahovyiLystNum_id");
	twExt->insertWidget(ui.comboBox_marshrut, "KodMarshrutu_id");
	twExt->insertWidget(ui.spinBox_mtGrafNum, "GrafikNum");
	twExt->insertWidget(ui.spinBox_mtZminaNum, "ZminaNum");
	twExt->insertWidget(ui.comboBox_nochivlya, "TypPoNochivli_id");
	twExt->insertWidget(ui.comboBox_vodiy, "VodiyTabelNum_id");
	twExt->insertWidget(ui.comboBox_auto, "GarajNum_id");
	twExt->insertWidget(ui.dateTimeEdit_vyizdDate, "DataVyizdu");
	twExt->insertWidget(ui.dateTimeEdit_zaizdDate, "DataZaizdu");
	twExt->insertWidget(ui.dateTimeEdit_toZvitDate, "ToZvitDate");
	twExt->insertWidget(ui.checkBox_korekciya, "IsKoryguv");
	twExt->insertWidget(ui.timeEdit_ChasVNaryadi, "ChasVNaryadi");
	twExt->insertWidget(ui.timeEdit_ChasVRezervi, "ChasVRezervi");
	twExt->insertWidget(ui.timeEdit_ChasVMarshruti, "ChasVMarshruti");
	twExt->insertWidget(ui.spinBox_KilkistProdanyhKvytkiv, "KilkProdKvytkiv");
	twExt->insertWidget(ui.doubleSpinBox_SumaProdanyhKvytkiv, "VartProdKvytkiv");
	twExt->insertWidget(ui.spinBox_KilkistProdanyhKvytkivAS, "KilkProdKvytkivAutoStat");
	twExt->insertWidget(ui.doubleSpinBox_SumaProdanyhKvytkivAS, "VartProdKvytkivAutoStat");
	twExt->insertWidget(ui.doubleSpinBox_PlanNaZminu, "PlanNaZminu");
	twExt->insertWidget(ui.spinBox_LORONumber, "LORONumber");
	twExt->insertWidget(ui.doubleSpinBox_ZapravkaZaGotivku, "ZapravkaZaGotivku");
	twExt->insertWidget(ui.spinBox_PilgoviPasajyry, "PilgoviPasajyry");
	twExt->insertWidget(ui.doubleSpinBox_ZagalnProbig, "ZagalnProbig");
	twExt->insertWidget(ui.spinBox_PlanKilkReisiv, "PlanKilkReisiv");
	twExt->insertWidget(ui.spinBox_FactKilkReisiv, "FaktKilkReisiv");
	twExt->insertWidget(ui.doubleSpinBox_PlanRozhidPalnogo, "PlanRozhidPalnogo");
	twExt->insertWidget(ui.doubleSpinBox_FactRozhidPalnogo, "FactRozhidPalnogo");
	
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
	delegateList.replaceValueAt(0, " --- Усі ---");
	twExt->populateComboBoxItems(ui.comboBox_autoFilter, delegateList);
	
		//Делегат Піб водія + Табельний номер
	delegateList.clear();
	delegateList.insert(0, "");
	query.exec("SELECT id, Prizv, Imia, PoBatk FROM npr ORDER BY Prizv, Imia, PoBatk");
	while (query.next()){
		delegateList.insert(query.value(0).toInt(), "["+query.value(0).toString()+"] "+query.value(1).toString()+" "+query.value(2).toString()+" "+query.value(3).toString());
	}
	twExt->setItemDelegateForColumn("VodiyTabelNum_id", delegateList);
	delegateList.replaceValueAt(0, " --- Усі ---");
	twExt->populateComboBoxItems(ui.comboBox_vodiyFilter, delegateList);
	
		//Делегат Номер маршруту
	delegateList.clear();
	delegateList.insert(0, "");
	query.exec("SELECT KodMarshrutu, MarshrutNapryamok FROM marshruty");
	while (query.next()){
		delegateList.insert(query.value(0).toInt(), "["+query.value(0).toString()+"] "+query.value(1).toString());
	}
	twExt->setItemDelegateForColumn("KodMarshrutu_id", delegateList);
	delegateList.replaceValueAt(0, " --- Усі ---");
	twExt->populateComboBoxItems(ui.comboBox_marshrutFilter, delegateList);
	
		//Делегат Признаку ночівлі
	delegateList.clear();
	delegateList.insert(0, "");
	query.exec("SELECT id, ShortTypName FROM typponochivli");
	while (query.next()){
		delegateList.insert(query.value(0).toInt(), query.value(1).toString());
	}
	twExt->setItemDelegateForColumn("TypPoNochivli_id", delegateList);
	delegateList.replaceValueAt(0, " --- Усі ---");
	twExt->populateComboBoxItems(ui.comboBox_nochivlyaFilter, delegateList);
		
		//Делегат корекції плану
	twExt->setItemDelegateForColumn("IsKoryguv", new UCheckBoxDelegate(twExt, "Так", "Ні"));
	
	ui.tableWidget_ShlyahovyiLyst->setItemDelegateForColumn(twExt->columnNumber("DataVyizdu"), new UDateTimeDelegate(ui.tableWidget_ShlyahovyiLyst,"dd.MM.yyyy"));
	ui.tableWidget_ShlyahovyiLyst->setItemDelegateForColumn(twExt->columnNumber("DataZaizdu"), new UDateTimeDelegate(ui.tableWidget_ShlyahovyiLyst,"dd.MM.yyyy"));
	ui.tableWidget_ShlyahovyiLyst->setItemDelegateForColumn(twExt->columnNumber("ToZvitDate"), new UDateTimeDelegate(ui.tableWidget_ShlyahovyiLyst,"dd.MM.yyyy"));
	
	ui.tableWidget_ShlyahovyiLyst->setItemDelegateForColumn(twExt->columnNumber("ChasVNaryadi"), new UTimeDelegate(ui.tableWidget_ShlyahovyiLyst));
	ui.tableWidget_ShlyahovyiLyst->setItemDelegateForColumn(twExt->columnNumber("ChasVRezervi"), new UTimeDelegate(ui.tableWidget_ShlyahovyiLyst));
	ui.tableWidget_ShlyahovyiLyst->setItemDelegateForColumn(twExt->columnNumber("ChasVMarshruti"), new UTimeDelegate(ui.tableWidget_ShlyahovyiLyst));
	
	ui.tableWidget_ShlyahovyiLyst->setItemDelegateForColumn(twExt->columnNumber("VartProdKvytkiv"), new UDoubleSpinBoxDelegate(0,100000, 2, ui.tableWidget_ShlyahovyiLyst));
	ui.tableWidget_ShlyahovyiLyst->setItemDelegateForColumn(twExt->columnNumber("VartProdKvytkivAutoStat"), new UDoubleSpinBoxDelegate(0,100000, 2, ui.tableWidget_ShlyahovyiLyst));
	ui.tableWidget_ShlyahovyiLyst->setItemDelegateForColumn(twExt->columnNumber("PlanNaZminu"), new UDoubleSpinBoxDelegate(0,100000, 2, ui.tableWidget_ShlyahovyiLyst));
	ui.tableWidget_ShlyahovyiLyst->setItemDelegateForColumn(twExt->columnNumber("ZapravkaZaGotivku"), new UDoubleSpinBoxDelegate(0,100000, 2, ui.tableWidget_ShlyahovyiLyst));
	ui.tableWidget_ShlyahovyiLyst->setItemDelegateForColumn(twExt->columnNumber("ZagalnProbig"), new UDoubleSpinBoxDelegate(0,100000, 2, ui.tableWidget_ShlyahovyiLyst));
	ui.tableWidget_ShlyahovyiLyst->setItemDelegateForColumn(twExt->columnNumber("PlanRozhidPalnogo"), new UDoubleSpinBoxDelegate(0,1000, 1, ui.tableWidget_ShlyahovyiLyst));
	ui.tableWidget_ShlyahovyiLyst->setItemDelegateForColumn(twExt->columnNumber("FactRozhidPalnogo"), new UDoubleSpinBoxDelegate(0,1000, 1, ui.tableWidget_ShlyahovyiLyst));
	ui.tableWidget_ShlyahovyiLyst->setItemDelegateForColumn(twExt->columnNumber("LORONumber"), new USpinBoxDelegate(0,999999, ui.tableWidget_ShlyahovyiLyst));
	
	ui.tableWidget_ShlyahovyiLyst->setColumnHidden(0, true);
	twExt->setColumnWidth("ShlyahovyiLystNum_id", 60);
	twExt->setColumnWidth("KodMarshrutu_id", 120);
	twExt->setColumnWidth("GrafikNum", 57);
	twExt->setColumnWidth("ZminaNum", 57);
	twExt->setColumnWidth("TypPoNochivli_id", 55);
	twExt->setColumnWidth("VodiyTabelNum_id", 140);
	twExt->setColumnWidth("GarajNum_id", 150);
	twExt->setColumnWidth("DataVyizdu", 100);
	twExt->setColumnWidth("DataZaizdu", 100);
	twExt->setColumnWidth("ToZvitDate", 100);
	twExt->setColumnWidth("IsKoryguv", 43);
	twExt->setColumnWidth("ChasVNaryadi", 55);
	twExt->setColumnWidth("ChasVRezervi", 55);
	twExt->setColumnWidth("ChasVMarshruti", 55);
	twExt->setColumnWidth("KilkProdKvytkiv", 70);
	twExt->setColumnWidth("VartProdKvytkiv", 60);
	twExt->setColumnWidth("KilkProdKvytkivAutoStat", 75);
	twExt->setColumnWidth("VartProdKvytkivAutoStat", 65);
	twExt->setColumnWidth("PlanNaZminu", 60);
	twExt->setColumnWidth("LORONumber", 60);
	twExt->setColumnWidth("ZapravkaZaGotivku", 60);
	twExt->setColumnWidth("PilgoviPasajyry", 40);
	twExt->setColumnWidth("ZagalnProbig", 65);
	twExt->setColumnWidth("PlanKilkReisiv", 90);
	twExt->setColumnWidth("FaktKilkReisiv", 90);
	twExt->setColumnWidth("PlanRozhidPalnogo", 95);
	twExt->setColumnWidth("FactRozhidPalnogo", 95);
	
	setDateFilter();
	
	connect(ui.toolButton_readDefaultMarshrutZnach, SIGNAL(clicked()), this, SLOT(populateDefaultMarshrutZnach()));
	
	connect(ui.pushButton_create, SIGNAL(clicked()), this, SLOT(pushButton_create_clicked()));
	connect(ui.pushButton_delete, SIGNAL(clicked()), this, SLOT(pushButton_delete_clicked()));
	connect(ui.pushButton_reload, SIGNAL(clicked()), this, SLOT(setDateFilter()));
	connect(ui.dateEdit_filtr, SIGNAL(dateChanged(const QDate &)), this, SLOT(setDateFilter()));
	
	connect(twExt, SIGNAL(tableItemEdited(QTableWidgetItem *)), this, SLOT(populateDovidnykValues(QTableWidgetItem *)));
	
	connect(ui.action_printVidomistVykonannyaPlanuVDen, SIGNAL(activated()), this, SLOT(action_printVidomistVykonannyaPlanuVDen_activated()));
	connect(ui.action_printZvedenaVidomistPoDorojnihLystahZaMisyac, SIGNAL(activated()), this, SLOT(action_printZvedenaVidomistPoDorojnihLystahZaMisyac_activated()));
	connect(ui.action_printZvedenaVidomistPoTupahMarshrutivZaMisyac, SIGNAL(activated()), this, SLOT(action_printZvedenaVidomistPoTupahMarshrutivZaMisyac_activated()));
	connect(ui.action_printZvitProZdanuVyruchkuGotivkoyu, SIGNAL(activated()), this, SLOT(action_printZvitProZdanuVyruchkuGotivkoyu_activated()));
	connect(ui.action_printZvitProPerevezPilgPasajyriv, SIGNAL(activated()), this, SLOT(action_printZvitProPerevezPilgPasajyriv_activated()));
	connect(ui.action_printVidomistMarshrutivVDen, SIGNAL(activated()), this, SLOT(action_printVidomistMarshrutivVDen_activated()));
	
	//Налаштування фільтрування
	groupBox_extFilter_toggled();
	connect(ui.pushButton_showHideExtSearch, SIGNAL(clicked()), this, SLOT(pushButton_showHideExtSearch_clicked()));
	connect(ui.groupBox_extFilter, SIGNAL(toggled(bool)), this, SLOT(groupBox_extFilter_toggled()));
	connect(ui.pushButton_execFilter, SIGNAL(clicked()), this, SLOT(pushButton_execFilter_clicked()));
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkShlyahovyiLyst::pushButton_create_clicked()
{
	if (!twExt->addRow("INSERT INTO shlyahovyiLyst (DataVyizdu, DataZaizdu, ToZvitDate) \
						VALUES ('"+ui.dateEdit_filtr->date().toString("yyyy-MM-dd")+"', \
								'"+ui.dateEdit_filtr->date().toString("yyyy-MM-dd")+"', \
								'"+ui.dateEdit_filtr->date().toString("yyyy-MM-dd")+"')"))
		QMessageBox::critical(0,"Помилка створення запису","Запис шляхового листа не створено не створено");
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkShlyahovyiLyst::pushButton_delete_clicked()
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
void UForm_AParkShlyahovyiLyst::setDateFilter()
{
	twExt->setSqlFilter("date(DataVyizdu)='"+ui.dateEdit_filtr->date().toString("yyyy-MM-dd")+"'");
	twExt->populateTable();
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkShlyahovyiLyst::populateDovidnykValues(QTableWidgetItem *item)
{
	int column=item->column();
	//int row = item->row();
	QString columnName = twExt->columnName(column);
	QSqlRecord rec;
	//bool korekciya = twExt->currentItemData("TypPoNochivli_id").toBool();
	
	if (columnName == "DataVyizdu"){
		QDate cDate = item->data(Qt::EditRole).toDate();
		const char nightType = twExt->currentItemData("TypPoNochivli_id").toInt();
		if (nightType != 2)
			twExt->setCurrentItemData("DataZaizdu", cDate);
		else
			twExt->setCurrentItemData("DataZaizdu", cDate.addDays(1));
		twExt->setCurrentItemData("ToZvitDate", cDate);
	}
	else if (columnName == "ZagalnProbig"){
		QSqlQuery query;
		
		//Заповнення плану на зміну
		query.exec("SELECT * FROM marshruty WHERE \
					KodMarshrutu="+twExt->currentItemData("KodMarshrutu_id").toString()+" and \
					GrafikNum="+twExt->currentItemData("GrafikNum").toString()+" and \
					ZminaNum="+twExt->currentItemData("ZminaNum").toString());
		if (query.next())
			rec = query.record();
		QSqlQuery q,q2;
		q.exec("SELECT RozhidPalnogo, MarkaPalnogo_Id FROM ruhomyisklad \
				WHERE GarajNumber="+twExt->currentItemData("GarajNum_id").toString());
		q.next();

		double planDovjMarshrutu = rec.value("DovjynaMarshrutu").toDouble();
		double dovjMarshrutu = twExt->currentItemData("ZagalnProbig").toDouble();
		double rozhidNa100Km = q.value(0).toDouble();
		double rozhidPalnNaMarshrut = 0;
		if (planDovjMarshrutu)
			rozhidPalnNaMarshrut = qRound(dovjMarshrutu * rozhidNa100Km / 100
						+ rec.value("VytrPalnNaBezdor").toDouble() * dovjMarshrutu / planDovjMarshrutu) ; //+витрата пального на бездоріжжя
		double cinaPalnogo = 0;
		double vyruchka = 0;

		q2.exec("SELECT cinaPalnogo.Cina FROM cinaPalnogoDate \
				LEFT JOIN cinaPalnogo ON cinaPalnogo.cinaPalnogoDate_id=cinaPalnogoDate.id \
				WHERE CDate <= date("+sqlStr(twExt->currentItemData("DataVyizdu").toDate())+") \
					and cinaPalnogo.Palne_id="+q.value(1).toString()+" \
				ORDER BY CDate DESC LIMIT 1");
		if (q2.next())
			cinaPalnogo = q2.value(0).toDouble();

		q2.exec("SELECT Plan FROM planNaZminuDate \
				LEFT JOIN planNaZminu ON planNaZminuDate.id=planNaZminu.planNaZminuDate_id \
				WHERE planNaZminuDate.CDate <= date("+sqlStr(twExt->currentItemData("DataVyizdu").toDate())+") \
						and planNaZminu.Marshrut_id="+rec.value("id").toString()+" \
				ORDER BY planNaZminuDate.CDate DESC LIMIT 1");
		if (q2.next() && planDovjMarshrutu)
			vyruchka = uDToM(q2.value(0).toDouble() * dovjMarshrutu / planDovjMarshrutu);
		
		double sumaZaPalneNaMarshrut = uDToM(rozhidPalnNaMarshrut * cinaPalnogo);
		//Для заокруглення Плану на зміну до гривень (завжди у вищу сторону) збільшуємо на необхідну кількість копійок виручку
		vyruchka += ceil(sumaZaPalneNaMarshrut + vyruchka) - (sumaZaPalneNaMarshrut + vyruchka);
		
		twExt->setCurrentItemData("ZapravkaZaGotivku", sumaZaPalneNaMarshrut);
		twExt->setCurrentItemData("PlanNaZminu", vyruchka + twExt->currentItemData("ZapravkaZaGotivku").toDouble());
		twExt->setCurrentItemData("PlanRozhidPalnogo", rozhidPalnNaMarshrut);
		twExt->setCurrentItemData("FactRozhidPalnogo", rozhidPalnNaMarshrut);
	}
	else if (columnName == "ZapravkaZaGotivku"){
		QSqlQuery query;
		
		//Заповнення плану на зміну
		query.exec("SELECT * FROM marshruty WHERE \
					KodMarshrutu="+twExt->currentItemData("KodMarshrutu_id").toString()+" and \
					GrafikNum="+twExt->currentItemData("GrafikNum").toString()+" and \
					ZminaNum="+twExt->currentItemData("ZminaNum").toString());
		if (query.next())
			rec = query.record();
		QSqlQuery q2;

		double planDovjMarshrutu = rec.value("DovjynaMarshrutu").toDouble();
		double dovjMarshrutu = twExt->currentItemData("ZagalnProbig").toDouble();
		double vyruchka = 0;

		q2.exec("SELECT Plan FROM planNaZminuDate \
				LEFT JOIN planNaZminu ON planNaZminuDate.id=planNaZminu.planNaZminuDate_id \
				WHERE planNaZminuDate.CDate <= date("+sqlStr(twExt->currentItemData("DataVyizdu").toDate())+") \
						and planNaZminu.Marshrut_id="+rec.value("id").toString()+" \
				ORDER BY planNaZminuDate.CDate DESC LIMIT 1");
		if (q2.next() && planDovjMarshrutu)
			vyruchka = uDToM(q2.value(0).toDouble() * dovjMarshrutu / planDovjMarshrutu);
		
		double sumaZaPalneNaMarshrut = uDToM(twExt->currentItemData("ZapravkaZaGotivku").toDouble());
		//Для заокруглення Плану на зміну до гривень (завжди у вищу сторону) збільшуємо на необхідну кількість копійок виручку
		vyruchka += ceil(sumaZaPalneNaMarshrut + vyruchka) - (sumaZaPalneNaMarshrut + vyruchka);
		twExt->setCurrentItemData("PlanNaZminu", vyruchka + twExt->currentItemData("ZapravkaZaGotivku").toDouble());
	}
	else if (columnName == "ChasVNaryadi"){
			QTime ChasVMarshruti = twExt->currentItemData("ChasVNaryadi").toTime();
			int minutesTime = (ChasVMarshruti.hour() - UAutoPark::reshtaChasu().hour()) * 60 +
								ChasVMarshruti.minute() - UAutoPark::reshtaChasu().minute();
			twExt->setCurrentItemData("ChasVMarshruti", QTime(minutesTime/60, fmod(minutesTime, 60)));
	}
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkShlyahovyiLyst::populateDefaultMarshrutZnach()
{
	QSqlQuery query;
	QSqlRecord rec;
	query.exec("SELECT * FROM marshruty WHERE \
					KodMarshrutu="+twExt->currentItemData("KodMarshrutu_id").toString()+" and \
					GrafikNum="+twExt->currentItemData("GrafikNum").toString()+" and \
					ZminaNum="+twExt->currentItemData("ZminaNum").toString());
	
	if (query.next()){
		rec = query.record();
		if (!twExt->currentItemData("IsKoryguv").toBool()){ //Без коригування, дані з бази
			twExt->setCurrentItemData("TypPoNochivli_id", rec.value("TypPoNochivli"));
			if (twExt->currentItemData("TypPoNochivli_id").toInt()==2)
				twExt->setCurrentItemData("DataZaizdu", twExt->currentItemData("DataVyizdu").toDate().addDays(1));
			QTime ChasVNaryadi = rec.value("ChasVNaryadi").toTime();
			twExt->setCurrentItemData("ChasVNaryadi", ChasVNaryadi);
			//twExt->setCurrentItemData("ZagalnProbig", rec.value("ProbigZagalnyi"));
			twExt->setCurrentItemData("PlanKilkReisiv", rec.value("KilkReisiv"));
			twExt->setCurrentItemData("FaktKilkReisiv", rec.value("KilkReisiv"));
		}
		else{
			twExt->setCurrentItemData("TypPoNochivli_id", rec.value("TypPoNochivli"));
			if (twExt->currentItemData("TypPoNochivli_id").toInt()==2)
				twExt->setCurrentItemData("DataZaizdu", twExt->currentItemData("DataVyizdu").toDate().addDays(1));
			QTime ChasVNaryadi = rec.value("ChasVNaryadi").toTime();
			twExt->setCurrentItemData("ChasVNaryadi", ChasVNaryadi);
			//twExt->setCurrentItemData("ZagalnProbig", rec.value("ProbigZagalnyi"));
		}
		//Заповнення плану на зміну
		QSqlQuery q,q2;
		q.exec("SELECT RozhidPalnogo, MarkaPalnogo_Id FROM ruhomyisklad \
				WHERE GarajNumber="+twExt->currentItemData("GarajNum_id").toString());
		q.next();

		double dovjMarshrutu = rec.value("ProbigZagalnyi").toDouble();
		double rozhidNa100Km = q.value(0).toDouble();
		double rozhidPalnNaMarshrut = qRound(dovjMarshrutu * rozhidNa100Km / 100
						+ rec.value("VytrPalnNaBezdor").toDouble()) ; //+витрата пального на бездоріжжя
		double cinaPalnogo = 0;
		double vyruchka = 0;

		q2.exec("SELECT cinaPalnogo.Cina FROM cinaPalnogoDate \
				LEFT JOIN cinaPalnogo ON cinaPalnogo.cinaPalnogoDate_id=cinaPalnogoDate.id \
				WHERE CDate <= date("+sqlStr(twExt->currentItemData("DataVyizdu").toDate())+") \
					and cinaPalnogo.Palne_id="+q.value(1).toString()+" \
				ORDER BY CDate DESC LIMIT 1");
		if (q2.next())
			cinaPalnogo = q2.value(0).toDouble();

		q2.exec("SELECT Plan FROM planNaZminuDate \
				LEFT JOIN planNaZminu ON planNaZminuDate.id=planNaZminu.planNaZminuDate_id \
				WHERE planNaZminuDate.CDate <= date("+sqlStr(twExt->currentItemData("DataVyizdu").toDate())+") \
						and planNaZminu.Marshrut_id="+rec.value("id").toString()+" \
				ORDER BY planNaZminuDate.CDate DESC LIMIT 1");
		if (q2.next())
			vyruchka = q2.value(0).toDouble();

		double sumaZaPalneNaMarshrut = uDToM(rozhidPalnNaMarshrut * cinaPalnogo);
		//Для заокруглення Плану на зміну до гривень (завжди у вищу сторону) збільшуємо на необхідну кількість копійок виручку
		vyruchka += ceil(sumaZaPalneNaMarshrut + vyruchka) - (sumaZaPalneNaMarshrut + vyruchka);
		
		twExt->setCurrentItemData("ZagalnProbig", dovjMarshrutu);
		twExt->setCurrentItemData("ZapravkaZaGotivku", uDToM(cinaPalnogo * rozhidPalnNaMarshrut));
		twExt->setCurrentItemData("PlanNaZminu", vyruchka + twExt->currentItemData("ZapravkaZaGotivku").toDouble());
		
	}
	else
		QMessageBox::information(0, "Помилка","У базі даних не знайдено маршруту з реквізитами:\n"
									"Код маршруту: "+twExt->currentItemData("KodMarshrutu_id").toString()+";\n"
									"Номер графіка: "+twExt->currentItemData("GrafikNum").toString()+";\n"
									"Номер зміни: "+twExt->currentItemData("ZminaNum").toString()+";");
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkShlyahovyiLyst::populateToolBar(QToolBar * tBar)
{
	tBar->addAction(ui.action_printVidomistVykonannyaPlanuVDen);
	tBar->addAction(ui.action_printVidomistMarshrutivVDen);
	tBar->addAction(ui.action_printZvedenaVidomistPoDorojnihLystahZaMisyac);
	tBar->addAction(ui.action_printZvedenaVidomistPoTupahMarshrutivZaMisyac);
	tBar->addAction(ui.action_printZvitProZdanuVyruchkuGotivkoyu);
	tBar->addAction(ui.action_printZvitProPerevezPilgPasajyriv);
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkShlyahovyiLyst::action_printVidomistVykonannyaPlanuVDen_activated()
{
	UDialog_AParkDateFilter *d = new UDialog_AParkDateFilter(ui.dateEdit_filtr->date(), "Дата для відомості");
	if (d->exec()) {
		UPrintDocs_APark *printDocs = new UPrintDocs_APark();
		printDocs->print_vidomistVykonannyaPlanuVDen(d->date());
		connect(this, SIGNAL(mainWindowClosed()), printDocs->printform, SLOT(close()));
		delete printDocs;
	}
	delete d;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkShlyahovyiLyst::action_printZvedenaVidomistPoDorojnihLystahZaMisyac_activated()
{
	UDialog_AParkMarshrutTypeDateFilter *d = new UDialog_AParkMarshrutTypeDateFilter(ui.dateEdit_filtr->date(), "Дата для відомості", "MM.yyyy");
	if (d->exec()) {
		UPrintDocs_APark *printDocs = new UPrintDocs_APark();
		printDocs->print_zvedenaVidomistPoDorojnihLystahZaMisyac(d->date(), d->marshrutType());
		connect(this, SIGNAL(mainWindowClosed()), printDocs->printform, SLOT(close()));
		delete printDocs;
	}
	delete d;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkShlyahovyiLyst::action_printZvedenaVidomistPoTupahMarshrutivZaMisyac_activated()
{
	UDialog_AParkMarshrutTypeDateFilter *d = new UDialog_AParkMarshrutTypeDateFilter(ui.dateEdit_filtr->date(), "Дата для відомості", "MM.yyyy");
	if (d->exec()) {
		UPrintDocs_APark *printDocs = new UPrintDocs_APark();
		printDocs->print_zvedenaVidomistPoTupahMarshrutivZaMisyac(d->date(), d->marshrutType());
		connect(this, SIGNAL(mainWindowClosed()), printDocs->printform, SLOT(close()));
		delete printDocs;
	}
	delete d;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkShlyahovyiLyst::action_printZvitProZdanuVyruchkuGotivkoyu_activated()
{
	UDialog_AParkDateFilter *d = new UDialog_AParkDateFilter(ui.dateEdit_filtr->date(), "Дата для відомості", "MM.yyyy");
	if (d->exec()){
		UPrintDocs_APark *printDocs = new UPrintDocs_APark();
		printDocs->print_zvitProZdanuVyruchkuGotivkoyuZaMisyac(d->date());
		connect(this, SIGNAL(mainWindowClosed()), printDocs->printform, SLOT(close()));
		delete printDocs;
	}
	delete d;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkShlyahovyiLyst::action_printZvitProPerevezPilgPasajyriv_activated()
{
	UDialog_AParkDateFilter *d = new UDialog_AParkDateFilter(ui.dateEdit_filtr->date(), "Дата для відомості", "MM.yyyy");
	if (d->exec()){
		UPrintDocs_APark *printDocs = new UPrintDocs_APark();
		printDocs->print_zvitProPerevezPilgPasajyriv(d->date());
		connect(this, SIGNAL(mainWindowClosed()), printDocs->printform, SLOT(close()));
		delete printDocs;
	}
	delete d;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkShlyahovyiLyst::action_printVidomistMarshrutivVDen_activated()
{
	UDialog_AParkDateFilter *d = new UDialog_AParkDateFilter(ui.dateEdit_filtr->date(), "Дата для відомості", "MM.yyyy");
	if (d->exec()){
		UPrintDocs_APark *printDocs = new UPrintDocs_APark();
		printDocs->print_VidomistMarshrutivVDen(d->date());
		connect(this, SIGNAL(mainWindowClosed()), printDocs->printform, SLOT(close()));
		delete printDocs;
	}
	delete d;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkShlyahovyiLyst::pushButton_showHideExtSearch_clicked()
{
	if (ui.groupBox_extFilter->isVisible()){ //Потрібно сховати
		ui.pushButton_showHideExtSearch->setIcon(QIcon(":/icontexto_webdev_pack/icontexto_webdev_pack/icontexto-webdev-arrow-down-016x016.png"));
		ui.groupBox_extFilter->setVisible(false);
	}
	else{ //Потрібно показати
		ui.pushButton_showHideExtSearch->setIcon(QIcon(":/icontexto_webdev_pack/icontexto_webdev_pack/icontexto-webdev-arrow-up-016x016.png"));
		ui.groupBox_extFilter->setChecked(true);
		ui.groupBox_extFilter->setVisible(true);
	}
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkShlyahovyiLyst::groupBox_extFilter_toggled()
{
	if (ui.groupBox_extFilter->isChecked()){ //використовуються складний пошук
		ui.dateEdit_filtr->setVisible(false);
	}
	else{ //використовується простий пошук по даті виїзду
		ui.dateEdit_filtr->setVisible(true);
		setDateFilter();
	}
	showFilterString();
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkShlyahovyiLyst::pushButton_execFilter_clicked()
{
	QString filterStr;
	bool needAnd = false;
	
	if (ui.groupBox_shyahLystNumberFilter->isChecked()){
		filterStr += (needAnd?QString(" and "):QString(" ")) + "ShlyahovyiLystNum_id=" 
					+ ui.spinBox_shyahLystNumberFilter->text();
		needAnd = true;
	}
	if (ui.groupBox_autoFilter->isChecked() && ui.comboBox_autoFilter->currentIndex()>0){
		filterStr += (needAnd?QString(" and "):QString(" ")) + "GarajNum_id=" 
					+ ui.comboBox_autoFilter->itemData(ui.comboBox_autoFilter->currentIndex(), Qt::UserRole).toString();
		needAnd = true;
	}
	if (ui.groupBox_vodiyFilter->isChecked() && ui.comboBox_vodiyFilter->currentIndex()>0){
		filterStr += (needAnd?QString(" and "):QString(" ")) + "VodiyTabelNum_id=" 
					+ ui.comboBox_vodiyFilter->itemData(ui.comboBox_vodiyFilter->currentIndex(), Qt::UserRole).toString();
		needAnd = true;
	}
	if (ui.groupBox_marshrutFilter->isChecked() && ui.comboBox_marshrutFilter->currentIndex()>0){
		filterStr += (needAnd?QString(" and "):QString(" ")) + "KodMarshrutu_id=" 
					+ ui.comboBox_marshrutFilter->itemData(ui.comboBox_marshrutFilter->currentIndex(), Qt::UserRole).toString();
		needAnd = true;
	}
	if (ui.groupBox_dataVyizduFilter->isChecked()){
		filterStr += (needAnd?QString(" and "):QString(" ")) + "date(DataVyizdu)=" + sqlStr(ui.dateEdit_dataVyizduFilter->date());
		needAnd = true;
	}
	if (ui.groupBox_monthVyizduFilter->isChecked()){
		UWorkMonth wMonth(ui.dateEdit_monthVyizduFilter->date().year(), ui.dateEdit_monthVyizduFilter->date().month());
		filterStr += (needAnd?QString(" and "):QString(" ")) + "(date(ToZvitDate) BETWEEN date("+sqlStr(wMonth.begDate())+") AND date("+sqlStr(wMonth.endDate())+"))";
		needAnd = true;
	}
	if (ui.groupBox_nochivlyaFilter->isChecked() && ui.comboBox_nochivlyaFilter->currentIndex()>0){
		filterStr += (needAnd?QString(" and "):QString(" ")) + "TypPoNochivli_id=" 
					+ ui.comboBox_nochivlyaFilter->itemData(ui.comboBox_nochivlyaFilter->currentIndex(), Qt::UserRole).toString();
		needAnd = true;
	}
	if (ui.groupBox_korygFilter->isChecked()){
		filterStr += (needAnd?QString(" and "):QString(" ")) + "IsKoryguv=" 
					+ sqlStr(ui.checkBox_korygFilter->isChecked());
		needAnd = true;
	}
	
	showFilterString();
	twExt->setSqlFilter(filterStr);
	twExt->populateTable();
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkShlyahovyiLyst::showFilterString()
{
	if (ui.groupBox_extFilter->isChecked()){ //використовуються складний пошук
		bool extFilterSet=false;
		QString fInfStr = "Розш.фільтр->";
		
		if (ui.groupBox_shyahLystNumberFilter->isChecked()){
			fInfStr += " № Шл.лст.: " 
						+ ui.spinBox_shyahLystNumberFilter->text()
						+ ";";
			extFilterSet = true;
		}
		if (ui.groupBox_autoFilter->isChecked() && ui.comboBox_autoFilter->currentIndex()>0){
			fInfStr += " Авт.: " 
					+ ui.comboBox_autoFilter->itemData(ui.comboBox_autoFilter->currentIndex(), Qt::UserRole).toString()
					+ ";";
			extFilterSet = true;
		}
		if (ui.groupBox_vodiyFilter->isChecked() && ui.comboBox_vodiyFilter->currentIndex()>0){
			fInfStr += " Вод.: " 
					+ ui.comboBox_vodiyFilter->itemData(ui.comboBox_vodiyFilter->currentIndex(), Qt::UserRole).toString()
					+ ";";;
			extFilterSet = true;
		}
		if (ui.groupBox_marshrutFilter->isChecked() && ui.comboBox_marshrutFilter->currentIndex()>0){
			fInfStr += " Маршр.: " 
					+ ui.comboBox_marshrutFilter->itemData(ui.comboBox_marshrutFilter->currentIndex(), Qt::UserRole).toString()
					+ ";";
			extFilterSet = true;
		}
		if (ui.groupBox_dataVyizduFilter->isChecked()){
			fInfStr += " Дат. виїзду: " + ui.dateEdit_dataVyizduFilter->date().toString("dd.MM.yyyy")
						+ ";";
			extFilterSet = true;
		}
		if (ui.groupBox_nochivlyaFilter->isChecked() && ui.comboBox_nochivlyaFilter->currentIndex()>0){
			fInfStr += " Ноч.: " 
					+ ui.comboBox_nochivlyaFilter->itemData(ui.comboBox_nochivlyaFilter->currentIndex(), Qt::UserRole).toString()
					+ ";";
			extFilterSet = true;
		}
		if (ui.groupBox_korygFilter->isChecked()){
			fInfStr += " Кор.: " 
						+ (ui.checkBox_korygFilter->isChecked()?QString("Так"):QString("Ні"))
						+ ";";
			extFilterSet = true;
		}
		
		if (extFilterSet)
			ui.label_filterStr->setText(fInfStr);
		else
			ui.label_filterStr->setText("Розширений фільтр не визначено");
	}
	else{ //використовується простий пошук по даті виїзду
		ui.label_filterStr->setText("Фільтр по даті виїзду");
	}
}
//--------------------utech--------------------utech--------------------utech--------------------
UForm_AParkShlyahovyiLyst::~UForm_AParkShlyahovyiLyst()
{
	
}
//--------------------utech--------------------utech--------------------utech--------------------
