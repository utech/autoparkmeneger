#include <QApplication>
#include <QDir>
#include <QTextCodec>
#include <QSettings>
#include <QSplashScreen>
#include <QPixmap>
#include <QDesktopWidget>
#include <QPainter>

#include <QtDebug>

#include "UProgUpdaterDialog.h"
#include "UProgUpdaterApi.h"

void correctExit();
QString readCurInstalledProgVersion();
//--------------------utech--------------------utech--------------------utech--------------------
int main(int argc, char **argv)
{
	QApplication app(argc,argv);
	
	QDir::setCurrent(QCoreApplication::applicationDirPath());
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("cp1251"));
	QApplication::setQuitOnLastWindowClosed(false);
	
	QPixmap pm(":/Splash/big/splash_256x256.png");
	QSplashScreen splash;
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
	splash.setPixmap(QPixmap::fromImage(resImage));
    splash.show();
	splash.showMessage("");
	
	UMainProgObj mainObj(&app);
	return app.exec();
}
//--------------------utech--------------------utech--------------------utech--------------------
