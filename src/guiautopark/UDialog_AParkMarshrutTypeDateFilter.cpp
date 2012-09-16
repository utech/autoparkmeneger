//--------------------utech--------------------utech--------------------utech--------------------
//
// Створений програмістами Компанії "Утех" 23.04.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#include "UDialog_AParkMarshrutTypeDateFilter.h"
#include <QSqlQuery>

//--------------------utech--------------------utech--------------------utech--------------------
UDialog_AParkMarshrutTypeDateFilter::UDialog_AParkMarshrutTypeDateFilter(QDate dt, QString title, QString dateFormat, QWidget *parent)
        : QDialog(parent)
{
    ui.setupUi(this);
	
	ui.dateEdit->setDisplayFormat(dateFormat);
	ui.dateEdit->setDate(dt);
	
	QSqlQuery query;
	query.exec("SELECT Id, TypNameMnoj FROM typmarshrutu");
	ui.comboBox_typMarshrutu->addItem("Усі типи", 0);
	while (query.next()){
		ui.comboBox_typMarshrutu->addItem(query.value(1).toString(), query.value(0));
	}
	ui.comboBox_typMarshrutu->setCurrentIndex(0);
	
	setWindowTitle(title);
	setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
}
//--------------------utech--------------------utech--------------------utech--------------------
int UDialog_AParkMarshrutTypeDateFilter::month()
{
	return ui.dateEdit->date().month();
}
//--------------------utech--------------------utech--------------------utech--------------------
int UDialog_AParkMarshrutTypeDateFilter::year()
{
	return ui.dateEdit->date().month();
}
//--------------------utech--------------------utech--------------------utech--------------------
QDate UDialog_AParkMarshrutTypeDateFilter::date()
{
	return ui.dateEdit->date();
}
//--------------------utech--------------------utech--------------------utech--------------------
int UDialog_AParkMarshrutTypeDateFilter::marshrutType()
{
	return ui.comboBox_typMarshrutu->itemData(ui.comboBox_typMarshrutu->currentIndex()).toInt();
}
//--------------------utech--------------------utech--------------------utech--------------------
UDialog_AParkMarshrutTypeDateFilter::~UDialog_AParkMarshrutTypeDateFilter()
{

}
//--------------------utech--------------------utech--------------------utech--------------------
