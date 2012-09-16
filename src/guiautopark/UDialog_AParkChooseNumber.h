//--------------------utech--------------------utech--------------------utech--------------------
//
// Створений програмістами Компанії "Утех" 23.04.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#ifndef UDialog_AParkChooseNumber_H
#define UDialog_AParkChooseNumber_H

#include <QDialog>
#include <QDate>
#include <QtDebug>

#include "ui_UDialog_AParkChooseNumber.h"
//--------------------utech--------------------utech--------------------utech--------------------
class UDialog_AParkChooseNumber : public QDialog
{
        Q_OBJECT

    public:
        UDialog_AParkChooseNumber(int minVal, int maxVal, int curVal, QString title="", QWidget *parent = 0);
		
		int currentValue();
		~UDialog_AParkChooseNumber();
    public slots:

    private:
		Ui::UDialog_AParkChooseNumber ui;
};
//--------------------utech--------------------utech--------------------utech--------------------
#endif
