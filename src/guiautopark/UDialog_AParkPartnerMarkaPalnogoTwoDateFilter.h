//--------------------utech--------------------utech--------------------utech--------------------
//
// Створений програмістами Компанії "Утех" 21.01.2012р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#ifndef UDIALOG_APARKPARTNERMARKAPALNOGOTWODATEFILTER_H
#define UDIALOG_APARKPARTNERMARKAPALNOGOTWODATEFILTER_H

#include <QDialog>
#include <QDate>
#include <QtDebug>

#include "ui_UDialog_AParkPartnerMarkaPalnogoTwoDateFilter.h"
//--------------------utech--------------------utech--------------------utech--------------------
class UDialog_AParkPartnerMarkaPalnogoTwoDateFilter : public QDialog
{
        Q_OBJECT

    public:
        UDialog_AParkPartnerMarkaPalnogoTwoDateFilter(QDate dt, QDate dt1, QString title="", QString dateFormat="dd.MM.yyyy", QWidget *parent = 0);
		
		int month();
		int month1();
		int year();
		int year1();
		QDate date();
		QDate date1();
		int partnerId();
		int markaPalnogoId();
		
		~UDialog_AParkPartnerMarkaPalnogoTwoDateFilter();
    public slots:

    private:
		Ui::UDialog_AParkPartnerMarkaPalnogoTwoDateFilter ui;
};
//--------------------utech--------------------utech--------------------utech--------------------
#endif
