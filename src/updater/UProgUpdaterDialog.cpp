//--------------------utech--------------------utech--------------------utech--------------------
//
// Створений програмістами Компанії "Утех" 19.02.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#include "UProgUpdaterDialog.h"

#include <QFileInfo>

//--------------------utech--------------------utech--------------------utech--------------------
UProgUpdaterDialog::UProgUpdaterDialog(QString curVer, QString newVer, QString urlToDownload)
{
	ui.setupUi(this);
	
	setMinimumSize(size());
	setMaximumSize(size());
	
	QUrl url(urlToDownload);
	url.setUserName(SERVER_USER_NAME);
	url.setPassword(SERVER_PASSWORD);
	
	request.setUrl(url);
	request.setRawHeader("ua-buh", "uProgUpdater 0.1");
	
	fileUrl = urlToDownload;
	installedProgVer = curVer;
	newProgVer = newVer;
	
	lastUpdFileSize = 1;
	
	accessMeneger = new QNetworkAccessManager(this);
	//connect(accessMeneger, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyFinished(QNetworkReply*)));
	
	netReply = NULL;
	updFileSave = new QFile(this);
	
	ui.labelCurVersion->setText("Поточна версія програми:    "+curVer);
	ui.labelNewVersion->setText("Необхідна версія програми:  "+newVer);
	ui.labelCurOperationInfo->setText("!!! Натисність \"Поновити\", щоб закачати необхідну версію Prog");
	
	ui.progressBar->setValue(0);
	
        //QDir dir(QCoreApplication::applicationDirPath());
	
	connect(ui.toolButtonUpdate, SIGNAL(clicked()), this, SLOT(startUpdate()));
	connect(ui.toolButtonCancel, SIGNAL(clicked()), this, SLOT(cancelUpdate()));
	
        startUpdate();
}
//--------------------utech--------------------utech--------------------utech--------------------
void UProgUpdaterDialog::startUpdate()
{
	ui.labelCurOperationInfo->setText("!!! Закачування програми");
	
#ifdef Q_OS_WIN32
        QDir::setCurrent(QDir::tempPath());
	updFileSave->setFileName(UPDATION_LOCAL_FILE_NAME+newProgVer+".exe");
#endif
#ifdef Q_OS_LINUX
        QDir::setCurrent(QCoreApplication::applicationDirPath()+"/..");
        QFileInfo fInfo(fileUrl);
        updFileSave->setFileName(fInfo.fileName());
#endif
	updFileSave->close();
	updFileSave->open(QFile::WriteOnly);
	
	downloadOk = false;
	
	netReply = accessMeneger->get(request);
	
	connect(netReply, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
	connect(netReply, SIGNAL(error(QNetworkReply::NetworkError)),this, SLOT(slotError(QNetworkReply::NetworkError)));
	connect(netReply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(showProgress(qint64,qint64)));
	connect(netReply, SIGNAL(finished()), this, SLOT(replyFinished()));
	
	ui.toolButtonUpdate->setEnabled(false);
}
//--------------------utech--------------------utech--------------------utech--------------------
void UProgUpdaterDialog::replyFinished()
{
#ifdef U_DEVELOP
	qDebug() << "slot void UProgUpdaterDialog::replyFinished() loaded.";
#endif
	updFileSave->write( netReply->readAll() );
	
	if (downloadOk && (netReply->error()==0)) //Успішне завантаження
		accept();
	else{ //Помилка завантаження
		ui.toolButtonUpdate->setEnabled(true);
		showProgress(0,lastUpdFileSize);
		QMessageBox::critical(0, "Помилка завантаження", "Спроба закачування програми поновлення Prog пройшла невдало.\n"
							"Спробуйте ще раз, натиснувши кнопку \"Поновити (автоматично)\","
							"або скористайтеся ручним поновленням клакнувши на \"самостійно скачати поновлення...\"");
	}
}
//--------------------utech--------------------utech--------------------utech--------------------
void UProgUpdaterDialog::slotReadyRead()
{
#ifdef U_DEVELOP
	qDebug() << "slot void ULoadVerInfo::slotReadyRead() loaded.";
#endif
	updFileSave->write( netReply->readAll() );
}
//--------------------utech--------------------utech--------------------utech--------------------
void UProgUpdaterDialog::slotError(QNetworkReply::NetworkError er)
{
#ifdef U_DEVELOP
	qDebug() << "slot void ULoadVerInfo::slotError(QNetworkReply::NetworkError er) loaded.";
	qDebug() << " - errorCode: " << er;
#endif
	ui.toolButtonUpdate->setEnabled(true);
}
//--------------------utech--------------------utech--------------------utech--------------------
void UProgUpdaterDialog::cancelUpdate()
{
#ifdef U_DEVELOP
	qDebug() << "slot void UProgUpdaterDialog::cancelUpdate() loaded.";
#endif
	if (netReply){
		netReply->abort();
		updFileSave-close();
	}
	reject();
}
//--------------------utech--------------------utech--------------------utech--------------------
void UProgUpdaterDialog::showProgress(qint64 done,qint64 total)
{
	lastUpdFileSize = total;
	
	if (done==total)
		downloadOk = true;
	
	ui.progressBar->setRange(0,total);
	ui.progressBar->setValue(done);
	
	ui.labelProgressInfo->setText("Скачано: "+QString::number(done)+".  Всього: " + QString::number(total)+"." );
}
//--------------------utech--------------------utech--------------------utech--------------------
void UProgUpdaterDialog::setUpdateFileName(QString fName)
{
	fileUrl = fName;
}
//--------------------utech--------------------utech--------------------utech--------------------
UProgUpdaterDialog::~UProgUpdaterDialog()
{
	delete updFileSave;
}
//--------------------utech--------------------utech--------------------utech--------------------
