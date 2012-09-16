//--------------------utech--------------------utech--------------------utech--------------------
//
// Створений програмістами Компанії "Утех" 26.06.2011р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#include "UDialog_AParkPartnerDateFilter.h"
#include <QSqlQuery>

//--------------------utech--------------------utech--------------------utech--------------------
UDialog_AParkPartnerDateFilter::UDialog_AParkPartnerDateFilter(QDate dt, QString title, QString dateFormat, QWidget *parent)
        : QDialog(parent)
{
    ui.setupUi(this);
	
	ui.dateEdit->setDisplayFormat(dateFormat);
	ui.dateEdit->setDate(dt);
	
	QSqlQuery query;
	query.exec("SELECT id, Name FROM dovpartners ORDER BY Name");
	//ui.comboBox_partner->addItem("Усі типи", 0);
	while (query.next()){
		ui.comboBox_partner->addItem("["+query.value(0).toString()+"] "+query.value(1).toString(), query.value(0));
	}
	ui.comboBox_partner->setCurrentIndex(0);
	
	setWindowTitle(title);
	setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
}
//--------------------utech--------------------utech--------------------utech--------------------
int UDialog_AParkPartnerDateFilter::month()
{
	return ui.dateEdit->date().month();
}
//--------------------utech--------------------utech--------------------utech--------------------
int UDialog_AParkPartnerDateFilter::year()
{
	return ui.dateEdit->date().month();
}
//--------------------utech--------------------utech--------------------utech--------------------
QDate UDialog_AParkPartnerDateFilter::date()
{
	return ui.dateEdit->date();
}
//--------------------utech--------------------utech--------------------utech--------------------
int UDialog_AParkPartnerDateFilter::partnerId()
{
	return ui.comboBox_partner->itemData(ui.comboBox_partner->currentIndex()).toInt();
}
//--------------------utech--------------------utech--------------------utech--------------------
UDialog_AParkPartnerDateFilter::~UDialog_AParkPartnerDateFilter()
{

}
//--------------------utech--------------------utech--------------------utech--------------------
