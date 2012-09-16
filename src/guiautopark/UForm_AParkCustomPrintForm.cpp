//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл виконання класу вікна налаштування програми
//
// Створений програмістами Компанії "Утех" 24.06.2011р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------
#include "UForm_AParkCustomPrintForm.h"

#include "UDifFunc_APark.h"
#include <UStandardDelegate>

#include <QtDebug>

#define FIRST_PALNE_COLUMN 1
//--------------------utech--------------------utech--------------------utech--------------------
UForm_AParkCustomPrintForm::UForm_AParkCustomPrintForm(QWidget *parent, QString title, bool fullPage)
        : UPrintForm(parent, title, fullPage)
{
	pushButtonFirstPage = new QPushButton("Перша сторінка",this);
	pushButtonSecondPage = new QPushButton("Друга сторінка",this);
	
	QIcon icon;
    icon.addFile(QString::fromUtf8(":/function_icon_set/function_icon_set/printer_48.png"), QSize(), QIcon::Normal, QIcon::Off);
    pushButtonFirstPage->setIcon(icon);
    pushButtonFirstPage->setIconSize(QSize(16, 16));
	
	pushButtonSecondPage->setIcon(icon);
    pushButtonSecondPage->setIconSize(QSize(16, 16));
	
	ui.hboxLayout->addWidget(pushButtonFirstPage);
	ui.hboxLayout->addWidget(pushButtonSecondPage);
	
	connect(pushButtonFirstPage, SIGNAL(clicked()), this,SLOT(pushButtonFirstPage_clicked()));
	connect(pushButtonSecondPage, SIGNAL(clicked()), this,SLOT(pushButtonSecondPage_clicked()));
}
//--------------------utech--------------------utech--------------------utech--------------------
UForm_AParkCustomPrintForm::~UForm_AParkCustomPrintForm()
{

}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkCustomPrintForm::pushButtonFirstPage_clicked()
{
	int prevFrom = prnt->fromPage();
	int prevTo = prnt->toPage();
	prnt->setFromTo(1, 1);
	doc = ui.textEdit->document();
	doc->print(prnt);
	prnt->setFromTo(prevFrom, prevTo);
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkCustomPrintForm::pushButtonSecondPage_clicked()
{
	int prevFrom = prnt->fromPage();
	int prevTo = prnt->toPage();
	prnt->setFromTo(2, 2);
	doc = ui.textEdit->document();
	doc->print(prnt);
	prnt->setFromTo(prevFrom, prevTo);
}
//--------------------utech--------------------utech--------------------utech--------------------
