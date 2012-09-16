//--------------------utech--------------------utech--------------------utech--------------------
//
// Створений програмістами Компанії "Утех" 19.02.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#ifndef UProgUPDATERAPI_H
#define UProgUPDATERAPI_H

#include <QDialog>
#include <QtNetwork>
#include <QDir>
#include <QTimer>
#include <QStyle>

#include "UProgUpdaterDialog.h"

#define SERVER_USER_NAME "atpupdater"
#define SERVER_PASSWORD "yfifrjujhnf"
#ifdef Q_OS_WIN32
    #define VERSION_FILE_URL "http://192.168.1.10/atpupdate/version.php?os=win32"
    #define PROGRAM_NAME "autopark.exe"
#endif
#ifdef Q_OS_LINUX
    #define VERSION_FILE_URL "http://192.168.1.10/atpupdate/version.php?os=linux"
    #define PROGRAM_NAME "./autopark"
#endif

#define UPDATION_LOCAL_FILE_NAME "AParkMeneger_bin_v_"

//--------------------utech--------------------utech--------------------utech--------------------
void correctExit(bool exitProg = true);
void correctExit(bool needImage, QString imgUrl);
QString readCurInstalledProgVersion();
//--------------------utech--------------------utech--------------------utech--------------------
class ULoadVerInfo : public QObject
{
    Q_OBJECT
	
	public:
        ULoadVerInfo(QObject *parent=0);
		~ULoadVerInfo();
		
		void loadVersion();
		QString newVersion();
		QString urlToDownload();
    public slots:
		void replyFinished(QNetworkReply* netReply);
		void slotReadyRead();
		void slotError(QNetworkReply::NetworkError er);
		void slotTimeOut();
    private:
		QNetworkAccessManager * accessMeneger;
		QNetworkReply * netReply;
		QNetworkRequest request;
		QString _newVersion;
		QString _downloadUrl;
		bool netRequestDone;
		int timerLoopCounter;
		int timeDelay;
		QTimer *timer;
		QString downloadedFile;
};
//--------------------utech--------------------utech--------------------utech--------------------
class UMainProgObj : public QObject
{
    Q_OBJECT
	
	public:
        UMainProgObj(QObject *parent=0);
		~UMainProgObj();
    public slots:
		
    private:
		ULoadVerInfo *loadVer;
};
//--------------------utech--------------------utech--------------------utech--------------------
#endif
