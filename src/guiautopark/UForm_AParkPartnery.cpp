//--------------------utech--------------------utech--------------------utech--------------------
//
// ���� ��������� ����� ���� ������������ ��������
//
// ��������� ������������ ������ "����" 29.03.2009�.
// � ���� ���������������� ���������� �������� QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------
#include "UForm_AParkPartnery.h"

#include "UDifFunc_APark.h"
#include <UStandardDelegate>

#include <QtDebug>
//--------------------utech--------------------utech--------------------utech--------------------
UForm_AParkPartnery::UForm_AParkPartnery(int tWType, QWidget *parent)
        : UAParkTabWidget(tWType, parent)
{
	ui.setupUi(this);
	
	ui.tableWidget_partnery->setColumnCount(5);
	twExt = new UDataFormView(ui.tableWidget_partnery, "dovPartners");
	twExt->setSortingEnabled(true);
	
	ui.tableWidget_partnery->setHorizontalHeaderLabels( QStringList() 
															<< "id"
															<< "�����"
															<< "������"
															<< "������"
															<< "���.");
	
	twExt->colNamesList << "Id"
						<< "Name"
						<< "EDRPOU"
						<< "Adresa"
						<< "Tel";
	
	twExt->addColAlignment("Id", Qt::AlignVCenter | Qt::AlignRight);
	twExt->addColAlignment("Name", Qt::AlignVCenter | Qt::AlignLeft);
	twExt->addColAlignment("EDRPOU", Qt::AlignVCenter | Qt::AlignLeft);
	twExt->addColAlignment("Adresa", Qt::AlignVCenter | Qt::AlignLeft);
	twExt->addColAlignment("Tel", Qt::AlignVCenter | Qt::AlignLeft);
	
	twExt->setColumnHidden(0);
	twExt->setColumnWidth("Id", 40);
	twExt->setColumnWidth("Name", 250);
	twExt->setColumnWidth("EDRPOU", 80);
	twExt->setColumnWidth("Adresa", 200);
	twExt->setColumnWidth("Tel", 100);
	
	twExt->populateTable();
	
	connect(ui.pushButton_reload, SIGNAL(clicked()), twExt,SLOT(populateTable()));
	connect(ui.pushButton_create, SIGNAL(clicked()), this, SLOT(pushButton_create_clicked()));
	connect(ui.pushButton_delete, SIGNAL(clicked()), this, SLOT(pushButton_delete_clicked()));
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkPartnery::populateToolBar(QToolBar * tBar)
{
	
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkPartnery::pushButton_create_clicked()
{
	if (!twExt->addRow("INSERT INTO dovPartners (IsPostach) VALUES (1)"))
		QMessageBox::critical(0,"������� ��������� ������","����� �������� �� ��������");
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkPartnery::pushButton_delete_clicked()
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
UForm_AParkPartnery::~UForm_AParkPartnery()
{
	
}
//--------------------utech--------------------utech--------------------utech--------------------
