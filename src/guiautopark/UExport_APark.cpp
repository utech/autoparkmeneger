//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл виконання класу вікна налаштування програми
//
// Створений програмістами Компанії "Утех" 28.12.2011р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#include <QMessageBox>
#include <QCoreApplication>
#include <QDir>
#include <QTextCodec>
#include <QStringList>
#include <QSqlQuery>
#include <UPostupForm>
#include <USqlAccessible>
#include <QDateTime>

#include "UExport_APark.h"
#include "libxl.h"
#include "UDifFunc.h"

#include <QDebug>

#define FIRST_TABLE_ROW 13

static const char *UAPARK_PATH_TO_CHECKY_EXCEL_ZVIT = "../templates/cheky_okko.xls";

bool AParkExport::exportCheckivVExcel(QDate dt, int zaprId, QString pathToExport)
{
    using namespace libxl;
	
	UPostupForm postup(0, 0);
	postup.show();
	
	qDebug() << " --- Початок експорту чеків у файл -----------------------" << QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss");
	
	bool exportResult = true;
	bool dataWarnings = false;
	QStringList monthList;
	monthList   << "січень"
				<< "лютий"
				<< "березень"
				<< "квітень"
				<< "травень"
				<< "червень"
				<< "липень"
				<< "серпень"
				<< "вересень"
				<< "жовтень"
				<< "листопад"
				<< "грудень";
	
    QTextCodec *codec = QTextCodec::codecForLocale();
	QDir::setCurrent(QCoreApplication::applicationDirPath());
	Book* book = xlCreateBook(); // use xlCreateXMLBook() for working with xlsx files
	bool res = book->load(UAPARK_PATH_TO_CHECKY_EXCEL_ZVIT);

	if (!res) {
	    qDebug() << "Error opening template excel file. Reason: " << book->errorMessage();
		book->release();
		QMessageBox::critical(0, "Помилка відкриття шаблону звіту", "Помилка відкриття шаблону звіту");
		return false;
	}
	
    //Create format for dd.mm.yyyy date
    int dateFormatNumber = book->addCustomNumFormat("dd.mm.yyyy");

    if (dateFormatNumber <= 0) {
        qDebug() << "Помилка створення формату дати \"dd.mm.yyyy\". При формуванні звіту буде використано формат по замовчуванню.";
    }

    Sheet* sheet = book->getSheet(0);

	// За місяць
	QString dateStr = QString("за %1 %2 року").arg(monthList.at(dt.month() - 1)).arg(dt.year());
	sheet->writeStr(2, 4, codec->fromUnicode(dateStr));
	
	// реквізити підприємства
    sheet->writeStr(5, 5, codec->fromUnicode(OrganizEDRPOU()));
    sheet->writeStr(6, 5, codec->fromUnicode(OrganizName()));
	sheet->writeStr(7, 5, codec->fromUnicode(OrganizIPN()));
	sheet->writeStr(8, 5, codec->fromUnicode(OrganizSvidPDVNum()));
	sheet->writeStr(9, 5, codec->fromUnicode(OrganizAdresa()));
	sheet->writeStr(10, 5, codec->fromUnicode(BuhgalterTel()));

	const int rowForFormat = FIRST_TABLE_ROW;
	Format* checkCellFormat = sheet->cellFormat(rowForFormat, 1);
	Format* dateCellFormat = sheet->cellFormat(rowForFormat, 2);
	Format* azsCellFormat = sheet->cellFormat(rowForFormat, 3);
	Format* sumaCellFormat = sheet->cellFormat(rowForFormat, 4);
	Format* noteCellFormat = sheet->cellFormat(rowForFormat, 5);

    if (dateFormatNumber > 0) {
        dateCellFormat->setNumFormat(dateFormatNumber);
    }
	
	QSqlQuery query;
	query.exec("SELECT count(*) \
				FROM zvitkupivlipalnogo zvit \
				LEFT JOIN zvitkupivlipalnogoorders orders \
					ON zvit.id = orders.ZvitKupivliPalnogo_id \
				WHERE zvit.DovPartners_id = "+sqlStr(zaprId)+" \
					and year(orders.CDate)="+sqlStr(dt.year())+" \
					and month(orders.CDate)="+sqlStr(dt.month()));
	query.next();
	int rowCount = query.value(0).toInt();
	postup.setNumPos(rowCount);
	
	query.exec("SELECT orders.DocNum, orders.CDate, TRIM(orders.KodZapravky), orders.Suma, \
					zvit.Npr_id, zvit.ZvitNum \
				FROM zvitkupivlipalnogo zvit \
				LEFT JOIN zvitkupivlipalnogoorders orders \
					ON zvit.id = orders.ZvitKupivliPalnogo_id \
				WHERE zvit.DovPartners_id = "+sqlStr(zaprId)+" \
					and year(orders.CDate)="+sqlStr(dt.year())+" \
					and month(orders.CDate)="+sqlStr(dt.month())+" \
				ORDER BY orders.CDate, TRIM(orders.KodZapravky)"
				);
	
	// Workaround for insertRow errors for rowCount 0, 1, 2
	if (rowCount < 2)
		rowCount = 2;
	res = sheet->insertRow(FIRST_TABLE_ROW, FIRST_TABLE_ROW + rowCount - 2);
	if (!res) {
	    qDebug() << "Eror inserting rows into xls document.";
		exportResult = false;
	}
	int row = FIRST_TABLE_ROW;
	int i;
	double sumAll = 0;
	for (i = 0; i < rowCount && query.next(); ++i) {
		
        int orderNumber = query.value(0).toString().trimmed().toInt();
		QDate cDate = query.value(1).toDate();
        QString azs = query.value(2).toString().toUpper();
		double suma = query.value(3).toDouble();
		
		sumAll += suma;
		
		if (orderNumber <= 0 ||
			cDate.year() != dt.year() ||
			cDate.month() != dt.month() ||
			azs.length() < 4 ||
			suma <= 0) {
		    qDebug() << "Можлива помилка у чеку № " << orderNumber << " від " << cDate.toString("dd.MM.yyyy") 
						<< " заправка: " << azs
						<< " на суму: " << uMToStr2(suma) << " водій: " << query.value(4).toInt() 
						<< " номер звіту: " << query.value(5).toString();
			dataWarnings = true;
		}
		
		// № чеку
        sheet->writeNum(row, 1, orderNumber, checkCellFormat);
		//Дата
        sheet->writeNum(row, 2, book->datePack(cDate.year(), cDate.month(), cDate.day()), dateCellFormat);
		//АЗС
        sheet->writeStr(row, 3, codec->fromUnicode(azs), azsCellFormat);
		//Сума (з ПДВ)
        sheet->writeNum(row, 4, suma, sumaCellFormat);
		//Примітка
        sheet->writeStr(row, 5, "", noteCellFormat);
		
		postup.incPos();
		++row;
	}
	
	QChar c = pathToExport.at(pathToExport.length() - 1);
	if (c != '\\' && c != '/') {
	    pathToExport += QDir::separator();
	}
	QString fileName = pathToExport+"zvitKupivliPalnogo_"+dt.toString("MM.yyyy")+".xls";
	if (QFile::exists(fileName)) {
		QFile::remove(fileName);
	}
    res = book->save(fileName.toLocal8Bit());
	if (!res) {
		qDebug() << "Error writing sheet to file.";
		exportResult = false;
	}

    book->release();
	
	qDebug() << " --- Закінчення експорту у файл -----------------------------" << QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss");
	postup.hide();
	
	QString message = QString("Кількість імпортованих чеків: %1.\n"
						"Загальна сума експорту: %2грн.\n"
						"Експортований файл: %3").arg(i).arg(uMToStr2(sumAll)).arg(fileName);
	
	if (exportResult == true && dataWarnings == false) {
		QMessageBox::information(0, "Укспорт успішно завершено.", "Експорт чеків у файл успішно завершено.\n"+message);
	}
	else if (exportResult == true && dataWarnings == true) {
	    QMessageBox::warning(0, "Експорт завершено з можливими помилками", 
			"Експорт чеків у файл завершено з можливими помилками.\n"+message+"\n Щоб проглянути можливі помилки оберіть у меню \"Програма\"->\"Програмні повідомлення\"");
	}
	else {
		QMessageBox::critical(0, "Помилка експорту.", "Помилка експорту файлу. \n"+message);
	}
	
	return exportResult;
}
