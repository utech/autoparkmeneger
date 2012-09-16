//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл виконання класу вікна налаштування програми
//
// Створений програмістами Компанії "Утех" 29.03.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#include "UMainWindow_AParkPerevez.h"

#include "UForm_AParkHelpWidget.h"
#include "UForm_AParkLystokRegulyarnostiRuhu.h"
#include "UForm_AParkRuhomyiSklad.h"
#include "UForm_AParkMarshruty.h"
#include "UForm_AParkShlyahovyiLyst.h"
#include "UForm_AParkMarkyAuto.h"
#include "UForm_AParkCinaPalnogo.h"
#include "UForm_AParkTOLog.h"
#include "UForm_AParkProbigInfo.h"
#include "UForm_AParkPracivnyky.h"
#include "UForm_AParkKartkyOblikuVykonannyaPlanu.h"
#include "UForm_AParkRozrahSumyKompensPoPilgah.h"
#include "UForm_AParkPlanNaZminu.h"
#include "UForm_AParkEditTabelWidget.h"
#include "UForm_AParkSvyatkoviDni.h"
#include "UForm_AParkKartkyRobotyVodiyiv.h"
#include "UDialogRegisterUser_APark.h"
#include "UForm_AParkDocumentsView.h"
#include "UForm_AParkEditSumTabelWidget.h"
#include "UForm_AParkZarplataAgentski.h"
#include "UForm_AParkDocumentsView_PlanovyiViddil.h"
#include "UForm_AParkCloseMonthes.h"
#include "UForm_AParkPrintDocksSigns.h"
#include "UForm_AParkPalneManagement.h"
#include "UForm_AParkPartnery.h"
#include "UForm_AParkEditTabelPidrozdilivWidget.h"

