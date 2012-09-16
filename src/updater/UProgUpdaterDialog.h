//--------------------utech--------------------utech--------------------utech--------------------
//
// Створений програмістами Компанії "Утех" 19.02.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#ifndef UProgUPDATERFORM_H
#define UProgUPDATERFORM_H

#include <QDialog>
#include <QtNetwork>
#include <QDir>
#include <QMessageBox>

#include "UProgUpdaterApi.h"
#include "ui_UProgUpdaterDialog.h"

//--------------------utech--------------------utech--------------------utech--------------------
class UProgUpdaterDialog : public QDialog
{
    Q_OBJECT
	
	public:
        UProgUpdaterDialog(QString curVer="", QString newVer="", QString urlToDownload="");
		~UProgUpdaterDialog();
		
		void setUpdateFileName(QString fName);
    public slots:
		void startUpdate();
		void cancelUpdate();
		void replyFinished();
		void slotReadyRead();
		void slotError(QNetworkReply::NetworkError er);
		void showProgress(qint64 done,qint64 total);
    private:
		Ui::UProgUpdaterDialog ui;
		QString fileUrl;
		QString installedProgVer;
		QString newProgVer;
		QFile *updFileSave;
		
		QNetworkAccessManager * accessMeneger;
		QNetworkReply * netReply;
		QNetworkRequest request;
		int lastUpdFileSize;
		
		bool downloadOk;
};
//--------------------utech--------------------utech--------------------utech--------------------
#endif
