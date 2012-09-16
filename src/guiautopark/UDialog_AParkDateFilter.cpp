//--------------------utech--------------------utech--------------------utech--------------------
//
// Створений програмістами Компанії "Утех" 23.04.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#include "UDialog_AParkDateFilter.h"

//--------------------utech--------------------utech--------------------utech--------------------
UDialog_AParkDateFilter::UDialog_AParkDateFilter(short year, short month, QString title, QWidget *parent)
        : QDialog(parent)
{
    ui.setupUi(this);

	ui.dateEdit->setDisplayFormat("MM.yyyy");
	setWindowTitle(title);
	setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
	ui.dateEdit->setDate(QDate(year, month, 1));
}
//--------------------utech--------------------utech--------------------utech--------------------
UDialog_AParkDateFilter::UDialog_AParkDateFilter(QDate dDate, QString title, QString editDisplayFormat, QWidget *parent)
        : QDialog(parent)
{
	ui.setupUi(this);

	ui.dateEdit->setDisplayFormat(editDisplayFormat);
	setWindowTitle(title);
	setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
	ui.dateEdit->setDate(dDate);
}
//--------------------utech--------------------utech--------------------utech--------------------
int UDialog_AParkDateFilter::month()
{
	return ui.dateEdit->date().month();
}
//--------------------utech--------------------utech--------------------utech--------------------
int UDialog_AParkDateFilter::year()
{
	return ui.dateEdit->date().year();
}
//--------------------utech--------------------utech--------------------utech--------------------
QDate UDialog_AParkDateFilter::date()
{
	return ui.dateEdit->date();
}
//--------------------utech--------------------utech--------------------utech--------------------
UDialog_AParkDateFilter::~UDialog_AParkDateFilter()
{

}
//--------------------utech--------------------utech--------------------utech--------------------
