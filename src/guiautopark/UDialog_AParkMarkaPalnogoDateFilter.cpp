//--------------------utech--------------------utech--------------------utech--------------------
//
// Створений програмістами Компанії "Утех" 26.06.2011р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#include "UDialog_AParkMarkaPalnogoDateFilter.h"
#include <QSqlQuery>

//--------------------utech--------------------utech--------------------utech--------------------
UDialog_AParkMarkaPalnogoDateFilter::UDialog_AParkMarkaPalnogoDateFilter(QDate dt, QString title, QString dateFormat, QWidget *parent)
        : QDialog(parent)
{
    ui.setupUi(this);
	
	ui.dateEdit->setDisplayFormat(dateFormat);
	ui.dateEdit->setDate(dt);
	
	QSqlQuery query;
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
int UDialog_AParkMarkaPalnogoDateFilter::month()
{
	return ui.dateEdit->date().month();
}
//--------------------utech--------------------utech--------------------utech--------------------
int UDialog_AParkMarkaPalnogoDateFilter::year()
{
	return ui.dateEdit->date().month();
}
//--------------------utech--------------------utech--------------------utech--------------------
QDate UDialog_AParkMarkaPalnogoDateFilter::date()
{
	return ui.dateEdit->date();
}
//--------------------utech--------------------utech--------------------utech--------------------
int UDialog_AParkMarkaPalnogoDateFilter::markaPalnogoId()
{
	return ui.comboBox_markaPalnogo->itemData(ui.comboBox_markaPalnogo->currentIndex()).toInt();
}
//--------------------utech--------------------utech--------------------utech--------------------
UDialog_AParkMarkaPalnogoDateFilter::~UDialog_AParkMarkaPalnogoDateFilter()
{

}
//--------------------utech--------------------utech--------------------utech--------------------
