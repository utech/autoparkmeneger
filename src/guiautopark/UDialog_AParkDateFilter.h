//--------------------utech--------------------utech--------------------utech--------------------
//
// Створений програмістами Компанії "Утех" 23.04.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#ifndef UDialog_AParkDateFilter_H
#define UDialog_AParkDateFilter_H

#include <QDialog>
#include <QDate>
#include <QtDebug>

#include "ui_UDialog_AParkDateFilter.h"
//--------------------utech--------------------utech--------------------utech--------------------
class UDialog_AParkDateFilter : public QDialog
{
        Q_OBJECT

    public:
        UDialog_AParkDateFilter(short year=0, short month=0, QString title="", QWidget *parent = 0);
		UDialog_AParkDateFilter(QDate dDate, QString title="", QString editDisplayFormat = "dd.MM.yyyy" , QWidget *parent = 0);
		
		int month();
		int year();
		QDate date();
		~UDialog_AParkDateFilter();
    public slots:

    private:
		Ui::UDialog_AParkDateFilter ui;
};
//--------------------utech--------------------utech--------------------utech--------------------
#endif
