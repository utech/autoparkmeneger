//--------------------utech--------------------utech--------------------utech--------------------
//
// ���� ��������� ����� ���� ������������ ��������
//
// ��������� ������������ ������ "����" 29.03.2009�.
// � ���� ���������������� ���������� �������� QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#include "UMainWindow_AParkPerevez.h"

#include "UDialogFirmInfo.h"

//--------------------utech--------------------utech--------------------utech--------------------
void UMainWindow_AParkPerevez::action_debugMessages_activated()
{
	emit requestDebugWindow();
}
//--------------------utech--------------------utech--------------------utech--------------------
void UMainWindow_AParkPerevez::action_close_activated()
{
	close();
}
//--------------------utech--------------------utech--------------------utech--------------------
void UMainWindow_AParkPerevez::action_firmInfo_activated()
{
	UDialogFirmInfo * firmInfo = new UDialogFirmInfo();
	firmInfo->exec();
	delete firmInfo;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UMainWindow_AParkPerevez::action_aboutProgram_activated()
{
	QMessageBox::about(this,"��� \"�������� ��������\"",
						"<center>�������� \"�������� ��������\" ���������� ��� ����� ������������ �������� ��� <br><br>"
						"����� "+QString(UAutoPark::version())+"</center>");
}
//--------------------utech--------------------utech--------------------utech--------------------
