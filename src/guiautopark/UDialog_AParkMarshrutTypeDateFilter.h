//--------------------utech--------------------utech--------------------utech--------------------
//
// Створений програмістами Компанії "Утех" 23.04.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#ifndef UDIALOG_APARKMARSHRUTTYPEDATEFILTER_H
#define UDIALOG_APARKMARSHRUTTYPEDATEFILTER_H

#include <QDialog>
#include <QDate>
#include <QtDebug>

#include "ui_UDialog_AParkMarshrutTypeDateFilter.h"
//--------------------utech--------------------utech--------------------utech--------------------
class UDialog_AParkMarshrutTypeDateFilter : public QDialog
{
        Q_OBJECT

    public:
        UDialog_AParkMarshrutTypeDateFilter(QDate dt, QString title="", QString dateFormat="dd.MM.yyyy", QWidget *parent = 0);
		
		int month();
		int year();
		QDate date();
		int marshrutType();
		
		~UDialog_AParkMarshrutTypeDateFilter();
    public slots:

    private:
		Ui::UDialog_AParkMarshrutTypeDateFilter ui;
};
//--------------------utech--------------------utech--------------------utech--------------------
#endif