//--------------------utech--------------------utech--------------------utech--------------------
void UMainWindow_AParkPerevez::treeWidget_zmist_itemDoubleClicked()
{
	populatePartsTabWidget(ui.treeWidget_zmist->currentItem()->data(0, Qt::UserRole).toInt());
}
//--------------------utech--------------------utech--------------------utech--------------------
void UMainWindow_AParkPerevez::buttonCreateTabParts_clicked()
{
	populatePartsTabWidget(UAutoPark::HelpWidget, UAutoPark::CreateTab);
}
//--------------------utech--------------------utech--------------------utech--------------------
void UMainWindow_AParkPerevez::buttonDeleteTabParts_clicked()
{
	if (ui.tabWidget_parts->count() > 1)
		delete ui.tabWidget_parts->currentWidget();
}
//--------------------utech--------------------utech--------------------utech--------------------
void UMainWindow_AParkPerevez::tabWidget_parts_tabCloseRequested(int index)
{
	if (ui.tabWidget_parts->count() > 1)
		delete ui.tabWidget_parts->widget(index);
}
//--------------------utech--------------------utech--------------------utech--------------------
void UMainWindow_AParkPerevez::populatePartsTabWidget(int tabWidgetType, 
				UAutoPark::UPerevezTabWidgetPartsWay tabWidgetActionType,
				bool showWarnings)
{
	if (tabWidgetType!=0 && tabWidgetType!=1 && !UDialogRegisterUser::userHasAccessToWidget(tabWidgetType)){
		if (showWarnings)
			QMessageBox::information(0, "Заборона доступу", "Ваші права доступу не дозволяють Вам зайти в\nобраний розділ.");
		return;
	}
	
	UAParkTabWidget *w = NULL;
	if (tabWidgetType == UAutoPark::NoWidget)
		w = new UForm_AParkHelpWidget(tabWidgetType, ui.tabWidget_parts);
	else if (tabWidgetType == UAutoPark::HelpWidget)
		w = new UForm_AParkHelpWidget(tabWidgetType, ui.tabWidget_parts);
	else if (tabWidgetType == UAutoPark::RuhomyiSkladWidget)
		w = new UForm_AParkRuhomyiSklad(tabWidgetType, ui.tabWidget_parts);
	else if (tabWidgetType == UAutoPark::MarshrutyWidget)
		w = new UForm_AParkMarshruty(tabWidgetType, ui.tabWidget_parts);
	else if (tabWidgetType == UAutoPark::ShlyahovyiLystWidget)
		w = new UForm_AParkShlyahovyiLyst(tabWidgetType, ui.tabWidget_parts);
	else if (tabWidgetType == UAutoPark::LystokRegulyarnostiRuhuWidget)
		w = new UForm_AParkLystokRegulyarnostiRuhu(tabWidgetType, ui.tabWidget_parts);
	else if (tabWidgetType == UAutoPark::PalneWidget)
		w = new UForm_AParkCinaPalnogo(tabWidgetType, ui.tabWidget_parts);
	else if (tabWidgetType == UAutoPark::TOLogWidget)
		w = new UForm_AParkTOLog(tabWidgetType, ui.tabWidget_parts);
	else if (tabWidgetType == UAutoPark::ProbigInfoWidget)
		w = new UForm_AParkProbigInfo(tabWidgetType, ui.tabWidget_parts);
	else if (tabWidgetType == UAutoPark::PerelikPracivnykiv)
		w = new UForm_AParkPracivnyky(tabWidgetType, ui.tabWidget_parts);
	else if (tabWidgetType == UAutoPark::KartkyOblikuVykonPlanu)
		w = new UForm_AParkKartkyOblikuVykonannyaPlanu(tabWidgetType, ui.tabWidget_parts);
	else if (tabWidgetType == UAutoPark::ZvitPoPilgovomuProizdu)
		w = new UForm_AParkRozrahSumyKompensPoPilgah(tabWidgetType, ui.tabWidget_parts);
	else if (tabWidgetType == UAutoPark::MarkaAutoWidget)
		w = new UForm_AParkMarkyAuto(tabWidgetType, ui.tabWidget_parts);
	else if (tabWidgetType == UAutoPark::PlanNaZminuWidget)
		w = new UForm_AParkPlanNaZminu(tabWidgetType, ui.tabWidget_parts);
	else if (tabWidgetType == UAutoPark::EditTabelWidget)
		w = new UForm_AParkEditTabelWidget(tabWidgetType, ui.tabWidget_parts);
	else if (tabWidgetType == UAutoPark::SvyatkoviDniWidget)
		w = new UForm_AParkSvyatkoviDni(tabWidgetType, ui.tabWidget_parts);
	else if (tabWidgetType == UAutoPark::KartkyRobotyVodiyivWidget)
		w = new UForm_AParkKartkyRobotyVodiyiv(tabWidgetType, ui.tabWidget_parts);
	else if (tabWidgetType == UAutoPark::DocumentsViewWidget)
		w = new UForm_AParkDocumentsView(tabWidgetType, ui.tabWidget_parts);
	else if (tabWidgetType == UAutoPark::EditSumTabelWidget)
		w = new UForm_AParkEditSumTabelWidget(tabWidgetType, ui.tabWidget_parts);
	else if (tabWidgetType == UAutoPark::EditZarplataAgentski)
		w = new UForm_AParkZarplataAgentski(tabWidgetType, ui.tabWidget_parts);
	else if (tabWidgetType == UAutoPark::DocumentsViewWidget_PlanovyiViddil)
		w = new UForm_AParkDocumentsView_PlanovyiViddil(tabWidgetType, ui.tabWidget_parts);
	else if (tabWidgetType == UAutoPark::MonthCloseWidget)
		w = new UForm_AParkCloseMonthes(tabWidgetType, ui.tabWidget_parts);
	else if (tabWidgetType == UAutoPark::PrintDocksSignsWidget)
		w = new UForm_AParkPrintDocksSigns(tabWidgetType, ui.tabWidget_parts);
	else if (tabWidgetType == UAutoPark::PalneManagementWidget)
		w = new UForm_AParkPalneManagement(tabWidgetType, ui.tabWidget_parts);
	else if (tabWidgetType == UAutoPark::PartneryWidget)
		w = new UForm_AParkPartnery(tabWidgetType, ui.tabWidget_parts);
	else if (tabWidgetType == UAutoPark::EditTabelPidrozdilivWidget)
		w = new UForm_AParkEditTabelPidrozdilivWidget(tabWidgetType, ui.tabWidget_parts);
	else{
		tabWidgetType = UAutoPark::HelpWidget;
		w = new UForm_AParkHelpWidget(tabWidgetType, ui.tabWidget_parts);
	}
	
	ui.toolBar_dockWidgets->clear();
	w->populateToolBar(ui.toolBar_dockWidgets);
	
	UPerevezTabWidgetPartsNames tabPartsNames;
	if (tabWidgetActionType == UAutoPark::UpdateTab){
		short curTabIndex = ui.tabWidget_parts->currentIndex();
		delete ui.tabWidget_parts->widget(curTabIndex);
		ui.tabWidget_parts->insertTab( curTabIndex, w, tabPartsNames.PartsNames[tabWidgetType] );
		ui.tabWidget_parts->setCurrentWidget( w );
	}
	else{
		ui.tabWidget_parts->addTab( w, tabPartsNames.PartsNames[tabWidgetType] );
		ui.tabWidget_parts->setCurrentWidget( w );
	}
}
//--------------------utech--------------------utech--------------------utech--------------------
void UMainWindow_AParkPerevez::tabWidget_parts_currentChanged(int index)
{
	UAParkTabWidget * w = qobject_cast<UAParkTabWidget *>(ui.tabWidget_parts->currentWidget());
	if (w){
		ui.toolBar_dockWidgets->clear();
		w->populateToolBar(ui.toolBar_dockWidgets);
	}
}
//--------------------utech--------------------utech--------------------utech--------------------
void UMainWindow_AParkPerevez::populateZmistTreeWidget()
{
	QTreeWidgetItem * topItem = NULL;
	QTreeWidgetItem * childItem = NULL;
	
	//Заголовок
	topItem = new QTreeWidgetItem();
	ui.treeWidget_zmist->setHeaderLabel( "Оберіть завдання підрозділу" );
	
	//Керівництво
	topItem = new QTreeWidgetItem();
	topItem->setData( 0, Qt::DisplayRole, "Керівництво" );
	topItem->setIcon(0, QIcon(":/function_icon_set/function_icon_set/star_48.png"));
	childItem = new QTreeWidgetItem(topItem);
	childItem->setData( 0, Qt::DisplayRole, "Перегляд документації" );
	childItem->setData( 0, Qt::UserRole, UAutoPark::DocumentsViewWidget );
	childItem = new QTreeWidgetItem(topItem);
	childItem->setData( 0, Qt::DisplayRole, "Пробіг (необхідність ТО)" );
	childItem->setData( 0, Qt::UserRole, UAutoPark::ProbigInfoWidget );
	childItem = new QTreeWidgetItem(topItem);
	childItem->setData( 0, Qt::DisplayRole, "Картки обліку виконання плану" );
	childItem->setData( 0, Qt::UserRole, UAutoPark::KartkyOblikuVykonPlanu );
	childItem = new QTreeWidgetItem(topItem);
	childItem->setData( 0, Qt::DisplayRole, "Картки роботи водіїв" );
	childItem->setData( 0, Qt::UserRole, UAutoPark::KartkyRobotyVodiyivWidget );
	ui.treeWidget_zmist->addTopLevelItem( topItem );
	
	//Диспетчерська
	topItem = new QTreeWidgetItem();
	topItem->setData( 0, Qt::DisplayRole, "Диспетчерська" );
	topItem->setIcon(0, QIcon(":/function_icon_set/function_icon_set/clock_48.png"));
	childItem = new QTreeWidgetItem(topItem);
	childItem->setData( 0, Qt::DisplayRole, "Рухомий склад" );
	childItem->setData( 0, Qt::UserRole, UAutoPark::RuhomyiSkladWidget );
	childItem = new QTreeWidgetItem(topItem);
	childItem->setData( 0, Qt::DisplayRole, "Маршрути" );
	childItem->setData( 0, Qt::UserRole, UAutoPark::MarshrutyWidget );
	childItem = new QTreeWidgetItem(topItem);
	childItem->setData( 0, Qt::DisplayRole, "Шляховий лист" );
	childItem->setData( 0, Qt::UserRole, UAutoPark::ShlyahovyiLystWidget );
	childItem = new QTreeWidgetItem(topItem);
	childItem->setData( 0, Qt::DisplayRole, "Листок регулярності руху автобуса" );
	childItem->setData( 0, Qt::UserRole, UAutoPark::LystokRegulyarnostiRuhuWidget );
	childItem = new QTreeWidgetItem(topItem);
	childItem->setData( 0, Qt::DisplayRole, "Ціни на пальне" );
	childItem->setData( 0, Qt::UserRole, UAutoPark::PalneWidget );
	childItem = new QTreeWidgetItem(topItem);
	childItem->setData( 0, Qt::DisplayRole, "Планова виручка" );
	childItem->setData( 0, Qt::UserRole, UAutoPark::PlanNaZminuWidget );
	childItem = new QTreeWidgetItem(topItem);
	childItem->setData( 0, Qt::DisplayRole, "Марки автобусів" );
	childItem->setData( 0, Qt::UserRole, UAutoPark::MarkaAutoWidget );
	ui.treeWidget_zmist->addTopLevelItem( topItem );
	
	//Техвідділ
	topItem = new QTreeWidgetItem();
	topItem->setData( 0, Qt::DisplayRole, "Технічний відділ" );
	topItem->setIcon(0, QIcon(":/function_icon_set/function_icon_set/spanner_48.png"));
	childItem = new QTreeWidgetItem(topItem);
	childItem->setData( 0, Qt::DisplayRole, "ТО" );
	childItem->setData( 0, Qt::UserRole, UAutoPark::TOLogWidget );
	childItem = new QTreeWidgetItem(topItem);
	childItem->setData( 0, Qt::DisplayRole, "Пробіг (необхідність ТО)" );
	childItem->setData( 0, Qt::UserRole, UAutoPark::ProbigInfoWidget );
	ui.treeWidget_zmist->addTopLevelItem( topItem );
	
	//Плановий відділ
	topItem = new QTreeWidgetItem();
	topItem->setData( 0, Qt::DisplayRole, "Плановий відділ" );
	topItem->setIcon(0, QIcon(":/function_icon_set/function_icon_set/pie_chart_48.png"));
	childItem = new QTreeWidgetItem(topItem);
	childItem->setData( 0, Qt::DisplayRole, "Картки обліку виконання плану" );
	childItem->setData( 0, Qt::UserRole, UAutoPark::KartkyOblikuVykonPlanu );
	childItem = new QTreeWidgetItem(topItem);
	childItem->setData( 0, Qt::DisplayRole, "Звіт по пільговому проїзду" );
	childItem->setData( 0, Qt::UserRole, UAutoPark::ZvitPoPilgovomuProizdu );
	childItem = new QTreeWidgetItem(topItem);
	childItem->setData( 0, Qt::DisplayRole, "Облік пального" );
	childItem->setData( 0, Qt::UserRole, UAutoPark::PalneManagementWidget );
	childItem = new QTreeWidgetItem(topItem);
	childItem->setData( 0, Qt::DisplayRole, "Партнери" );
	childItem->setData( 0, Qt::UserRole, UAutoPark::PartneryWidget );
	childItem = new QTreeWidgetItem(topItem);
	childItem->setData( 0, Qt::DisplayRole, "Перегляд документації" );
	childItem->setData( 0, Qt::UserRole, UAutoPark::DocumentsViewWidget_PlanovyiViddil );
	ui.treeWidget_zmist->addTopLevelItem( topItem );
	
	//Відділ кадрів
	topItem = new QTreeWidgetItem();
	topItem->setData( 0, Qt::DisplayRole, "Відділ кадрів" );
	topItem->setIcon(0, QIcon(":/function_icon_set/function_icon_set/users_two_48.png"));
	childItem = new QTreeWidgetItem(topItem);
	childItem->setData( 0, Qt::DisplayRole, "Перелік працівників" );
	childItem->setData( 0, Qt::UserRole, UAutoPark::PerelikPracivnykiv );
	ui.treeWidget_zmist->addTopLevelItem( topItem );
	
	//Облік робочого часу
	topItem = new QTreeWidgetItem();
	topItem->setData( 0, Qt::DisplayRole, "Облік робочого часу" );
	topItem->setIcon(0, QIcon(":/function_icon_set/function_icon_set/table_48.png"));
	childItem = new QTreeWidgetItem(topItem);
	childItem->setData( 0, Qt::DisplayRole, "Святкові дні" );
	childItem->setData( 0, Qt::UserRole, UAutoPark::SvyatkoviDniWidget );
	childItem = new QTreeWidgetItem(topItem);
	childItem->setData( 0, Qt::DisplayRole, "Табель водіїв" );
	childItem->setData( 0, Qt::UserRole, UAutoPark::EditTabelWidget );
	childItem = new QTreeWidgetItem(topItem);
	childItem->setData( 0, Qt::DisplayRole, "Табель підрозділів" );
	childItem->setData( 0, Qt::UserRole, UAutoPark::EditTabelPidrozdilivWidget );
	childItem = new QTreeWidgetItem(topItem);
	childItem->setData( 0, Qt::DisplayRole, "Табель підсумковий" );
	childItem->setData( 0, Qt::UserRole, UAutoPark::EditSumTabelWidget );
	childItem = new QTreeWidgetItem(topItem);
	childItem->setData( 0, Qt::DisplayRole, "Картки роботи водіїв" );
	childItem->setData( 0, Qt::UserRole, UAutoPark::KartkyRobotyVodiyivWidget );
	ui.treeWidget_zmist->addTopLevelItem( topItem );
	
	//Зарплата
	topItem = new QTreeWidgetItem();
	topItem->setData( 0, Qt::DisplayRole, "Зарлата" );
	topItem->setIcon(0, QIcon(":/icontexto_webdev_pack/icontexto_webdev_pack/icontexto-webdev-user-016x016.png"));
	childItem = new QTreeWidgetItem(topItem);
	childItem->setData( 0, Qt::DisplayRole, "Агентські" );
	childItem->setData( 0, Qt::UserRole, UAutoPark::EditZarplataAgentski );
	ui.treeWidget_zmist->addTopLevelItem( topItem );
	
	//Адміністрування
	topItem = new QTreeWidgetItem();
	topItem->setData( 0, Qt::DisplayRole, "Адміністрування" );
	topItem->setIcon(0, QIcon(":/icontexto_webdev_pack/icontexto_webdev_pack/icontexto-webdev-rss-feed-016x016.png"));
	childItem = new QTreeWidgetItem(topItem);
	childItem->setData( 0, Qt::DisplayRole, "Закриття місяців" );
	childItem->setData( 0, Qt::UserRole, UAutoPark::MonthCloseWidget );
	childItem = new QTreeWidgetItem(topItem);
	childItem->setData( 0, Qt::DisplayRole, "Підписи документів" );
	childItem->setData( 0, Qt::UserRole, UAutoPark::PrintDocksSignsWidget );
	ui.treeWidget_zmist->addTopLevelItem( topItem );
	
	ui.treeWidget_zmist->expandAll();
}
//--------------------utech--------------------utech--------------------utech--------------------
bool UMainWindow_AParkPerevez::loadUserSession()
{
	QSqlQuery query;
	query.exec("SELECT window_id, window_isActive FROM usersSessionsApark \
				WHERE user_id="+sqlStr(UDialogRegisterUser::registeredUserId())+" \
				ORDER BY window_order");
	short windowCount=0;
	UAutoPark::UPerevezTabWidgetPartsWay operType = UAutoPark::UpdateTab;
	int activeWidgetIndex = 0;
	for (;query.next(); ++windowCount){
		populatePartsTabWidget(query.value(0).toInt(), operType, false);
		if (query.value(1).toBool())
			activeWidgetIndex = windowCount;
		operType = UAutoPark::CreateTab;
		
		if (windowCount == 4) //максимум 5 вікон
			break;
	}
	
	if (windowCount){
		ui.tabWidget_parts->setCurrentIndex(activeWidgetIndex);
		tabWidget_parts_currentChanged(activeWidgetIndex);
	}
		
	return windowCount ? true : false;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UMainWindow_AParkPerevez::saveUserSession()
{
	QSqlQuery query;
	query.exec("DELETE FROM usersSessionsApark WHERE user_id="+sqlStr(UDialogRegisterUser::registeredUserId()));
	
	int wCount = ui.tabWidget_parts->count();
	for (int iter=0; iter<wCount; ++iter){
		UAParkTabWidget *w = dynamic_cast<UAParkTabWidget *>(ui.tabWidget_parts->widget(iter));
		if (w)
			query.exec("INSERT INTO usersSessionsApark (user_id, window_id, window_order, window_isActive) \
					VALUES ("+sqlStr(UDialogRegisterUser::registeredUserId())+", \
							"+sqlStr(w->tabWidgetType())+", \
							"+sqlStr(iter)+", \
							"+sqlStr(ui.tabWidget_parts->currentIndex()==iter ? true : false)+")");
	}
}
//--------------------utech--------------------utech--------------------utech--------------------
