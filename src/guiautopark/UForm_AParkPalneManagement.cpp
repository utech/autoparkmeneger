//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл виконання класу вікна налаштування програми
//
// Створений програмістами Компанії "Утех" 07.06.2011р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------
#include "UForm_AParkPalneManagement.h"

#include "UDifFunc_APark.h"
#include "UPrintDocs_APark.h"
#include <UStandardDelegate>
#include "UDialog_AParkDateFilter.h"
#include "UDialog_AParkMarkaPalnogoDateFilter.h"
#include "UDialog_AParkPartnerDateFilter.h"
#include "UAutoParkMeneger_APark.h"
#include "UExport_APark.h"
#include "UDialog_AParkPartnerMarkaPalnogoDateFilter.h"

#include <U2List>

#include <QtDebug>

//--------------------utech--------------------utech--------------------utech--------------------
UForm_AParkPalneManagement::UForm_AParkPalneManagement(int tWType, QWidget *parent)
        : UAParkTabWidget(tWType, parent)
{
	
	ui.setupUi(this);
    
	// Don't need a pointer, because argument pointer's object becomes a parent of object
	new UIntEditingComboBox(ui.comboBox_vodiyFilter);
	new UIntEditingComboBox(ui.comboBox_typPalnogoFilter);
	
	ui.groupBox_vodiyFilter->setChecked(false);
	ui.groupBox_monthFilter->setChecked(false);
	ui.groupBox_dateFilter->setChecked(true);
	ui.groupBox_palneFilter->setChecked(false);
	
	ui.dateEdit_dateFilter->setDate(QDate::currentDate());
	ui.dateEdit_monthFilter->setDate(QDate::currentDate());
	
	// Init tableWidget_zvitKupivliPalnogo
	ui.tableWidget_zvitKupivliPalnogo->setColumnCount( 6 );
	twExtZvity = new UTableWidgetSqlExt(ui.tableWidget_zvitKupivliPalnogo, "zvitKupivliPalnogo");
	twExtZvity->setSortingEnabled(true);
	
	ui.tableWidget_zvitKupivliPalnogo->setHorizontalHeaderLabels( QStringList() 
															<< "id"
															<< "Водій"
															<< "Дата"
															<< "Пальн."
															<< "№ звіту"
															<< "Партнер");
	
	twExtZvity->colNamesList << "Id"
						<< "Npr_id"
						<< "CDate"
						<< "MarkaPalnogo_id"
						<< "ZvitNum"
						<< "DovPartners_id";
	
	twExtZvity->addColAlignment("Npr_id", Qt::AlignVCenter | Qt::AlignLeft);
	twExtZvity->addColAlignment("CDate", Qt::AlignVCenter | Qt::AlignRight);
	twExtZvity->addColAlignment("MarkaPalnogo_id", Qt::AlignVCenter | Qt::AlignLeft);
	twExtZvity->addColAlignment("ZvitNum", Qt::AlignVCenter | Qt::AlignLeft);
	
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
	twExtZvity->setItemDelegateForColumn("Npr_id", new UIntStringListComboDelegate(ui.tableWidget_zvitKupivliPalnogo, delegateList));
	delegateList.remove(0);
	int size = delegateList.size();
	for (int iter=0; iter<size; iter++)
		ui.comboBox_vodiyFilter->addItem(delegateList.valueAt(iter), delegateList.keyAt(iter));
	
		//Делегат Марка пального
	delegateList.clear();
	delegateList.insert(0, "");
	query.exec("SELECT id, MarkaName FROM markapalnogo");
	while (query.next()){
		delegateList.insert(query.value(0).toInt(), "["+query.value(0).toString()+"] "+query.value(1).toString());
	}
	twExtZvity->setItemDelegateForColumn("MarkaPalnogo_id", new UIntStringListComboDelegate(ui.tableWidget_zvitKupivliPalnogo, delegateList));
	delegateList.remove(0);
	size = delegateList.size();
	for (int iter=0; iter<size; iter++)
		ui.comboBox_typPalnogoFilter->addItem(delegateList.valueAt(iter), delegateList.keyAt(iter));
	ui.comboBox_typPalnogoFilter->setCurrentIndex(ui.comboBox_typPalnogoFilter->findData(5));
	
		//Делегат Довідника партнерів
	delegateList.clear();
	delegateList.insert(0, "");
	query.exec("SELECT id, Name FROM dovpartners ORDER BY Name");
	while (query.next()){
		delegateList.insert(query.value(0).toInt(), "["+query.value(0).toString()+"] "+query.value(1).toString());
	}
	twExtZvity->setItemDelegateForColumn("DovPartners_id", new UIntStringListComboDelegate(ui.tableWidget_zvitKupivliPalnogo, delegateList));
	delegateList.remove(0);
	size = delegateList.size();
	for (int iter=0; iter<size; iter++)
		ui.comboBox_partnerIdFilter->addItem(delegateList.valueAt(iter), delegateList.keyAt(iter));
	ui.comboBox_partnerIdFilter->setCurrentIndex(ui.comboBox_partnerIdFilter->findData(1));
	
	twExtZvity->setItemDelegateForColumn("CDate", new UDateTimeDelegate(ui.tableWidget_zvitKupivliPalnogo,"dd.MM.yyyy"));
	
	twExtZvity->setColumnHidden(0, true);
	twExtZvity->setColumnWidth("Npr_id", 200);
	twExtZvity->setColumnWidth("CDate", 70);
	twExtZvity->setColumnWidth("MarkaPalnogo_id", 50);
	twExtZvity->setColumnWidth("ZvitNum", 70);
	twExtZvity->setColumnWidth("DovPartners_id", 100);
	
	// Init tableWidget_ZvitKupivliPalnogoOrders
	ui.tableWidget_ZvitKupivliPalnogoOrders->setColumnCount( 6 );
	twExtOrders = new UTableWidgetSqlExt(ui.tableWidget_ZvitKupivliPalnogoOrders, "zvitKupivliPalnogoOrders");
	twExtOrders->setSortingEnabled(true);
	
	ui.tableWidget_ZvitKupivliPalnogoOrders->setHorizontalHeaderLabels( QStringList() 
															<< "id"
															<< "Дата"
															<< "Запр."
															<< "№ документа (чека)"
															<< "К-сть"
															<< "Сума, грн.");
	
	twExtOrders->colNamesList << "id"
						<< "CDate"
						<< "KodZapravky"
						<< "DocNum"
						<< "Kilkist"
						<< "Suma";
	
	twExtOrders->addColAlignment("CDate", Qt::AlignVCenter | Qt::AlignRight);
	twExtOrders->addColAlignment("KodZapravky", Qt::AlignVCenter | Qt::AlignRight);
	twExtOrders->addColAlignment("DocNum", Qt::AlignVCenter | Qt::AlignRight);
	twExtOrders->addColAlignment("Kilkist", Qt::AlignVCenter | Qt::AlignRight);
	twExtOrders->addColAlignment("Suma", Qt::AlignVCenter | Qt::AlignRight);
	
	twExtOrders->setItemDelegateForColumn("CDate", new UDateTimeDelegate(ui.tableWidget_ZvitKupivliPalnogoOrders,"dd.MM.yyyy"));
	twExtOrders->setItemDelegateForColumn("Kilkist", new UDoubleSpinBoxDelegate(0,10000000,2,ui.tableWidget_ZvitKupivliPalnogoOrders));
	twExtOrders->setItemDelegateForColumn("Suma", new UDoubleSpinBoxDelegate(0,10000000,2,ui.tableWidget_ZvitKupivliPalnogoOrders));
	
	twExtOrders->setColumnHidden(0, true);
	twExtOrders->setColumnWidth("CDate", 80);
	twExtOrders->setColumnWidth("KodZapravky", 60);
        twExtOrders->setColumnWidth("DocNum", 100);
        twExtOrders->setColumnWidth("Kilkist", 80);
        twExtOrders->setColumnWidth("Suma", 80);
	
	populateZvitKupivliPalnogo();
	
	connect(ui.pushButton_zvitKupivliPalnogoFilter, SIGNAL(clicked()), this, SLOT(populateZvitKupivliPalnogo()));
    connect(ui.pushButton_reloadZvitKupivliPalnogo, SIGNAL(clicked()), this, SLOT(populateZvitKupivliPalnogo()));
	connect(ui.pushButton_createZvitKupivliPalnogo, SIGNAL(clicked()), this, SLOT(createZvitKupivliPalnogo()));
	connect(ui.pushButton_deleteZvitKupivliPalnogo, SIGNAL(clicked()), this, SLOT(deleteZvitKupivliPalnogo()));
	
	connect(ui.pushButton_reloadZvitKupivliPalnogoOrders, SIGNAL(clicked()), this, SLOT(populateZvitKupivliPalnogoOrders()));
	connect(ui.pushButton_createZvitKupivliPalnogoOrders, SIGNAL(clicked()), this, SLOT(createZvitKupivliPalnogoOrders()));
	connect(ui.pushButton_deleteZvitKupivliPalnogoOrders, SIGNAL(clicked()), this, SLOT(deleteZvitKupivliPalnogoOrders()));
	connect(ui.tableWidget_zvitKupivliPalnogo->selectionModel(), SIGNAL(currentRowChanged(const QModelIndex &,const QModelIndex &)), 
				this, SLOT(populateZvitKupivliPalnogoOrders()));
	
	connect(ui.tableWidget_ZvitKupivliPalnogoOrders, SIGNAL(itemChanged(QTableWidgetItem *)), 
				this, SLOT(calcOrdersSummary()));
    
	connect(ui.action_printZvitVykorystannyaKoshtivPalne, SIGNAL(activated()), this, SLOT(printZvitVykorystannyaKoshtivPalne()));
	
	connect(ui.action_printReyestrChekivGAZ, SIGNAL(activated()), 
				this, SLOT(action_printReyestrChekivGAZ_activated()));
	connect(ui.action_printReyestrChekivDailyGAZ, SIGNAL(activated()), 
				this, SLOT(action_printReyestrChekivDailyGAZ_activated()));
	connect(ui.action_printReyestrChekivPALNE, SIGNAL(activated()), 
				this, SLOT(action_printReyestrChekivPALNE_activated()));
        connect(ui.action_printReyestrChekivVidPostachalnykaPALNE, SIGNAL(activated()),
                                this, SLOT(action_printReyestrChekivVidPostachalnykaPALNE_activated()));
	connect(ui.action_printVidomistZakupivliPalnogoPoVodiyahZaMisyac, SIGNAL(activated()), 
				this, SLOT(action_printVidomistZakupivliPalnogoPoVodiyahZaMisyac_activated()));
	connect(ui.action_printVidomistZakupivliPalnogoPoVodiyahZaMisyacVRozriziRahunkiv, SIGNAL(activated()), 
				this, SLOT(action_printVidomistZakupivliPalnogoPoVodiyahZaMisyacVRozriziRahunkiv_activated()));
	connect(ui.action_printReyestrChekivVidPostachalnykaPoVyduPalnogo, SIGNAL(activated()), 
				this, SLOT(action_printReyestrChekivVidPostachalnykaPoVyduPalnogo_activated()));
	
	connect(ui.action_exportInformaciiVExcel, SIGNAL(activated()), 
				this, SLOT(action_exportInformaciiVExcel_activated()));
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkPalneManagement::populateToolBar(QToolBar * tBar)
{
    tBar->addAction(ui.action_printZvitVykorystannyaKoshtivPalne);
    tBar->addAction(ui.action_printReyestrChekivGAZ);
    tBar->addAction(ui.action_printReyestrChekivDailyGAZ);
    tBar->addAction(ui.action_printReyestrChekivPALNE);
    tBar->addAction(ui.action_printReyestrChekivVidPostachalnykaPALNE);
    tBar->addAction(ui.action_printVidomistZakupivliPalnogoPoVodiyahZaMisyac);
    tBar->addAction(ui.action_printVidomistZakupivliPalnogoPoVodiyahZaMisyacVRozriziRahunkiv);
	tBar->addAction(ui.action_printReyestrChekivVidPostachalnykaPoVyduPalnogo);
    tBar->addAction(ui.action_exportInformaciiVExcel);
}
//--------------------utech--------------------utech--------------------utech--------------------
UForm_AParkPalneManagement::~UForm_AParkPalneManagement()
{
	
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkPalneManagement::populateZvitKupivliPalnogo()
{
    if (!ui.groupBox_vodiyFilter->isChecked() &&
            !ui.groupBox_monthFilter->isChecked() &&
            !ui.groupBox_dateFilter->isChecked() &&
            !ui.groupBox_palneFilter->isChecked()) {
        QMessageBox::critical(0, "Помилка","При застосуванні фільтру, хоча б одина\nіз його частин повинна бути ввімкнена");
        return;
    }

    QString filterStr;
    bool needAnd = false;
    if (ui.groupBox_vodiyFilter->isChecked()
            && ui.comboBox_vodiyFilter->itemData(ui.comboBox_vodiyFilter->currentIndex(), Qt::UserRole ).toInt() > 0)
    {
        if (needAnd)
            filterStr += " and ";
        filterStr += "Npr_id="+sqlStr( ui.comboBox_vodiyFilter
                                       ->itemData(ui.comboBox_vodiyFilter->currentIndex(), Qt::UserRole ).toInt() );
        needAnd = true;
    }

    if ( ui.groupBox_monthFilter->isChecked() ) {
        if (needAnd)
            filterStr += " and ";
        filterStr += "year(CDate)="+sqlStr( ui.dateEdit_monthFilter->date().year() )
                + " and " + "month(CDate)="+sqlStr( ui.dateEdit_monthFilter->date().month() );
        needAnd = true;
    }

    if ( ui.groupBox_dateFilter->isChecked() ) {
        if (needAnd)
            filterStr += " and ";
        filterStr += "date(CDate)="+sqlStr( ui.dateEdit_dateFilter->date() );
        needAnd = true;
    }

    if ( ui.groupBox_palneFilter->isChecked()
         && ui.comboBox_typPalnogoFilter->itemData(ui.comboBox_typPalnogoFilter->currentIndex(), Qt::UserRole ).toInt() > 0 ) {
        if (needAnd)
            filterStr += " and ";
        filterStr += "MarkaPalnogo_id="+sqlStr( ui.comboBox_typPalnogoFilter
                                                ->itemData(ui.comboBox_typPalnogoFilter->currentIndex(), Qt::UserRole ).toInt() );
        needAnd = true;
    }

    if ( ui.groupBox_partnerId->isChecked()
         && ui.comboBox_partnerIdFilter->itemData(ui.comboBox_partnerIdFilter->currentIndex(), Qt::UserRole ).toInt() > 0 ) {
        if (needAnd)
            filterStr += " and ";
        filterStr += "DovPartners_id="+sqlStr( ui.comboBox_partnerIdFilter
                                               ->itemData(ui.comboBox_partnerIdFilter->currentIndex(), Qt::UserRole ).toInt() );
        needAnd = true;
    }

    twExtZvity->setSqlFilter(filterStr);
    twExtZvity->populateTable();

    // Populate orders table
    populateZvitKupivliPalnogoOrders();
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkPalneManagement::createZvitKupivliPalnogo()
{
    if (!twExtZvity->addRow("INSERT INTO zvitKupivliPalnogo (CDate, MarkaPalnogo_id, DovPartners_id) \
                            VALUES ("+sqlStr(ui.dateEdit_dateFilter->date())+", \
                                    "+sqlStr(ui.comboBox_typPalnogoFilter->itemData(ui.comboBox_typPalnogoFilter
                                    ->currentIndex(), Qt::UserRole ).toInt())+", \
            "+sqlStr(ui.comboBox_partnerIdFilter->itemData(ui.comboBox_partnerIdFilter
            ->currentIndex(), Qt::UserRole ).toInt())+")"))
            QMessageBox::critical(0,"Помилка створення запису","Запис звіту не створено");
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkPalneManagement::deleteZvitKupivliPalnogo()
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
    if (!twExtZvity->deleteSelectedRows())
        QMessageBox::critical(0,"Помикла видалення запису","Запис не видалено");
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkPalneManagement::populateZvitKupivliPalnogoOrders()
{
    twExtOrders->setSqlFilter("ZvitKupivliPalnogo_id="+sqlStr(twExtZvity->currentItemData("Id").toInt()));
    twExtOrders->populateTable();
    calcOrdersSummary();
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkPalneManagement::createZvitKupivliPalnogoOrders()
{
	disconnect(ui.tableWidget_ZvitKupivliPalnogoOrders, SIGNAL(itemChanged(QTableWidgetItem *)), 
				this, SLOT(calcOrdersSummary()));
	
	int id = twExtZvity->currentItemData("Id").toInt();
	if ( id > 0 ) {
	    if (!twExtOrders->addRow("INSERT INTO zvitKupivliPalnogoOrders (CDate, ZvitKupivliPalnogo_id, DocNum) \
						VALUES ("+sqlStr(twExtZvity->currentItemData("CDate").toDate())+", \
								"+sqlStr(id)+", \
								'')"))
		    QMessageBox::critical(0,"Помилка створення запису","Запис платіжного документа не створено");
		calcOrdersSummary();
	}
	else
	    QMessageBox::information(0,"Помилка вводу", "для внесеня чеків оберіть необхідний звіт");
		
	connect(ui.tableWidget_ZvitKupivliPalnogoOrders, SIGNAL(itemChanged(QTableWidgetItem *)), 
                                this, SLOT(calcOrdersSummary()));
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkPalneManagement::deleteZvitKupivliPalnogoOrders()
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
	if (!twExtOrders->deleteSelectedRows())
		QMessageBox::critical(0,"Помикла видалення запису","Запис не видалено");
	
        calcOrdersSummary();
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkPalneManagement::calcOrdersSummary()
{
    //qDebug() << "calcOrdersSummary()";
	int rowCount = ui.tableWidget_ZvitKupivliPalnogoOrders->rowCount();
	int sumCol = twExtOrders->columnNumber("Suma");
	int palneCol = twExtOrders->columnNumber("Kilkist");
	double sum = 0;
	double palne = 0;
	
	if (sumCol > 0 && palneCol > 0) {
	    for ( int row = 0; row < rowCount; row++ ) {
	    sum += ui.tableWidget_ZvitKupivliPalnogoOrders->item(row, sumCol)->data(Qt::EditRole).toDouble();
		palne += ui.tableWidget_ZvitKupivliPalnogoOrders->item(row, palneCol)->data(Qt::EditRole).toDouble();
		}
	}
	
	ui.label_ordersSummary->setText(QString("К-сть записів: %1; об'єм пального: %2; сума: %3грн.")
									.arg(QString::number(rowCount), uMToStr2(palne), uMToStr2(sum)));
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkPalneManagement::printZvitVykorystannyaKoshtivPalne()
{
    int zvitId = twExtZvity->currentItemData("Id").toInt();
	if (zvitId < 1) {
	    QMessageBox::critical(0,"Помилка","Не вибрано звіт для друку.\nПозначте запис \"Звіту використання коштів\" для друку");
		return;
	}
	
	UPrintDocs_APark *printDocs = new UPrintDocs_APark();
	printDocs->print_zvitVykorystannyaKoshtivPalne(zvitId);
	connect(this, SIGNAL(mainWindowClosed()), printDocs->printform, SLOT(close()));
	delete printDocs;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkPalneManagement::action_printReyestrChekivGAZ_activated()
{
    UDialog_AParkPartnerDateFilter *d = new UDialog_AParkPartnerDateFilter(ui.dateEdit_monthFilter->date(), "Реквізити реєстру", "MM.yyyy");
	if (d->exec()) {
		UPrintDocs_APark *printDocs = new UPrintDocs_APark();
		printDocs->print_reyestrChekivGazZaMisyac(d->date(), d->partnerId());
		connect(this, SIGNAL(mainWindowClosed()), printDocs->printform, SLOT(close()));
		delete printDocs;
	}
	delete d;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkPalneManagement::action_printReyestrChekivDailyGAZ_activated()
{
    UDialog_AParkPartnerDateFilter *d = new UDialog_AParkPartnerDateFilter(ui.dateEdit_monthFilter->date(), "Реквізити реєстру", "MM.yyyy");
	if (d->exec()) {
		UPrintDocs_APark *printDocs = new UPrintDocs_APark();
		printDocs->print_reyestrChekivGazZaMisyacDaily(d->date(), d->partnerId());
		connect(this, SIGNAL(mainWindowClosed()), printDocs->printform, SLOT(close()));
		delete printDocs;
	}
	delete d;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkPalneManagement::action_printReyestrChekivPALNE_activated()
{
    UDialog_AParkDateFilter *d = new UDialog_AParkDateFilter(ui.dateEdit_monthFilter->date(), "Дата реєстру", "MM.yyyy");
    if (d->exec()) {
        UPrintDocs_APark *printDocs = new UPrintDocs_APark();
        printDocs->print_reyestrChekivPalneZaMisyac(d->date());
        connect(this, SIGNAL(mainWindowClosed()), printDocs->printform, SLOT(close()));
        delete printDocs;
    }
    delete d;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkPalneManagement::action_printReyestrChekivVidPostachalnykaPALNE_activated()
{
    UDialog_AParkPartnerDateFilter *d = new UDialog_AParkPartnerDateFilter(ui.dateEdit_monthFilter->date(), "Дата реєстру", "MM.yyyy");
    if (d->exec()) {
        UPrintDocs_APark *printDocs = new UPrintDocs_APark();
        printDocs->print_reyestrChekivVidPostachalnyksPalneZaMisyac(d->partnerId(), d->date());
        connect(this, SIGNAL(mainWindowClosed()), printDocs->printform, SLOT(close()));
        delete printDocs;
    }
    delete d;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkPalneManagement::action_printVidomistZakupivliPalnogoPoVodiyahZaMisyac_activated()
{
    UDialog_AParkMarkaPalnogoDateFilter *d = new UDialog_AParkMarkaPalnogoDateFilter(ui.dateEdit_monthFilter->date(), "Дата відомості", "MM.yyyy");
	if (d->exec()) {
		UPrintDocs_APark *printDocs = new UPrintDocs_APark();
		printDocs->print_vidomistZakupivliPalnogoPoVodiyahZaMisyac(d->date(), d->markaPalnogoId());
		connect(this, SIGNAL(mainWindowClosed()), printDocs->printform, SLOT(close()));
		delete printDocs;
	}
	delete d;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkPalneManagement::action_printVidomistZakupivliPalnogoPoVodiyahZaMisyacVRozriziRahunkiv_activated()
{
    UDialog_AParkDateFilter *d = new UDialog_AParkDateFilter(ui.dateEdit_monthFilter->date(), "Дата відомості", "MM.yyyy");
	if (d->exec()) {
		UPrintDocs_APark *printDocs = new UPrintDocs_APark();
		printDocs->print_vidomistZakupivliPalnogoPoVodiyahZaMisyacVRozriziRahunkiv(d->date());
		connect(this, SIGNAL(mainWindowClosed()), printDocs->printform, SLOT(close()));
		delete printDocs;
	}
	delete d;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkPalneManagement::action_printReyestrChekivVidPostachalnykaPoVyduPalnogo_activated()
{
	UDialog_AParkPartnerMarkaPalnogoDateFilter *d = new UDialog_AParkPartnerMarkaPalnogoDateFilter(QDate::currentDate(), "Вибір реквізитів для реєстру", "MM.yyyy", this);
	if (d->exec()) {
	    UPrintDocs_APark *printDocs = new UPrintDocs_APark();
		printDocs->print_reyestrChekivVidPostachalnykaPoVyduPalnogo(d->date(), d->partnerId(), d->markaPalnogoId());
		connect(this, SIGNAL(mainWindowClosed()), printDocs->printform, SLOT(close()));
		delete printDocs;
	}
	delete d;
	
	
	
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkPalneManagement::action_exportInformaciiVExcel_activated()
{
	UDialog_AParkPartnerDateFilter *d = new UDialog_AParkPartnerDateFilter(QDate::currentDate(), "Вибір АЗС (підприємства) для експорту чеків", "MM.yyyy", this);
	if (d->exec()) {
	    QString path = QFileDialog::getExistingDirectory(0, "Вибір папки", 
														QDesktopServices::storageLocation(QDesktopServices::DesktopLocation));
		if (path.length() > 0) {
		    AParkExport::exportCheckivVExcel(d->date(), d->partnerId(), path);
		}
	}
	delete d;
}
//--------------------utech--------------------utech--------------------utech--------------------
