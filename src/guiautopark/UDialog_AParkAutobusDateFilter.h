//--------------------utech--------------------utech--------------------utech--------------------
//
// Створений програмістами Компанії "Утех" 23.04.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#ifndef UDialog_AParkAutobusDateFilter_H
#define UDialog_AParkAutobusDateFilter_H

#include <QDialog>
#include <QDate>
#include <QtDebug>

#include "ui_UDialog_AParkAutobusDateFilter.h"
//--------------------utech--------------------utech--------------------utech--------------------
class UDialog_AParkAutobusDateFilter : public QDialog
{
        Q_OBJECT

    public:
        UDialog_AParkAutobusDateFilter(short year=0, short month=0, QString title="", QWidget *parent = 0);
		
		int month();
		int year();
		int garajNumber();
		
		~UDialog_AParkAutobusDateFilter();
    public slots:


    private:
		Ui::UDialog_AParkAutobusDateFilter ui;
		
		QDate date;
};
//--------------------utech--------------------utech--------------------utech--------------------
#endif
