//--------------------utech--------------------utech--------------------utech--------------------
//
// Створений програмістами Компанії "Утех" 23.04.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#ifndef UPRINTDOCS_APARK_H
#define UPRINTDOCS_APARK_H

#include <QString>
#include <QVariant>
#include <QTextLength>
#include <QTextTable>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDate>
#include <QTextTableCell>
#include <QTextCursor>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QTextDocumentFragment>
#include <QTextFrameFormat>
#include <UPrintForm.h>

#include <math.h>
//--------------------utech--------------------utech--------------------utech--------------------

//--------------------utech--------------------utech--------------------utech--------------------
class UPrintDocs_APark
{
    public:
        UPrintDocs_APark();
		~UPrintDocs_APark();
		
		QImage verticalTextToImage(const QString & text, QTextCharFormat & textCharFormat);
		
		void print_lystkyRegulyarnostiRuhu(QList<int> idList);
		void print_lystkyPustogrRegulyarnostiRuhu();
		void print_backSideLystkaRegulyarnostiRuhu(unsigned char numberCopys);
		void print_misyachnyiProbigUsihAvtobusiv(short year, short month);
		void print_misyachnyiProbigOdnogoAvtobusa(short year, short month, int autoGarajNumber);
		void print_perelikAvtobusivNaTO(short TONumber = 0);
		void print_vidomistVykonannyaPlanuVDen(QDate vDate);
		void print_zvedenaVidomistPoDorojnihLystahZaMisyac(QDate vDate, short marshrutType=0);
		void print_zvedenaVidomistPoTupahMarshrutivZaMisyac(QDate vDate, short marshrutType=0);
		void print_zvitProZdanuVyruchkuGotivkoyuZaMisyac(QDate vDate);
		void print_KartkyOblikuVykonPlanu(QDate vDate, QList<int> vodiyiList);
		void print_KartkyRobotyVodiyiv(QDate vDate, QList<int> vodiyiList);
		void print_RozrahSumyKompensPoPilgah(int pilgId);
		// If pidrozdilId is empty (= -1), tabel will be created for drivers only
		void print_monthTabel(short year, short month, int pidrozdilId = -1);
		void print_zvitProPerevezPilgPasajyriv(QDate vDate);
		void print_planyValovyhDohodiv(QDate vDate);
		void print_VidomistMarshrutivVDen(QDate vDate);
		void print_zvitVykorystannyaKoshtivPalne(int zvitId);
		void print_reyestrChekivGazZaMisyac(QDate vDate, int partnerId);
		void print_reyestrChekivGazZaMisyacDaily(QDate vDate, int partnerId);
		void print_reyestrChekivPalneZaMisyac(QDate vDate);
                void print_reyestrChekivVidPostachalnyksPalneZaMisyac(int partnerId, QDate vDate);
		void print_vidomistZakupivliPalnogoPoVodiyahZaMisyac(QDate vDate, int markaPalnogoId);
		void print_vidomistZakupivliPalnogoPoVodiyahZaMisyacVRozriziRahunkiv(QDate vDate);
		void print_reyestrChekivVidPostachalnykaPoVyduPalnogo(QDate vDate, int partnerId, int markaPalnogoId);
		
		QTextDocumentFragment create_backSideLystkaRegulyarnostiRuhu();
		QTextDocumentFragment create_lystokRegulyarnostiRuhu(int id);
		QTextDocumentFragment create_kartkuOblikuVykonPlanu(QDate vDate, int vodiyTabNum);
		QTextDocumentFragment create_kartkaRobotyVodiya(QDate vDate, int vodiyTabNum);
		
		int timeToSec(QString time){
			return time.section(':',0,0).toInt()*60 + time.section(':',1,1).toInt();
		};
		int timeToMinute(QTime time){
			return time.hour()*60 + time.minute();
		};
		QString secToTime(int sec){
			if (sec==0)
				return "-";
			return QString::number(int (sec/60))+":"+QString::number(fmod(sec,60)).rightJustified(2,'0');
		};
		QTextDocumentFragment pidpysy(int dockId, QTextCharFormat textCharFormat, QPrinter::Orientation orient = QPrinter::Portrait);
		
		UPrintForm *printform;
    public slots:
		
	signals:
		
    private:
		//QSqlTableModel tableModel;
		QSqlRecord record;
		QDate date;
		QStringList monthlist;
		QSqlQuery *query, *tQuery;
};
//--------------------utech--------------------utech--------------------utech--------------------
#endif
