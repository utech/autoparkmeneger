//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл виконання класу вікна налаштування програми
//
// Створений програмістами Компанії "Утех" 29.03.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
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
	QMessageBox::about(this,"Про \"Автопарк менеджер\"",
						"<center>Програма \"Автопарк менеджер\" призначена для обліку господарської діяльності АТП <br><br>"
						"Версія "+QString(UAutoPark::version())+"</center>");
}
//--------------------utech--------------------utech--------------------utech--------------------
