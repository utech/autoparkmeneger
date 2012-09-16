//--------------------utech--------------------utech--------------------utech--------------------
//
// Створений програмістами Компанії "Утех" 23.04.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#include "UDialog_AParkChooseNumber.h"

//--------------------utech--------------------utech--------------------utech--------------------
UDialog_AParkChooseNumber::UDialog_AParkChooseNumber(int minVal, int maxVal, int curVal, QString title, QWidget *parent)
        : QDialog(parent)
{
    ui.setupUi(this);
	
	setWindowTitle(title);
	ui.spinBox->setMinimum(minVal);
	ui.spinBox->setMaximum(maxVal);
	ui.spinBox->setValue(curVal);
}
//--------------------utech--------------------utech--------------------utech--------------------
int UDialog_AParkChooseNumber::currentValue()
{
	return ui.spinBox->value();
}
//--------------------utech--------------------utech--------------------utech--------------------
UDialog_AParkChooseNumber::~UDialog_AParkChooseNumber()
{

}
//--------------------utech--------------------utech--------------------utech--------------------
