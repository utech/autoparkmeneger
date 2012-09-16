#include <QApplication>
#include <QSplashScreen>
#include <QTextStream>
#include <QFile>
#include <QMessageBox>

#include "UAutoParkMeneger_APark.h"
#include "UDialogRegisterUser_APark.h"
#include <UDebugForm>

#include "UMainWindow_AParkPerevez.h"
#include "UPeopleSalaryMainWindow.h"
#include "USalaryDbUpdaterFunctions.h"
#include "UMainWindow_gurt_sklad.h"

#include <iostream>

//--------------------utech--------------------utech--------------------utech--------------------
int main(int argc, char *argv[])
{
	//Реагування на наявність аргументів запуску
	if (argc > 1)
		if ( !strcmp(argv[1],"-v\0") ){
			std::cout << UAutoPark::version();
			return 0;
		}
	
	QApplication app(argc, argv);
	QDir::setCurrent(QCoreApplication::applicationDirPath());
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName(U_PROG_CHAR_CODING));
	
	QPixmap pm(":/Splash/big/splash_256x256.png");
	QSplashScreen *splash = new QSplashScreen();
	QRect pRect = pm.rect();
	QDesktopWidget *dWinget = new QDesktopWidget();
	QRect scrRect = dWinget->screenGeometry();
	delete dWinget;
	QPixmap grPm = QPixmap::grabWindow(0, qRound((scrRect.width()-pRect.width())/2.0), qRound((scrRect.height()-pRect.height())/2.0), pRect.width(), pRect.height());
	
	
	QImage resImage(pRect.width(),pRect.height(), QImage::Format_ARGB32_Premultiplied);
	QPainter painter(&resImage);
	painter.drawPixmap(pRect, grPm, pRect);
	painter.drawPixmap(pRect, pm, pRect);
	painter.save();
	splash->setPixmap(QPixmap::fromImage(resImage));
    splash->show();
	splash->showMessage("");
	
	UDebug::createDebugForm();
	if (connectToDB()){
		UDialogRegisterUser *registerDialog = new UDialogRegisterUser();
		if (registerDialog->exec() == QDialog::Rejected)
			return 0;
		QMainWindow * mainWin = NULL;
		if (registerDialog->registeredUserProgram() == UAutoPark::ProgramPerevez){
			mainWin = new UMainWindow_AParkPerevez();
			mainWin->showMaximized();
		}
		else if (registerDialog->registeredUserProgram() == UAutoPark::ProgramZarplata){
			USalaryDbUpdater *upd = new USalaryDbUpdater();
			if (!upd->checkVersions())
				return 0;
			delete upd;
			mainWin = new UPeopleSalaryMainWindow();
			mainWin->show();
		}
		else if (registerDialog->registeredUserProgram() == UAutoPark::ProgramSklad){
			mainWin = new UMainWindow_gurt_sklad();
			mainWin->show();
		}
		
		splash->finish(mainWin);
		delete splash;
		
		QApplication::connect(mainWin, SIGNAL(requestDebugWindow()), UDebug::debugFormPointer, SLOT(showDebug()));
		QApplication::connect(mainWin, SIGNAL(mainWindowClosed()), UDebug::debugFormPointer, SLOT(close()));
		QApplication::connect(mainWin, SIGNAL(closeLoginSignal()), UDebug::debugFormPointer, SLOT(close()));
		
		//QApplication::setQuitOnLastWindowClosed(false);
		
		return app.exec();
	}
	else 
		delete splash;
	return 1;
}
//--------------------utech--------------------utech--------------------utech--------------------
