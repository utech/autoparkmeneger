//--------------------utech--------------------utech--------------------utech--------------------
//
// ���� ��������� ����� ���� ������������ ��������
//
// ��������� ������������ ������ "����" 29.03.2009�.
// � ���� ���������������� ���������� �������� QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------
#include "UForm_AParkCloseMonthes.h"

#include "UDifFunc_APark.h"
#include <UStandardDelegate>

#include <QtDebug>
//--------------------utech--------------------utech--------------------utech--------------------
UForm_AParkCloseMonthes::UForm_AParkCloseMonthes(int tWType, QWidget *parent)
        : UAParkTabWidget(tWType, parent)
{
	ui.setupUi(this);
	
	twExt = new UDataFormView(ui.tableWidget, "monthPeriods");
	twExt->setSortingEnabled(true);
	
	twExt->colNamesList << "Id"
						<< "CDate"
						<< "Closed";
	
	twExt->addColAlignment("CDate", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("Closed",Qt::AlignVCenter | Qt::AlignRight);
	
	twExt->setColumnHidden(0);
	twExt->setColumnWidth("CDate", 100);
	twExt->setColumnWidth("Closed", 100);
	twExt->setSqlOrderBy("CDate");
	
	twExt->setItemDelegateForColumn(1, new UDateTimeDelegate(ui.tableWidget,"MM.yyyy"));
	twExt->setItemDelegateForColumn(2, new UCheckBoxDelegate(twExt, "��������", "-"));
	
	twExt->populateTable();
	
	connect(ui.pushButton_reload, SIGNAL(clicked()), twExt,SLOT(populateTable()));
	connect(ui.pushButton_create, SIGNAL(clicked()), this, SLOT(pushButton_create_clicked()));
	connect(ui.pushButton_delete, SIGNAL(clicked()), this, SLOT(pushButton_delete_clicked()));
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkCloseMonthes::populateToolBar(QToolBar * tBar)
{
	
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkCloseMonthes::pushButton_create_clicked()
{
	if (!twExt->addRow())
		QMessageBox::critical(0,"������� ��������� ������","����� �� ��������");
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkCloseMonthes::pushButton_delete_clicked()
{
	if	( QMessageBox::question(
                this,
                "!!! ��������� ������ !!!",
                "�� ����� ������ �������� ������?",
                "���",
				"ͳ-�-�",
                QString(), 0, 1)
		)
		return;
	if (!twExt->deleteRow())
		QMessageBox::critical(0,"������� ��������� ������","����� �� ��������");
}
//--------------------utech--------------------utech--------------------utech--------------------
UForm_AParkCloseMonthes::~UForm_AParkCloseMonthes()
{
	
}
//--------------------utech--------------------utech--------------------utech--------------------
