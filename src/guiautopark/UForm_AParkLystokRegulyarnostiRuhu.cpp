//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл виконання класу вікна налаштування програми
//
// Створений програмістами Компанії "Утех" 29.03.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------
#include "UForm_AParkLystokRegulyarnostiRuhu.h"

#include "UDifFunc_APark.h"
#include "UPrintDocs_APark.h"
#include <UStandardDelegate>
#include "UAutoParkMeneger_APark.h"
#include "UDialog_AParkChooseNumber.h"

#include <QtDebug>
//--------------------utech--------------------utech--------------------utech--------------------
UForm_AParkLystokRegulyarnostiRuhu::UForm_AParkLystokRegulyarnostiRuhu(int tWType, QWidget *parent)
        : UAParkTabWidget(tWType, parent)
{
	ui.setupUi(this);
	autoFilterCB = new UIntEditingComboBox(ui.comboBox_autoFilter);
	vodiyFilterCB = new UIntEditingComboBox(ui.comboBox_vodiyFilter);
	marshrutFilterCB = new UIntEditingComboBox(ui.comboBox_marshrutFilter);
	nochivlyaFilterCB = new UIntEditingComboBox(ui.comboBox_nochivlyaFilter);
	
	ui.groupBox_extFilter->setChecked(false);
	ui.groupBox_autoFilter->setChecked(false);
	ui.groupBox_vodiyFilter->setChecked(false);
	ui.groupBox_marshrutFilter->setChecked(false);
	ui.groupBox_dataVyizduFilter->setChecked(false);
	ui.groupBox_monthVyizduFilter->setChecked(false);
	ui.groupBox_nochivlyaFilter->setChecked(false);
	ui.groupBox_extFilter->setVisible(false);
	ui.pushButton_showHideExtSearch->setIcon(QIcon(":/icontexto_webdev_pack/icontexto_webdev_pack/icontexto-webdev-arrow-up-016x016.png"));
	
	ui.dateEdit_filtr->setDate(QDate::currentDate());
	ui.dateEdit_dataVyizduFilter->setDate(QDate::currentDate());
	ui.dateEdit_monthVyizduFilter->setDate(QDate::currentDate());
	
	twExt = new UDataFormView(ui.tableWidget_LystokRegulyarnostiRuhu, "lystRegulyarnostiRuhu");
	twExt->setSortingEnabled(true);
	twExt->colNamesList << "Id"
						<< "Auto_id"
						<< "Vodiy_Id"
						<< "Marshrut_id"
						<< "GrafikNum"
						<< "ZminaNum"
						<< "ReisyCount"
						<< "BrygadaNum"
						<< "Nochivlya"
						<< "VyizdDate"
						<< "ZaizdDate"
						<< "PlanNaZminu"
						<< "MarkaPalnogo_id"
						<< "PlanNormaPalnogo"
						<< "CinaPalnogo";
	
	twExt->addColAlignment("Auto_id", Qt::AlignVCenter | Qt::AlignLeft);
	twExt->addColAlignment("Vodiy_Id", Qt::AlignVCenter | Qt::AlignLeft);
	twExt->addColAlignment("Marshrut_id", Qt::AlignVCenter | Qt::AlignLeft);
	twExt->addColAlignment("GrafikNum", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("ZminaNum", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("ReisyCount", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("BrygadaNum", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("Nochivlya", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("VyizdDate", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("ZaizdDate", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("PlanNaZminu", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("MarkaPalnogo_id", Qt::AlignVCenter | Qt::AlignLeft);
	twExt->addColAlignment("PlanNormaPalnogo", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("CinaPalnogo", Qt::AlignVCenter | Qt::AlignRight);
	
	twExt->insertWidget(ui.comboBox_vodiy, "Vodiy_Id");
	twExt->insertWidget(ui.comboBox_auto, "Auto_id");
	twExt->insertWidget(ui.comboBox_marshrut, "Marshrut_id");
	twExt->insertWidget(ui.spinBox_mtGrafNum, "GrafikNum");
	twExt->insertWidget(ui.spinBox_mtZminaNum, "ZminaNum");
	twExt->insertWidget(ui.spinBox_reisyCount, "ReisyCount");
	twExt->insertWidget(ui.spinBox_brygadaNum, "BrygadaNum");
	twExt->insertWidget(ui.dateEdit_vyizdDate, "VyizdDate");
	twExt->insertWidget(ui.dateEdit_zaizdDate, "ZaizdDate");
	twExt->insertWidget(ui.comboBox_nochivlya, "Nochivlya");
	twExt->insertWidget(ui.doubleSpinBox_PlanNaZminu, "PlanNaZminu");
	twExt->insertWidget(ui.comboBox_MarkaPalnogo, "MarkaPalnogo_id");
	twExt->insertWidget(ui.doubleSpinBox_PlanNormaPaln, "PlanNormaPalnogo");
	twExt->insertWidget(ui.doubleSpinBox_CinaPalnogo, "CinaPalnogo");
	
	
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
	twExt->setItemDelegateForColumn("Auto_id", delegateList);
	delegateList.replaceValueAt(0, " --- Усі ---");
	twExt->populateComboBoxItems(ui.comboBox_autoFilter, delegateList);
	
		//Делегат Піб водія + Табельний номер
	delegateList.clear();
	delegateList.insert(0, "");
	query.exec("SELECT id, Prizv, Imia, PoBatk FROM npr ORDER BY Prizv, Imia, PoBatk");
	while (query.next()){
		delegateList.insert(query.value(0).toInt(), "["+query.value(0).toString()+"] "+query.value(1).toString()+" "+query.value(2).toString()+" "+query.value(3).toString());
	}
	twExt->setItemDelegateForColumn("Vodiy_Id", delegateList);
	delegateList.replaceValueAt(0, " --- Усі ---");
	twExt->populateComboBoxItems(ui.comboBox_vodiyFilter, delegateList);
	
		//Делегат Номер маршруту
	delegateList.clear();
	delegateList.insert(0, "");
	query.exec("SELECT KodMarshrutu, MarshrutNapryamok FROM marshruty");
	while (query.next()){
		delegateList.insert(query.value(0).toInt(), "["+query.value(0).toString()+"] "+query.value(1).toString());
	}
	twExt->setItemDelegateForColumn("Marshrut_id", delegateList);
	delegateList.replaceValueAt(0, " --- Усі ---");
	twExt->populateComboBoxItems(ui.comboBox_marshrutFilter, delegateList);
	
		//Делегат Признаку ночівлі
	delegateList.clear();
	delegateList.insert(0, "");
	query.exec("SELECT id, ShortTypName FROM typponochivli");
	while (query.next()){
		delegateList.insert(query.value(0).toInt(), query.value(1).toString());
	}
	twExt->setItemDelegateForColumn("Nochivlya", delegateList);
	delegateList.replaceValueAt(0, " --- Усі ---");
	twExt->populateComboBoxItems(ui.comboBox_nochivlyaFilter, delegateList);
	
		//Делегат марки пального
	delegateList.clear();
	delegateList.insert(0, "");
	query.exec("SELECT id, MarkaName FROM markapalnogo");
	while (query.next()){
		delegateList.insert(query.value(0).toInt(), query.value(1).toString());
	}
	twExt->setItemDelegateForColumn("MarkaPalnogo_id", delegateList);
	
	twExt->setItemDelegateForColumn("GodVRoboti", new UTimeDelegate(ui.tableWidget_LystokRegulyarnostiRuhu, "H:mm"));
	
	ui.tableWidget_LystokRegulyarnostiRuhu->setColumnHidden(0, true);
	twExt->setColumnWidth("Auto_id", 200);
	twExt->setColumnWidth("Vodiy_Id", 200);
	twExt->setColumnWidth("Marshrut_id", 200);
	
	setDateFilter();
	
	connect(ui.toolButton_avtoZapovn, SIGNAL(clicked()), this, SLOT(toolButton_avtoZapovn_clicked()));
	
	connect(ui.pushButton_create, SIGNAL(clicked()), this, SLOT(pushButton_create_clicked()));
	connect(ui.pushButton_delete, SIGNAL(clicked()), this, SLOT(pushButton_delete_clicked()));
	connect(ui.pushButton_reload, SIGNAL(clicked()), twExt,SLOT(populateTable()));
	connect(ui.dateEdit_filtr, SIGNAL(dateChanged(const QDate &)), this, SLOT(setDateFilter()));
	connect(twExt, SIGNAL(tableItemEdited(QTableWidgetItem *)), this, SLOT(populateDovidnykValues(QTableWidgetItem *)));
	
	connect(ui.action_printLystkyRegulyarnostiRuhu, SIGNAL(activated()), this, SLOT(action_printLystkyRegulyarnostiRuhu_activated()));
	connect(ui.action_printBackSideOfLystokRegulyarnosti, SIGNAL(activated()), this, SLOT(action_printBackSideOfLystokRegulyarnosti_activated()));
	connect(ui.action_printPustogrLystkaRegulRuhu, SIGNAL(activated()), this, SLOT(action_printPustogrLystkaRegulRuhu_activated()));
	
	//Налаштування фільтрування
	groupBox_extFilter_toggled();
	connect(ui.pushButton_showHideExtSearch, SIGNAL(clicked()), this, SLOT(pushButton_showHideExtSearch_clicked()));
	connect(ui.groupBox_extFilter, SIGNAL(toggled(bool)), this, SLOT(groupBox_extFilter_toggled()));
	connect(ui.pushButton_execFilter, SIGNAL(clicked()), this, SLOT(pushButton_execFilter_clicked()));
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkLystokRegulyarnostiRuhu::toolButton_avtoZapovn_clicked()
{
	QSqlQuery query;
	
	double ProbigZagalnyi = 0;
	double VytrPalnNaBezdor = 0;
	
	// Автозаповнення маршруту
	query.exec("SELECT KilkReisiv, TypPonoChivli, '', \
						VytrPalnNaBezdor, ProbigZagalnyi, VytrPalnNaBezdor \
				FROM marshruty \
				WHERE KodMarshrutu="+twExt->currentItemData("Marshrut_id").toString()+" \
					and GrafikNum="+twExt->currentItemData("GrafikNum").toString()+" \
					and ZminaNum="+twExt->currentItemData("ZminaNum").toString());
	if (query.next()){
		twExt->setCurrentItemData("ReisyCount", query.value(0));
		twExt->setCurrentItemData("Nochivlya", query.value(1));
		
		ProbigZagalnyi = query.value(4).toDouble();
		VytrPalnNaBezdor = query.value(5).toDouble();
	}
	
	//Автозаповнення № автоколони
	query.exec("SELECT MarkaPalnogo_Id, RozhidPalnogo FROM ruhomyisklad \
				WHERE GarajNumber="+twExt->currentItemData("Auto_id").toString());
	if (query.next()){
		twExt->setCurrentItemData("MarkaPalnogo_id", query.value(0));
		twExt->setCurrentItemData("PlanNormaPalnogo", qRound(ProbigZagalnyi * query.value(1).toDouble() / 100.0 + VytrPalnNaBezdor));
	}
	
	//Номер бригади
	query.exec("SELECT BrygadaNum FROM npr \
				WHERE id="+twExt->currentItemData("Vodiy_Id").toString());
	if (query.next())
		twExt->setCurrentItemData("BrygadaNum", query.value(0));
	
	//Ціна пального
	twExt->setCurrentItemData("CinaPalnogo", UAutoPark::cinaPalnogo(twExt->currentItemData("MarkaPalnogo_id").toInt(), 
											twExt->currentItemData("VyizdDate").toDate()));
	
	//План на зміну
	twExt->setCurrentItemData("PlanNaZminu", UAutoPark::planNaZminu(twExt->currentItemData("Marshrut_id").toInt(), \
												twExt->currentItemData("GrafikNum").toInt(), 
												twExt->currentItemData("ZminaNum").toInt(), 
												twExt->currentItemData("VyizdDate").toDate(),
												twExt->currentItemData("CinaPalnogo").toDouble(),
												twExt->currentItemData("PlanNormaPalnogo").toDouble()));
	
	//Дата заїзду
	if (twExt->currentItemData("Nochivlya").toInt() == 2)
		twExt->setCurrentItemData("ZaizdDate", twExt->currentItemData("VyizdDate").toDate().addDays(1));
	else
		twExt->setCurrentItemData("ZaizdDate", twExt->currentItemData("VyizdDate"));
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkLystokRegulyarnostiRuhu::pushButton_create_clicked()
{
	if (!twExt->addRow("INSERT INTO lystRegulyarnostiRuhu (VyizdDate, ZaizdDate) \
						VALUES ('"+ui.dateEdit_filtr->date().toString("yyyy-MM-dd")+"', \
								'"+ui.dateEdit_filtr->date().toString("yyyy-MM-dd")+"')"))
		QMessageBox::critical(0,"Помилка створення запису","Запис автобуса не створено");
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkLystokRegulyarnostiRuhu::pushButton_delete_clicked()
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
void UForm_AParkLystokRegulyarnostiRuhu::setDateFilter()
{
	twExt->setSqlFilter("VyizdDate='"+ui.dateEdit_filtr->date().toString("yyyy-MM-dd")+"'");
	twExt->populateTable();
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkLystokRegulyarnostiRuhu::populateDovidnykValues(QTableWidgetItem *item)
{
	
	int column=item->column();
	//int row = item->row();
	QString columnName = twExt->columnName(column);
	QSqlRecord rec;
	
	if (columnName == "VyizdDate"){
		QDate cDate = item->data(Qt::EditRole).toDate();
		const char nightType = twExt->currentItemData("Nochivlya").toInt();
		if (nightType != 2)
			twExt->setCurrentItemData("ZaizdDate", cDate);
		else
			twExt->setCurrentItemData("ZaizdDate", cDate.addDays(1));
	}
	
	//calcVartistPalnogoZaZminu();
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkLystokRegulyarnostiRuhu::calcVartistPalnogoZaZminu()
{
	//ui.label_vartistPalnogoZaZminu->setText("Вартість пального: "+QString::number(ui.doubleSpinBox_PlanNormaPaln->value()*ui.doubleSpinBox_CinaPalnogo->value(),'f',2)+" грн.");
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkLystokRegulyarnostiRuhu::action_printLystkyRegulyarnostiRuhu_activated()
{
	QModelIndexList selList = ui.tableWidget_LystokRegulyarnostiRuhu->selectionModel()->selectedRows(0);
	QList<int> intList;
	for (int iter=0; iter<selList.size(); ++iter){
		intList << selList[iter].data(Qt::EditRole).toInt();
	}
	
	if (intList.size() == 0){
		QMessageBox::critical(this, "Помилка", "Ви не позначили жодного \"Листка регулярності руху\" для друку.");
		return;
	}
	
	UPrintDocs_APark *printDocs = new UPrintDocs_APark();
	printDocs->print_lystkyRegulyarnostiRuhu(intList);
	connect(this, SIGNAL(mainWindowClosed()), printDocs->printform, SLOT(close()));
	delete printDocs;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkLystokRegulyarnostiRuhu::action_printBackSideOfLystokRegulyarnosti_activated()
{
	QSqlQuery query;
	int numberCopys = 2;
	query.exec("SELECT Znach FROM progOptionsApark WHERE id=2"); //Кількість копій задньої частини фішки
	if (query.next() && query.value(0).toInt()>0)
		numberCopys = query.value(0).toInt();
	
	UDialog_AParkChooseNumber d(1, 2, numberCopys, "Вибір кількості копій");
	if ( !d.exec() )
		return;
	
	if (query.value(0).toInt() != d.currentValue())
		query.exec("UPDATE progOptionsApark SET Znach="+sqlStr(d.currentValue())+" WHERE id=2");
	
	UPrintDocs_APark *printDocs = new UPrintDocs_APark();
	printDocs->print_backSideLystkaRegulyarnostiRuhu(d.currentValue());
	connect(this, SIGNAL(mainWindowClosed()), printDocs->printform, SLOT(close()));
	delete printDocs;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkLystokRegulyarnostiRuhu::action_printPustogrLystkaRegulRuhu_activated()
{
	UPrintDocs_APark *printDocs = new UPrintDocs_APark();
	printDocs->print_lystkyPustogrRegulyarnostiRuhu();
	connect(this, SIGNAL(mainWindowClosed()), printDocs->printform, SLOT(close()));
	delete printDocs;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkLystokRegulyarnostiRuhu::populateToolBar(QToolBar * tBar)
{
	tBar->addAction(ui.action_printLystkyRegulyarnostiRuhu);
	tBar->addAction(ui.action_printPustogrLystkaRegulRuhu);
	tBar->addAction(ui.action_printBackSideOfLystokRegulyarnosti);
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkLystokRegulyarnostiRuhu::pushButton_showHideExtSearch_clicked()
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
void UForm_AParkLystokRegulyarnostiRuhu::groupBox_extFilter_toggled()
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
void UForm_AParkLystokRegulyarnostiRuhu::pushButton_execFilter_clicked()
{
	QString filterStr;
	bool needAnd = false;
	
	if (ui.groupBox_autoFilter->isChecked() && ui.comboBox_autoFilter->currentIndex()>0){
		filterStr += (needAnd?QString(" and "):QString(" ")) + "Auto_id=" 
					+ ui.comboBox_autoFilter->itemData(ui.comboBox_autoFilter->currentIndex(), Qt::UserRole).toString();
		needAnd = true;
	}
	if (ui.groupBox_vodiyFilter->isChecked() && ui.comboBox_vodiyFilter->currentIndex()>0){
		filterStr += (needAnd?QString(" and "):QString(" ")) + "Vodiy_Id=" 
					+ ui.comboBox_vodiyFilter->itemData(ui.comboBox_vodiyFilter->currentIndex(), Qt::UserRole).toString();
		needAnd = true;
	}
	if (ui.groupBox_marshrutFilter->isChecked() && ui.comboBox_marshrutFilter->currentIndex()>0){
		filterStr += (needAnd?QString(" and "):QString(" ")) + "Marshrut_id=" 
					+ ui.comboBox_marshrutFilter->itemData(ui.comboBox_marshrutFilter->currentIndex(), Qt::UserRole).toString();
		needAnd = true;
	}
	if (ui.groupBox_dataVyizduFilter->isChecked()){
		filterStr += (needAnd?QString(" and "):QString(" ")) + "VyizdDate=" + sqlStr(ui.dateEdit_dataVyizduFilter->date());
		needAnd = true;
	}
	
	if (ui.groupBox_monthVyizduFilter->isChecked()){
		UWorkMonth wMonth(ui.dateEdit_monthVyizduFilter->date().year(), ui.dateEdit_monthVyizduFilter->date().month());
		filterStr += (needAnd?QString(" and "):QString(" ")) + "(date(VyizdDate) BETWEEN date("+sqlStr(wMonth.begDate())+") AND date("+sqlStr(wMonth.endDate())+"))";
		needAnd = true;
	}
	
	if (ui.groupBox_nochivlyaFilter->isChecked() && ui.comboBox_nochivlyaFilter->currentIndex()>0){
		filterStr += (needAnd?QString(" and "):QString(" ")) + "Nochivlya=" 
					+ ui.comboBox_nochivlyaFilter->itemData(ui.comboBox_nochivlyaFilter->currentIndex(), Qt::UserRole).toString();
		needAnd = true;
	}
	
	showFilterString();
	twExt->setSqlFilter(filterStr);
	twExt->populateTable();
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkLystokRegulyarnostiRuhu::showFilterString()
{
	if (ui.groupBox_extFilter->isChecked()){ //використовуються складний пошук
		bool extFilterSet=false;
		QString fInfStr = "Розш.фільтр->";
		
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
UForm_AParkLystokRegulyarnostiRuhu::~UForm_AParkLystokRegulyarnostiRuhu()
{
	
}
//--------------------utech--------------------utech--------------------utech--------------------
