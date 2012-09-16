//--------------------utech--------------------utech--------------------utech--------------------
//
// Створений програмістами Компанії "Утех" 19.02.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#include <QCleanlooksStyle>
#include <QDesktopServices>

#include "UProgUpdaterApi.h"

//--------------------utech--------------------utech--------------------utech--------------------
void correctExit(bool exitProg)
{
	QDir::setCurrent(QCoreApplication::applicationDirPath());
        QProcess::startDetached(PROGRAM_NAME);
	if (exitProg)
		exit(0);
}
//--------------------utech--------------------utech--------------------utech--------------------
QString readCurInstalledProgVersion()
{
	QProcess aParkPro;
	aParkPro.start(PROGRAM_NAME+QString(" -v"));
	aParkPro.waitForFinished(5000);
	
	QString ver = aParkPro.readAll().trimmed();
#ifdef U_DEVELOP
	qDebug() << "curVersion: " << ver;
#endif
	if (ver.size() < 3)
		ver = "0.0.0";
	
	return ver;
}
//--------------------utech--------------------utech--------------------utech--------------------
ULoadVerInfo::ULoadVerInfo(QObject *parent) : QObject(parent)
{
	QUrl url(VERSION_FILE_URL);
	url.setUserName(SERVER_USER_NAME);
	url.setPassword(SERVER_PASSWORD);
	
	request.setUrl(url);
	request.setRawHeader("ua-buh", "uProgUpdater 0.1");
	
	timeDelay = 2000;
	
	accessMeneger = new QNetworkAccessManager(this);
	connect(accessMeneger, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyFinished(QNetworkReply*)));
}
//--------------------utech--------------------utech--------------------utech--------------------
void ULoadVerInfo::loadVersion()
{
#ifdef U_DEVELOP
	qDebug() << "bool ULoadVerInfo::loadVersion() loaded.";
#endif
	netReply = accessMeneger->get(request);
	connect(netReply, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
	connect(netReply, SIGNAL(error(QNetworkReply::NetworkError)),this, SLOT(slotError(QNetworkReply::NetworkError)));
	
	netRequestDone = false;
	
	timer = new QTimer(this);
	timer->setSingleShot(true);
	connect(timer, SIGNAL(timeout()), this, SLOT(slotTimeOut()));
	timer->start(timeDelay);
}
//--------------------utech--------------------utech--------------------utech--------------------
QString ULoadVerInfo::newVersion()
{
	return _newVersion;
}
//--------------------utech--------------------utech--------------------utech--------------------
QString ULoadVerInfo::urlToDownload()
{
	return _downloadUrl;
}
//--------------------utech--------------------utech--------------------utech--------------------
void ULoadVerInfo::replyFinished(QNetworkReply* netReply)
{
#ifdef U_DEVELOP
	qDebug() << "slot void replyFinished(QNetworkReply* netReply) loaded.";
#endif
	timer->stop();
	delete timer;
	
	netRequestDone = true;
	QTextStream stream(netReply);
	downloadedFile = stream.readAll();
	_newVersion = downloadedFile.section("<br>",1,1).trimmed();
	_downloadUrl = downloadedFile.section("<br>",2,2).trimmed();
#ifdef U_DEVELOP	
	qDebug() << "downloadedFile:" << downloadedFile;
	qDebug() << "_newVersion:" << _newVersion;
	qDebug() << "_downloadUrl:" << _downloadUrl;
#endif
	QString installedVersion = readCurInstalledProgVersion();
	if ((installedVersion.size() < 3) || (_newVersion.size() < 3)){
		correctExit();
		return;
	}
	
	if (_newVersion == installedVersion){
		correctExit();
		return;
	}
	
	QApplication::setStyle( new QCleanlooksStyle() );
	UProgUpdaterDialog * d = new UProgUpdaterDialog(installedVersion, _newVersion, _downloadUrl);
	int dRes = d->exec();
	delete d;
	if (dRes == QDialog::Rejected){
#ifdef U_DEVELOP
		qDebug() << "dialogRejected()";
#endif
		correctExit();
		return;
	}

#ifdef U_DEVELOP
       qDebug() << "dialogAccepted()";
#endif

#ifdef Q_OS_WIN32
	QString updaterFileName = QString(QDir::tempPath())+"\\"+UPDATION_LOCAL_FILE_NAME+_newVersion+".exe";
 #ifdef U_DEVELOP
	qDebug() << "updaterLoadingPath: " << updaterFileName;
 #endif
	QDir installDir(QApplication::applicationDirPath());
	installDir.cdUp();
	QProcess::startDetached(updaterFileName+" /S /D="+installDir.absolutePath().replace("/","\\"));
	//QFile::remove(updaterFileName);
	exit(0);
	//correctExit();
#endif

#ifdef Q_OS_LINUX
        QFileInfo fInfo(_downloadUrl);
        QString updaterFileName = fInfo.fileName();
        QDir::setCurrent(QCoreApplication::applicationDirPath()+"/..");
 #ifdef U_DEVELOP
        qDebug() << "updaterLoadingPath: " << updaterFileName;
        qDebug() << "command: " << "tar --overwrite -xvjf "+updaterFileName;
 #endif
        QProcess::execute("chmod 755 "+updaterFileName);
        QProcess::execute("./"+updaterFileName+" -y");

        //Запуск конфігураційного скрипта
        QDir::setCurrent(QCoreApplication::applicationDirPath());
        QProcess::execute("../install/linux/config.sh");
        QDir::setCurrent(QCoreApplication::applicationDirPath());
        QProcess::execute("rm -f ../"+updaterFileName);
        correctExit();
#endif
}
//--------------------utech--------------------utech--------------------utech--------------------
void ULoadVerInfo::slotReadyRead()
{
#ifdef U_DEVELOP
        //qDebug() << "slot void ULoadVerInfo::slotReadyRead() loaded.";
#endif
}
//--------------------utech--------------------utech--------------------utech--------------------
void ULoadVerInfo::slotError(QNetworkReply::NetworkError er)
{
#ifdef U_DEVELOP
	qDebug() << "slot void ULoadVerInfo::slotError(QNetworkReply::NetworkError er) loaded.";
	qDebug() << " - errorCode: " << er;
#endif
	correctExit();
}
//--------------------utech--------------------utech--------------------utech--------------------
void ULoadVerInfo::slotTimeOut()
{
#ifdef U_DEVELOP
	qDebug() << "slot void ULoadVerInfo::slotTimeOut() loaded.";
#endif
	timer->stop();
	delete timer;
	correctExit();
}
//--------------------utech--------------------utech--------------------utech--------------------
ULoadVerInfo::~ULoadVerInfo()
{
	
}
//--------------------utech--------------------utech--------------------utech--------------------
UMainProgObj::UMainProgObj(QObject * parent) : QObject(parent)
{
#ifdef U_DEVELOP
	qDebug() << "UMainProgObj::UMainProgObj(QObject * parent) loaded.";
#endif
	loadVer = new ULoadVerInfo(parent);
	loadVer->loadVersion();
}
//--------------------utech--------------------utech--------------------utech--------------------
UMainProgObj::~UMainProgObj()
{
	delete loadVer;
}
//--------------------utech--------------------utech--------------------utech--------------------
