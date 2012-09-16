//--------------------utech--------------------utech--------------------utech--------------------
//
// Створений програмістами Компанії "Утех" 26.06.2011р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#ifndef UDIALOG_APARKMARKAPALNOGODATEFILTER_H
#define UDIALOG_APARKMARKAPALNOGODATEFILTER_H

#include <QDialog>
#include <QDate>
#include <QtDebug>

#include "ui_UDialog_AParkMarkaPalnogoDateFilter.h"
//--------------------utech--------------------utech--------------------utech--------------------
class UDialog_AParkMarkaPalnogoDateFilter : public QDialog
{
        Q_OBJECT

    public:
        UDialog_AParkMarkaPalnogoDateFilter(QDate dt, QString title="", QString dateFormat="dd.MM.yyyy", QWidget *parent = 0);
		
		int month();
		int year();
		QDate date();
		int markaPalnogoId();
		
		~UDialog_AParkMarkaPalnogoDateFilter();
    public slots:

    private:
		Ui::UDialog_AParkMarkaPalnogoDateFilter ui;
};
//--------------------utech--------------------utech--------------------utech--------------------
#endif
