//--------------------utech--------------------utech--------------------utech--------------------
//
// ���� ��������� ����� ���� ������������ ��������
//
// ��������� ������������ ������ "����" 29.03.2009�.
// � ���� ���������������� ���������� �������� QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------
#include "UForm_AParkHelpWidget.h"

#include "UDifFunc_APark.h"
#include <UStandardDelegate>

#include <QtDebug>
//--------------------utech--------------------utech--------------------utech--------------------
UForm_AParkHelpWidget::UForm_AParkHelpWidget(int tWType, QWidget *parent)
        : UAParkTabWidget(tWType, parent)
{
	ui.setupUi(this);
}
//--------------------utech--------------------utech--------------------utech--------------------
void UForm_AParkHelpWidget::populateToolBar(QToolBar * tBar)
{
	
}
//--------------------utech--------------------utech--------------------utech--------------------
UForm_AParkHelpWidget::~UForm_AParkHelpWidget()
{
	
}
//--------------------utech--------------------utech--------------------utech--------------------
