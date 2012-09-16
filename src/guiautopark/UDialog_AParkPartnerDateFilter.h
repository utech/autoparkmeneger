//--------------------utech--------------------utech--------------------utech--------------------
//
// Створений програмістами Компанії "Утех" 26.06.2011р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#ifndef UDIALOG_APARKPARTNERDATEFILTER_H
#define UDIALOG_APARKPARTNERDATEFILTER_H

#include <QDialog>
#include <QDate>
#include <QtDebug>

#include "ui_UDialog_AParkPartnerDateFilter.h"
//--------------------utech--------------------utech--------------------utech--------------------
class UDialog_AParkPartnerDateFilter : public QDialog
{
        Q_OBJECT

    public:
        UDialog_AParkPartnerDateFilter(QDate dt, QString title="", QString dateFormat="dd.MM.yyyy", QWidget *parent = 0);
		
		int month();
		int year();
		QDate date();
		int partnerId();
		
		~UDialog_AParkPartnerDateFilter();
    public slots:

    private:
		Ui::UDialog_AParkPartnerDateFilter ui;
};
//--------------------utech--------------------utech--------------------utech--------------------
#endif
