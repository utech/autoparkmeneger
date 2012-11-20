//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл декларації класу вікна реєстрації користувача
//
// Створений програмістами Компанії "Утех" 29.03.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#include "UAutoParkMeneger_APark.h"

#include <math.h>
#include <UMath>

//--------------------utech--------------------utech--------------------utech--------------------
const char* UAutoPark::version()
{
    return "1.2.0";
}
//--------------------utech--------------------utech--------------------utech--------------------
int UAutoPark::dbVersion()
{
    return 1;
}
//--------------------utech--------------------utech--------------------utech--------------------
QTime UAutoPark::reshtaChasu()
{
	return QTime(0, 33);
}
//--------------------utech--------------------utech--------------------utech--------------------
double UAutoPark::cinaPalnogo(short palneId, QDate dt)
{
	QSqlQuery query;
	query.exec("SELECT Cina FROM cinaPalnogoDate \
				LEFT JOIN (SELECT * FROM cinaPalnogo WHERE Palne_id="+sqlStr(palneId)+") AS cP \
					ON cP.cinaPalnogoDate_id=cinaPalnogoDate.id \
				WHERE date("+sqlStr(dt)+")>=cinaPalnogoDate.CDate and cp.Cina>0 \
				ORDER BY CDate DESC, cp.Cina DESC \
				LIMIT 1");
	if (query.next())
		return query.value(0).toDouble();
	return 0;
}
//--------------------utech--------------------utech--------------------utech--------------------
/*inline double UAutoPark::planNaZminu(int Marshrut_id, QDate dt)
{
	QSqlQuery query;
	query.exec("SELECT pNZ.Plan FROM planNaZminuDate \
				LEFT JOIN (SELECT * FROM planNaZminu WHERE Marshrut_id="+sqlStr(Marshrut_id)+") AS pNZ \
					ON pNZ.planNaZminuDate_id=planNaZminuDate.id \
				WHERE date("+sqlStr(dt)+")>=planNaZminuDate.CDate and pNZ.Plan>0 \
				ORDER BY CDate DESC, pNZ.Plan DESC \
				LIMIT 1");
	if (query.next())
		return query.value(0).toDouble();
	return 0;
}
*/
//--------------------utech--------------------utech--------------------utech--------------------
double UAutoPark::planNaZminu(int kodMarshrutu, short grafikNum, short zminaNum, QDate dt, 
							double cinaPalnogo, double kilkPalnogo)
{
	QSqlQuery query;
	query.exec("SELECT id FROM marshruty \
				WHERE KodMarshrutu="+sqlStr(kodMarshrutu)+" \
					and GrafikNum="+sqlStr(grafikNum)+" \
					and ZminaNum="+sqlStr(zminaNum)+" \
				LIMIT 1");
	if (query.next()) {
		query.exec("SELECT pNZ.Plan FROM planNaZminuDate \
				LEFT JOIN (SELECT * FROM planNaZminu WHERE Marshrut_id="+sqlStr(query.value(0).toInt())+") AS pNZ \
					ON pNZ.planNaZminuDate_id=planNaZminuDate.id \
				WHERE date("+sqlStr(dt)+")>=planNaZminuDate.CDate and pNZ.Plan>0 \
				ORDER BY CDate DESC, pNZ.Plan DESC \
				LIMIT 1");
		if (query.next()){
			return ceil(query.value(0).toDouble() + uDToM(cinaPalnogo * kilkPalnogo));
		}
	}
	return 0;
}
//--------------------utech--------------------utech--------------------utech--------------------
UAutoParkPrograms::UAutoParkPrograms()
{
	ProgramsList << "Перевезення" << "Зарплата" << "Склад";
}
//--------------------utech--------------------utech--------------------utech--------------------
UPerevezTabWidgetPartsNames::UPerevezTabWidgetPartsNames()
{
	PartsNames << "Порожня" 
				<< "Допомога" 
				<< "Рухомий склад" 
				<< "Маршрути" 
				<< "Шляховий лист" 
				<< "Листок регулярності руху автобуса"
				<< "Ціни на пальне"
				<< "Технічний огляд автобусів"
				<< "Пробіг (необхідність ТО)"
				<< "Перелік працівників"
				<< "Картки обліку виконання плану"
				<< "Звіт по пільговому проїзду"
				<< "Довідник \"Марки автобусів\""
				<< "Планова виручка"
				<< "Редагування табеля водіїв"
				<< "Святкові дні"
				<< "Картки роботи водіїв"
				<< "Документація підприємства"
				<< "Підсумковий табель"
				<< "Зарплата АГЕНТСЬКІ"
				<< "Перегляд документів"
				<< "Закр. місяця"
				<< "Підписи документів"
				<< "Облік пального"
				<< "Партнери"
				<< "Табель підрозділів";
}
//--------------------utech--------------------utech--------------------utech--------------------
//Задання значення першого дня місяця
#define BEG_DAY_OF_WORK_MONTH 1
UWorkMonth::UWorkMonth(short year, short month)
{
	_begDate.setDate(year, month, BEG_DAY_OF_WORK_MONTH);
	_endDate.setDate(year, month, _begDate.daysInMonth());
}
//--------------------utech--------------------utech--------------------utech--------------------
UWorkMonth::UWorkMonth(QDate date)
{
	_begDate.setDate(date.year(), date.month(), BEG_DAY_OF_WORK_MONTH);
	_endDate.setDate(date.year(), date.month(), _begDate.daysInMonth());
}
//--------------------utech--------------------utech--------------------utech--------------------
QDate UWorkMonth::begDate()
{
	return _begDate;
}
//--------------------utech--------------------utech--------------------utech--------------------
QDate UWorkMonth::endDate()
{
	return _endDate;
}
//--------------------utech--------------------utech--------------------utech--------------------
