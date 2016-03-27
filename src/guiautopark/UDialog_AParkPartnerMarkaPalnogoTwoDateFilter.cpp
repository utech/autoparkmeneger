//--------------------utech--------------------utech--------------------utech--------------------
//
// Створений програмістами Компанії "Утех" 21.01.2012р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#include "UDialog_AParkPartnerMarkaPalnogoTwoDateFilter.h"
#include <QSqlQuery>

//--------------------utech--------------------utech--------------------utech--------------------
UDialog_AParkPartnerMarkaPalnogoTwoDateFilter::UDialog_AParkPartnerMarkaPalnogoTwoDateFilter(QDate dt, QDate dt1, QString title, QString dateFormat, QWidget *parent)
        : QDialog(parent)
{
    ui.setupUi(this);
	
	ui.dateEdit->setDisplayFormat(dateFormat);
	ui.dateEdit->setDate(dt);
	
	ui.dateEdit_2->setDisplayFormat(dateFormat);
	ui.dateEdit_2->setDate(dt1);
	
	QSqlQuery query;
	query.exec("SELECT id, Name FROM dovpartners ORDER BY Name");
	//ui.comboBox_partner->addItem("Усі типи", 0);
	while (query.next()){
		ui.comboBox_partner->addItem("["+query.value(0).toString()+"] "+query.value(1).toString(), query.value(0));
	}
	ui.comboBox_partner->setCurrentIndex(0);
	
	query.exec("SELECT Id, MarkaName FROM markaPalnogo ORDER BY id");
	//ui.comboBox_markaPalnogo->addItem("Усі типи", 0);
	while (query.next()){
		ui.comboBox_markaPalnogo->addItem(query.value(1).toString(), query.value(0));
	}
	ui.comboBox_markaPalnogo->setCurrentIndex(4);
	
	setWindowTitle(title);
	setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
}
//--------------------utech--------------------utech--------------------utech--------------------
int UDialog_AParkPartnerMarkaPalnogoTwoDateFilter::month()
{
	return ui.dateEdit->date().month();
}
//--------------------utech--------------------utech--------------------utech--------------------
int UDialog_AParkPartnerMarkaPalnogoTwoDateFilter::month1()
{
	return ui.dateEdit_2->date().month();
}
//--------------------utech--------------------utech--------------------utech--------------------
int UDialog_AParkPartnerMarkaPalnogoTwoDateFilter::year()
{
	return ui.dateEdit->date().month();
}
//--------------------utech--------------------utech--------------------utech--------------------
int UDialog_AParkPartnerMarkaPalnogoTwoDateFilter::year1()
{
	return ui.dateEdit_2->date().month();
}
//--------------------utech--------------------utech--------------------utech--------------------
QDate UDialog_AParkPartnerMarkaPalnogoTwoDateFilter::date()
{
	return ui.dateEdit->date();
}
//--------------------utech--------------------utech--------------------utech--------------------
QDate UDialog_AParkPartnerMarkaPalnogoTwoDateFilter::date1()
{
	return ui.dateEdit_2->date();
}
//--------------------utech--------------------utech--------------------utech--------------------
int UDialog_AParkPartnerMarkaPalnogoTwoDateFilter::partnerId()
{
	return ui.comboBox_partner->itemData(ui.comboBox_partner->currentIndex()).toInt();
}
//--------------------utech--------------------utech--------------------utech--------------------
int UDialog_AParkPartnerMarkaPalnogoTwoDateFilter::markaPalnogoId()
{
	return ui.comboBox_markaPalnogo->itemData(ui.comboBox_markaPalnogo->currentIndex()).toInt();
}
//--------------------utech--------------------utech--------------------utech--------------------
UDialog_AParkPartnerMarkaPalnogoTwoDateFilter::~UDialog_AParkPartnerMarkaPalnogoTwoDateFilter()
{

}
//--------------------utech--------------------utech--------------------utech--------------------
