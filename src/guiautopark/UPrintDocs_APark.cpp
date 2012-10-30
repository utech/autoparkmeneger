//--------------------utech--------------------utech--------------------utech--------------------
//
// Створений програмістами Компанії "Утех" 23.04.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#include "UPrintDocs_APark.h"

#include <UPopulateTextTableCells>
#include <UPostupForm>
#include "UDifFunc.h"
#include "UAutoParkMeneger_APark.h"

//--------------------utech--------------------utech--------------------utech--------------------
UPrintDocs_APark::UPrintDocs_APark()
{
	date= QDate::currentDate();
	
	monthlist 	<< "січень"
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
	query = new QSqlQuery();
	tQuery = new QSqlQuery();
}
//--------------------utech--------------------utech--------------------utech--------------------
UPrintDocs_APark::~UPrintDocs_APark()
{
	delete query;
	delete tQuery;
}
//--------------------utech--------------------utech--------------------utech--------------------
#include <QImage>
#include <QPainter>
#include <QFontMetrics>
QImage UPrintDocs_APark::verticalTextToImage(const QString & text, QTextCharFormat & textCharFormat)
{
	QFontMetrics fontMetr(textCharFormat.font());
	int width = fontMetr.width(text);
	QImage img(fontMetr.height(), width, QImage::Format_Mono);
	QPainter painter(&img);
	painter.setFont(textCharFormat.font());
	painter.setPen(QColor(Qt::black));
	painter.fillRect(img.rect(), QColor(Qt::white));
	QMatrix matrix;
	matrix.rotate(-90);
	painter.setMatrix(matrix);
	painter.drawText(-width, fontMetr.height()-fontMetr.xHeight(), text);
	return img;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UPrintDocs_APark::print_lystkyRegulyarnostiRuhu(QList<int> idList)
{
	UPostupForm *postupForm = new UPostupForm(0, idList.size() );
	postupForm->show();
	
	printform = new UPrintForm(0, ((idList.size()==1) ? "Листок" : "Листки") +QString(" регулярнострі руху автобуса"));
	
	QTextCursor cursor(printform->document());
	
	QTextBlockFormat pageEndBlockFormat, nonBrBlockFormat;
	pageEndBlockFormat.setPageBreakPolicy(QTextFormat::PageBreak_AlwaysAfter);
	
	bool needSeparator = true;
	for (int iter=0; iter<idList.size(); iter++){
		if (iter!=0){
			if (needSeparator){
				cursor.insertBlock();
				cursor.insertBlock();
				cursor.insertBlock();
				cursor.insertBlock();
				
				needSeparator = false;
			}
			else{
				cursor.insertBlock(pageEndBlockFormat);
				cursor.insertText(" ");
				cursor.insertBlock(nonBrBlockFormat);
				
				needSeparator = true;
			}
		}
		cursor.insertFragment(create_lystokRegulyarnostiRuhu(idList[iter]));
		
		postupForm->inc_pos();
	}
	
	printform->printer()->setDocName(((idList.size()==1) ? "Листок" : "Листки") +QString(" регулярнострі руху автобуса"));
	printform->printer()->setPageMargins( 15, 5, 5, 5, QPrinter::Millimeter );
	printform->show();
	delete postupForm;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UPrintDocs_APark::print_lystkyPustogrRegulyarnostiRuhu()
{
	printform = new UPrintForm(0, "Пустографка Листка регулярнострі руху автобуса");
	
	QTextCursor cursor(printform->document()), cellCursor;
	
	//Шапка документа
	QTextBlockFormat blockFormat;
	QTextTableCell cell;
	QTextCharFormat textCharFormat, textCharFormat_bold, textCharFormat_small;
	QFont fnt = textCharFormat_bold.font();
	fnt.setBold(true);
	textCharFormat_bold.setFont(fnt);
	
	blockFormat.setAlignment( Qt::AlignLeft );
	cursor.setBlockFormat( blockFormat );
	textCharFormat_bold.setFontPointSize( 12 );
	cursor.insertText(OrganizShortName(), textCharFormat_bold);
	textCharFormat_small.setFontPointSize( 5 );
	textCharFormat_bold.setFontPointSize( 11 );
	textCharFormat.setFontPointSize( 11 );
	blockFormat.setAlignment( Qt::AlignRight );
	cursor.insertBlock(blockFormat);
	cursor.insertText("Бригада _______", textCharFormat);
	cursor.insertBlock(blockFormat);
	cursor.insertText(" ", textCharFormat_small);
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	blockFormat.setAlignment( Qt::AlignHCenter );
	cursor.insertBlock(blockFormat);
	textCharFormat_bold.setFontPointSize( 12 );
	cursor.insertText("ЛИСТОК РЕГУЛЯРНОСТІ РУХУ АВТОБУСА", textCharFormat_bold);
	textCharFormat_bold.setFontPointSize( 11 );
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	blockFormat.setAlignment( Qt::AlignCenter );
	cursor.insertBlock(blockFormat);
	cursor.insertText("Дата виїзду:  \"____\"________20___р.", textCharFormat);
	cursor.insertText("    заїзду:  \"____\"________20___р.", textCharFormat);
	blockFormat.setAlignment( Qt::AlignLeft );
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	
	//Створення таблиці, при друку - невидима
	QTextTableFormat tableFormat;
	QVector<QTextLength> constraints;
	constraints << QTextLength(QTextLength::FixedLength, 550);
	constraints << QTextLength(QTextLength::FixedLength, 100);
	
	tableFormat.setColumnWidthConstraints(constraints);
	tableFormat.setCellSpacing(0);
	tableFormat.setCellPadding(1);
	tableFormat.setBorder(0);
	QTextTable *table = cursor.insertTable(3, 2, tableFormat);
	UPopulateCell tableCell(table);
	
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignTop);
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignTop);
	
	tableCell.set(0,0, "Автобус:  ", textCharFormat);
	tableCell.insertText("номерн. знак  ________________", textCharFormat);
	tableCell.insertText(",    марка  ____________________", textCharFormat);
	tableCell.set(0,1, "_________", textCharFormat);
	tableCell.insertText("\n", textCharFormat);
	tableCell.insertText("\n", textCharFormat);
	
	tableCell.set(1,0, "Водій:  ______________________________________", textCharFormat);
	tableCell.set(1,1, "_________", textCharFormat_bold);
	tableCell.insertText("\n", textCharFormat);
	tableCell.insertText("\n", textCharFormat);
	
	tableCell.set(2,0, "Маршрут:  ", textCharFormat);
	tableCell.insertText("    напр. _________________________________", textCharFormat);
	tableCell.insertText("    рейси  _______", textCharFormat);
	tableCell.set(2,1, "_____________", textCharFormat);
	
	cursor.movePosition(QTextCursor::End);
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	cursor.insertText("План на зміну: _____________грн.", textCharFormat);
	
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	cursor.insertText("План пального: ________", textCharFormat);
	cursor.insertText(" (норма: ________) x (ціна: __________грн.) = (вартість: _________грн.)", textCharFormat);
	
	cursor.insertBlock(blockFormat);
	blockFormat.setAlignment( Qt::AlignCenter );
	cursor.insertBlock(blockFormat);
	cursor.insertText("Час виїзду  ____________", textCharFormat);
	blockFormat.setAlignment( Qt::AlignLeft );
	cursor.insertBlock(blockFormat);
	cursor.insertText(" ", textCharFormat_small);
	
	//Створення таблиці
	constraints.clear();
	constraints << QTextLength(QTextLength::FixedLength, 130);
	constraints << QTextLength(QTextLength::FixedLength, 130);
	constraints << QTextLength(QTextLength::FixedLength, 130);
	constraints << QTextLength(QTextLength::FixedLength, 130);
	constraints << QTextLength(QTextLength::FixedLength, 130);
		
	tableFormat.setColumnWidthConstraints(constraints);
	tableFormat.setCellSpacing(0);
	tableFormat.setCellPadding(3);
	tableFormat.setBorder(0.7);
	table = cursor.insertTable(2, 5, tableFormat);
	tableCell.setTextTable(table);
	
	blockFormat.setBottomMargin(0);
	blockFormat.setTopMargin(0);
	
	tableCell.setAlignment(Qt::AlignCenter);
	table->mergeCells(0,3,1,2);
	tableCell.set(0,0,"Планова виручка", textCharFormat);
	tableCell.set(0,1,"Фактична виручка", textCharFormat);
	tableCell.set(0,2,"Відхилення", textCharFormat);
	tableCell.set(0,3,"Відхилення по пальному", textCharFormat);
	tableCell.set(1,0,"___________", textCharFormat);
	tableCell.set(1,1,"___________", textCharFormat);
	tableCell.set(1,2,"___________", textCharFormat);
	tableCell.set(1,3,"___________", textCharFormat);
	tableCell.set(1,4,"___________", textCharFormat);
	
	cursor.movePosition(QTextCursor::End);
	blockFormat.setAlignment( Qt::AlignLeft );
	cursor.insertBlock(blockFormat);
	
	printform->printer()->setDocName("Пустографка Листка регулярнострі руху автобуса");
	printform->printer()->setPageMargins( 15, 5, 5, 5, QPrinter::Millimeter );
	printform->show();
}
//--------------------utech--------------------utech--------------------utech--------------------
void UPrintDocs_APark::print_backSideLystkaRegulyarnostiRuhu(unsigned char numberCopys)
{
	printform = new UPrintForm(0, "Задня частина Листка регулярності руху автобуса");
	
	QTextCursor cursor(printform->document());
	QTextDocumentFragment fragment = create_backSideLystkaRegulyarnostiRuhu();
	for (int i=0; i<numberCopys; i++) {
		if (i) {
			cursor.insertBlock();
			cursor.insertBlock();
			cursor.insertBlock();
		}
		cursor.insertFragment(fragment);
	}
	
	printform->printer()->setDocName("Задня частина Листка регулярності руху автобуса");
	printform->printer()->setPageMargins( 5, 5, 5, 5, QPrinter::Millimeter );
	printform->show();
}
//--------------------utech--------------------utech--------------------utech--------------------
void UPrintDocs_APark::print_misyachnyiProbigUsihAvtobusiv(short year, short month)
{
	printform = new UPrintForm(0, "Місячний пробіг усіх автобусів підприємства");
	
        QDate xDate(year, month, 1);
	QTextCursor cursor(printform->document()), cellCursor;
	//Шапка документа
	QTextBlockFormat blockFormat;
	QTextTableCell cell;
	QTextCharFormat textCharFormat, textCharFormat_bold, textCharFormat_small;
	QFont fnt = textCharFormat_bold.font();
	fnt.setBold(true);
	textCharFormat_bold.setFont(fnt);
	
	blockFormat.setAlignment( Qt::AlignRight );
	cursor.setBlockFormat( blockFormat );
	textCharFormat.setFontPointSize( 8 );
	cursor.insertText("Документ створено програмою \"Автопарк менеджер\" "+QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm"), textCharFormat);
	blockFormat.setAlignment( Qt::AlignCenter );
	cursor.insertBlock(blockFormat);
	textCharFormat_bold.setFontPointSize( 11 );
	textCharFormat_small.setFontPointSize( 5 );
	cursor.insertText("МІСЯЧНИЙ ПРОБІГ УСІХ АВТОБУСІВ ПІДПРИЄМСТВА", textCharFormat_bold);
	blockFormat.setAlignment( Qt::AlignRight );
	cursor.insertBlock(blockFormat);
        cursor.insertText("за "+monthlist[month-1]+" "+QString::number(year)+" року", textCharFormat);
	blockFormat.setAlignment( Qt::AlignHCenter );
	cursor.insertBlock(blockFormat);
	cursor.insertText(" ", textCharFormat_small);
	cursor.insertBlock(blockFormat);
	//Створення таблиці
	QTextTableFormat tableFormat;
	QVector<QTextLength> constraints;
	constraints << QTextLength(QTextLength::FixedLength, 100);
	constraints << QTextLength(QTextLength::FixedLength, 100);
	constraints << QTextLength(QTextLength::FixedLength, 100);
	constraints << QTextLength(QTextLength::FixedLength, 100);
	constraints << QTextLength(QTextLength::FixedLength, 100);
	constraints << QTextLength(QTextLength::FixedLength, 100);
	constraints << QTextLength(QTextLength::FixedLength, 100);
		
	tableFormat.setColumnWidthConstraints(constraints);
	tableFormat.setCellSpacing(0);
	tableFormat.setCellPadding(1);
	QTextTable *table = cursor.insertTable(7, 7, tableFormat);
	UPopulateCell tableCell(table);
	
	blockFormat.setBottomMargin(0);
	blockFormat.setTopMargin(0);
	
	//Заповнення шапки таблиці
	textCharFormat.setFontPointSize( 12 );
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	textCharFormat_bold.setFontPointSize( 12 );
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	
	tableCell.setAlignment(Qt::AlignCenter);
	tableCell.set(0,0,"ПОНЕДІЛОК", textCharFormat);
	tableCell.set(0,1,"ВІВТОРОК", textCharFormat);
	tableCell.set(0,2,"СЕРЕДА", textCharFormat);
	tableCell.set(0,3,"ЧЕТВЕР", textCharFormat);
	tableCell.set(0,4,"П'ЯТНИЦЯ", textCharFormat);
	tableCell.set(0,5,"СУБОТА", textCharFormat);
	tableCell.set(0,6,"НЕДІЛЯ", textCharFormat);
	
	QSqlQuery query;
	short row=1;
	textCharFormat_bold.setFontPointSize(10);
        while (xDate.month() == month){
		query.exec("SELECT sum(ZagalnProbig) FROM shlyahovyilyst \
					WHERE date(DataVyizdu)='"+xDate.toString("yyyy-MM-dd")+"'");
		query.seek(0);
		tableCell.setWithFrame(row,xDate.dayOfWeek()-1,xDate.toString("dd.MM.yyyy")+"\n\n"+query.value(0).toString().replace('.',','), textCharFormat_bold);
		
		xDate = xDate.addDays(1);
		if (xDate.dayOfWeek()==1)
			++row;
	}
	
	cursor.movePosition(QTextCursor::End);
	blockFormat.setAlignment( Qt::AlignLeft );
	cursor.insertFragment(pidpysy(3, textCharFormat));
	
	printform->printer()->setDocName("Місячний пробіг усіх автобусів підприємства");
	printform->printer()->setPageMargins( 5, 5, 5, 5, QPrinter::Millimeter );
	printform->show();
}
//--------------------utech--------------------utech--------------------utech--------------------
void UPrintDocs_APark::print_misyachnyiProbigOdnogoAvtobusa(short year, short month, int autoGarajNumber)
{
	printform = new UPrintForm(0, "Місячний пробіг одного автобуса");
	
	QSqlQuery query;
        QDate xDate(year, month, 1);
	QTextCursor cursor(printform->document()), cellCursor;
	//Шапка документа
	QTextBlockFormat blockFormat;
	QTextTableCell cell;
	QTextCharFormat textCharFormat, textCharFormat_bold, textCharFormat_small;
	QFont fnt = textCharFormat_bold.font();
	fnt.setBold(true);
	textCharFormat_bold.setFont(fnt);
	
	blockFormat.setAlignment( Qt::AlignRight );
	cursor.setBlockFormat( blockFormat );
	textCharFormat.setFontPointSize( 8 );
	cursor.insertText("Документ створено програмою \"Автопарк менеджер\" "+QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm"), textCharFormat);
	blockFormat.setAlignment( Qt::AlignCenter );
	cursor.insertBlock(blockFormat);
	textCharFormat_bold.setFontPointSize( 11 );
	textCharFormat_small.setFontPointSize( 5 );
	cursor.insertText("МІСЯЧНИЙ ПРОБІГ АВТОБУСА", textCharFormat_bold);
	cursor.insertBlock(blockFormat);
	query.exec("SELECT ruhomyiSklad.GarajNumber, ruhomyiSklad.NomernyiZnak, \
						markaAuto.MarkaShyfr \
				FROM ruhomyiSklad \
				LEFT JOIN markaauto ON markaAuto.id=ruhomyiSklad.MarkaAuto_id \
				WHERE GarajNumber="+QString::number(autoGarajNumber));
	query.seek(0);
	cursor.insertText("№"+query.value(0).toString()+" ["+query.value(1).toString()+"] - "+query.value(2).toString(), textCharFormat_bold);
	blockFormat.setAlignment( Qt::AlignRight );
	cursor.insertBlock(blockFormat);
        cursor.insertText("за "+monthlist[month-1]+" "+QString::number(year)+" року", textCharFormat);
	blockFormat.setAlignment( Qt::AlignHCenter );
	cursor.insertBlock(blockFormat);
	cursor.insertText(" ", textCharFormat_small);
	cursor.insertBlock(blockFormat);
	//Створення таблиці
	QTextTableFormat tableFormat;
	QVector<QTextLength> constraints;
	constraints << QTextLength(QTextLength::FixedLength, 100);
	constraints << QTextLength(QTextLength::FixedLength, 100);
	constraints << QTextLength(QTextLength::FixedLength, 100);
	constraints << QTextLength(QTextLength::FixedLength, 100);
	constraints << QTextLength(QTextLength::FixedLength, 100);
	constraints << QTextLength(QTextLength::FixedLength, 100);
	constraints << QTextLength(QTextLength::FixedLength, 100);
		
	tableFormat.setColumnWidthConstraints(constraints);
	tableFormat.setCellSpacing(0);
	tableFormat.setCellPadding(1);
	QTextTable *table = cursor.insertTable(7, 7, tableFormat);
	UPopulateCell tableCell(table);
	
	blockFormat.setBottomMargin(0);
	blockFormat.setTopMargin(0);
	
	//Заповнення шапки таблиці
	textCharFormat.setFontPointSize( 12 );
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	textCharFormat_bold.setFontPointSize( 12 );
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	
	tableCell.setAlignment(Qt::AlignCenter);
	tableCell.set(0,0,"ПОНЕДІЛОК", textCharFormat);
	tableCell.set(0,1,"ВІВТОРОК", textCharFormat);
	tableCell.set(0,2,"СЕРЕДА", textCharFormat);
	tableCell.set(0,3,"ЧЕТВЕР", textCharFormat);
	tableCell.set(0,4,"П'ЯТНИЦЯ", textCharFormat);
	tableCell.set(0,5,"СУБОТА", textCharFormat);
	tableCell.set(0,6,"НЕДІЛЯ", textCharFormat);
	
	short row=1;
	textCharFormat_bold.setFontPointSize(10);
        while (xDate.month() == month){
		query.exec("SELECT sum(ZagalnProbig) FROM shlyahovyilyst \
					WHERE date(DataVyizdu)='"+xDate.toString("yyyy-MM-dd")+"' \
						and GarajNum_id="+QString::number(autoGarajNumber));
		query.seek(0);
		tableCell.setWithFrame(row,xDate.dayOfWeek()-1,xDate.toString("dd.MM.yyyy")+"\n\n"+query.value(0).toString().replace('.',','), textCharFormat_bold);
		
		xDate = xDate.addDays(1);
		if (xDate.dayOfWeek()==1)
			++row;
	}
	
	cursor.movePosition(QTextCursor::End);
	blockFormat.setAlignment( Qt::AlignLeft );
	cursor.insertFragment(pidpysy(3, textCharFormat));
	
	printform->printer()->setDocName("Місячний пробіг одного автобуса");
	printform->printer()->setPageMargins( 5, 5, 5, 5, QPrinter::Millimeter );
	printform->show();
}
//--------------------utech--------------------utech--------------------utech--------------------
void UPrintDocs_APark::print_perelikAvtobusivNaTO(short TONumber)
{
	printform = new UPrintForm(0, "Перелік автобусів на техогляд");
	
	QSqlQuery query;
	QString TONumberFilterStr;
	if (TONumber > 0)
		TONumberFilterStr = " AND IF(autoTONum.PrevToNum=1,2,1)="+QString::number(TONumber)+" ";
	
	query.exec("SELECT count(*)	FROM ((ruhomyiSklad \
				LEFT JOIN (SELECT GarajNum_Id, sum(ZagalnProbig) AS ZagProbig FROM shlyahovyiLyst \
						WHERE DATE(DataVyizdu)>=(SELECT max(TOLog.TODate) FROM TOLog WHERE TOLog.GarajNum_id=shlyahovyiLyst.GarajNum_Id) \
							OR (SELECT max(TOLog.TODate) FROM TOLog WHERE TOLog.GarajNum_id=shlyahovyiLyst.GarajNum_Id) IS NULL \
						GROUP BY GarajNum_Id) AS autoProbig \
					ON autoProbig.GarajNum_Id=ruhomyiSklad.GarajNumber) \
				LEFT JOIN (SELECT GarajNum_id, TONum AS PrevToNum FROM TOLog t \
						WHERE TODate=(SELECT max(TOLog.TODate) FROM TOLog WHERE TOLog.GarajNum_id=t.GarajNum_Id)) AS autoTONum \
					ON autoTONum.GarajNum_id=ruhomyiSklad.GarajNumber) \
				LEFT JOIN MarkaAuto ON MarkaAuto.id=ruhomyiSklad.MarkaAuto_Id \
				WHERE IF(autoTONum.PrevTONum=1,ruhomyiSklad.TO2,ruhomyiSklad.TO1)-autoProbig.ZagProbig < 500 "+TONumberFilterStr);
	query.seek(0);
	int rowCount = query.value(0).toInt();
	
	QTextCursor cursor(printform->document()), cellCursor;
	//Шапка документа
	QTextBlockFormat blockFormat;
	QTextTableCell cell;
	QTextCharFormat textCharFormat, textCharFormat_bold, textCharFormat_small;
	QFont fnt = textCharFormat_bold.font();
	fnt.setBold(true);
	textCharFormat_bold.setFont(fnt);
	
	blockFormat.setAlignment( Qt::AlignRight );
	cursor.setBlockFormat( blockFormat );
	textCharFormat.setFontPointSize( 8 );
	cursor.insertText("Документ створено програмою \"Автопарк менеджер\" "+QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm"), textCharFormat);
	blockFormat.setAlignment( Qt::AlignCenter );
	cursor.insertBlock(blockFormat);
	textCharFormat_bold.setFontPointSize( 11 );
	textCharFormat_small.setFontPointSize( 5 );
	cursor.insertText("ПЕРЕЛІК АВТОБУСІВ НА ТЕХОГЛЯД", textCharFormat_bold);
	blockFormat.setAlignment( Qt::AlignHCenter );
	cursor.insertBlock(blockFormat);
	cursor.insertText(" ", textCharFormat_small);
	cursor.insertBlock(blockFormat);
	//Створення таблиці
	QTextTableFormat tableFormat;
	QVector<QTextLength> constraints;
	constraints << QTextLength(QTextLength::FixedLength, 30);
	constraints << QTextLength(QTextLength::FixedLength, 330);
	constraints << QTextLength(QTextLength::FixedLength, 30);
	constraints << QTextLength(QTextLength::FixedLength, 100);
	constraints << QTextLength(QTextLength::FixedLength, 100);
	constraints << QTextLength(QTextLength::FixedLength, 120);
		
	tableFormat.setColumnWidthConstraints(constraints);
	tableFormat.setCellSpacing(0);
	tableFormat.setCellPadding(3);
	short additionalRowsCount = 2;
	if (TONumber == 0)
		additionalRowsCount = 3;
	QTextTable *table = cursor.insertTable(rowCount+additionalRowsCount, 6, tableFormat);
	UPopulateCell tableCell(table);
	
	blockFormat.setBottomMargin(0);
	blockFormat.setTopMargin(0);
	
	//Заповнення шапки таблиці
	textCharFormat.setFontPointSize( 12 );
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	textCharFormat_bold.setFontPointSize( 12 );
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	
	tableCell.setAlignment(Qt::AlignCenter);
	tableCell.set(0,0,"№ з/п", textCharFormat);
	tableCell.set(0,1,"Автобус", textCharFormat);
	tableCell.set(0,2,"№ ТО", textCharFormat);
	tableCell.set(0,3,"Поточний пробіг", textCharFormat);
	tableCell.set(0,4,"До ТО / перевищ.ТО", textCharFormat);
	tableCell.set(0,5,"Примітка", textCharFormat);
	
	query.exec("SELECT ruhomyiSklad.GarajNumber, IF(autoTONum.PrevToNum=1,ruhomyiSklad.TO2,ruhomyiSklad.TO1) AS probigForTO, \
					autoProbig.ZagProbig, autoTONum.PrevTONum, IF(autoTONum.PrevToNum=1,2,1) AS needToNum, \
					MarkaAuto.MarkaName, MarkaAuto.MarkaShyfr, ruhomyiSklad.NomernyiZnak \
				FROM ((ruhomyiSklad \
				LEFT JOIN (SELECT GarajNum_Id, sum(ZagalnProbig) AS ZagProbig FROM shlyahovyiLyst \
						WHERE DATE(DataVyizdu)>=(SELECT max(TOLog.TODate) FROM TOLog WHERE TOLog.GarajNum_id=shlyahovyiLyst.GarajNum_Id) \
							OR (SELECT max(TOLog.TODate) FROM TOLog WHERE TOLog.GarajNum_id=shlyahovyiLyst.GarajNum_Id) IS NULL \
						GROUP BY GarajNum_Id) AS autoProbig \
					ON autoProbig.GarajNum_Id=ruhomyiSklad.GarajNumber) \
				LEFT JOIN (SELECT GarajNum_id, TONum AS PrevToNum FROM TOLog t \
						WHERE TODate=(SELECT max(TOLog.TODate) FROM TOLog WHERE TOLog.GarajNum_id=t.GarajNum_Id)) AS autoTONum \
					ON autoTONum.GarajNum_id=ruhomyiSklad.GarajNumber) \
				LEFT JOIN MarkaAuto ON MarkaAuto.id=ruhomyiSklad.MarkaAuto_Id \
				WHERE IF(autoTONum.PrevTONum=1,ruhomyiSklad.TO2,ruhomyiSklad.TO1)-autoProbig.ZagProbig < 500 "+TONumberFilterStr+
				" ORDER BY IF(autoTONum.PrevToNum=1,2,1)");
	int row;
	int TO1Count=0, TO2Count=0;
	for (row=1; row<=rowCount && query.next(); ++row){
		tableCell.setAlignment(Qt::AlignCenter);
		tableCell.set(row,0,QString::number(row), textCharFormat);
		tableCell.setAlignment(Qt::AlignLeft);
		tableCell.set(row,1,"№"+query.value(0).toString()+" ["+query.value(7).toString()+"] - "+query.value(6).toString(), textCharFormat);
		tableCell.setAlignment(Qt::AlignRight);
		tableCell.set(row,2,query.value(4).toString(), textCharFormat);
		tableCell.set(row,3,query.value(2).toString().replace('.',','), textCharFormat);
		tableCell.set(row,4,QString::number(query.value(2).toDouble() - query.value(1).toDouble()).replace('.',','), textCharFormat);
		tableCell.set(row,5,"", textCharFormat);
		if (query.value(4).toInt()==1)
			++TO1Count;
		else if (query.value(4).toInt()==2)
			++TO2Count;
	}
	--additionalRowsCount;
	for (int curTOSumary=(TONumber==0?1:TONumber); additionalRowsCount>0; --additionalRowsCount){
		tableCell.setAlignment(Qt::AlignLeft);
		table->mergeCells(row, 0, 1, 2);
		tableCell.setAlignment(Qt::AlignLeft);
		tableCell.set(row,0,"Всього автобусів для ТО"+QString::number(TONumber>0?TONumber:curTOSumary), textCharFormat);
		tableCell.setAlignment(Qt::AlignRight);
		tableCell.set(row,2,QString::number(curTOSumary==1?TO1Count:TO2Count), textCharFormat);
		++curTOSumary;
		++row;
	}
	
	cursor.movePosition(QTextCursor::End);
	blockFormat.setAlignment( Qt::AlignLeft );
	cursor.insertFragment(pidpysy(4, textCharFormat));
	
	printform->printer()->setDocName("Перелік автобусів на техогляд");
	printform->printer()->setPageMargins( 5, 5, 5, 5, QPrinter::Millimeter );
	printform->show();
}
//--------------------utech--------------------utech--------------------utech--------------------
void UPrintDocs_APark::print_vidomistVykonannyaPlanuVDen(QDate vDate)
{
	printform = new UPrintForm(0, "Відомість виконання плану виручки та наявності пального");
	
	int columnCount=15;
	QTextCursor cursor(printform->document());
	QTextBlockFormat blockFormat;
	QTextTableCell cell;
	QTextCharFormat textCharFormat, textCharFormat_bold, textCharFormat_small;
	QFont fnt = textCharFormat_bold.font();
	fnt.setBold(true);
	textCharFormat_bold.setFont(fnt);
	
	blockFormat.setAlignment( Qt::AlignRight );
	cursor.setBlockFormat( blockFormat );
	textCharFormat.setFontPointSize( 8 );
	cursor.insertText("Документ створено програмою \"Автопарк менеджер\" "+QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm"), textCharFormat);
	blockFormat.setAlignment( Qt::AlignCenter );
	cursor.insertBlock(blockFormat);
	textCharFormat_bold.setFontPointSize( 11 );
	textCharFormat_small.setFontPointSize( 5 );
	cursor.insertText("ВІДОМІСТЬ\n виконання плану виручки та наявності пального водіями автоколони\nстаном на "+vDate.toString("dd.MM.yyyy"), textCharFormat_bold);
	blockFormat.setAlignment( Qt::AlignHCenter );
	cursor.insertBlock(blockFormat);
	cursor.insertText(" ", textCharFormat_small);
	cursor.insertBlock(blockFormat);
	//Створення таблиці
	QTextTableFormat tableFormat;
	QVector<QTextLength> constraints;
	constraints << QTextLength(QTextLength::FixedLength, 70);
	constraints << QTextLength(QTextLength::FixedLength, 70);
	constraints << QTextLength(QTextLength::FixedLength, 70);
	constraints << QTextLength(QTextLength::FixedLength, 70);
	constraints << QTextLength(QTextLength::FixedLength, 70);
	constraints << QTextLength(QTextLength::FixedLength, 70);
	constraints << QTextLength(QTextLength::FixedLength, 70);
	constraints << QTextLength(QTextLength::FixedLength, 70);
	constraints << QTextLength(QTextLength::FixedLength, 70);
	constraints << QTextLength(QTextLength::FixedLength, 70);
	constraints << QTextLength(QTextLength::FixedLength, 70);
	constraints << QTextLength(QTextLength::FixedLength, 70);
	constraints << QTextLength(QTextLength::FixedLength, 70);
	constraints << QTextLength(QTextLength::FixedLength, 70);
	constraints << QTextLength(QTextLength::FixedLength, 70);
		
	tableFormat.setColumnWidthConstraints(constraints);
	tableFormat.setCellSpacing(0);
	tableFormat.setCellPadding(1);
	QTextTable *table = cursor.insertTable(3, columnCount, tableFormat);
	UPopulateCell tableCell(table);
	
	blockFormat.setBottomMargin(0);
	blockFormat.setTopMargin(0);
	
	//Заповнення шапки таблиці
	textCharFormat.setFontPointSize( 9.5 );
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	textCharFormat_bold.setFontPointSize( 9.5 );
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	
	table->mergeCells(0,0,2,1);
	table->mergeCells(0,1,1,4);
	table->mergeCells(0,5,1,3);
	table->mergeCells(0,8,1,4);
	table->mergeCells(0,12,1,3);
	
	tableCell.setAlignment(Qt::AlignCenter);
	tableCell.set(0,0,"Бригада", textCharFormat);
	tableCell.set(0,1,"Виручка за день", textCharFormat);
	tableCell.set(1,1,"ПЛАН.", textCharFormat);
	tableCell.set(1,2,"ФАКТ.", textCharFormat);
	tableCell.set(1,3,"ВІДХИЛ.", textCharFormat);
	tableCell.set(1,4,"%", textCharFormat);
	tableCell.set(0,5,"Розхід пального за день", textCharFormat);
	tableCell.set(1,5,"ПО НОРМІ", textCharFormat);
	tableCell.set(1,6,"ЗА ЗМІНУ", textCharFormat);
	tableCell.set(1,7,"ВІДХИЛ.", textCharFormat);
	tableCell.set(0,8,"Виручка з початку місяця", textCharFormat);
	tableCell.set(1,8,"ПЛАН.", textCharFormat);
	tableCell.set(1,9,"ФАКТ.", textCharFormat);
	tableCell.set(1,10,"ВІДХИЛ.", textCharFormat);
	tableCell.set(1,11,"%", textCharFormat);
	tableCell.set(0,12,"Розхід пального з початку місяця", textCharFormat);
	tableCell.set(1,12,"ПО НОРМІ", textCharFormat);
	tableCell.set(1,13,"ЗА ЗМІНИ", textCharFormat);
	tableCell.set(1,14,"ВІДХИЛ.", textCharFormat);
	
	int row=1;
	
	UWorkMonth wMonth(vDate);
	QDate begMonthDate = wMonth.begDate();
	
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignTop);
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignTop);
	
	double planVyruchkyVDen=0, 
			factVyruchkyVDen=0, 
			planPalnogoVDen=0, 
			factPalnogoVDen=0, 
			planVyruchkyVMisyac=0, 
			factVyruchkyVMisyac=0, 
			planPalnogoVMisyac=0, 
			factPalnogoVMisyac=0;
	QSqlQuery query, brygQuery, pokaznQuery;
	//Ідентифікатор посади водіїв
	query.exec("SELECT znach FROM progOptionsAPark WHERE id=1");
	query.next();
	brygQuery.exec("SELECT BrygadaNum FROM npr WHERE Posada_id="+query.value(0).toString()+" \
					GROUP BY BrygadaNum ORDER BY BrygadaNum");
	while (brygQuery.next()){
		++row;
		table->insertRows(row, 1);
		double plan, fact;
		
		tableCell.setAlignment(Qt::AlignCenter);
		tableCell.set(row,0,brygQuery.value(0).toString(), textCharFormat);
		//Виручка за день
		pokaznQuery.exec("SELECT sum(sday.PlanNaZminu), sum(sday.VartProdKvytkiv+sday.VartProdKvytkivAutoStat), \
						sum(sday.PlanRozhidPalnogo), sum(sday.FactRozhidPalnogo) \
					FROM \
						((SELECT * FROM npr WHERE BrygadaNum="+brygQuery.value(0).toString()+") AS n \
					INNER JOIN (SELECT * FROM shlyahovyiLyst \
							WHERE date(ToZvitDate)='"+vDate.toString("yyyy-MM-dd")+"') AS sday ON sday.VodiyTabelNum_id=n.id)");
		pokaznQuery.next();
		tableCell.setAlignment(Qt::AlignRight);
		plan = qRound(pokaznQuery.value(0).toDouble()*100)/100.0;
		fact = qRound(pokaznQuery.value(1).toDouble()*100)/100.0;
		planVyruchkyVDen += plan;
		factVyruchkyVDen += fact;
		tableCell.setDash(row,1,plan, textCharFormat);
		tableCell.setDash(row,2,fact, textCharFormat);
		tableCell.setDash(row,3,fact-plan, textCharFormat);
		if (plan != 0)
			tableCell.setDash(row,4,qRound(fact*10000/plan)/100.0, textCharFormat);
		else
			tableCell.set(row,4,"-", textCharFormat);
		//Витрата пального за день
		plan = qRound(pokaznQuery.value(2).toDouble()*100)/100.0;
		fact = qRound(pokaznQuery.value(3).toDouble()*100)/100.0;
		planPalnogoVDen += plan;
		factPalnogoVDen += fact;
		tableCell.setDash(row,5,plan, textCharFormat);
		tableCell.setDash(row,6,fact, textCharFormat);
		tableCell.setDash(row,7,fact-plan, textCharFormat);
		//Виручка в місяць
		pokaznQuery.exec("SELECT sum(sday.PlanNaZminu), sum(sday.VartProdKvytkiv+sday.VartProdKvytkivAutoStat), \
						sum(sday.PlanRozhidPalnogo), sum(sday.FactRozhidPalnogo) \
					FROM \
						((SELECT * FROM npr WHERE BrygadaNum="+brygQuery.value(0).toString()+") AS n \
					INNER JOIN (SELECT * FROM shlyahovyiLyst \
							WHERE date(ToZvitDate) BETWEEN '"+begMonthDate.toString("yyyy-MM-dd")+"' \
								AND '"+vDate.toString("yyyy-MM-dd")+"') AS sday ON sday.VodiyTabelNum_id=n.id)");
		pokaznQuery.next();
		plan = qRound(pokaznQuery.value(0).toDouble()*100)/100.0;
		fact = qRound(pokaznQuery.value(1).toDouble()*100)/100.0;
		planVyruchkyVMisyac += plan;
		factVyruchkyVMisyac += fact;
		tableCell.setDash(row,8,plan, textCharFormat);
		tableCell.setDash(row,9,fact, textCharFormat);
		tableCell.setDash(row,10,fact-plan, textCharFormat);
		if (plan != 0)
			tableCell.setDash(row,11,qRound(fact*10000/plan)/100.0, textCharFormat);
		else
			tableCell.set(row,11,"-", textCharFormat);
		//Витрата пального за місяць
		plan = qRound(pokaznQuery.value(2).toDouble()*100)/100.0;
		fact = qRound(pokaznQuery.value(3).toDouble()*100)/100.0;
		planPalnogoVMisyac += plan;
		factPalnogoVMisyac += fact;
		tableCell.setDash(row,12,plan, textCharFormat);
		tableCell.setDash(row,13,fact, textCharFormat);
		tableCell.setDash(row,14,fact-plan, textCharFormat);
	}
	
	++row;
	tableCell.setAlignment(Qt::AlignCenter);
	tableCell.set(row,0,"Всього", textCharFormat_bold);
	//Виручка за день
	tableCell.setAlignment(Qt::AlignRight);
	tableCell.setDash(row,1,planVyruchkyVDen, textCharFormat);
	tableCell.setDash(row,2,factVyruchkyVDen, textCharFormat);
	tableCell.setDash(row,3,factVyruchkyVDen-planVyruchkyVDen, textCharFormat);
	if (planVyruchkyVDen != 0)
		tableCell.setDash(row,4,qRound(factVyruchkyVDen*10000/planVyruchkyVDen)/100.0, textCharFormat);
	else
		tableCell.set(row,4,"-", textCharFormat);
	//Витрата пального за день
	tableCell.setDash(row,5,planPalnogoVDen, textCharFormat);
	tableCell.setDash(row,6,factPalnogoVDen, textCharFormat);
	tableCell.setDash(row,7,factPalnogoVDen-planPalnogoVDen, textCharFormat);
	//Виручка в місяць
	tableCell.setDash(row,8,planVyruchkyVMisyac, textCharFormat);
	tableCell.setDash(row,9,factVyruchkyVMisyac, textCharFormat);
	tableCell.setDash(row,10,factVyruchkyVMisyac-planVyruchkyVMisyac, textCharFormat);
	if (planVyruchkyVMisyac != 0)
		tableCell.setDash(row,11,qRound(factVyruchkyVMisyac*10000/planVyruchkyVMisyac)/100.0, textCharFormat);
	else
		tableCell.set(row,11,"-", textCharFormat);
	//Витрата пального за місяць
	tableCell.setDash(row,12,planPalnogoVMisyac, textCharFormat);
	tableCell.setDash(row,13,factPalnogoVMisyac, textCharFormat);
	tableCell.setDash(row,14,factPalnogoVMisyac-planPalnogoVMisyac, textCharFormat);
	
	cursor.movePosition(QTextCursor::End);
	blockFormat.setAlignment( Qt::AlignLeft );
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	
	query.exec("SELECT count(*) FROM shlyahovyiLyst WHERE date(ToZvitDate)='"+vDate.toString("yyyy-MM-dd")+"'");
	query.next();
	cursor.insertText("Кількість шляхових листів за день: "+query.value(0).toString()+".", textCharFormat);
	cursor.setBlockFormat( blockFormat );
	cursor.insertBlock(blockFormat);
	query.exec("SELECT count(*) FROM shlyahovyiLyst \
				WHERE date(ToZvitDate) BETWEEN '"+begMonthDate.toString("yyyy-MM-dd")+"' \
									AND '"+vDate.toString("yyyy-MM-dd")+"'");
	query.next();
	cursor.insertText("Кількість шляхових листів з початку місяця: "+query.value(0).toString()+".", textCharFormat);
	
	cursor.insertFragment(pidpysy(5, textCharFormat, QPrinter::Landscape));
	
	printform->printer()->setOrientation(QPrinter::Landscape);
	printform->printer()->setDocName("Відомість виконання плану виручки та наявності пального");
	printform->printer()->setPageMargins( 4, 10, 4, 20, QPrinter::Millimeter );
	printform->show();
}
//--------------------utech--------------------utech--------------------utech--------------------
void UPrintDocs_APark::print_zvedenaVidomistPoDorojnihLystahZaMisyac(QDate vDate, short marshrutType)
{
	printform = new UPrintForm(0, "Зведена відомість по дорожніх листах за місяць");
	
	
	QSqlQuery query;
	
	query.exec("SELECT count(*) FROM (SELECT BrygadaNum FROM npr WHERE Posada_id=10 \
					GROUP BY BrygadaNum) AS br");
	query.next();
	UPostupForm *postup = new UPostupForm(0, query.value(0).toInt());
	postup->show();
	
	int columnCount=20;
	UWorkMonth wMonth(vDate.year(), vDate.month());
	
	QTextCursor cursor(printform->document());
	QTextBlockFormat blockFormat;
	QTextTableCell cell;
	QTextCharFormat textCharFormat, textCharFormat_bold, textCharFormat_small;
	QFont fnt = textCharFormat_bold.font();
	fnt.setBold(true);
	textCharFormat_bold.setFont(fnt);
	
	blockFormat.setAlignment( Qt::AlignRight );
	cursor.setBlockFormat( blockFormat );
	textCharFormat.setFontPointSize( 8 );
	cursor.insertText("Документ створено програмою \"Автопарк менеджер\" "+QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm"), textCharFormat);
	blockFormat.setAlignment( Qt::AlignCenter );
	cursor.insertBlock(blockFormat);
	textCharFormat_bold.setFontPointSize( 11 );
	textCharFormat_small.setFontPointSize( 5 );
	cursor.insertText("ЗВЕДЕНА ВІДОМІСТЬ\n по дорожніх листах підприємства \n за період з "+wMonth.begDate().toString("dd.MM.yyyy")+" до "+wMonth.endDate().toString("dd.MM.yyyy")+"р.", textCharFormat_bold);
	blockFormat.setAlignment( Qt::AlignLeft );
	cursor.insertBlock(blockFormat);
	textCharFormat_bold.setFontPointSize( 10 );
	cursor.insertText("Тип маршрутів: ", textCharFormat_bold);
	if (marshrutType != 0){
		query.exec("SELECT TypNameMnoj FROM typMarshrutu WHERE id="+QString::number(marshrutType));
		query.seek(0);
		cursor.insertText(query.value(0).toString()+".", textCharFormat_bold);
	}
	else{
		cursor.insertText("УСІ.", textCharFormat_bold);
	}
	cursor.insertBlock(blockFormat);
	cursor.insertText(" ", textCharFormat_small);
	cursor.insertBlock(blockFormat);
	
	//Створення таблиці
	QTextTableFormat tableFormat;
	QVector<QTextLength> constraints;
	constraints << QTextLength(QTextLength::FixedLength, 30);
	constraints << QTextLength(QTextLength::FixedLength, 30);
	constraints << QTextLength(QTextLength::FixedLength, 100);
	constraints << QTextLength(QTextLength::FixedLength, 30);
	constraints << QTextLength(QTextLength::FixedLength, 50);
	constraints << QTextLength(QTextLength::FixedLength, 50);
	constraints << QTextLength(QTextLength::FixedLength, 66);
	constraints << QTextLength(QTextLength::FixedLength, 66);
	constraints << QTextLength(QTextLength::FixedLength, 40);
	constraints << QTextLength(QTextLength::FixedLength, 40);
	constraints << QTextLength(QTextLength::FixedLength, 30);
	constraints << QTextLength(QTextLength::FixedLength, 66);
	constraints << QTextLength(QTextLength::FixedLength, 66);
	constraints << QTextLength(QTextLength::FixedLength, 66);
	constraints << QTextLength(QTextLength::FixedLength, 56);
	constraints << QTextLength(QTextLength::FixedLength, 56);
	constraints << QTextLength(QTextLength::FixedLength, 40);
	constraints << QTextLength(QTextLength::FixedLength, 56);
	constraints << QTextLength(QTextLength::FixedLength, 56);
	constraints << QTextLength(QTextLength::FixedLength, 56);
		
	tableFormat.setColumnWidthConstraints(constraints);
	tableFormat.setCellSpacing(0);
	tableFormat.setCellPadding(1);
	tableFormat.setHeaderRowCount(1);
	tableFormat.setBorder(0.5);
	QTextTable *table = cursor.insertTable(2, columnCount, tableFormat);
	UPopulateCell tableCell(table);
	
	blockFormat.setBottomMargin(0);
	blockFormat.setTopMargin(0);
	
	//Заповнення шапки таблиці
	textCharFormat.setFontPointSize( 7.5 );
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	textCharFormat_bold.setFontPointSize( 7 );
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	
	tableCell.setAlignment(Qt::AlignCenter);
	tableCell.set(0,0,"№ з/п", textCharFormat);
	tableCell.set(0,1,"Таб. ном.", textCharFormat);
	tableCell.set(0,2,"ПІБ", textCharFormat);
	tableCell.set(0,3,"Дні в роб.", textCharFormat);
	tableCell.set(0,4,"Год. в наряді", textCharFormat);
	tableCell.set(0,5,"Замовл / Резерв", textCharFormat);
	tableCell.set(0,6,"Пробіг ЗАГ.", textCharFormat);
	tableCell.set(0,7,"Пробіг ПЛАТН.", textCharFormat);
	tableCell.set(0,8,"Пасажи-ри", textCharFormat);
	tableCell.set(0,9,"Пільгові пас.", textCharFormat);
	tableCell.set(0,10,"Дні в роз.", textCharFormat);
	tableCell.set(0,11,"Виручка ПЛАН.", textCharFormat);
	tableCell.set(0,12,"Виручка ФАКТ.", textCharFormat);
	tableCell.set(0,13,"в т.ч. виручка водія", textCharFormat);
	tableCell.set(0,14,"в т.ч. виручка АС", textCharFormat);
	tableCell.set(0,15,"Відхил.", textCharFormat);
	tableCell.set(0,16,"% викон.", textCharFormat);
	tableCell.set(0,17,"Розхід пальн. по нормі", textCharFormat);
	tableCell.set(0,18,"Розхід пальн. факт.", textCharFormat);
	tableCell.set(0,19,"Запр. гот.", textCharFormat);
	
	int row=0;
	
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignTop);
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignTop);
	
	int dniVRobotiAll=0,
		godNaLiniyiAll=0,
		godPoGrafikuAll=0,
		pasajyryAll=0,
		dniVRozAll=0,
		pilgovykyCountAll=0;
	double probigZagAll=0,
			probigPlatnAll=0,
			vyruchkaPlanAll=0,
			vyruchkaFactAll=0,
			vyruchkaVodAll=0,
			vyruchkaASAll=0,
			palnePoNormiAll=0,
			palneFactAll=0,
			zaprGotivkouAll=0;
	
	QSqlQuery brygQuery;
	brygQuery.exec("SELECT BrygadaNum FROM npr WHERE Posada_id=10 \
						GROUP BY BrygadaNum ORDER BY BrygadaNum");
	while (brygQuery.next()){
		++row;
		table->insertRows(row, 2);
		table->mergeCells(row,0,1,columnCount);
		tableCell.setAlignment(Qt::AlignLeft);
		tableCell.set(row,0,"    Бригада № "+brygQuery.value(0).toString(), textCharFormat_bold);
		
		query.exec("SELECT n.Id, n.Prizv, n.Imia, n.Pobatk, sum(DATEDIFF(date(s.DataZaizdu), date(s.DataVyizdu))+1) AS dniVRob, \
						sum(time_to_sec(if (s.ChasVNaryadi IS NULL, 0,s.ChasVNaryadi )) \
												+ time_to_sec(if (s.ChasVRezervi IS NULL, 0,s.ChasVRezervi ))) AS godNaLiniyi, \
						sum(time_to_sec(if (s.ChasVRezervi IS NULL, 0,s.ChasVRezervi ))) AS godPoGraf, \
						sum(s.ZagalnProbig) AS probigZagaln, \
						sum(s.ZagalnProbig-s.NulyovyiProbig) AS plantyiProbig, sum(s.KilkProdKvytkiv+s.KilkProdKvytkivAutoStat) AS pasajyry, \
						sum(s.curDniVRozyizdi) AS dniVRozizdi, sum(s.PlanNaZminu) AS vyruchkaPlanova, '', \
						sum(s.PilgoviPasajyry) AS pilgPasajyry, sum(s.PlanRozhidPalnogo) AS rozhidPalnogoPoNormi, \
						sum(s.FactRozhidPalnogo) AS rozhidPalnogoFact, sum(s.VartProdKvytkiv) AS vyruchkaFact, \
						sum(s.VartProdKvytkivAutoStat) AS vyruchkaFactAS, sum(s.ZapravkaZaGotivku) AS ZaprGotivkou \
					FROM \
						(SELECT * FROM npr WHERE Posada_id=10 \
							and BrygadaNum="+brygQuery.value(0).toString()+") AS n\
					LEFT JOIN (SELECT shlyahovyiLyst.*, marshruty.TypMarshrutu_id, if(shlyahovyiLyst.TypPoNochivli_id=2,1,0) AS curDniVRozyizdi FROM shlyahovyiLyst \
						LEFT JOIN marshruty ON shlyahovyiLyst.KodMarshrutu_id = marshruty.KodMarshrutu \
							and shlyahovyiLyst.GrafikNum = marshruty.GrafikNum \
							and shlyahovyiLyst.ZminaNum = marshruty.ZminaNum \
						WHERE "+(marshrutType>0?QString("marshruty.TypMarshrutu_id=")+QString::number(marshrutType)+" and ": "")+" \
							date(ToZvitDate) BETWEEN date('"+wMonth.begDate().toString("yyyy-MM-dd")+"') \
								AND date('"+wMonth.endDate().toString("yyyy-MM-dd")+"')) AS s \
					ON n.id=s.VodiyTabelNum_id \
					GROUP BY s.VodiyTabelNum_id, n.Prizv, n.Imia, n.Pobatk \
					ORDER BY n.Naparnyky, n.Prizv, n.Imia, n.Pobatk");
		int wCounter = 0;
		
		int dniVRoboti=0,
			godNaLiniyi=0,
			godPoGrafiku=0,
			pasajyry=0,
			dniVRoz=0,
			pilgovykyCount=0;
		double probigZag=0,
				probigPlatn=0,
				vyruchkaPlan=0,
				vyruchkaFact=0,
				vyruchkaVod=0,
				vyruchkaAS=0,
				palnePoNormi=0,
				palneFact=0,
				zaprGotivkou=0;
		int iVal;
		double dVal;
		
		while (query.next()){
			++row;
			++wCounter;
			table->insertRows(row, 1);
			QSqlRecord rec = query.record();
			QString pib = query.value(1).toString()+QString(" ")+(query.value(2).toString().size()>0?query.value(2).toString().at(0).toUpper()+QString(".")+(query.value(3).toString().size()>0?query.value(3).toString().at(0).toUpper()+QString("."):QString("")):QString(""));
			
			QString str;
			tableCell.setAlignment(Qt::AlignCenter);
			tableCell.set(row,0,wCounter, textCharFormat);
			tableCell.setAlignment(Qt::AlignRight);
			tableCell.setDash(row,1,rec.value(0).toInt(), textCharFormat);
			tableCell.setAlignment(Qt::AlignLeft);
			tableCell.set(row,2,pib, textCharFormat);
			tableCell.setAlignment(Qt::AlignRight);
			iVal = query.value(4).toInt();
			dniVRoboti += iVal;
			tableCell.setDash(row,3,iVal, textCharFormat);
			iVal = query.value(5).toInt()/60;
			godNaLiniyi += iVal;
			tableCell.set(row,4,secToTime(iVal), textCharFormat);
			iVal = query.value(6).toInt()/60;
			godPoGrafiku += iVal;
			tableCell.set(row,5,secToTime(iVal), textCharFormat);
			dVal = query.value(7).toDouble();
			probigZag += dVal;
			tableCell.setDash(row,6,dVal, textCharFormat);
			dVal = query.value(8).toDouble();
			probigPlatn += dVal;
			tableCell.setDash(row,7,dVal, textCharFormat);
			iVal = query.value(9).toInt();
			pasajyry += iVal;
			tableCell.setDash(row,8,iVal, textCharFormat);
			iVal = query.value(13).toInt();
			pilgovykyCount += iVal;
			tableCell.setDash(row,9,iVal, textCharFormat);
			iVal = query.value(10).toInt();
			dniVRoz += iVal;
			tableCell.setDash(row,10,iVal, textCharFormat);
			dVal = query.value(11).toDouble();
			vyruchkaPlan += dVal;
			tableCell.setDash(row,11,dVal, textCharFormat);
			dVal = query.value(16).toDouble() + query.value(17).toDouble();
			vyruchkaFact += dVal;
			tableCell.setDash(row,12,dVal, textCharFormat);
			
			dVal = query.value(16).toDouble();
			vyruchkaVod += dVal;
			tableCell.setDash(row,13,dVal, textCharFormat);
			dVal = query.value(17).toDouble();
			vyruchkaAS += dVal;
			tableCell.setDash(row,14,dVal, textCharFormat);
			
			
			tableCell.setDash(row,15,query.value(16).toDouble() + query.value(17).toDouble() - query.value(11).toDouble(), textCharFormat);
			if (query.value(11).toDouble() != 0)
				tableCell.setDash(row,16,qRound((query.value(16).toDouble() + query.value(17).toDouble())*10000/query.value(11).toDouble())/100.0, textCharFormat);
			else
				tableCell.set(row,16,"-", textCharFormat);
			dVal = query.value(14).toDouble();
			palnePoNormi += dVal;
			tableCell.setDash(row,17,dVal, textCharFormat);
			dVal = query.value(15).toDouble();
			palneFact += dVal;
			tableCell.setDash(row,18,dVal, textCharFormat);
			dVal = query.value(18).toDouble();
			zaprGotivkou += dVal;
			tableCell.setDash(row,19,dVal, textCharFormat);
		}
		++row;
		
		table->mergeCells(row,0,1,3);
		tableCell.setAlignment(Qt::AlignLeft);
		tableCell.set(row,0,"      Всього по Бригаді № "+brygQuery.value(0).toString(), textCharFormat_bold);
		
		tableCell.setAlignment(Qt::AlignRight);
		tableCell.setDash(row,3,dniVRoboti, textCharFormat_bold);
		tableCell.set(row,4,secToTime(godNaLiniyi), textCharFormat_bold);
		tableCell.set(row,5,secToTime(godPoGrafiku), textCharFormat_bold);
		tableCell.setDash(row,6,probigZag, textCharFormat_bold);
		tableCell.setDash(row,7,probigPlatn, textCharFormat_bold);
		tableCell.setDash(row,8,pasajyry, textCharFormat_bold);
		tableCell.setDash(row,9,pilgovykyCount, textCharFormat_bold);
		tableCell.setDash(row,10,dniVRoz, textCharFormat_bold);
		tableCell.setDash(row,11,vyruchkaPlan, textCharFormat_bold);
		tableCell.setDash(row,12,vyruchkaFact, textCharFormat_bold);
		
		tableCell.setDash(row,13,vyruchkaVod, textCharFormat_bold);
		tableCell.setDash(row,14,vyruchkaAS, textCharFormat_bold);
		
		tableCell.setDash(row,15,vyruchkaFact-vyruchkaPlan, textCharFormat_bold);
		if (vyruchkaPlan != 0)
			tableCell.setDash(row,16,qRound(vyruchkaFact*10000/vyruchkaPlan)/100.0, textCharFormat_bold);
		else
			tableCell.set(row,16,"-", textCharFormat_bold);
		tableCell.setDash(row,17,palnePoNormi, textCharFormat_bold);
		tableCell.setDash(row,18,palneFact, textCharFormat_bold);
		tableCell.setDash(row,19,zaprGotivkou, textCharFormat_bold);
		
		dniVRobotiAll += dniVRoboti;
		godNaLiniyiAll += godNaLiniyi;
		godPoGrafikuAll += godPoGrafiku;
		pasajyryAll += pasajyry;
		dniVRozAll += dniVRoz;
		pilgovykyCountAll += pilgovykyCount;
		probigZagAll += probigZag;
		probigPlatnAll += probigPlatn;
		vyruchkaPlanAll += vyruchkaPlan;
		vyruchkaFactAll += vyruchkaFact;
		
		vyruchkaVodAll += vyruchkaVod;
		vyruchkaASAll += vyruchkaAS;
		
		palnePoNormiAll += palnePoNormi;
		palneFactAll += palneFact;
		zaprGotivkouAll += zaprGotivkou;
		
		postup->incPos();
	}
	
	++row;
	
	
	table->mergeCells(row,0,1,3);
	tableCell.setAlignment(Qt::AlignLeft);
	tableCell.set(row,0,"  Всього по підприємству", textCharFormat_bold);
	
	tableCell.setAlignment(Qt::AlignRight);
	tableCell.setDash(row,3,dniVRobotiAll, textCharFormat_bold);
	tableCell.set(row,4,secToTime(godNaLiniyiAll), textCharFormat_bold);
	tableCell.set(row,5,secToTime(godPoGrafikuAll), textCharFormat_bold);
	tableCell.setDash(row,6,probigZagAll, textCharFormat_bold);
	tableCell.setDash(row,7,probigPlatnAll, textCharFormat_bold);
	tableCell.setDash(row,8,pasajyryAll, textCharFormat_bold);
	tableCell.setDash(row,9,pilgovykyCountAll, textCharFormat_bold);
	tableCell.setDash(row,10,dniVRozAll, textCharFormat_bold);
	tableCell.setDash(row,11,vyruchkaPlanAll, textCharFormat_bold);
	tableCell.setDash(row,12,vyruchkaFactAll, textCharFormat_bold);
	
	tableCell.setDash(row,13,vyruchkaVodAll, textCharFormat_bold);
	tableCell.setDash(row,14,vyruchkaASAll, textCharFormat_bold);
	
	tableCell.setDash(row,15,vyruchkaFactAll-vyruchkaPlanAll, textCharFormat_bold);
	if (vyruchkaPlanAll != 0)
		tableCell.setDash(row,16,qRound(vyruchkaFactAll*10000/vyruchkaPlanAll)/100.0, textCharFormat_bold);
	else
		tableCell.set(row,16,"-", textCharFormat_bold);
	
	tableCell.setDash(row,17,palnePoNormiAll, textCharFormat_bold);
	tableCell.setDash(row,18,palneFactAll, textCharFormat_bold);
	tableCell.setDash(row,19,zaprGotivkouAll, textCharFormat_bold);
	
	cursor.movePosition(QTextCursor::End);
	cursor.insertFragment(pidpysy(6, textCharFormat));
	
	printform->printer()->setOrientation(QPrinter::Landscape);
	printform->printer()->setDocName("Зведена відомість по дорожніх листах за місяць");
	printform->printer()->setPageMargins( 7, 10, 4, 20, QPrinter::Millimeter );
	delete postup;
	printform->show();
}
//--------------------utech--------------------utech--------------------utech--------------------
void UPrintDocs_APark::print_zvedenaVidomistPoTupahMarshrutivZaMisyac(QDate vDate, short marshrutType)
{
	printform = new UPrintForm(0, "Зведена відомість по дорожніх листах за місяць");
	
	QSqlQuery query;
	
	UPostupForm *postup = new UPostupForm(0, query.value(0).toInt());
	postup->show();
	
	int columnCount=19;
	UWorkMonth wMonth(vDate.year(), vDate.month());
	
	QTextCursor cursor(printform->document());
	QTextBlockFormat blockFormat;
	QTextTableCell cell;
	QTextCharFormat textCharFormat, textCharFormat_bold, textCharFormat_small;
	QFont fnt = textCharFormat_bold.font();
	fnt.setBold(true);
	textCharFormat_bold.setFont(fnt);
	
	blockFormat.setAlignment( Qt::AlignRight );
	cursor.setBlockFormat( blockFormat );
	textCharFormat.setFontPointSize( 8 );
	cursor.insertText("Документ створено програмою \"Автопарк менеджер\" "+QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm"), textCharFormat);
	blockFormat.setAlignment( Qt::AlignCenter );
	cursor.insertBlock(blockFormat);
	textCharFormat_bold.setFontPointSize( 11 );
	textCharFormat_small.setFontPointSize( 5 );
	cursor.insertText("ЗВЕДЕНА ВІДОМІСТЬ\n по дорожніх листах підприємства \n за період з "+wMonth.begDate().toString("dd.MM.yyyy")+" до "+wMonth.endDate().toString("dd.MM.yyyy")+"р.", textCharFormat_bold);
	blockFormat.setAlignment( Qt::AlignLeft );
	cursor.insertBlock(blockFormat);
	textCharFormat_bold.setFontPointSize( 10 );
	cursor.insertText("Тип маршруту: ", textCharFormat_bold);
	if (marshrutType != 0){
		query.exec("SELECT TypNameMnoj FROM typMarshrutu WHERE id="+QString::number(marshrutType));
		query.seek(0);
		cursor.insertText(query.value(0).toString()+".", textCharFormat_bold);
	}
	else{
		cursor.insertText("УСІ.", textCharFormat_bold);
	}
	cursor.insertBlock(blockFormat);
	cursor.insertText(" ", textCharFormat_small);
	cursor.insertBlock(blockFormat);
	
	//Створення таблиці
	QTextTableFormat tableFormat;
	QVector<QTextLength> constraints;
	constraints << QTextLength(QTextLength::FixedLength, 30);
	constraints << QTextLength(QTextLength::FixedLength, 30);
	constraints << QTextLength(QTextLength::FixedLength, 110);
	constraints << QTextLength(QTextLength::FixedLength, 30);
	constraints << QTextLength(QTextLength::FixedLength, 50);
	constraints << QTextLength(QTextLength::FixedLength, 50);
	constraints << QTextLength(QTextLength::FixedLength, 70);
	constraints << QTextLength(QTextLength::FixedLength, 70);
	constraints << QTextLength(QTextLength::FixedLength, 40);
	constraints << QTextLength(QTextLength::FixedLength, 40);
	constraints << QTextLength(QTextLength::FixedLength, 30);
	constraints << QTextLength(QTextLength::FixedLength, 70);
	constraints << QTextLength(QTextLength::FixedLength, 70);
	constraints << QTextLength(QTextLength::FixedLength, 70);
	constraints << QTextLength(QTextLength::FixedLength, 60);
	constraints << QTextLength(QTextLength::FixedLength, 60);
	constraints << QTextLength(QTextLength::FixedLength, 40);
	constraints << QTextLength(QTextLength::FixedLength, 60);
	constraints << QTextLength(QTextLength::FixedLength, 60);
		
	tableFormat.setColumnWidthConstraints(constraints);
	tableFormat.setCellSpacing(0);
	tableFormat.setCellPadding(1);
	tableFormat.setBorder(0.5);
	tableFormat.setHeaderRowCount(1);
	QTextTable *table = cursor.insertTable(2, columnCount, tableFormat);
	UPopulateCell tableCell(table);
	
	blockFormat.setBottomMargin(0);
	blockFormat.setTopMargin(0);
	
	//Заповнення шапки таблиці
	textCharFormat.setFontPointSize( 8.5 );
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	textCharFormat_bold.setFontPointSize( 8 );
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	
	tableCell.setAlignment(Qt::AlignCenter);
	tableCell.set(0,0,"№ з/п", textCharFormat);
	tableCell.set(0,1,"Код типу", textCharFormat);
	tableCell.set(0,2,"Тип Маршруту", textCharFormat);
	tableCell.set(0,3,"Дні в роб.", textCharFormat);
	tableCell.set(0,4,"Год. в наряді", textCharFormat);
	tableCell.set(0,5,"Замовл / Резерв", textCharFormat);
	tableCell.set(0,6,"Пробіг ЗАГ.", textCharFormat);
	tableCell.set(0,7,"Пробіг ПЛАТН.", textCharFormat);
	tableCell.set(0,8,"Пасажи-ри", textCharFormat);
	tableCell.set(0,9,"Пільгові пас.", textCharFormat);
	tableCell.set(0,10,"Дні в роз.", textCharFormat);
	tableCell.set(0,11,"Виручка ПЛАН.", textCharFormat);
	tableCell.set(0,12,"Виручка ФАКТ.", textCharFormat);
	tableCell.set(0,13,"в т.ч. виручка водія", textCharFormat);
	tableCell.set(0,14,"в т.ч. виручка АС", textCharFormat);
	tableCell.set(0,15,"Відхил.", textCharFormat);
	tableCell.set(0,16,"% викон.", textCharFormat);
	tableCell.set(0,17,"Розхід пальн. по нормі", textCharFormat);
	tableCell.set(0,18,"Розхід пальн. факт.", textCharFormat);
	
	int row=0;
	
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignTop);
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignTop);
	
	int dniVRobotiAll=0,
		godNaLiniyiAll=0,
		godPoGrafikuAll=0,
		pasajyryAll=0,
		dniVRozAll=0,
		pilgovykyCountAll=0;
	double probigZagAll=0,
			probigPlatnAll=0,
			vyruchkaPlanAll=0,
			vyruchkaFactAll=0,
			vyruchkaVodAll=0,
			vyruchkaASAll=0,
			palnePoNormiAll=0,
			palneFactAll=0;
	int wCounter = 0;
	
	if (marshrutType == 0) {
		QSqlQuery brygQuery;
		brygQuery.exec("SELECT id, TypNameMnoj FROM typMarshrutu ORDER BY id");
		while (brygQuery.next()){
			++wCounter;
		
				query.exec("SELECT '', '', '', '', sum(DATEDIFF(date(s.DataZaizdu), date(s.DataVyizdu))+1) AS dniVRob, \
								sum(time_to_sec(if (s.ChasVNaryadi IS NULL, 0,s.ChasVNaryadi )) \
														+ time_to_sec(if (s.ChasVRezervi IS NULL, 0,s.ChasVRezervi ))) AS godNaLiniyi, \
								sum(time_to_sec(if (s.ChasVRezervi IS NULL, 0,s.ChasVRezervi ))) AS godPoGraf, \
								sum(s.ZagalnProbig) AS probigZagaln, \
								sum(s.ZagalnProbig-s.NulyovyiProbig) AS plantyiProbig, sum(s.KilkProdKvytkiv+s.KilkProdKvytkivAutoStat) AS pasajyry, \
								sum(s.curDniVRozyizdi) AS dniVRozizdi, sum(s.PlanNaZminu) AS vyruchkaPlanova, '', \
								sum(s.PilgoviPasajyry) AS pilgPasajyry, sum(s.PlanRozhidPalnogo) AS rozhidPalnogoPoNormi, \
								sum(s.FactRozhidPalnogo) AS rozhidPalnogoFact, sum(s.VartProdKvytkiv) AS vyruchkaFact, sum(s.VartProdKvytkivAutoStat) AS vyruchkaFactAS \
							FROM \
								(SELECT shlyahovyiLyst.*, marshruty.TypMarshrutu_id, if(shlyahovyiLyst.TypPoNochivli_id=2,1,0) AS curDniVRozyizdi FROM shlyahovyiLyst \
								LEFT JOIN marshruty ON shlyahovyiLyst.KodMarshrutu_id = marshruty.KodMarshrutu \
									and shlyahovyiLyst.GrafikNum = marshruty.GrafikNum \
									and shlyahovyiLyst.ZminaNum = marshruty.ZminaNum \
								WHERE marshruty.TypMarshrutu_id="+brygQuery.value(0).toString()+" and \
									date(ToZvitDate) BETWEEN date('"+wMonth.begDate().toString("yyyy-MM-dd")+"') \
										AND date('"+wMonth.endDate().toString("yyyy-MM-dd")+"')) AS s");
		
			int iVal;
			double dVal;
		
			while (query.next()){
				++row;
				table->insertRows(row, 1);
				QSqlRecord rec = query.record();
			
				QString str;
				tableCell.setAlignment(Qt::AlignCenter);
				tableCell.set(row,0,wCounter, textCharFormat);
				tableCell.setAlignment(Qt::AlignRight);
				tableCell.setDash(row,1,brygQuery.value(0).toInt(), textCharFormat);
				tableCell.setAlignment(Qt::AlignLeft);
				tableCell.set(row,2,brygQuery.value(1).toString(), textCharFormat);
				tableCell.setAlignment(Qt::AlignRight);
				iVal = query.value(4).toInt();
				dniVRobotiAll += iVal;
				tableCell.setDash(row,3,iVal, textCharFormat);
				iVal = query.value(5).toInt()/60;
				godNaLiniyiAll += iVal;
				tableCell.set(row,4,secToTime(iVal), textCharFormat);
				iVal = query.value(6).toInt()/60;
				godPoGrafikuAll += iVal;
				tableCell.set(row,5,secToTime(iVal), textCharFormat);
				dVal = query.value(7).toDouble();
				probigZagAll += dVal;
				tableCell.setDash(row,6,dVal, textCharFormat);
				dVal = query.value(8).toDouble();
				probigPlatnAll += dVal;
				tableCell.setDash(row,7,dVal, textCharFormat);
				iVal = query.value(9).toInt();
				pasajyryAll += iVal;
				tableCell.setDash(row,8,iVal, textCharFormat);
				iVal = query.value(13).toInt();
				pilgovykyCountAll += iVal;
				tableCell.setDash(row,9,iVal, textCharFormat);
				iVal = query.value(10).toInt();
				dniVRozAll += iVal;
				tableCell.setDash(row,10,iVal, textCharFormat);
				dVal = query.value(11).toDouble();
				vyruchkaPlanAll += dVal;
				tableCell.setDash(row,11,dVal, textCharFormat);
				dVal = query.value(16).toDouble() + query.value(17).toDouble();
				vyruchkaFactAll += dVal;
				tableCell.setDash(row,12,dVal, textCharFormat);
			
				dVal = query.value(16).toDouble();
				vyruchkaVodAll += dVal;
				tableCell.setDash(row,13,dVal, textCharFormat);
				dVal = query.value(17).toDouble();
				vyruchkaASAll += dVal;
				tableCell.setDash(row,14,dVal, textCharFormat);
			
				tableCell.setDash(row,15,query.value(16).toDouble() + query.value(17).toDouble() - query.value(11).toDouble(), textCharFormat);
				if (query.value(11).toDouble() != 0)
					tableCell.setDash(row,16,qRound((query.value(16).toDouble() + query.value(17).toDouble())*10000/query.value(11).toDouble())/100.0, textCharFormat);
				else
					tableCell.set(row,16,"-", textCharFormat);
				dVal = query.value(14).toDouble();
				palnePoNormiAll += dVal;
				tableCell.setDash(row,17,dVal, textCharFormat);
				dVal = query.value(15).toDouble();
				palneFactAll += dVal;
				tableCell.setDash(row,18,dVal, textCharFormat);
			}
		}
		++row;
	
		table->mergeCells(row,0,1,3);
		tableCell.setAlignment(Qt::AlignLeft);
		tableCell.set(row,0,"  Всього по підприємству", textCharFormat_bold);
		
		tableCell.setAlignment(Qt::AlignRight);
		tableCell.setDash(row,3,dniVRobotiAll, textCharFormat_bold);
		tableCell.set(row,4,secToTime(godNaLiniyiAll), textCharFormat_bold);
		tableCell.set(row,5,secToTime(godPoGrafikuAll), textCharFormat_bold);
		tableCell.setDash(row,6,probigZagAll, textCharFormat_bold);
		tableCell.setDash(row,7,probigPlatnAll, textCharFormat_bold);
		tableCell.setDash(row,8,pasajyryAll, textCharFormat_bold);
		tableCell.setDash(row,9,pilgovykyCountAll, textCharFormat_bold);
		tableCell.setDash(row,10,dniVRozAll, textCharFormat_bold);
		tableCell.setDash(row,11,vyruchkaPlanAll, textCharFormat_bold);
		tableCell.setDash(row,12,vyruchkaFactAll, textCharFormat_bold);
	
		tableCell.setDash(row,13,vyruchkaVodAll, textCharFormat_bold);
		tableCell.setDash(row,14,vyruchkaASAll, textCharFormat_bold);
	
		tableCell.setDash(row,15,vyruchkaFactAll-vyruchkaPlanAll, textCharFormat_bold);
		if (vyruchkaPlanAll != 0) 
			tableCell.setDash(row,16,qRound(vyruchkaFactAll*10000/vyruchkaPlanAll)/100.0, textCharFormat_bold);
		else 
			tableCell.set(row,16,"-", textCharFormat_bold);
			tableCell.setDash(row,17,palnePoNormiAll, textCharFormat_bold);
			tableCell.setDash(row,18,palneFactAll, textCharFormat_bold);
	
			cursor.movePosition(QTextCursor::End);
			cursor.insertFragment(pidpysy(6, textCharFormat, QPrinter::Landscape));
	}
	else { 
		QSqlQuery brygQuery;
		brygQuery.exec("SELECT id, TypNameMnoj FROM typMarshrutu WHERE id = "+QString::number(marshrutType)+" ");
		while (brygQuery.next()){
			++wCounter;
		
				query.exec("SELECT '', '', n.KodMarshrutu, n.MarshrutNapryamok, \
									sum(DATEDIFF(date(s.DataZaizdu), date(s.DataVyizdu))+1) AS dniVRob,\
									sum(time_to_sec(if (s.ChasVNaryadi IS NULL, 0,s.ChasVNaryadi ))\
										+ time_to_sec(if (s.ChasVRezervi IS NULL, 0,s.ChasVRezervi ))) AS godNaLiniyi,\
									sum(time_to_sec(if (s.ChasVRezervi IS NULL, 0,s.ChasVRezervi ))) AS godPoGraf,\
									sum(s.ZagalnProbig) AS probigZagaln,\
									sum(s.ZagalnProbig-s.NulyovyiProbig) AS plantyiProbig, sum(s.KilkProdKvytkiv+s.KilkProdKvytkivAutoStat) AS pasajyry,\
									sum(s.curDniVRozyizdi) AS dniVRozizdi, sum(s.PlanNaZminu) AS vyruchkaPlanova, '',\
									sum(s.PilgoviPasajyry) AS pilgPasajyry, sum(s.PlanRozhidPalnogo) AS rozhidPalnogoPoNormi,\
									sum(s.FactRozhidPalnogo) AS rozhidPalnogoFact, sum(s.VartProdKvytkiv) AS vyruchkaFact,\
									sum(s.VartProdKvytkivAutoStat) AS vyruchkaFactAS, sum(s.ZapravkaZaGotivku) AS ZaprGotivkou\
							FROM\
								(SELECT * FROM marshruty WHERE TypMarshrutu_Id="+QString::number(marshrutType)+") AS n\
								LEFT JOIN (SELECT shlyahovyiLyst.*, marshruty.TypMarshrutu_id, if(shlyahovyiLyst.TypPoNochivli_id=2,1,0) AS curDniVRozyizdi FROM shlyahovyiLyst\
								LEFT JOIN marshruty ON shlyahovyiLyst.KodMarshrutu_id = marshruty.KodMarshrutu\
								and shlyahovyiLyst.GrafikNum = marshruty.GrafikNum\
								and shlyahovyiLyst.ZminaNum = marshruty.ZminaNum\
							WHERE\
								marshruty.TypMarshrutu_id="+QString::number(marshrutType)+" and\
								date(ToZvitDate) BETWEEN date('"+wMonth.begDate().toString("yyyy-MM-dd")+"') \
								AND date('"+wMonth.endDate().toString("yyyy-MM-dd")+"')) AS s\
								ON n.KodMarshrutu=s.KodMarshrutu_id\
								and s.GrafikNum = n.GrafikNum\
								and s.ZminaNum = n.ZminaNum\
								GROUP BY n.KodMarshrutu \
								ORDER BY n.KodMarshrutu");
		
			int iVal;
			double dVal;
		
			while (query.next()){
				++row;
				table->insertRows(row, 1);
				QSqlRecord rec = query.record();
			
			QString str;
				tableCell.setAlignment(Qt::AlignCenter);
				tableCell.set(row,0,wCounter++, textCharFormat);
				tableCell.setAlignment(Qt::AlignRight);
				tableCell.setDash(row,1,query.value(2).toInt(), textCharFormat);
				tableCell.setAlignment(Qt::AlignLeft);
				tableCell.set(row,2,query.value(3).toString(), textCharFormat);
				tableCell.setAlignment(Qt::AlignRight);
				iVal = query.value(4).toInt();
				dniVRobotiAll += iVal;
				tableCell.setDash(row,3,iVal, textCharFormat);
				iVal = query.value(5).toInt()/60;
				godNaLiniyiAll += iVal;
				tableCell.set(row,4,secToTime(iVal), textCharFormat);
				iVal = query.value(6).toInt()/60;
				godPoGrafikuAll += iVal;
				tableCell.set(row,5,secToTime(iVal), textCharFormat);
				dVal = query.value(7).toDouble();
				probigZagAll += dVal;
				tableCell.setDash(row,6,dVal, textCharFormat);
				dVal = query.value(8).toDouble();
				probigPlatnAll += dVal;
				tableCell.setDash(row,7,dVal, textCharFormat);
				iVal = query.value(9).toInt();
				pasajyryAll += iVal;
				tableCell.setDash(row,8,iVal, textCharFormat);
				iVal = query.value(13).toInt();
				pilgovykyCountAll += iVal;
				tableCell.setDash(row,9,iVal, textCharFormat);
				iVal = query.value(10).toInt();
				dniVRozAll += iVal;
				tableCell.setDash(row,10,iVal, textCharFormat);
				dVal = query.value(11).toDouble();
				vyruchkaPlanAll += dVal;
				tableCell.setDash(row,11,dVal, textCharFormat);
				dVal = query.value(16).toDouble() + query.value(17).toDouble();
				vyruchkaFactAll += dVal;
				tableCell.setDash(row,12,dVal, textCharFormat);
			
				dVal = query.value(16).toDouble();
				vyruchkaVodAll += dVal;
				tableCell.setDash(row,13,dVal, textCharFormat);
				dVal = query.value(17).toDouble();
				vyruchkaASAll += dVal;
				tableCell.setDash(row,14,dVal, textCharFormat);
			
				tableCell.setDash(row,15,query.value(16).toDouble() + query.value(17).toDouble() - query.value(11).toDouble(), textCharFormat);
				if (query.value(11).toDouble() != 0)
					tableCell.setDash(row,16,qRound((query.value(16).toDouble() + query.value(17).toDouble())*10000/query.value(11).toDouble())/100.0, textCharFormat);
				else
					tableCell.set(row,16,"-", textCharFormat);
				dVal = query.value(14).toDouble();
				palnePoNormiAll += dVal;
				tableCell.setDash(row,17,dVal, textCharFormat);
				dVal = query.value(15).toDouble();
				palneFactAll += dVal;
				tableCell.setDash(row,18,dVal, textCharFormat);
			}
		}
		++row;
	
		table->mergeCells(row,0,1,3);
		tableCell.setAlignment(Qt::AlignLeft);
		tableCell.set(row,0,"  Всього по маршруту", textCharFormat_bold);
	
		
		tableCell.setAlignment(Qt::AlignRight);
		tableCell.setDash(row,3,dniVRobotiAll, textCharFormat_bold);
		tableCell.set(row,4,secToTime(godNaLiniyiAll), textCharFormat_bold);
		tableCell.set(row,5,secToTime(godPoGrafikuAll), textCharFormat_bold);
		tableCell.setDash(row,6,probigZagAll, textCharFormat_bold);
		tableCell.setDash(row,7,probigPlatnAll, textCharFormat_bold);
		tableCell.setDash(row,8,pasajyryAll, textCharFormat_bold);
		tableCell.setDash(row,9,pilgovykyCountAll, textCharFormat_bold);
		tableCell.setDash(row,10,dniVRozAll, textCharFormat_bold);
		tableCell.setDash(row,11,vyruchkaPlanAll, textCharFormat_bold);
		tableCell.setDash(row,12,vyruchkaFactAll, textCharFormat_bold);
	
		tableCell.setDash(row,13,vyruchkaVodAll, textCharFormat_bold);
		tableCell.setDash(row,14,vyruchkaASAll, textCharFormat_bold);
	
		tableCell.setDash(row,15,vyruchkaFactAll-vyruchkaPlanAll, textCharFormat_bold);
		if (vyruchkaPlanAll != 0) 
			tableCell.setDash(row,16,qRound(vyruchkaFactAll*10000/vyruchkaPlanAll)/100.0, textCharFormat_bold);
		else 
			tableCell.set(row,16,"-", textCharFormat_bold);
			tableCell.setDash(row,17,palnePoNormiAll, textCharFormat_bold);
			tableCell.setDash(row,18,palneFactAll, textCharFormat_bold);
	
			cursor.movePosition(QTextCursor::End);
			cursor.insertFragment(pidpysy(6, textCharFormat, QPrinter::Landscape));
			
	}
	
			printform->printer()->setOrientation(QPrinter::Landscape);
			printform->printer()->setDocName("Зведена відомість по дорожніх листах за місяць");
			printform->printer()->setPageMargins( 7, 10, 4, 20, QPrinter::Millimeter );
			
			delete postup;
			
			printform->show();
		
	
}
//--------------------utech--------------------utech--------------------utech--------------------
void UPrintDocs_APark::print_zvitProZdanuVyruchkuGotivkoyuZaMisyac(QDate vDate)
{
	printform = new UPrintForm(0, "Звіт про здану виручку готівкою за місяць");
	
	QSqlQuery query;
	int columnCount=5;
	UWorkMonth wMonth(vDate.year(), vDate.month());
	
	QTextCursor cursor(printform->document());
	QTextBlockFormat blockFormat;
	QTextTableCell cell;
	QTextCharFormat textCharFormat, textCharFormat_bold, textCharFormat_small;
	QFont fnt = textCharFormat_bold.font();
	fnt.setBold(true);
	textCharFormat_bold.setFont(fnt);
	
	blockFormat.setAlignment( Qt::AlignRight );
	cursor.setBlockFormat( blockFormat );
	textCharFormat.setFontPointSize( 8 );
	cursor.insertText("Документ створено програмою \"Автопарк менеджер\" "+QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm"), textCharFormat);
	blockFormat.setAlignment( Qt::AlignCenter );
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	textCharFormat_bold.setFontPointSize( 12 );
	textCharFormat_small.setFontPointSize( 5 );
	cursor.insertText("ЗВІТ\n про здану виручку готівкою водіями підприємства "+OrganizName()+"\n за період з "+wMonth.begDate().toString("dd.MM.yyyy")+" до "+wMonth.endDate().toString("dd.MM.yyyy")+"р.", textCharFormat_bold);
	blockFormat.setAlignment( Qt::AlignLeft );
	textCharFormat_bold.setFontPointSize( 11 );
	cursor.insertBlock(blockFormat);
	cursor.insertText(" ", textCharFormat_small);
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	
	//Створення таблиці
	QTextTableFormat tableFormat;
	QVector<QTextLength> constraints;
	constraints << QTextLength(QTextLength::FixedLength, 80);
	constraints << QTextLength(QTextLength::FixedLength, 80);
	constraints << QTextLength(QTextLength::FixedLength, 170);
	constraints << QTextLength(QTextLength::FixedLength, 140);
	constraints << QTextLength(QTextLength::FixedLength, 140);
		
	tableFormat.setColumnWidthConstraints(constraints);
	tableFormat.setCellSpacing(0);
	tableFormat.setCellPadding(2);
	tableFormat.setHeaderRowCount(1);
	QTextTable *table = cursor.insertTable(2, columnCount, tableFormat);
	UPopulateCell tableCell(table);
	
	blockFormat.setBottomMargin(0);
	blockFormat.setTopMargin(0);
	
	//Заповнення шапки таблиці
	textCharFormat.setFontPointSize( 10 );
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	textCharFormat_bold.setFontPointSize( 9.5 );
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	
	tableCell.setAlignment(Qt::AlignCenter);
	tableCell.set(0,0,"Бригада", textCharFormat);
	tableCell.set(0,1,"Код типу", textCharFormat);
	tableCell.set(0,2,"Тип Маршруту", textCharFormat);
	tableCell.set(0,3,"Сума, грн.", textCharFormat);
	tableCell.set(0,4,"К-сть пас.", textCharFormat);
	
	int row=0;
	int iVal;
	double dVal;
	QHash<int, double> sumAll;
	QHash<int, int> countAll;
	int margeRowsCount=0;
	
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignTop);
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignTop);
	
	QSqlQuery mTypeQuery("SELECT Id, TypNameMnoj, VidsPodatkuPoVyruchci FROM typmarshrutu ORDER BY Id");
	
	QSqlQuery brygQuery;
	brygQuery.exec("SELECT BrygadaNum FROM npr WHERE Posada_id=10 \
						GROUP BY BrygadaNum ORDER BY BrygadaNum");
	while (brygQuery.next()){
		mTypeQuery.seek(-1);
		margeRowsCount=0;
		while (mTypeQuery.next()){
			margeRowsCount++;
		
			query.exec("SELECT sum(s.VartProdKvytkiv+s.VartProdKvytkivAutoStat) AS vyruchkaFact, \
							sum(s.KilkProdKvytkiv+s.KilkProdKvytkivAutoStat) AS pasajyry \
						FROM \
							(SELECT * FROM npr WHERE Posada_id=10 \
								and BrygadaNum="+brygQuery.value(0).toString()+") AS n\
						LEFT JOIN (SELECT shlyahovyiLyst.*, marshruty.TypMarshrutu_id FROM shlyahovyiLyst \
							LEFT JOIN marshruty ON shlyahovyiLyst.KodMarshrutu_id = marshruty.KodMarshrutu \
								and shlyahovyiLyst.GrafikNum = marshruty.GrafikNum \
								and shlyahovyiLyst.ZminaNum = marshruty.ZminaNum \
							WHERE marshruty.TypMarshrutu_id="+mTypeQuery.value(0).toString()+" and \
								date(ToZvitDate) BETWEEN date('"+wMonth.begDate().toString("yyyy-MM-dd")+"') \
									AND date('"+wMonth.endDate().toString("yyyy-MM-dd")+"')) AS s \
						ON n.id=s.VodiyTabelNum_id");
			query.next();
			
			++row;
			table->insertRows(row, 1);
			
			tableCell.setAlignment(Qt::AlignCenter);
			//"Код типу"
			tableCell.set(row,1,mTypeQuery.value(0).toString(), textCharFormat);
			//"Тип Маршруту"
			tableCell.setAlignment(Qt::AlignLeft);
			tableCell.set(row,2,mTypeQuery.value(1).toString(), textCharFormat);
			//"Сума, грн."
			tableCell.setAlignment(Qt::AlignRight);
			dVal = query.value(0).toDouble();
			sumAll[mTypeQuery.value(0).toInt()] += dVal;
			tableCell.setDash(row,3,dVal, textCharFormat);
			//"К-сть пас."
			iVal = query.value(1).toInt();
			countAll[mTypeQuery.value(0).toInt()] += iVal;
			tableCell.setDash(row,4,iVal, textCharFormat);
		}
		table->mergeCells(row-margeRowsCount+1,0,margeRowsCount,1);
		
		tableCell.setAlignment(Qt::AlignCenter);
		//"Бригада"
		tableCell.set(row-margeRowsCount+1,0,brygQuery.value(0).toString(), textCharFormat);
	}
	
	//Підсумок по підприєвству
	margeRowsCount=0;
	mTypeQuery.seek(-1);
	while (mTypeQuery.next()){
		++row;
		++margeRowsCount;
		table->insertRows(row, 1);
		
		//"Тип Маршруту"
		tableCell.setAlignment(Qt::AlignLeft);
		tableCell.set(row,2,mTypeQuery.value(1).toString(), textCharFormat_bold);
		//"Сума, грн."
		tableCell.setAlignment(Qt::AlignRight);
		tableCell.setDash(row,3,sumAll[mTypeQuery.value(0).toInt()], textCharFormat_bold);
		//"К-сть пас."
		tableCell.setDash(row,4,countAll[mTypeQuery.value(0).toInt()], textCharFormat_bold);
	}
	table->mergeCells(row-margeRowsCount+1,0,margeRowsCount,2);
		
	tableCell.setAlignment(Qt::AlignCenter);
	tableCell.set(row-margeRowsCount+1,0,"Разом", textCharFormat_bold);
	
	//Розрахунок податку
	margeRowsCount=0;
	mTypeQuery.seek(-1);
	double sumaDoOplaty=0;
	while (mTypeQuery.next()){
		++row;
		++margeRowsCount;
		table->insertRows(row, 1);
		
		//"Тип Маршруту"
		tableCell.setAlignment(Qt::AlignLeft);
		tableCell.set(row,2,mTypeQuery.value(1).toString()+" ["+QString::number(mTypeQuery.value(2).toDouble()).replace('.',',')+"%]", textCharFormat_bold);
		//"Сума, грн."
		tableCell.setAlignment(Qt::AlignRight);
		double groupVyrSum = sumAll[mTypeQuery.value(0).toInt()];
		double groupKoef = mTypeQuery.value(2).toDouble()/100.0;
		dVal = uDToM( groupVyrSum / 1.2 / (1 + groupKoef) * groupKoef );
		sumaDoOplaty += dVal;
		tableCell.setDash(row,3,dVal, textCharFormat_bold);
		//"К-сть пас."
		tableCell.set(row,4,"-", textCharFormat_bold);
	}
	table->mergeCells(row-margeRowsCount+1,0,margeRowsCount,2);
		
	tableCell.setAlignment(Qt::AlignLeft);
	tableCell.set(row-margeRowsCount+1,0,"Сума до оплати по:", textCharFormat_bold);
	
	//Всього до оплати
	row++;
	table->mergeCells(row,0,1,3);
	tableCell.setAlignment(Qt::AlignLeft);
	tableCell.set(row,0,"Всього до оплати", textCharFormat);
	//"Сума, грн."
	tableCell.setAlignment(Qt::AlignRight);
	tableCell.setDash(row,3,sumaDoOplaty, textCharFormat_bold);
	//"К-сть пас."
	tableCell.set(row,4,"-", textCharFormat_bold);
	
	cursor.movePosition(QTextCursor::End);
	blockFormat.setAlignment( Qt::AlignLeft );
	cursor.insertFragment(pidpysy(7, textCharFormat));
	
	printform->printer()->setDocName("Звіт про здану виручку готівкою за місяць");
	printform->printer()->setPageMargins( 15, 10, 10, 5, QPrinter::Millimeter );
	printform->show();
}
//--------------------utech--------------------utech--------------------utech--------------------
void UPrintDocs_APark::print_KartkyOblikuVykonPlanu(QDate vDate, QList<int> vodiyiList)
{
	UPostupForm *postupForm = new UPostupForm(0, vodiyiList.size());
	postupForm->show();
	
	printform = new UPrintForm(0, ((vodiyiList.size()==1) ? "Картка" : "Картки") +QString(" обліку виконання плану"));
	
	QTextCursor cursor(printform->document());
	
	QTextBlockFormat pageEndBlockFormat, pageNonEndBlockFormat;
	pageEndBlockFormat.setPageBreakPolicy(QTextFormat::PageBreak_AlwaysAfter);
	pageEndBlockFormat.setAlignment( Qt::AlignRight );
	pageNonEndBlockFormat.setAlignment( Qt::AlignRight );
	cursor.setBlockFormat(pageEndBlockFormat);
	bool firstCard=true;
	
	foreach (int id, vodiyiList){
		if (!firstCard){
			cursor.insertBlock(pageEndBlockFormat);
			cursor.insertBlock(pageNonEndBlockFormat);
		}
		cursor.insertFragment(create_kartkuOblikuVykonPlanu(vDate, id));
		
		postupForm->inc_pos();
		firstCard=false;
	}
	
	printform->printer()->setDocName(((vodiyiList.size()==1) ? "Картка" : "Картки") +QString(" обліку виконання плану"));
	printform->printer()->setPageMargins( 10, 10, 10, 5, QPrinter::Millimeter );
	printform->show();
	delete postupForm;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UPrintDocs_APark::print_KartkyRobotyVodiyiv(QDate vDate, QList<int> vodiyiList)
{
	UPostupForm *postupForm = new UPostupForm(0, vodiyiList.size());
	postupForm->show();
	
	printform = new UPrintForm(0, ((vodiyiList.size()==1) ? "Картка роботи водія" : "Картки роботи водіїв"));
	
	QTextCursor cursor(printform->document());
	
	QTextBlockFormat pageEndBlockFormat, pageNonEndBlockFormat;
	pageEndBlockFormat.setPageBreakPolicy(QTextFormat::PageBreak_AlwaysAfter);
	pageEndBlockFormat.setAlignment( Qt::AlignRight );
	pageNonEndBlockFormat.setAlignment( Qt::AlignRight );
	cursor.setBlockFormat(pageEndBlockFormat);
	bool firstCard=true;
	
	foreach (int id, vodiyiList){
		if (!firstCard){
			cursor.insertBlock(pageEndBlockFormat);
			cursor.insertBlock(pageNonEndBlockFormat);
		}
		cursor.insertFragment(create_kartkaRobotyVodiya(vDate, id));
		
		postupForm->inc_pos();
		firstCard=false;
	}
	
	printform->printer()->setDocName(((vodiyiList.size()==1) ? "Картка роботи водія" : "Картки роботи водіїв"));
	printform->printer()->setOrientation(QPrinter::Landscape);
	printform->printer()->setPageMargins( 7, 5, 4, 10, QPrinter::Millimeter );
	printform->show();
	delete postupForm;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UPrintDocs_APark::print_RozrahSumyKompensPoPilgah(int pilgId)
{
	printform = new UPrintForm(0, "Розрахунок суми за пільговий проїзд");
	
	QSqlQuery query;
	query.exec("SELECT CurDate, VyruchkaZagalna, TaryfZaPasajKm, KilkistPlatnPasaj, \
						Koef, KilkistPilgovykiv, KilkistVrahPilgovykiv \
				FROM pilgyAParkPokazn WHERE id="+QString::number(pilgId));
	query.seek(0);
	
	QTextCursor cursor(printform->document());
	QTextBlockFormat blockFormat;
	QTextTableCell cell;
	QTextCharFormat textCharFormat, textCharFormat_bold, textCharFormat_small;
	QFont fnt = textCharFormat_bold.font();
	fnt.setBold(true);
	textCharFormat_bold.setFont(fnt);
	
	blockFormat.setAlignment( Qt::AlignLeft );
	cursor.setBlockFormat( blockFormat );
	textCharFormat.setFontPointSize( 8 );
	cursor.insertText("Документ створено програмою \"Автопарк менеджер\" "+QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm")+". © Компанія \"УТЕХ\", веб: www.utech.com.ua", textCharFormat);
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	
	QTextTableFormat tableFormat;
	QVector<QTextLength> constraints;
	constraints << QTextLength(QTextLength::FixedLength, 490);
	constraints << QTextLength(QTextLength::FixedLength, 280);
		
	tableFormat.setColumnWidthConstraints(constraints);
	tableFormat.setCellSpacing(0);
	tableFormat.setCellPadding(1);
	tableFormat.setBorder(0);
	tableFormat.setHeaderRowCount(1);
	QTextTable *table = cursor.insertTable(1, 2, tableFormat);
	UPopulateCell tableCell(table);
	
	blockFormat.setBottomMargin(0);
	blockFormat.setTopMargin(0);
	
	//Заповнення шапки таблиці
	textCharFormat.setFontPointSize( 9 );
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	
	tableCell.setAlignment(Qt::AlignLeft);
	tableCell.set(0,1,"		Додаток 1\nДо Тимчасового порядку проведення\nрозрахунків з компенсаційних витрат\nза пільговий проїзд окремих\nкатегорій громадян\n", textCharFormat);
	
	cursor.movePosition(QTextCursor::End);
	blockFormat.setAlignment( Qt::AlignCenter );
	
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	textCharFormat_bold.setFontPointSize( 13 );
	textCharFormat.setFontPointSize( 12 );
	textCharFormat_small.setFontPointSize( 5 );
	cursor.insertText("РОЗРАХУНОК", textCharFormat_bold);
	textCharFormat_bold.setFontPointSize( 12 );
	cursor.insertBlock(blockFormat);
	cursor.insertText("суми компенсації за пільговий проїзд окремих категорій", textCharFormat_bold);
	cursor.insertBlock(blockFormat);
	cursor.insertText("громадян на приміських маршрутах", textCharFormat_bold);
	cursor.insertBlock(blockFormat);
	cursor.insertText("Самбірського району", textCharFormat_bold);
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	cursor.insertText("по "+OrganizShortName(), textCharFormat);
	blockFormat.setAlignment( Qt::AlignLeft );
	cursor.insertBlock(blockFormat);
	cursor.insertText("  за "+monthlist.at(query.value(0).toDate().month()-1)+" "+QString::number(query.value(0).toDate().year())+" року", textCharFormat);
	blockFormat.setAlignment( Qt::AlignLeft );
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	
	//Створення таблиці
	constraints.clear();
	constraints << QTextLength(QTextLength::FixedLength, 70);
	constraints << QTextLength(QTextLength::FixedLength, 70);
	constraints << QTextLength(QTextLength::FixedLength, 70);
	constraints << QTextLength(QTextLength::FixedLength, 70);
	constraints << QTextLength(QTextLength::FixedLength, 70);
	constraints << QTextLength(QTextLength::FixedLength, 70);
	constraints << QTextLength(QTextLength::FixedLength, 70);
	constraints << QTextLength(QTextLength::FixedLength, 70);
	constraints << QTextLength(QTextLength::FixedLength, 70);
	constraints << QTextLength(QTextLength::FixedLength, 70);
		
	tableFormat.setColumnWidthConstraints(constraints);
	tableFormat.setCellSpacing(0);
	tableFormat.setCellPadding(1);
	tableFormat.setHeaderRowCount(1);
	tableFormat.setBorder(0.5);
	tableFormat.setBorderBrush(QBrush(Qt::black));
	table = cursor.insertTable(3, 10, tableFormat);
	tableCell.setTextTable(table);
	
	blockFormat.setBottomMargin(0);
	blockFormat.setTopMargin(0);
	
	//Заповнення шапки таблиці
	textCharFormat.setFontPointSize( 10 );
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	textCharFormat_bold.setFontPointSize( 10 );
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	
	tableCell.setAlignment(Qt::AlignCenter);
	tableCell.set(0,0,"Виручка від переве-зення пасажирів, що оплачують проїзд  (грн.)", textCharFormat);
	tableCell.set(0,1,"Тариф за 1пас./км. (грн.)", textCharFormat);
	tableCell.set(0,2,"Кількість переве-зених пасажирів, що оплачують проїзд (чол.)", textCharFormat);
	tableCell.set(0,3,"Середня дальність поїздки, км. (гр.1/гр.2/ гр.3)", textCharFormat);
	tableCell.set(0,4,"Середня вартість поїздки 1 пасажира грн. (гр.2*гр.4)", textCharFormat);
	tableCell.set(0,5,"Коефіцієнт співвідно-шення затверд-жений у районі", textCharFormat);
	tableCell.set(0,6,"Кількість переве-зених пільговиків з врахуван-ням коефіцієнта статистики (чол.) (гр.3*гр.6)", textCharFormat);
	tableCell.set(0,7,"Кількість переве-зених пільговиків за даними перевізника (чол.)", textCharFormat);
	tableCell.set(0,8,"Кількість пільгови-ків, що прий-мається до розрахунку (менше значення) (чол.)", textCharFormat);
	tableCell.set(0,9,"Сума втрат доходів, грн. (гр.5*гр.9)", textCharFormat);
	tableCell.setAlignment(Qt::AlignCenter);
	tableCell.set(1,0,"1", textCharFormat);
	tableCell.set(1,1,"2", textCharFormat);
	tableCell.set(1,2,"3", textCharFormat);
	tableCell.set(1,3,"4", textCharFormat);
	tableCell.set(1,4,"5", textCharFormat);
	tableCell.set(1,5,"6", textCharFormat);
	tableCell.set(1,6,"7", textCharFormat);
	tableCell.set(1,7,"8", textCharFormat);
	tableCell.set(1,8,"9", textCharFormat);
	tableCell.set(1,9,"10", textCharFormat);
	
	double col1, col2, col4, col5, col6, col10;
	int col3, col7, col8, col9;
	col1 = query.value(1).toDouble();
	col2 = query.value(2).toDouble();
	col3 = query.value(3).toInt();
	if (col2!=0 && col3!=0){
		col4 = col1 / col2/ col3;
		col4 = qRound(col4 * 1000) / 1000.0;
	}
	else
		col4 = 0;
	col5 = qRound(col2 * col4 * 100) / 100.0;
	col6 = query.value(4).toDouble();
	col7 = qRound(col3 * col6);
	col8 = query.value(5).toInt();
	col9 = query.value(6).toInt();
	col10 = qRound(col5 * col9 * 100) / 100.0;
	
	tableCell.setAlignment(Qt::AlignCenter);
	tableCell.setDash(2,0,col1, textCharFormat);
	tableCell.setDash(2,1,col2, textCharFormat);
	tableCell.setDash(2,2,col3, textCharFormat);
	tableCell.set(2,3,QString::number(col4).replace('.',','), textCharFormat);
	tableCell.setDash(2,4,col5, textCharFormat);
	tableCell.set(2,5,QString::number(col6).replace('.',','), textCharFormat);
	tableCell.setDash(2,6,col7, textCharFormat);
	tableCell.setDash(2,7,col8, textCharFormat);
	tableCell.setDash(2,8,col9, textCharFormat);
	tableCell.setDash(2,9,col10, textCharFormat);
	
	cursor.movePosition(QTextCursor::End);
	blockFormat.setAlignment( Qt::AlignLeft );
	
	/*
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	
	//Створення таблиці підписів
	constraints.clear();
	constraints << QTextLength(QTextLength::FixedLength, 250);
	constraints << QTextLength(QTextLength::FixedLength, 220);
	constraints << QTextLength(QTextLength::FixedLength, 220);
		
	tableFormat.setColumnWidthConstraints(constraints);
	tableFormat.setCellSpacing(0);
	tableFormat.setCellPadding(1);
	tableFormat.setBorder(0);
	table = cursor.insertTable(5, 3, tableFormat);
	tableCell.setTextTable(table);
	
	blockFormat.setBottomMargin(0);
	blockFormat.setTopMargin(0);
	
	//Заповнення таблиці
	textCharFormat.setFontPointSize( 10.5 );
	textCharFormat_small.setFontPointSize( 8 );
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	textCharFormat_bold.setFontPointSize( 10 );
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	
	tableCell.setAlignment(Qt::AlignLeft);
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignBottom);
	tableCell.set(0,0,"  Голова правління\n  "+OrganizShortName(), textCharFormat);
	tableCell.setAlignment(Qt::AlignCenter);
	tableCell.set(0,1,"______________________", textCharFormat);
	tableCell.set(0,2,"______________________", textCharFormat);
	
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignTop);
	tableCell.setAlignment(Qt::AlignCenter);
	tableCell.set(1,1,"(підпис)", textCharFormat_small);
	tableCell.set(1,2,"( П.І.Б. )", textCharFormat_small);
	
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	tableCell.setAlignment(Qt::AlignLeft);
	tableCell.set(2,0,"\n\n        М.П.\n\n\n", textCharFormat);
	
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignBottom);
	tableCell.setAlignment(Qt::AlignLeft);
	tableCell.set(3,0,"  Виконавець", textCharFormat);
	tableCell.setAlignment(Qt::AlignCenter);
	tableCell.set(3,1,"______________________", textCharFormat);
	tableCell.set(3,2,"______________________", textCharFormat);
	
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignTop);
	tableCell.setAlignment(Qt::AlignCenter);
	tableCell.set(4,1,"(підпис)", textCharFormat_small);
	tableCell.set(4,2,"( П.І.Б. )", textCharFormat_small);
	*/
	
	cursor.insertFragment(pidpysy(8, textCharFormat, QPrinter::Landscape));
	
	printform->printer()->setDocName("Розрахунок суми за пільговий проїзд");
	printform->printer()->setPageMargins( 10, 10, 10, 3, QPrinter::Millimeter );
	printform->show();
}
//--------------------utech--------------------utech--------------------utech--------------------
