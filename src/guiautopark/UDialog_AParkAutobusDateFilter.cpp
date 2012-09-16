//--------------------utech--------------------utech--------------------utech--------------------
//
// Створений програмістами Компанії "Утех" 23.04.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#include "UDialog_AParkAutobusDateFilter.h"
#include <QSqlQuery>

//--------------------utech--------------------utech--------------------utech--------------------
UDialog_AParkAutobusDateFilter::UDialog_AParkAutobusDateFilter(short year, short month, QString title, QWidget *parent)
        : QDialog(parent)
{
    ui.setupUi(this);

	date = QDate::currentDate();
	if (date.month() == 12)
		ui.spinBox_year->setMaximum(date.year()+1);
	else
		ui.spinBox_year->setMaximum(date.year());
	
	QSqlQuery query;
	query.exec("SELECT ruhomyiSklad.GarajNumber, ruhomyiSklad.NomernyiZnak, \
						markaAuto.MarkaShyfr \
				FROM ruhomyiSklad \
				LEFT JOIN markaauto ON markaAuto.id=ruhomyiSklad.MarkaAuto_id \
				ORDER BY ruhomyiSklad.NomernyiZnak");
	while (query.next())
		ui.comboBox_autobus->addItem("№"+query.value(0).toString()+" ["+query.value(1).toString()+"] - "+query.value(2).toString(), query.value(0).toInt());
	
	if (ui.comboBox_autobus->count() > 0)
		ui.comboBox_autobus->setCurrentIndex(0);
	
	setWindowTitle(title);
	setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
	ui.spinBox_year->setValue(year);
	ui.spinBox_month->setValue(month);
}
//--------------------utech--------------------utech--------------------utech--------------------
int UDialog_AParkAutobusDateFilter::month()
{
	return ui.spinBox_month->value();
}
//--------------------utech--------------------utech--------------------utech--------------------
int UDialog_AParkAutobusDateFilter::year()
{
	return ui.spinBox_year->value();
}
//--------------------utech--------------------utech--------------------utech--------------------
int UDialog_AParkAutobusDateFilter::garajNumber()
{
	return ui.comboBox_autobus->itemData(ui.comboBox_autobus->currentIndex(), Qt::UserRole).toInt();
}
//--------------------utech--------------------utech--------------------utech--------------------
UDialog_AParkAutobusDateFilter::~UDialog_AParkAutobusDateFilter()
{

}
//--------------------utech--------------------utech--------------------utech--------------------
