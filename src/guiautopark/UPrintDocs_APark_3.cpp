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
#include <math.h>

//--------------------utech--------------------utech--------------------utech--------------------
void UPrintDocs_APark::print_reyestrChekivGazZaMisyac(QDate vDate, int partnerId)
{
    printform = new UPrintForm(0, "Реєстр чеків за придбаний стиснений природний газ за "+vDate.toString("MM.yyyy"));
	printform->printer()->setPageMargins( 15, 4, 5, 10, QPrinter::Millimeter );
	
	QSqlQuery query;
	query.exec("SELECT Name FROM dovpartners WHERE id="+sqlStr(partnerId));
	query.next();
	QString zaprName = query.value(0).toString();
	
	query.exec("SELECT count(*) \
				FROM zvitKupivliPalnogo zvit \
				LEFT JOIN zvitKupivliPalnogoOrders orders \
					ON orders.zvitKupivliPalnogo_id=zvit.id \
				WHERE year(zvit.CDate)="+sqlStr(vDate.year())+" \
					and month(zvit.CDate)="+sqlStr(vDate.month())+" \
					and zvit.MarkaPalnogo_id=6 \
					and zvit.DovPartners_id="+sqlStr(partnerId)+" \
					and orders.id>0");
	query.next();
	int rowCount = query.value(0).toInt();
	int colCount = 6;
	
	UPostupForm *postup = new UPostupForm(0, rowCount);
	postup->show();
	
	QTextCursor cursor(printform->document());
	QTextBlockFormat blockFormat;
	QTextTableCell cell;
	QTextCharFormat textCharFormat, textCharFormat_bold, textCharFormat_small;
	QFont fnt = textCharFormat_bold.font();
	fnt.setBold(true);
	textCharFormat_bold.setFont(fnt);
	
	blockFormat.setAlignment( Qt::AlignRight );
	cursor.setBlockFormat( blockFormat );
	textCharFormat.setFontPointSize( 7 );
	cursor.insertText("Документ створено програмою \"Автопарк менеджер\" "+QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm"), textCharFormat);
	blockFormat.setAlignment( Qt::AlignCenter );
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	textCharFormat_bold.setFontPointSize( 13 );
	cursor.insertText("РЕЄСТР\n", textCharFormat_bold);
	textCharFormat_bold.setFontPointSize( 12 );
	cursor.insertText("чеків за придбаний стиснений природний газ\nна "+zaprName+"\n", textCharFormat_bold);
	cursor.insertText("за "+monthlist[vDate.month()-1]+" "+QString::number(vDate.year())+" року\n", textCharFormat_bold);
	cursor.insertText(OrganizName(), textCharFormat_bold);
	
	blockFormat.setAlignment( Qt::AlignLeft );
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	
	textCharFormat.setFontPointSize( 11 );
	textCharFormat_bold.setFontPointSize( 11 );
	cursor.insertText("Реквізити організації:\n", textCharFormat);
	cursor.insertText("Індивідуальний податковий номер: ", textCharFormat);
	cursor.insertText(OrganizIPN()+"\n", textCharFormat_bold);
	cursor.insertText("Номер свідоцтва платника ПДВ: ", textCharFormat);
	cursor.insertText(OrganizSvidPDVNum()+"\n", textCharFormat_bold);
	cursor.insertText("Юридична адреса: ", textCharFormat);
	cursor.insertText(OrganizAdresa()+"\n", textCharFormat_bold);
	cursor.insertText("Фізична адреса: ", textCharFormat);
	cursor.insertText(OrganizAdresa(), textCharFormat_bold);
	
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	
	//Створення таблиці
	QTextTableFormat tableFormat;
	QVector<QTextLength> constraints;
	constraints << QTextLength(QTextLength::FixedLength, 50);
	constraints << QTextLength(QTextLength::FixedLength, 200);
	constraints << QTextLength(QTextLength::FixedLength, 70);
	constraints << QTextLength(QTextLength::FixedLength, 100);
	constraints << QTextLength(QTextLength::FixedLength, 100);
	constraints << QTextLength(QTextLength::FixedLength, 100);
	
	tableFormat.setColumnWidthConstraints(constraints);
	tableFormat.setCellSpacing(0);
	tableFormat.setCellPadding(1);
	tableFormat.setBorder(0.6);
	tableFormat.setBorderBrush(QColor(Qt::black));
	tableFormat.setHeaderRowCount(1);
	QTextTable *table = cursor.insertTable(2 + rowCount, colCount, tableFormat);
	UPopulateCell tableCell(table);
	
	blockFormat.setBottomMargin(0);
	blockFormat.setTopMargin(0);
	
	//Заповнення шапки таблиці
	textCharFormat.setFontPointSize( 9.5 );
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	textCharFormat_bold.setFontPointSize( 9.5 );
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	
	tableCell.setAlignment(Qt::AlignCenter);
	tableCell.set(0,0,"№ з/п", textCharFormat);
	tableCell.set(0,1,"№ чека", textCharFormat);
	tableCell.set(0,2,"Дата", textCharFormat);
	tableCell.set(0,3,"Об'єм (м.куб)", textCharFormat);
	tableCell.set(0,4,"Сума (грн.)", textCharFormat);
	tableCell.set(0,5,"В т.ч. ПДВ", textCharFormat);
	
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignTop);
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignTop);
	
	double obyemSum = 0, sumaSum = 0, pdvSum = 0;
    double dVal;	
	query.exec("SELECT orders.DocNum, orders.CDate, orders.Kilkist, orders.Suma \
				FROM zvitKupivliPalnogo zvit \
				LEFT JOIN zvitKupivliPalnogoOrders orders \
					ON orders.zvitKupivliPalnogo_id=zvit.id \
				WHERE year(zvit.CDate)="+sqlStr(vDate.year())+" \
					and month(zvit.CDate)="+sqlStr(vDate.month())+" \
					and zvit.MarkaPalnogo_id=6 \
					and zvit.DovPartners_id="+sqlStr(partnerId)+" \
					and orders.id>0 \
				ORDER BY orders.CDate, orders.DocNum");
	int row;
	for (row = 1; row <= rowCount && query.next(); row++) {
	    tableCell.setAlignment(Qt::AlignCenter);
	    // "№ п/п"
		tableCell.set(row,0,row, textCharFormat);
	    // "№ чека"
		tableCell.setAlignment(Qt::AlignLeft);
                tableCell.set(row,1,"Чек №"+query.value(0).toString(), textCharFormat);
	    // "Дата"
		tableCell.setAlignment(Qt::AlignRight);
		tableCell.set(row,2,query.value(1).toDate().toString("dd.MM.yyyy"), textCharFormat);
	    // "Об'єм (м.куб)"
		dVal = query.value(2).toDouble();
		obyemSum += dVal;
		tableCell.set(row,3,uMToStr2(dVal), textCharFormat);
	    // "Сума (грн.)"
		dVal = query.value(3).toDouble();
		sumaSum += dVal;
		tableCell.set(row,4,uMToStr2(dVal), textCharFormat);
	    // "В т.ч. ПДВ"
		dVal = uDToM(dVal / 6.0);
		pdvSum += dVal;
		tableCell.set(row,5,uMToStr2(dVal), textCharFormat);
		
		postup->incPos();
	}
	
	table->mergeCells(row, 0, 1, 3);
	
	tableCell.set(row,0,"Разом", textCharFormat);
	// "Об'єм (м.куб)"
	tableCell.set(row,3,uMToStr2(obyemSum), textCharFormat);
	// "Сума (грн.)"
	tableCell.set(row,4,uMToStr2(sumaSum), textCharFormat);
	// "В т.ч. ПДВ"
	tableCell.set(row,5,uMToStr2(pdvSum), textCharFormat);
	
	//Підписи
	textCharFormat.setFontPointSize( 9 );
	cursor.movePosition(QTextCursor::End);
	cursor.insertFragment(pidpysy(12, textCharFormat, QPrinter::Portrait));
	
	delete postup;
	
	printform->printer()->setDocName("Реєстр чеків за придбаний стиснений природний газ за "+vDate.toString("MM.yyyy"));
	printform->show();
}
//--------------------utech--------------------utech--------------------utech--------------------
void UPrintDocs_APark::print_reyestrChekivGazZaMisyacDaily(QDate vDate, int partnerId)
{
    printform = new UPrintForm(0, "Реєстр чеків за придбаний стиснений природний газ за "+vDate.toString("MM.yyyy"));
	printform->printer()->setPageMargins( 15, 4, 5, 5, QPrinter::Millimeter );
	
	QSqlQuery query;
	query.exec("SELECT Name FROM dovpartners WHERE id="+sqlStr(partnerId));
	query.next();
	QString zaprName = query.value(0).toString();
	
	int rowCount = vDate.daysInMonth();
	int colCount = 6;
	
	UPostupForm *postup = new UPostupForm(0, rowCount);
	postup->show();
	
	QTextCursor cursor(printform->document());
	QTextBlockFormat blockFormat;
	QTextTableCell cell;
	QTextCharFormat textCharFormat, textCharFormat_bold, textCharFormat_small;
	QFont fnt = textCharFormat_bold.font();
	fnt.setBold(true);
	textCharFormat_bold.setFont(fnt);
	
	blockFormat.setAlignment( Qt::AlignRight );
	cursor.setBlockFormat( blockFormat );
	textCharFormat.setFontPointSize( 7 );
	cursor.insertText("Документ створено програмою \"Автопарк менеджер\" "+QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm"), textCharFormat);
	blockFormat.setAlignment( Qt::AlignCenter );
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	textCharFormat_bold.setFontPointSize( 13 );
	cursor.insertText("РЕЄСТР\n", textCharFormat_bold);
	textCharFormat_bold.setFontPointSize( 12 );
	cursor.insertText("чеків за придбаний стиснений природний газ\nна "+zaprName+"\n", textCharFormat_bold);
	cursor.insertText("за "+monthlist[vDate.month()-1]+" "+QString::number(vDate.year())+" року\n", textCharFormat_bold);
	cursor.insertText(OrganizName(), textCharFormat_bold);
	
	blockFormat.setAlignment( Qt::AlignLeft );
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	
	textCharFormat.setFontPointSize( 11 );
	textCharFormat_bold.setFontPointSize( 11 );
	cursor.insertText("Реквізити організації:\n", textCharFormat);
	cursor.insertText("Індивідуальний податковий номер: ", textCharFormat);
	cursor.insertText(OrganizIPN()+"\n", textCharFormat_bold);
	cursor.insertText("Номер свідоцтва платника ПДВ: ", textCharFormat);
	cursor.insertText(OrganizSvidPDVNum()+"\n", textCharFormat_bold);
	cursor.insertText("Юридична адреса: ", textCharFormat);
	cursor.insertText(OrganizAdresa(), textCharFormat_bold);
	
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	
	//Створення таблиці
	QTextTableFormat tableFormat;
	QVector<QTextLength> constraints;
	constraints << QTextLength(QTextLength::FixedLength, 70);
	constraints << QTextLength(QTextLength::FixedLength, 100);
	constraints << QTextLength(QTextLength::FixedLength, 120);
	constraints << QTextLength(QTextLength::FixedLength, 120);
	constraints << QTextLength(QTextLength::FixedLength, 120);
	constraints << QTextLength(QTextLength::FixedLength, 120);
	
	tableFormat.setColumnWidthConstraints(constraints);
	tableFormat.setCellSpacing(0);
	tableFormat.setCellPadding(1);
	tableFormat.setBorder(0.6);
	tableFormat.setBorderBrush(QColor(Qt::black));
	tableFormat.setHeaderRowCount(1);
	QTextTable *table = cursor.insertTable(2 + rowCount, colCount, tableFormat);
	UPopulateCell tableCell(table);
	
	blockFormat.setBottomMargin(0);
	blockFormat.setTopMargin(0);
	
	//Заповнення шапки таблиці
	textCharFormat.setFontPointSize( 9.5 );
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	textCharFormat_bold.setFontPointSize( 9.5 );
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	
	tableCell.setAlignment(Qt::AlignCenter);
	tableCell.set(0,0,"Дата", textCharFormat);
	tableCell.set(0,1,"№ податкової накладної", textCharFormat);
	tableCell.set(0,2,"Об'єм, м.куб", textCharFormat);
	tableCell.set(0,3,"Заг.сума постач., з ПДВ (грн.)", textCharFormat);
	tableCell.set(0,4,"В т.ч. сума без ПДВ(грн.)", textCharFormat);
	tableCell.set(0,5,"В т.ч. ПДВ", textCharFormat);
	
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignTop);
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignTop);
	
	double obyemSum = 0, sumaSum = 0, pdvSum = 0;
    double dVal;	
	int row = 1;
	QDate xDate;
	for (xDate.setDate(vDate.year(), vDate.month(), 1); xDate <= QDate(vDate.year(), vDate.month(), vDate.daysInMonth()); xDate = xDate.addDays(1)) {
	    query.exec("SELECT sum(orders.Kilkist), sum(orders.Suma)\
				FROM zvitKupivliPalnogo zvit \
				LEFT JOIN zvitKupivliPalnogoOrders orders \
					ON orders.zvitKupivliPalnogo_id=zvit.id \
				WHERE year(zvit.CDate)="+sqlStr(xDate.year())+" \
					and month(zvit.CDate)="+sqlStr(xDate.month())+" \
					and day(zvit.CDate)="+sqlStr(xDate.day())+" \
					and zvit.MarkaPalnogo_id=6 \
					and zvit.DovPartners_id="+sqlStr(partnerId)+" \
					and orders.id>0");
		query.next();
		row = xDate.day();
		
		tableCell.setAlignment(Qt::AlignRight);
	    // "Дата"
		tableCell.set(row,0,xDate.toString("dd.MM.yyyy"), textCharFormat);
	    // "№ податкової накладної"
		tableCell.setAlignment(Qt::AlignLeft);
		//tableCell.set(row,1,query.value(0).toString(), textCharFormat);
	    // "Об'єм, м.куб"
		tableCell.setAlignment(Qt::AlignRight);
		dVal = query.value(0).toDouble();
		obyemSum += dVal;
		tableCell.setDash(row,2,dVal, textCharFormat);
	    // "Загальна сума постачання, включаючи ПДВ (грн.)"
		dVal = query.value(1).toDouble();
		sumaSum += dVal;
		double curSuma = dVal;
		tableCell.setDash(row,3,dVal, textCharFormat);
		// "В т.ч. ПДВ"
		dVal = uDToM(curSuma / 6.0);
		pdvSum += dVal;
		double curPdv = dVal;
		tableCell.setDash(row,5,dVal, textCharFormat);
	    // "В т.ч. сума без ПДВ(грн.)"
		dVal = curSuma - curPdv;
		tableCell.setDash(row,4,dVal, textCharFormat);
		
		postup->incPos();
	}
	
	++row;
	table->mergeCells(row, 0, 1, 2);
	
	tableCell.setAlignment(Qt::AlignRight);
	tableCell.set(row,0,"Разом", textCharFormat);
	// "Об'єм, м.куб"
	tableCell.setDash(row,2,obyemSum, textCharFormat);
	// "Загальна сума постачання, включаючи ПДВ (грн.)"
	tableCell.setDash(row,3,sumaSum, textCharFormat);
	// "В т.ч. ПДВ"
	tableCell.setDash(row,5,pdvSum, textCharFormat);
	// "В т.ч. сума без ПДВ(грн.)"
	tableCell.setDash(row,4,sumaSum-pdvSum, textCharFormat);
	
	//Підписи
	textCharFormat.setFontPointSize( 9 );
	cursor.movePosition(QTextCursor::End);
	cursor.insertFragment(pidpysy(12, textCharFormat, QPrinter::Portrait));
	
	delete postup;
	
	printform->printer()->setDocName("Реєстр чеків за придбаний стиснений природний газ за "+vDate.toString("MM.yyyy"));
	printform->show();
}
//--------------------utech--------------------utech--------------------utech--------------------
void UPrintDocs_APark::print_reyestrChekivPalneZaMisyac(QDate vDate)
{
    printform = new UPrintForm(0, "Реєстр чеків за придбане пальне газ за "+vDate.toString("MM.yyyy"));
	printform->printer()->setOrientation(QPrinter::Landscape);
	printform->printer()->setPageMargins( 15, 8, 5, 10, QPrinter::Millimeter );
	
	QSqlQuery query;
	int rowCount = vDate.daysInMonth();
	int colCount = 12;
	
	UPostupForm *postup = new UPostupForm(0, rowCount);
	postup->show();
	
	QTextCursor cursor(printform->document());
	QTextBlockFormat blockFormat;
	QTextTableCell cell;
	QTextCharFormat textCharFormat, textCharFormat_bold, textCharFormat_small;
	QFont fnt = textCharFormat_bold.font();
	fnt.setBold(true);
	textCharFormat_bold.setFont(fnt);
	
	blockFormat.setAlignment( Qt::AlignRight );
	cursor.setBlockFormat( blockFormat );
	textCharFormat.setFontPointSize( 7 );
	cursor.insertText("Документ створено програмою \"Автопарк менеджер\" "+QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm"), textCharFormat);
	blockFormat.setAlignment( Qt::AlignCenter );
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	textCharFormat_bold.setFontPointSize( 13 );
	cursor.insertText("РЕЄСТР\n", textCharFormat_bold);
	textCharFormat_bold.setFontPointSize( 12 );
	cursor.insertText("чеків за придбане пальне\n", textCharFormat_bold);
	cursor.insertText("за "+monthlist[vDate.month()-1]+" "+QString::number(vDate.year())+" року\n", textCharFormat_bold);
	cursor.insertText(OrganizName(), textCharFormat_bold);
	
	blockFormat.setAlignment( Qt::AlignLeft );
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	
	textCharFormat.setFontPointSize( 10 );
	textCharFormat_bold.setFontPointSize( 10 );
	cursor.insertText("Реквізити організації:\n", textCharFormat);
	cursor.insertText("Індивідуальний податковий номер: ", textCharFormat);
	cursor.insertText(OrganizIPN()+"\n", textCharFormat_bold);
	cursor.insertText("Номер свідоцтва платника ПДВ: ", textCharFormat);
	cursor.insertText(OrganizSvidPDVNum()+"\n", textCharFormat_bold);
	cursor.insertText("Юридична адреса: ", textCharFormat);
	cursor.insertText(OrganizAdresa()+"\n", textCharFormat_bold);
	cursor.insertText("Фізична адреса: ", textCharFormat);
	cursor.insertText(OrganizAdresa(), textCharFormat_bold);
	
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	
	//Створення таблиці
	QTextTableFormat tableFormat;
	QVector<QTextLength> constraints;
	constraints << QTextLength(QTextLength::FixedLength, 70);
	constraints << QTextLength(QTextLength::FixedLength, 80);
	constraints << QTextLength(QTextLength::FixedLength, 80);
	constraints << QTextLength(QTextLength::FixedLength, 80);
	constraints << QTextLength(QTextLength::FixedLength, 80);
	constraints << QTextLength(QTextLength::FixedLength, 80);
	constraints << QTextLength(QTextLength::FixedLength, 80);
	constraints << QTextLength(QTextLength::FixedLength, 80);
	constraints << QTextLength(QTextLength::FixedLength, 80);
	constraints << QTextLength(QTextLength::FixedLength, 80);
	constraints << QTextLength(QTextLength::FixedLength, 80);
	constraints << QTextLength(QTextLength::FixedLength, 80);
	
	tableFormat.setColumnWidthConstraints(constraints);
	tableFormat.setCellSpacing(0);
	tableFormat.setCellPadding(1);
	tableFormat.setBorder(0.6);
	tableFormat.setBorderBrush(QColor(Qt::black));
	tableFormat.setHeaderRowCount(2);
	QTextTable *table = cursor.insertTable(3 + rowCount, colCount, tableFormat);
	UPopulateCell tableCell(table);
	
	blockFormat.setBottomMargin(0);
	blockFormat.setTopMargin(0);
	
	//Заповнення шапки таблиці
	textCharFormat.setFontPointSize( 9 );
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	textCharFormat_bold.setFontPointSize( 9 );
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	
	table->mergeCells(0, 1, 1, 2);
	table->mergeCells(0, 3, 1, 2);
	table->mergeCells(0, 5, 1, 2);
	table->mergeCells(0, 7, 1, 2);
	table->mergeCells(0, 9, 1, 2);
	
	table->mergeCells(0, 0, 2, 1);
	table->mergeCells(0, 11, 2, 1);
	
	tableCell.setAlignment(Qt::AlignCenter);
	tableCell.set(0,0,"Дата", textCharFormat);
	
	tableCell.set(0,1,"Дизпальне", textCharFormat);
	tableCell.set(0,3,"А-95", textCharFormat);
	tableCell.set(0,5,"А-92", textCharFormat);
	tableCell.set(0,7,"А-80", textCharFormat);
	tableCell.set(0,9,"ГАЗ, Пропан-бутан", textCharFormat);
	tableCell.set(0,11,"Всього, грн.", textCharFormat);
	
	tableCell.set(1,1,"К-сть, л.", textCharFormat);
	tableCell.set(1,2,"Сума, грн.", textCharFormat);
	tableCell.set(1,3,"К-сть, л.", textCharFormat);
	tableCell.set(1,4,"Сума (грн.)", textCharFormat);
	tableCell.set(1,5,"К-сть, л.", textCharFormat);
	tableCell.set(1,6,"Сума, грн.", textCharFormat);
	tableCell.set(1,7,"К-сть, л.", textCharFormat);
	tableCell.set(1,8,"Сума, грн.", textCharFormat);
	tableCell.set(1,9,"К-сть, л.", textCharFormat);
	tableCell.set(1,10,"Сума, грн.", textCharFormat);
	
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignTop);
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignTop);
	
    double dVal;
	double sumCol[colCount];
	for (int i = 0; i < colCount; i++) {
		sumCol[i] = 0;
	}
	int row = 1;
	QDate xDate;
	double rowSum;
	for (int day = 1; day <= rowCount; day++) {
	    row++;
		xDate.setDate(vDate.year(), vDate.month(), day);
		rowSum = 0;
	    tableCell.setAlignment(Qt::AlignRight);
	    // Дата
		tableCell.set(row,0,xDate.toString("dd.MM"), textCharFormat);
		// Дизпальне
		query.exec("SELECT sum(orders.Kilkist), sum(orders.Suma) \
				FROM zvitKupivliPalnogo zvit \
				LEFT JOIN zvitKupivliPalnogoOrders orders \
					ON orders.zvitKupivliPalnogo_id=zvit.id \
				WHERE year(zvit.CDate)="+sqlStr(xDate.year())+" \
					and month(zvit.CDate)="+sqlStr(xDate.month())+" \
					and orders.CDate=date("+sqlStr(xDate)+") \
					and zvit.MarkaPalnogo_id="+sqlStr(5)+" \
					and orders.id>0");
		query.next();
		dVal = query.value(0).toDouble();
		sumCol[1] += dVal;
		tableCell.setDash(row, 1, dVal, textCharFormat);
		dVal = query.value(1).toDouble();
		rowSum += dVal;
		sumCol[2] += dVal;
		tableCell.setDash(row, 2, dVal, textCharFormat);
		// А-95
		query.exec("SELECT sum(orders.Kilkist), sum(orders.Suma) \
				FROM zvitKupivliPalnogo zvit \
				LEFT JOIN zvitKupivliPalnogoOrders orders \
					ON orders.zvitKupivliPalnogo_id=zvit.id \
				WHERE year(zvit.CDate)="+sqlStr(xDate.year())+" \
					and month(zvit.CDate)="+sqlStr(xDate.month())+" \
					and orders.CDate=date("+sqlStr(xDate)+") \
					and zvit.MarkaPalnogo_id="+sqlStr(4)+" \
					and orders.id>0");
		query.next();
		dVal = query.value(0).toDouble();
		sumCol[3] += dVal;
		tableCell.setDash(row, 3, dVal, textCharFormat);
		dVal = query.value(1).toDouble();
		rowSum += dVal;
		sumCol[4] += dVal;
		tableCell.setDash(row, 4, dVal, textCharFormat);
		// А-92
		query.exec("SELECT sum(orders.Kilkist), sum(orders.Suma) \
				FROM zvitKupivliPalnogo zvit \
				LEFT JOIN zvitKupivliPalnogoOrders orders \
					ON orders.zvitKupivliPalnogo_id=zvit.id \
				WHERE year(zvit.CDate)="+sqlStr(xDate.year())+" \
					and month(zvit.CDate)="+sqlStr(xDate.month())+" \
					and orders.CDate=date("+sqlStr(xDate)+") \
					and zvit.MarkaPalnogo_id="+sqlStr(3)+" \
					and orders.id>0");
		query.next();
		dVal = query.value(0).toDouble();
		sumCol[5] += dVal;
		tableCell.setDash(row, 5, dVal, textCharFormat);
		dVal = query.value(1).toDouble();
		rowSum += dVal;
		sumCol[6] += dVal;
		tableCell.setDash(row, 6, dVal, textCharFormat);
		// А-80
		query.exec("SELECT sum(orders.Kilkist), sum(orders.Suma) \
				FROM zvitKupivliPalnogo zvit \
				LEFT JOIN zvitKupivliPalnogoOrders orders \
					ON orders.zvitKupivliPalnogo_id=zvit.id \
				WHERE year(zvit.CDate)="+sqlStr(xDate.year())+" \
					and month(zvit.CDate)="+sqlStr(xDate.month())+" \
					and orders.CDate=date("+sqlStr(xDate)+") \
					and zvit.MarkaPalnogo_id="+sqlStr(2)+" \
					and orders.id>0");
		query.next();
		dVal = query.value(0).toDouble();
		sumCol[7] += dVal;
		tableCell.setDash(row, 7, dVal, textCharFormat);
		dVal = query.value(1).toDouble();
		rowSum += dVal;
		sumCol[8] += dVal;
		tableCell.setDash(row, 8, dVal, textCharFormat);
		
		// ГАЗ, Пропан-бутан
		query.exec("SELECT sum(orders.Kilkist), sum(orders.Suma) \
				FROM zvitKupivliPalnogo zvit \
				LEFT JOIN zvitKupivliPalnogoOrders orders \
					ON orders.zvitKupivliPalnogo_id=zvit.id \
				WHERE year(zvit.CDate)="+sqlStr(xDate.year())+" \
					and month(zvit.CDate)="+sqlStr(xDate.month())+" \
					and orders.CDate=date("+sqlStr(xDate)+") \
					and zvit.MarkaPalnogo_id="+sqlStr(8)+" \
					and orders.id>0");
		query.next();
		dVal = query.value(0).toDouble();
		sumCol[9] += dVal;
		tableCell.setDash(row, 9, dVal, textCharFormat);
		dVal = query.value(1).toDouble();
		rowSum += dVal;
		sumCol[10] += dVal;
		tableCell.setDash(row, 10, dVal, textCharFormat);
		
		// Всього
		sumCol[11] += rowSum;
		tableCell.setDash(row, 11, rowSum, textCharFormat);
		
		postup->incPos();
	}
	
	row++;
	tableCell.set(row, 0, "Разом", textCharFormat);
	for(int col = 1; col< colCount; col++)
	    tableCell.setDash(row, col, sumCol[col], textCharFormat);
	
	//Підписи
	textCharFormat.setFontPointSize( 9 );
	cursor.movePosition(QTextCursor::End);
	cursor.insertFragment(pidpysy(13, textCharFormat, QPrinter::Portrait));
	
	delete postup;
	
	printform->printer()->setDocName("Реєстр чеків за придбане пальне газ за "+vDate.toString("MM.yyyy"));
	printform->show();
}
//--------------------utech--------------------utech--------------------utech--------------------
void UPrintDocs_APark::print_reyestrChekivVidPostachalnyksPalneZaMisyac(int partnerId, QDate vDate)
{
    printform = new UPrintForm(0, "Реєстр чеків за придбане пальне газ за "+vDate.toString("MM.yyyy"));
        printform->printer()->setOrientation(QPrinter::Landscape);
        printform->printer()->setPageMargins( 15, 8, 5, 10, QPrinter::Millimeter );

        QSqlQuery query;
        int rowCount = vDate.daysInMonth();
        int colCount = 12;

        UPostupForm *postup = new UPostupForm(0, rowCount);
        postup->show();

        QTextCursor cursor(printform->document());
        QTextBlockFormat blockFormat;
        QTextTableCell cell;
        QTextCharFormat textCharFormat, textCharFormat_bold, textCharFormat_small;
        QFont fnt = textCharFormat_bold.font();
        fnt.setBold(true);
        textCharFormat_bold.setFont(fnt);

        blockFormat.setAlignment( Qt::AlignRight );
        cursor.setBlockFormat( blockFormat );
        textCharFormat.setFontPointSize( 7 );
        cursor.insertText("Документ створено програмою \"Автопарк менеджер\" "+QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm"), textCharFormat);
        blockFormat.setAlignment( Qt::AlignCenter );
        cursor.insertBlock(blockFormat);
        cursor.insertBlock(blockFormat);
        cursor.insertBlock(blockFormat);
        textCharFormat_bold.setFontPointSize( 13 );
        cursor.insertText("РЕЄСТР\n", textCharFormat_bold);
        textCharFormat_bold.setFontPointSize( 12 );
        cursor.insertText("чеків за придбане пальне в постачальника\n", textCharFormat_bold);
		query.exec("SELECT Name FROM dovPartners WHERE id="+sqlStr(partnerId));
		query.next();
		cursor.insertText(query.value(0).toString()+"\n", textCharFormat_bold);
        cursor.insertText("за "+monthlist[vDate.month()-1]+" "+QString::number(vDate.year())+" року\n", textCharFormat_bold);
        cursor.insertText(OrganizName(), textCharFormat_bold);

        blockFormat.setAlignment( Qt::AlignLeft );
        cursor.insertBlock(blockFormat);
        cursor.insertBlock(blockFormat);

        textCharFormat.setFontPointSize( 10 );
        textCharFormat_bold.setFontPointSize( 10 );
        cursor.insertText("Реквізити організації:\n", textCharFormat);
        cursor.insertText("Індивідуальний податковий номер: ", textCharFormat);
        cursor.insertText(OrganizIPN()+"\n", textCharFormat_bold);
        cursor.insertText("Номер свідоцтва платника ПДВ: ", textCharFormat);
        cursor.insertText(OrganizSvidPDVNum()+"\n", textCharFormat_bold);
        cursor.insertText("Юридична адреса: ", textCharFormat);
        cursor.insertText(OrganizAdresa()+"\n", textCharFormat_bold);
        cursor.insertText("Фізична адреса: ", textCharFormat);
        cursor.insertText(OrganizAdresa(), textCharFormat_bold);

        cursor.insertBlock(blockFormat);
        cursor.insertBlock(blockFormat);

        //Створення таблиці
        QTextTableFormat tableFormat;
        QVector<QTextLength> constraints;
        constraints << QTextLength(QTextLength::FixedLength, 70);
        constraints << QTextLength(QTextLength::FixedLength, 80);
        constraints << QTextLength(QTextLength::FixedLength, 80);
        constraints << QTextLength(QTextLength::FixedLength, 80);
        constraints << QTextLength(QTextLength::FixedLength, 80);
        constraints << QTextLength(QTextLength::FixedLength, 80);
        constraints << QTextLength(QTextLength::FixedLength, 80);
        constraints << QTextLength(QTextLength::FixedLength, 80);
        constraints << QTextLength(QTextLength::FixedLength, 80);
        constraints << QTextLength(QTextLength::FixedLength, 80);
        constraints << QTextLength(QTextLength::FixedLength, 80);
        constraints << QTextLength(QTextLength::FixedLength, 80);

        tableFormat.setColumnWidthConstraints(constraints);
        tableFormat.setCellSpacing(0);
        tableFormat.setCellPadding(1);
        tableFormat.setBorder(0.6);
        tableFormat.setBorderBrush(QColor(Qt::black));
        tableFormat.setHeaderRowCount(2);
        QTextTable *table = cursor.insertTable(3 + rowCount, colCount, tableFormat);
        UPopulateCell tableCell(table);

        blockFormat.setBottomMargin(0);
        blockFormat.setTopMargin(0);

        //Заповнення шапки таблиці
        textCharFormat.setFontPointSize( 9 );
        textCharFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
        textCharFormat_bold.setFontPointSize( 9 );
        textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignMiddle);

        table->mergeCells(0, 1, 1, 2);
        table->mergeCells(0, 3, 1, 2);
        table->mergeCells(0, 5, 1, 2);
        table->mergeCells(0, 7, 1, 2);
        table->mergeCells(0, 9, 1, 2);

        table->mergeCells(0, 0, 2, 1);
        table->mergeCells(0, 11, 2, 1);

        tableCell.setAlignment(Qt::AlignCenter);
        tableCell.set(0,0,"Дата", textCharFormat);

        tableCell.set(0,1,"Дизпальне", textCharFormat);
        tableCell.set(0,3,"А-95", textCharFormat);
        tableCell.set(0,5,"А-92", textCharFormat);
        tableCell.set(0,7,"А-80", textCharFormat);
        tableCell.set(0,9,"ГАЗ, Пропан-бутан", textCharFormat);
        tableCell.set(0,11,"Всього, грн.", textCharFormat);

        tableCell.set(1,1,"К-сть, л.", textCharFormat);
        tableCell.set(1,2,"Сума, грн.", textCharFormat);
        tableCell.set(1,3,"К-сть, л.", textCharFormat);
        tableCell.set(1,4,"Сума (грн.)", textCharFormat);
        tableCell.set(1,5,"К-сть, л.", textCharFormat);
        tableCell.set(1,6,"Сума, грн.", textCharFormat);
        tableCell.set(1,7,"К-сть, л.", textCharFormat);
        tableCell.set(1,8,"Сума, грн.", textCharFormat);
        tableCell.set(1,9,"К-сть, л.", textCharFormat);
        tableCell.set(1,10,"Сума, грн.", textCharFormat);

        textCharFormat.setVerticalAlignment(QTextCharFormat::AlignTop);
        textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignTop);

    double dVal;
        double sumCol[colCount];
        for (int i = 0; i < colCount; i++) {
                sumCol[i] = 0;
        }
        int row = 1;
        QDate xDate;
        double rowSum;
        for (int day = 1; day <= rowCount; day++) {
            row++;
                xDate.setDate(vDate.year(), vDate.month(), day);
                rowSum = 0;
            tableCell.setAlignment(Qt::AlignRight);
            // Дата
                tableCell.set(row,0,xDate.toString("dd.MM"), textCharFormat);
                // Дизпальне
                query.exec("SELECT sum(orders.Kilkist), sum(orders.Suma) \
                                FROM zvitKupivliPalnogo zvit \
                                LEFT JOIN zvitKupivliPalnogoOrders orders \
                                        ON orders.zvitKupivliPalnogo_id=zvit.id \
                                WHERE year(zvit.CDate)="+sqlStr(xDate.year())+" \
                                        and month(zvit.CDate)="+sqlStr(xDate.month())+" \
                                        and orders.CDate=date("+sqlStr(xDate)+") \
                                        and zvit.MarkaPalnogo_id="+sqlStr(5)+" \
										and zvit.DovPartners_id="+sqlStr(partnerId)+" \
                                        and orders.id>0");
                query.next();
                dVal = query.value(0).toDouble();
                sumCol[1] += dVal;
                tableCell.setDash(row, 1, dVal, textCharFormat);
                dVal = query.value(1).toDouble();
                rowSum += dVal;
                sumCol[2] += dVal;
                tableCell.setDash(row, 2, dVal, textCharFormat);
                // А-95
                query.exec("SELECT sum(orders.Kilkist), sum(orders.Suma) \
                                FROM zvitKupivliPalnogo zvit \
                                LEFT JOIN zvitKupivliPalnogoOrders orders \
                                        ON orders.zvitKupivliPalnogo_id=zvit.id \
                                WHERE year(zvit.CDate)="+sqlStr(xDate.year())+" \
                                        and month(zvit.CDate)="+sqlStr(xDate.month())+" \
                                        and orders.CDate=date("+sqlStr(xDate)+") \
                                        and zvit.MarkaPalnogo_id="+sqlStr(4)+" \
										and zvit.DovPartners_id="+sqlStr(partnerId)+" \
                                        and orders.id>0");
                query.next();
                dVal = query.value(0).toDouble();
                sumCol[3] += dVal;
                tableCell.setDash(row, 3, dVal, textCharFormat);
                dVal = query.value(1).toDouble();
                rowSum += dVal;
                sumCol[4] += dVal;
                tableCell.setDash(row, 4, dVal, textCharFormat);
                // А-92
                query.exec("SELECT sum(orders.Kilkist), sum(orders.Suma) \
                                FROM zvitKupivliPalnogo zvit \
                                LEFT JOIN zvitKupivliPalnogoOrders orders \
                                        ON orders.zvitKupivliPalnogo_id=zvit.id \
                                WHERE year(zvit.CDate)="+sqlStr(xDate.year())+" \
                                        and month(zvit.CDate)="+sqlStr(xDate.month())+" \
                                        and orders.CDate=date("+sqlStr(xDate)+") \
                                        and zvit.MarkaPalnogo_id="+sqlStr(3)+" \
										and zvit.DovPartners_id="+sqlStr(partnerId)+" \
                                        and orders.id>0");
                query.next();
                dVal = query.value(0).toDouble();
                sumCol[5] += dVal;
                tableCell.setDash(row, 5, dVal, textCharFormat);
                dVal = query.value(1).toDouble();
                rowSum += dVal;
                sumCol[6] += dVal;
                tableCell.setDash(row, 6, dVal, textCharFormat);
                // А-80
                query.exec("SELECT sum(orders.Kilkist), sum(orders.Suma) \
                                FROM zvitKupivliPalnogo zvit \
                                LEFT JOIN zvitKupivliPalnogoOrders orders \
                                        ON orders.zvitKupivliPalnogo_id=zvit.id \
                                WHERE year(zvit.CDate)="+sqlStr(xDate.year())+" \
                                        and month(zvit.CDate)="+sqlStr(xDate.month())+" \
                                        and orders.CDate=date("+sqlStr(xDate)+") \
                                        and zvit.MarkaPalnogo_id="+sqlStr(2)+" \
										and zvit.DovPartners_id="+sqlStr(partnerId)+" \
                                        and orders.id>0");
                query.next();
                dVal = query.value(0).toDouble();
                sumCol[7] += dVal;
                tableCell.setDash(row, 7, dVal, textCharFormat);
                dVal = query.value(1).toDouble();
                rowSum += dVal;
                sumCol[8] += dVal;
                tableCell.setDash(row, 8, dVal, textCharFormat);

                // ГАЗ, Пропан-бутан
                query.exec("SELECT sum(orders.Kilkist), sum(orders.Suma) \
                                FROM zvitKupivliPalnogo zvit \
                                LEFT JOIN zvitKupivliPalnogoOrders orders \
                                        ON orders.zvitKupivliPalnogo_id=zvit.id \
                                WHERE year(zvit.CDate)="+sqlStr(xDate.year())+" \
                                        and month(zvit.CDate)="+sqlStr(xDate.month())+" \
                                        and orders.CDate=date("+sqlStr(xDate)+") \
                                        and zvit.MarkaPalnogo_id="+sqlStr(8)+" \
										and zvit.DovPartners_id="+sqlStr(partnerId)+" \
                                        and orders.id>0");
                query.next();
                dVal = query.value(0).toDouble();
                sumCol[9] += dVal;
                tableCell.setDash(row, 9, dVal, textCharFormat);
                dVal = query.value(1).toDouble();
                rowSum += dVal;
                sumCol[10] += dVal;
                tableCell.setDash(row, 10, dVal, textCharFormat);

                // Всього
                sumCol[11] += rowSum;
                tableCell.setDash(row, 11, rowSum, textCharFormat);

                postup->incPos();
        }

        row++;
        tableCell.set(row, 0, "Разом", textCharFormat);
        for(int col = 1; col< colCount; col++)
            tableCell.setDash(row, col, sumCol[col], textCharFormat);

        //Підписи
        textCharFormat.setFontPointSize( 9 );
        cursor.movePosition(QTextCursor::End);
        cursor.insertFragment(pidpysy(13, textCharFormat, QPrinter::Portrait));

        delete postup;

        printform->printer()->setDocName("Реєстр чеків за придбане пальне газ за "+vDate.toString("MM.yyyy"));
        printform->show();
}
//--------------------utech--------------------utech--------------------utech--------------------
void UPrintDocs_APark::print_vidomistZakupivliPalnogoPoVodiyahZaMisyac(QDate vDate, int markaPalnogoId)
{
    printform = new UPrintForm(0, "Відомість закупівлі пального по водіях за "+vDate.toString("MM.yyyy"));
	printform->printer()->setPageMargins( 10, 5, 5, 5, QPrinter::Millimeter );
	
	QSqlQuery query;
	query.exec("SELECT count(*) FROM (SELECT zvit.Npr_id, npr.Prizv, npr.Imia, npr.PoBatk, sum(orders.Kilkist), sum(orders.Suma), count(*) \
				FROM (zvitKupivliPalnogo zvit \
				LEFT JOIN zvitKupivliPalnogoOrders orders \
					ON orders.zvitKupivliPalnogo_id=zvit.id) \
				LEFT JOIN npr \
					ON npr.id=zvit.Npr_id \
				WHERE year(zvit.CDate)="+sqlStr(vDate.year())+" \
					and month(zvit.CDate)="+sqlStr(vDate.month())+" \
					and zvit.MarkaPalnogo_id="+sqlStr(markaPalnogoId)+" \
					and orders.id>0 \
				GROUP BY zvit.Npr_id, npr.Prizv, npr.Imia, npr.PoBatk) AS tTable");
	query.next();
	int rowCount = query.value(0).toInt();
	int colCount = 8;
	
	UPostupForm *postup = new UPostupForm(0, rowCount);
	postup->show();
	
	QTextCursor cursor(printform->document());
	QTextBlockFormat blockFormat;
	QTextTableCell cell;
	QTextCharFormat textCharFormat, textCharFormat_bold, textCharFormat_small;
	QFont fnt = textCharFormat_bold.font();
	fnt.setBold(true);
	textCharFormat_bold.setFont(fnt);
	
	blockFormat.setAlignment( Qt::AlignRight );
	cursor.setBlockFormat( blockFormat );
	textCharFormat.setFontPointSize( 7 );
	cursor.insertText("Документ створено програмою \"Автопарк менеджер\" "+QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm"), textCharFormat);
	blockFormat.setAlignment( Qt::AlignCenter );
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	textCharFormat_bold.setFontPointSize( 13 );
	cursor.insertText("ВІДОМІСТЬ\n", textCharFormat_bold);
	textCharFormat_bold.setFontPointSize( 12 );
	cursor.insertText("закупівлі пального по водіях\n", textCharFormat_bold);
	cursor.insertText("за "+monthlist[vDate.month()-1]+" "+QString::number(vDate.year())+" року\n", textCharFormat_bold);
	cursor.insertText(OrganizName(), textCharFormat_bold);
	blockFormat.setAlignment( Qt::AlignLeft );
	cursor.insertBlock(blockFormat);
	query.exec("SELECT MarkaName FROM markaPalnogo WHERE id="+sqlStr(markaPalnogoId));
	query.next();
	textCharFormat_bold.setFontPointSize( 10 );
	textCharFormat.setFontPointSize( 10 );
	cursor.insertText("Тип пального: ", textCharFormat);
	cursor.insertText(query.value(0).toString(), textCharFormat_bold);
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	
	//Створення таблиці
	QTextTableFormat tableFormat;
	QVector<QTextLength> constraints;
	constraints << QTextLength(QTextLength::FixedLength, 40);
	constraints << QTextLength(QTextLength::FixedLength, 50);
	constraints << QTextLength(QTextLength::FixedLength, 230);
	constraints << QTextLength(QTextLength::FixedLength, 65);
	constraints << QTextLength(QTextLength::FixedLength, 80);
	constraints << QTextLength(QTextLength::FixedLength, 80);
	constraints << QTextLength(QTextLength::FixedLength, 80);
	constraints << QTextLength(QTextLength::FixedLength, 80);
	
	tableFormat.setColumnWidthConstraints(constraints);
	tableFormat.setCellSpacing(0);
	tableFormat.setCellPadding(1);
	tableFormat.setBorder(0.6);
	tableFormat.setBorderBrush(QColor(Qt::black));
	tableFormat.setHeaderRowCount(1);
	QTextTable *table = cursor.insertTable(2 + rowCount, colCount, tableFormat);
	UPopulateCell tableCell(table);
	
	blockFormat.setBottomMargin(0);
	blockFormat.setTopMargin(0);
	
	//Заповнення шапки таблиці
	textCharFormat.setFontPointSize( 9 );
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	textCharFormat_bold.setFontPointSize( 9 );
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	
	tableCell.setAlignment(Qt::AlignCenter);
	tableCell.set(0,0,"№ з/п", textCharFormat);
	tableCell.set(0,1,"Таб.ном.", textCharFormat);
	tableCell.set(0,2,"ПІБ", textCharFormat);
	tableCell.set(0,3,"К-сть чек.", textCharFormat);
	tableCell.set(0,4,markaPalnogoId==6?"Об'єм, м.куб":"Об'єм, л.", textCharFormat);
	tableCell.set(0,5,"71 рах.", textCharFormat);
	tableCell.set(0,6,markaPalnogoId==6?"06/4 рах.":"06/1", textCharFormat);
	tableCell.set(0,7,"68 рах.", textCharFormat);
	
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignTop);
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignTop);
	
	double obyemSum = 0, sumaSum = 0, withoutPdvSum = 0, pdvSum = 0;
    double dVal, suma;	
	int iVal, chekySum = 0;;
	query.exec("SELECT zvit.Npr_id, npr.Prizv, npr.Imia, npr.PoBatk, sum(orders.Kilkist), sum(orders.Suma), count(*) \
				FROM (zvitKupivliPalnogo zvit \
				LEFT JOIN zvitKupivliPalnogoOrders orders \
					ON orders.zvitKupivliPalnogo_id=zvit.id) \
				LEFT JOIN npr \
					ON npr.id=zvit.Npr_id \
				WHERE year(zvit.CDate)="+sqlStr(vDate.year())+" \
					and month(zvit.CDate)="+sqlStr(vDate.month())+" \
					and zvit.MarkaPalnogo_id="+sqlStr(markaPalnogoId)+" \
					and orders.id>0 \
				GROUP BY zvit.Npr_id, npr.Prizv, npr.Imia, npr.PoBatk \
				ORDER BY npr.Prizv, npr.Imia, npr.PoBatk");
	int row;
	for (row = 1; row <= rowCount && query.next(); row++) {
	    tableCell.setAlignment(Qt::AlignRight);
	    // "№ п/п"
		tableCell.set(row,0,row, textCharFormat);
		// "Таб.ном."
		tableCell.set(row,1,query.value(0).toInt(), textCharFormat);
		// "ПІБ"
		tableCell.setAlignment(Qt::AlignLeft);
		tableCell.set(row,2,query.value(1).toString()+" "+query.value(2).toString()+" "+query.value(3).toString(), textCharFormat);
		// "К-сть чеків"
		tableCell.setAlignment(Qt::AlignRight);
		iVal = query.value(6).toInt();
		chekySum += iVal;
		tableCell.set(row,3,iVal, textCharFormat);
		// "Об'єм"
		dVal = query.value(4).toDouble();
		obyemSum += dVal;
		tableCell.set(row,4,dVal, textCharFormat);
		// "71 рах."
		suma = query.value(5).toDouble();
		sumaSum += suma;
		tableCell.set(row,5,suma, textCharFormat);
		// "68 рах."
		dVal = uDToM(suma / 6.0);
		pdvSum += dVal;
		tableCell.set(row,7,dVal, textCharFormat);
		// "6/01 рах...."
		dVal = suma - dVal;
		withoutPdvSum += dVal;
		tableCell.set(row,6,dVal, textCharFormat);
		
		postup->incPos();
	}
	
	table->mergeCells(row, 0, 1, 3);
	
	tableCell.set(row,0,"Разом", textCharFormat);
	// Кількість чеків
	tableCell.set(row,3,chekySum, textCharFormat);
	// "Об'єм (м.куб)"
	tableCell.set(row,4,uMToStr2(obyemSum), textCharFormat);
	// "71
	tableCell.set(row,5,uMToStr2(sumaSum), textCharFormat);
	// 6/01...
	tableCell.set(row,6,uMToStr2(withoutPdvSum), textCharFormat);
	// 68
	tableCell.set(row,7,uMToStr2(pdvSum), textCharFormat);
	
	//Підписи
	
	cursor.movePosition(QTextCursor::End);
	cursor.insertBlock(blockFormat);
	textCharFormat.setFontPointSize( 7 );
	cursor.insertText("* У документі наводиться перелік водіїв, що протягом звітного місяця заправляли поточним типом пального.", textCharFormat);
	cursor.insertBlock(blockFormat);
	textCharFormat.setFontPointSize( 10 );
	cursor.insertFragment(pidpysy(14, textCharFormat, QPrinter::Portrait));
	
	delete postup;
	
	printform->printer()->setDocName("Відомість закупівлі пального по водіях за "+vDate.toString("MM.yyyy"));
	printform->show();
}
//--------------------utech--------------------utech--------------------utech--------------------
void UPrintDocs_APark::print_vidomistZakupivliPalnogoPoVodiyahZaMisyacVRozriziRahunkiv(QDate vDate)
{
    printform = new UPrintForm(0, "Відомість закупівлі пального по водіях в розрізі рахунків за "+vDate.toString("MM.yyyy"));
	printform->printer()->setPaperSize(QPrinter::A5);
	printform->printer()->setPageMargins( 4, 3, 3, 3, QPrinter::Millimeter );
	
	QTextCursor cursor(printform->document());
	QTextBlockFormat blockFormat;
	QTextTableCell cell;
	QTextCharFormat textCharFormat, textCharFormat_bold, textCharFormat_small;
	QFont fnt = textCharFormat_bold.font();
	fnt.setBold(true);
	textCharFormat_bold.setFont(fnt);
	
	blockFormat.setAlignment( Qt::AlignLeft );
	cursor.setBlockFormat( blockFormat );
	textCharFormat.setFontPointSize( 15 );
	cursor.insertText("Документ в стані розробки", textCharFormat);
	
	
	printform->printer()->setDocName("Відомість закупівлі пального по водіях в розрізі рахунків за "+vDate.toString("MM.yyyy"));
	printform->show();
}
//--------------------utech--------------------utech--------------------utech--------------------
void UPrintDocs_APark::print_reyestrChekivZaPalyvnoMastylniMaterialy(QDate vDate, QDate eDate, int partnerId, int markaPalnogoId)
{
    printform = new UPrintForm(0, "РЕЄСТР чеків з "+vDate.toString("dd.MM.yyyy")+" по "+eDate.toString("dd.MM.yyyy"));
	printform->printer()->setPageMargins( 10, 5, 5, 10, QPrinter::Millimeter );
	
	QSqlQuery query;
	query.exec("SELECT count(*) FROM( zvitKupivliPalnogoOrders orders \
					LEFT JOIN zvitKupivliPalnogo zvit \
						ON zvit.id=orders.zvitKupivliPalnogo_id) \
					where orders.CDate BETWEEN date("+sqlStr(vDate)+") and date("+sqlStr(eDate)+") \
					and zvit.MarkaPalnogo_id= "+sqlStr(markaPalnogoId)+" \
				    and zvit.DovPartners_id = "+sqlStr(partnerId)+"  \
						and orders.id>0 ");
/*WHERE year(orders.CDate)="+sqlStr(vDate.year())+" \
					and month(orders.CDate)="+sqlStr(vDate.month())+" \
					and zvit.MarkaPalnogo_id="+sqlStr(markaPalnogoId)+" \
					and zvit.DovPartners_id="+sqlStr(partnerId)+" \
					and orders.id>0");*/
	query.next();
	int rowCount = query.value(0).toInt();
	int colCount = 10;
	
	UPostupForm *postup = new UPostupForm(0, rowCount);
	postup->show();
	
	QTextCursor cursor(printform->document());
	QTextBlockFormat blockFormat;
	QTextTableCell cell;
	QTextCharFormat textCharFormat, textCharFormat_bold, textCharFormat_small;
	QFont fnt = textCharFormat_bold.font();
	fnt.setBold(true);
	textCharFormat_bold.setFont(fnt);
	
	blockFormat.setAlignment( Qt::AlignRight );
	cursor.setBlockFormat( blockFormat );
	textCharFormat.setFontPointSize( 7 );
	cursor.insertText("Документ створено програмою \"Автопарк менеджер\" "+QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm"), textCharFormat);
	blockFormat.setAlignment( Qt::AlignCenter );
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	textCharFormat_bold.setFontPointSize( 11 );
	cursor.insertText("РЕЄСТР\n", textCharFormat_bold);
	cursor.insertText("чеків за придбані паливо-мастильні матеріали\n", textCharFormat_bold);
	query.exec("SELECT Name FROM dovPartners WHERE id="+sqlStr(partnerId));
	query.next();
	cursor.insertText("Нa: ", textCharFormat_bold);
	cursor.insertText(query.value(0).toString(), textCharFormat_bold);

	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	
	textCharFormat.setFontPointSize( 10 );
    textCharFormat_bold.setFontPointSize( 10 );
	blockFormat.setAlignment( Qt::AlignLeft );
	cursor.setBlockFormat( blockFormat );
    cursor.insertText("Реквізити організації:\n", textCharFormat);
    cursor.insertText("Індивідуальний податковий номер: ", textCharFormat);
    cursor.insertText(OrganizIPN()+"\n", textCharFormat_bold);
    cursor.insertText("Номер свідоцтва платника ПДВ: ", textCharFormat);
    cursor.insertText(OrganizSvidPDVNum()+"\n", textCharFormat_bold);
    cursor.insertText("Юридична адреса: ", textCharFormat);
    cursor.insertText(OrganizAdresa()+"\n", textCharFormat_bold);
    cursor.insertText("Фізична адреса: ", textCharFormat);
    cursor.insertText(OrganizAdresa(), textCharFormat_bold);
	//cursor.insertText("Телефон: ", textCharFormat);
   // cursor.insertText(Organiz()+"\n", textCharFormat_bold);	

    cursor.insertBlock(blockFormat);
    cursor.insertBlock(blockFormat);
	
	//Створення таблиці
	QTextTableFormat tableFormat;
	QVector<QTextLength> constraints;
	constraints << QTextLength(QTextLength::FixedLength, 25);
	constraints << QTextLength(QTextLength::FixedLength, 70);
	constraints << QTextLength(QTextLength::FixedLength, 70);
	constraints << QTextLength(QTextLength::FixedLength, 50);
	constraints << QTextLength(QTextLength::FixedLength, 50);
	constraints << QTextLength(QTextLength::FixedLength, 60);
	constraints << QTextLength(QTextLength::FixedLength, 60);
	constraints << QTextLength(QTextLength::FixedLength, 70);
	constraints << QTextLength(QTextLength::FixedLength, 70);
	constraints << QTextLength(QTextLength::FixedLength, 70);
	
	tableFormat.setColumnWidthConstraints(constraints);
	tableFormat.setCellSpacing(0);
	tableFormat.setCellPadding(1);
	tableFormat.setBorder(0.6);
	tableFormat.setBorderBrush(QColor(Qt::black));
	tableFormat.setHeaderRowCount(1);
	QTextTable *table = cursor.insertTable(2 + rowCount, colCount, tableFormat);
	UPopulateCell tableCell(table);
	
	blockFormat.setBottomMargin(0);
	blockFormat.setTopMargin(0);
	
	//Заповнення шапки таблиці
	textCharFormat.setFontPointSize( 8 );
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	textCharFormat_bold.setFontPointSize( 8 );
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	
	tableCell.setAlignment(Qt::AlignCenter);
	tableCell.set(0,0,"№ з/п", textCharFormat);
	tableCell.set(0,1,"Дата", textCharFormat);
	tableCell.set(0,2,"Вид палива", textCharFormat);
	tableCell.set(0,3,"№ АЗС", textCharFormat);
	tableCell.set(0,4,"№ Чеку", textCharFormat);
	tableCell.set(0,5,"К-сть л.", textCharFormat);
	tableCell.set(0,6,"Ціна за 1 л.", textCharFormat);
	tableCell.set(0,7,"Загальна сума", textCharFormat);
	tableCell.set(0,8,"ПДВ", textCharFormat);
	tableCell.set(0,9,"Сума без ПДВ", textCharFormat);
	
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignTop);
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignTop);
	
	    double dVal, allSuma = 0, allPDV = 0, allBezPDV = 0;
	query.exec("SELECT orders.CDate, palne.MarkaName, orders.KodZapravky, \
					   orders.DocNum, orders.Kilkist, \
				       ROUND(orders.Suma/orders.Kilkist, 2)  AS 'cina', \
                       orders.Suma, ROUND(orders.Suma-(orders.Suma/1.2), 2) AS 'PDV', \
                       ROUND(orders.Suma-(orders.Suma-(orders.Suma/1.2)), 2) AS 'bez PDV' \
				FROM zvitKupivliPalnogo zvit \
					LEFT JOIN zvitKupivliPalnogoOrders orders \
					ON orders.zvitKupivliPalnogo_id=zvit.id \
					LEFT JOIN markapalnogo palne \
					ON palne.id=zvit.MarkaPalnogo_id \
				WHERE \
					orders.CDate BETWEEN date("+sqlStr(vDate)+") and date("+sqlStr(eDate)+") \
					and zvit.MarkaPalnogo_id= "+sqlStr(markaPalnogoId)+" \
				    and zvit.DovPartners_id = "+sqlStr(partnerId)+" \
					and orders.id>0 \
				ORDER BY orders.CDate");
	int row;
	for (row = 1; row <= rowCount && query.next(); row++) {
	    tableCell.setAlignment(Qt::AlignRight);
		tableCell.set(row,0,row, textCharFormat);
		
		tableCell.set(row,1,query.value(0).toString(), textCharFormat);
		
		tableCell.setAlignment(Qt::AlignLeft);
		tableCell.set(row,2,query.value(1).toString(), textCharFormat);
		
		tableCell.setAlignment(Qt::AlignRight);
		tableCell.set(row,3,query.value(2).toString(), textCharFormat);
		
		tableCell.set(row,4,query.value(3).toInt(), textCharFormat);
		// "Ціна"
		tableCell.set(row,5,query.value(4).toDouble(), textCharFormat);
		// "загальна сума"
		tableCell.set(row,6,query.value(5).toDouble(), textCharFormat);
		// "ПДВ"
		dVal = query.value(6).toDouble();
		allSuma += dVal;
		tableCell.setDash(row,7,dVal, textCharFormat);
		// "Без ПДВ"
		dVal = uDToM(query.value(7).toDouble());
		allPDV += dVal;
		tableCell.setDash(row,8,dVal, textCharFormat);
		
		dVal = uDToM(query.value(8).toDouble());
		allBezPDV += dVal;
		tableCell.setDash(row,9,dVal, textCharFormat);

		
		postup->incPos();
	}
	
	table->mergeCells(row, 0, 1, 7);
	
	tableCell.set(row,0,"Разом", textCharFormat);
	// "К-сть"
	tableCell.setDash(row,7,allSuma, textCharFormat);
	// "Сума"
	tableCell.setDash(row,8,allPDV, textCharFormat);
	
	tableCell.setDash(row,9,allBezPDV, textCharFormat);

	
	//Підписи
	cursor.movePosition(QTextCursor::End);
	cursor.insertBlock(blockFormat);
	textCharFormat.setFontPointSize( 9 );
	cursor.insertFragment(pidpysy(15, textCharFormat, QPrinter::Portrait));
	
	delete postup;
	
	printform->printer()->setDocName("Реєстр чеків з "+vDate.toString("dd.MM.yyyy")+" по "+eDate.toString("dd.MM.yyyy"));
	printform->show();
	
}
//--------------------utech--------------------utech--------------------utech--------------------
void UPrintDocs_APark::print_reyestrChekivVidPostachalnykaPoVyduPalnogo(QDate vDate, int partnerId, int markaPalnogoId)
{
	printform = new UPrintForm(0, "Реєстр чеків за "+vDate.toString("MM.yyyy"));
	printform->printer()->setPageMargins( 10, 5, 5, 10, QPrinter::Millimeter );
	
	QSqlQuery query;
	query.exec("SELECT count(*) \
				FROM ((zvitKupivliPalnogo zvit \
				LEFT JOIN zvitKupivliPalnogoOrders orders \
					ON orders.zvitKupivliPalnogo_id=zvit.id) \
				LEFT JOIN npr \
					ON npr.id=zvit.Npr_id) \
				WHERE year(orders.CDate)="+sqlStr(vDate.year())+" \
					and month(orders.CDate)="+sqlStr(vDate.month())+" \
					and zvit.MarkaPalnogo_id="+sqlStr(markaPalnogoId)+" \
					and zvit.DovPartners_id="+sqlStr(partnerId)+" \
					and orders.id>0");
	query.next();
	int rowCount = query.value(0).toInt();
	int colCount = 9;
	
	UPostupForm *postup = new UPostupForm(0, rowCount);
	postup->show();
	
	QTextCursor cursor(printform->document());
	QTextBlockFormat blockFormat;
	QTextTableCell cell;
	QTextCharFormat textCharFormat, textCharFormat_bold, textCharFormat_small;
	QFont fnt = textCharFormat_bold.font();
	fnt.setBold(true);
	textCharFormat_bold.setFont(fnt);
	
	blockFormat.setAlignment( Qt::AlignRight );
	cursor.setBlockFormat( blockFormat );
	textCharFormat.setFontPointSize( 7 );
	cursor.insertText("Документ створено програмою \"Автопарк менеджер\" "+QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm"), textCharFormat);
	blockFormat.setAlignment( Qt::AlignCenter );
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	textCharFormat_bold.setFontPointSize( 11 );
	cursor.insertText("РЕЄСТР\n", textCharFormat_bold);
	cursor.insertText("закупівлі пального\n", textCharFormat_bold);
	cursor.insertText("за "+monthlist[vDate.month()-1]+" "+QString::number(vDate.year())+" року\n", textCharFormat_bold);
	cursor.insertText(OrganizName(), textCharFormat_bold);
	blockFormat.setAlignment( Qt::AlignLeft );
	cursor.insertBlock(blockFormat);
	query.exec("SELECT Name FROM dovPartners WHERE id="+sqlStr(partnerId));
	query.next();
	textCharFormat_bold.setFontPointSize( 10 );
	textCharFormat.setFontPointSize( 10 );
	cursor.insertText("Постачальник: ", textCharFormat);
	cursor.insertText(query.value(0).toString(), textCharFormat_bold);
	query.exec("SELECT MarkaName FROM markaPalnogo WHERE id="+sqlStr(markaPalnogoId));
	query.next();
	cursor.insertBlock(blockFormat);
	cursor.insertText("Тип пального: ", textCharFormat);
	cursor.insertText(query.value(0).toString(), textCharFormat_bold);
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	
	//Створення таблиці
	QTextTableFormat tableFormat;
	QVector<QTextLength> constraints;
	constraints << QTextLength(QTextLength::FixedLength, 40);
	constraints << QTextLength(QTextLength::FixedLength, 50);
	constraints << QTextLength(QTextLength::FixedLength, 195);
	constraints << QTextLength(QTextLength::FixedLength, 65);
	constraints << QTextLength(QTextLength::FixedLength, 65);
	constraints << QTextLength(QTextLength::FixedLength, 65);
	constraints << QTextLength(QTextLength::FixedLength, 65);
	constraints << QTextLength(QTextLength::FixedLength, 80);
	constraints << QTextLength(QTextLength::FixedLength, 80);
	
	tableFormat.setColumnWidthConstraints(constraints);
	tableFormat.setCellSpacing(0);
	tableFormat.setCellPadding(1);
	tableFormat.setBorder(0.6);
	tableFormat.setBorderBrush(QColor(Qt::black));
	tableFormat.setHeaderRowCount(1);
	QTextTable *table = cursor.insertTable(2 + rowCount, colCount, tableFormat);
	UPopulateCell tableCell(table);
	
	blockFormat.setBottomMargin(0);
	blockFormat.setTopMargin(0);
	
	//Заповнення шапки таблиці
	textCharFormat.setFontPointSize( 8 );
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	textCharFormat_bold.setFontPointSize( 8 );
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	
	tableCell.setAlignment(Qt::AlignCenter);
	tableCell.set(0,0,"№ з/п", textCharFormat);
	tableCell.set(0,1,"Таб.ном.", textCharFormat);
	tableCell.set(0,2,"ПІБ", textCharFormat);
	tableCell.set(0,3,"№ звіту", textCharFormat);
	tableCell.set(0,4,"Дата", textCharFormat);
	tableCell.set(0,5,"# запр.", textCharFormat);
	tableCell.set(0,6,"№ док.", textCharFormat);
	tableCell.set(0,7,"К-сть", textCharFormat);
	tableCell.set(0,8,"Сума, грн", textCharFormat);
	
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignTop);
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignTop);
	
    double dVal, allKilkist = 0, allSuma = 0;	
	query.exec("SELECT zvit.Npr_id, npr.Prizv, npr.Imia, npr.PoBatk, zvit.ZvitNum, \
						orders.CDate, orders.KodZapravky, orders.DocNum, orders.Kilkist, orders.Suma \
				FROM ((zvitKupivliPalnogo zvit \
				LEFT JOIN zvitKupivliPalnogoOrders orders \
					ON orders.zvitKupivliPalnogo_id=zvit.id) \
				LEFT JOIN npr \
					ON npr.id=zvit.Npr_id) \
				WHERE year(orders.CDate)="+sqlStr(vDate.year())+" \
					and month(orders.CDate)="+sqlStr(vDate.month())+" \
					and zvit.MarkaPalnogo_id="+sqlStr(markaPalnogoId)+" \
					and zvit.DovPartners_id="+sqlStr(partnerId)+" \
					and orders.id>0 \
				ORDER BY npr.Prizv, npr.Imia, npr.PoBatk");
	int row;
	for (row = 1; row <= rowCount && query.next(); row++) {
	    tableCell.setAlignment(Qt::AlignRight);
		// "№ з/п"
		tableCell.set(row,0,row, textCharFormat);
		// Таб.ном."
		tableCell.set(row,1,query.value(0).toInt(), textCharFormat);
		// "ПІБ"
		tableCell.setAlignment(Qt::AlignLeft);
		tableCell.set(row,2,uPrizvIB(query.value(1).toString(), query.value(2).toString(), query.value(3).toString()), textCharFormat);
		// "№ звіту"
		tableCell.setAlignment(Qt::AlignRight);
		tableCell.set(row,3,query.value(4).toString(), textCharFormat);
		// "Дата"
		tableCell.set(row,4,!query.value(5).isNull() ? query.value(5).toDate().toString("dd.MM.yyyy") : "-", textCharFormat);
		// "# запр."
		tableCell.set(row,5,query.value(6).toString(), textCharFormat);
		// "№ док."
		tableCell.set(row,6,query.value(7).toString(), textCharFormat);
		// "К-сть"
		dVal = query.value(8).toDouble();
		allKilkist += dVal;
		tableCell.setDash(row,7,dVal, textCharFormat);
		// "Сума"
		dVal = uDToM(query.value(9).toDouble());
		allSuma += dVal;
		tableCell.setDash(row,8,dVal, textCharFormat);
		
		postup->incPos();
	}
	
	table->mergeCells(row, 0, 1, 7);
	
	tableCell.set(row,0,"Разом", textCharFormat);
	// "К-сть"
	tableCell.setDash(row,7,allKilkist, textCharFormat);
	// "Сума"
	tableCell.setDash(row,8,allSuma, textCharFormat);
	
	//Підписи
	cursor.movePosition(QTextCursor::End);
	cursor.insertBlock(blockFormat);
	textCharFormat.setFontPointSize( 9 );
	cursor.insertFragment(pidpysy(14, textCharFormat, QPrinter::Portrait));
	
	delete postup;
	
	printform->printer()->setDocName("Реєстр чеків за "+vDate.toString("MM.yyyy"));
	printform->show();
}
//--------------------utech--------------------utech--------------------utech--------------------
