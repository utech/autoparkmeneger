//--------------------utech--------------------utech--------------------utech--------------------
//
// Створений програмістами Компанії "Утех" 21.01.2012р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#ifndef UDIALOG_APARKPARTNERMARKAPALNOGODATEFILTER_H
#define UDIALOG_APARKPARTNERMARKAPALNOGODATEFILTER_H

#include <QDialog>
#include <QDate>
#include <QtDebug>

#include "ui_UDialog_AParkPartnerMarkaPalnogoDateFilter.h"
//--------------------utech--------------------utech--------------------utech--------------------
class UDialog_AParkPartnerMarkaPalnogoDateFilter : public QDialog
{
        Q_OBJECT

    public:
        UDialog_AParkPartnerMarkaPalnogoDateFilter(QDate dt, QString title="", QString dateFormat="dd.MM.yyyy", QWidget *parent = 0);
		
		int month();
		int year();
		QDate date();
		int partnerId();
		int markaPalnogoId();
		
		~UDialog_AParkPartnerMarkaPalnogoDateFilter();
    public slots:

    private:
		Ui::UDialog_AParkPartnerMarkaPalnogoDateFilter ui;
};
//--------------------utech--------------------utech--------------------utech--------------------
#endif
