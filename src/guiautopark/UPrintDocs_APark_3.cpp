//--------------------utech--------------------utech--------------------utech--------------------
//
// ��������� ������������ ������ "����" 23.04.2009�.
// � ���� ���������������� ���������� �������� QT4.x
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
    printform = new UPrintForm(0, "����� ���� �� ��������� ��������� ��������� ��� �� "+vDate.toString("MM.yyyy"));
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
	cursor.insertText("�������� �������� ��������� \"�������� ��������\" "+QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm"), textCharFormat);
	blockFormat.setAlignment( Qt::AlignCenter );
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	textCharFormat_bold.setFontPointSize( 13 );
	cursor.insertText("�Ū���\n", textCharFormat_bold);
	textCharFormat_bold.setFontPointSize( 12 );
	cursor.insertText("���� �� ��������� ��������� ��������� ���\n�� "+zaprName+"\n", textCharFormat_bold);
	cursor.insertText("�� "+monthlist[vDate.month()-1]+" "+QString::number(vDate.year())+" ����\n", textCharFormat_bold);
	cursor.insertText(OrganizName(), textCharFormat_bold);
	
	blockFormat.setAlignment( Qt::AlignLeft );
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	
	textCharFormat.setFontPointSize( 11 );
	textCharFormat_bold.setFontPointSize( 11 );
	cursor.insertText("�������� ����������:\n", textCharFormat);
	cursor.insertText("������������� ���������� �����: ", textCharFormat);
	cursor.insertText(OrganizIPN()+"\n", textCharFormat_bold);
	cursor.insertText("����� �������� �������� ���: ", textCharFormat);
	cursor.insertText(OrganizSvidPDVNum()+"\n", textCharFormat_bold);
	cursor.insertText("�������� ������: ", textCharFormat);
	cursor.insertText(OrganizAdresa()+"\n", textCharFormat_bold);
	cursor.insertText("Գ����� ������: ", textCharFormat);
	cursor.insertText(OrganizAdresa(), textCharFormat_bold);
	
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	
	//��������� �������
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
	
	//���������� ����� �������
	textCharFormat.setFontPointSize( 9.5 );
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	textCharFormat_bold.setFontPointSize( 9.5 );
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	
	tableCell.setAlignment(Qt::AlignCenter);
	tableCell.set(0,0,"� �/�", textCharFormat);
	tableCell.set(0,1,"� ����", textCharFormat);
	tableCell.set(0,2,"����", textCharFormat);
	tableCell.set(0,3,"��'�� (�.���)", textCharFormat);
	tableCell.set(0,4,"���� (���.)", textCharFormat);
	tableCell.set(0,5,"� �.�. ���", textCharFormat);
	
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
	    // "� �/�"
		tableCell.set(row,0,row, textCharFormat);
	    // "� ����"
		tableCell.setAlignment(Qt::AlignLeft);
                tableCell.set(row,1,"��� �"+query.value(0).toString(), textCharFormat);
	    // "����"
		tableCell.setAlignment(Qt::AlignRight);
		tableCell.set(row,2,query.value(1).toDate().toString("dd.MM.yyyy"), textCharFormat);
	    // "��'�� (�.���)"
		dVal = query.value(2).toDouble();
		obyemSum += dVal;
		tableCell.set(row,3,uMToStr2(dVal), textCharFormat);
	    // "���� (���.)"
		dVal = query.value(3).toDouble();
		sumaSum += dVal;
		tableCell.set(row,4,uMToStr2(dVal), textCharFormat);
	    // "� �.�. ���"
		dVal = uDToM(dVal / 6.0);
		pdvSum += dVal;
		tableCell.set(row,5,uMToStr2(dVal), textCharFormat);
		
		postup->incPos();
	}
	
	table->mergeCells(row, 0, 1, 3);
	
	tableCell.set(row,0,"�����", textCharFormat);
	// "��'�� (�.���)"
	tableCell.set(row,3,uMToStr2(obyemSum), textCharFormat);
	// "���� (���.)"
	tableCell.set(row,4,uMToStr2(sumaSum), textCharFormat);
	// "� �.�. ���"
	tableCell.set(row,5,uMToStr2(pdvSum), textCharFormat);
	
	//ϳ�����
	textCharFormat.setFontPointSize( 9 );
	cursor.movePosition(QTextCursor::End);
	cursor.insertFragment(pidpysy(12, textCharFormat, QPrinter::Portrait));
	
	delete postup;
	
	printform->printer()->setDocName("����� ���� �� ��������� ��������� ��������� ��� �� "+vDate.toString("MM.yyyy"));
	printform->show();
}
//--------------------utech--------------------utech--------------------utech--------------------
void UPrintDocs_APark::print_reyestrChekivGazZaMisyacDaily(QDate vDate, int partnerId)
{
    printform = new UPrintForm(0, "����� ���� �� ��������� ��������� ��������� ��� �� "+vDate.toString("MM.yyyy"));
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
	cursor.insertText("�������� �������� ��������� \"�������� ��������\" "+QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm"), textCharFormat);
	blockFormat.setAlignment( Qt::AlignCenter );
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	textCharFormat_bold.setFontPointSize( 13 );
	cursor.insertText("�Ū���\n", textCharFormat_bold);
	textCharFormat_bold.setFontPointSize( 12 );
	cursor.insertText("���� �� ��������� ��������� ��������� ���\n�� "+zaprName+"\n", textCharFormat_bold);
	cursor.insertText("�� "+monthlist[vDate.month()-1]+" "+QString::number(vDate.year())+" ����\n", textCharFormat_bold);
	cursor.insertText(OrganizName(), textCharFormat_bold);
	
	blockFormat.setAlignment( Qt::AlignLeft );
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	
	textCharFormat.setFontPointSize( 11 );
	textCharFormat_bold.setFontPointSize( 11 );
	cursor.insertText("�������� ����������:\n", textCharFormat);
	cursor.insertText("������������� ���������� �����: ", textCharFormat);
	cursor.insertText(OrganizIPN()+"\n", textCharFormat_bold);
	cursor.insertText("����� �������� �������� ���: ", textCharFormat);
	cursor.insertText(OrganizSvidPDVNum()+"\n", textCharFormat_bold);
	cursor.insertText("�������� ������: ", textCharFormat);
	cursor.insertText(OrganizAdresa(), textCharFormat_bold);
	
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	
	//��������� �������
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
	
	//���������� ����� �������
	textCharFormat.setFontPointSize( 9.5 );
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	textCharFormat_bold.setFontPointSize( 9.5 );
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	
	tableCell.setAlignment(Qt::AlignCenter);
	tableCell.set(0,0,"����", textCharFormat);
	tableCell.set(0,1,"� ��������� ��������", textCharFormat);
	tableCell.set(0,2,"��'��, �.���", textCharFormat);
	tableCell.set(0,3,"���.���� ������., � ��� (���.)", textCharFormat);
	tableCell.set(0,4,"� �.�. ���� ��� ���(���.)", textCharFormat);
	tableCell.set(0,5,"� �.�. ���", textCharFormat);
	
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
	    // "����"
		tableCell.set(row,0,xDate.toString("dd.MM.yyyy"), textCharFormat);
	    // "� ��������� ��������"
		tableCell.setAlignment(Qt::AlignLeft);
		//tableCell.set(row,1,query.value(0).toString(), textCharFormat);
	    // "��'��, �.���"
		tableCell.setAlignment(Qt::AlignRight);
		dVal = query.value(0).toDouble();
		obyemSum += dVal;
		tableCell.setDash(row,2,dVal, textCharFormat);
	    // "�������� ���� ����������, ��������� ��� (���.)"
		dVal = query.value(1).toDouble();
		sumaSum += dVal;
		double curSuma = dVal;
		tableCell.setDash(row,3,dVal, textCharFormat);
		// "� �.�. ���"
		dVal = uDToM(curSuma / 6.0);
		pdvSum += dVal;
		double curPdv = dVal;
		tableCell.setDash(row,5,dVal, textCharFormat);
	    // "� �.�. ���� ��� ���(���.)"
		dVal = curSuma - curPdv;
		tableCell.setDash(row,4,dVal, textCharFormat);
		
		postup->incPos();
	}
	
	++row;
	table->mergeCells(row, 0, 1, 2);
	
	tableCell.setAlignment(Qt::AlignRight);
	tableCell.set(row,0,"�����", textCharFormat);
	// "��'��, �.���"
	tableCell.setDash(row,2,obyemSum, textCharFormat);
	// "�������� ���� ����������, ��������� ��� (���.)"
	tableCell.setDash(row,3,sumaSum, textCharFormat);
	// "� �.�. ���"
	tableCell.setDash(row,5,pdvSum, textCharFormat);
	// "� �.�. ���� ��� ���(���.)"
	tableCell.setDash(row,4,sumaSum-pdvSum, textCharFormat);
	
	//ϳ�����
	textCharFormat.setFontPointSize( 9 );
	cursor.movePosition(QTextCursor::End);
	cursor.insertFragment(pidpysy(12, textCharFormat, QPrinter::Portrait));
	
	delete postup;
	
	printform->printer()->setDocName("����� ���� �� ��������� ��������� ��������� ��� �� "+vDate.toString("MM.yyyy"));
	printform->show();
}
//--------------------utech--------------------utech--------------------utech--------------------
void UPrintDocs_APark::print_reyestrChekivPalneZaMisyac(QDate vDate)
{
    printform = new UPrintForm(0, "����� ���� �� �������� ������ ��� �� "+vDate.toString("MM.yyyy"));
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
	cursor.insertText("�������� �������� ��������� \"�������� ��������\" "+QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm"), textCharFormat);
	blockFormat.setAlignment( Qt::AlignCenter );
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	textCharFormat_bold.setFontPointSize( 13 );
	cursor.insertText("�Ū���\n", textCharFormat_bold);
	textCharFormat_bold.setFontPointSize( 12 );
	cursor.insertText("���� �� �������� ������\n", textCharFormat_bold);
	cursor.insertText("�� "+monthlist[vDate.month()-1]+" "+QString::number(vDate.year())+" ����\n", textCharFormat_bold);
	cursor.insertText(OrganizName(), textCharFormat_bold);
	
	blockFormat.setAlignment( Qt::AlignLeft );
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	
	textCharFormat.setFontPointSize( 10 );
	textCharFormat_bold.setFontPointSize( 10 );
	cursor.insertText("�������� ����������:\n", textCharFormat);
	cursor.insertText("������������� ���������� �����: ", textCharFormat);
	cursor.insertText(OrganizIPN()+"\n", textCharFormat_bold);
	cursor.insertText("����� �������� �������� ���: ", textCharFormat);
	cursor.insertText(OrganizSvidPDVNum()+"\n", textCharFormat_bold);
	cursor.insertText("�������� ������: ", textCharFormat);
	cursor.insertText(OrganizAdresa()+"\n", textCharFormat_bold);
	cursor.insertText("Գ����� ������: ", textCharFormat);
	cursor.insertText(OrganizAdresa(), textCharFormat_bold);
	
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	
	//��������� �������
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
	
	//���������� ����� �������
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
	tableCell.set(0,0,"����", textCharFormat);
	
	tableCell.set(0,1,"���������", textCharFormat);
	tableCell.set(0,3,"�-95", textCharFormat);
	tableCell.set(0,5,"�-92", textCharFormat);
	tableCell.set(0,7,"�-80", textCharFormat);
	tableCell.set(0,9,"���, ������-�����", textCharFormat);
	tableCell.set(0,11,"������, ���.", textCharFormat);
	
	tableCell.set(1,1,"�-���, �.", textCharFormat);
	tableCell.set(1,2,"����, ���.", textCharFormat);
	tableCell.set(1,3,"�-���, �.", textCharFormat);
	tableCell.set(1,4,"���� (���.)", textCharFormat);
	tableCell.set(1,5,"�-���, �.", textCharFormat);
	tableCell.set(1,6,"����, ���.", textCharFormat);
	tableCell.set(1,7,"�-���, �.", textCharFormat);
	tableCell.set(1,8,"����, ���.", textCharFormat);
	tableCell.set(1,9,"�-���, �.", textCharFormat);
	tableCell.set(1,10,"����, ���.", textCharFormat);
	
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
	    // ����
		tableCell.set(row,0,xDate.toString("dd.MM"), textCharFormat);
		// ���������
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
		// �-95
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
		// �-92
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
		// �-80
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
		
		// ���, ������-�����
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
		
		// ������
		sumCol[11] += rowSum;
		tableCell.setDash(row, 11, rowSum, textCharFormat);
		
		postup->incPos();
	}
	
	row++;
	tableCell.set(row, 0, "�����", textCharFormat);
	for(int col = 1; col< colCount; col++)
	    tableCell.setDash(row, col, sumCol[col], textCharFormat);
	
	//ϳ�����
	textCharFormat.setFontPointSize( 9 );
	cursor.movePosition(QTextCursor::End);
	cursor.insertFragment(pidpysy(13, textCharFormat, QPrinter::Portrait));
	
	delete postup;
	
	printform->printer()->setDocName("����� ���� �� �������� ������ ��� �� "+vDate.toString("MM.yyyy"));
	printform->show();
}
//--------------------utech--------------------utech--------------------utech--------------------
void UPrintDocs_APark::print_reyestrChekivVidPostachalnyksPalneZaMisyac(int partnerId, QDate vDate)
{
    printform = new UPrintForm(0, "����� ���� �� �������� ������ ��� �� "+vDate.toString("MM.yyyy"));
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
        cursor.insertText("�������� �������� ��������� \"�������� ��������\" "+QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm"), textCharFormat);
        blockFormat.setAlignment( Qt::AlignCenter );
        cursor.insertBlock(blockFormat);
        cursor.insertBlock(blockFormat);
        cursor.insertBlock(blockFormat);
        textCharFormat_bold.setFontPointSize( 13 );
        cursor.insertText("�Ū���\n", textCharFormat_bold);
        textCharFormat_bold.setFontPointSize( 12 );
        cursor.insertText("���� �� �������� ������ � �������������\n", textCharFormat_bold);
		query.exec("SELECT Name FROM dovPartners WHERE id="+sqlStr(partnerId));
		query.next();
		cursor.insertText(query.value(0).toString()+"\n", textCharFormat_bold);
        cursor.insertText("�� "+monthlist[vDate.month()-1]+" "+QString::number(vDate.year())+" ����\n", textCharFormat_bold);
        cursor.insertText(OrganizName(), textCharFormat_bold);

        blockFormat.setAlignment( Qt::AlignLeft );
        cursor.insertBlock(blockFormat);
        cursor.insertBlock(blockFormat);

        textCharFormat.setFontPointSize( 10 );
        textCharFormat_bold.setFontPointSize( 10 );
        cursor.insertText("�������� ����������:\n", textCharFormat);
        cursor.insertText("������������� ���������� �����: ", textCharFormat);
        cursor.insertText(OrganizIPN()+"\n", textCharFormat_bold);
        cursor.insertText("����� �������� �������� ���: ", textCharFormat);
        cursor.insertText(OrganizSvidPDVNum()+"\n", textCharFormat_bold);
        cursor.insertText("�������� ������: ", textCharFormat);
        cursor.insertText(OrganizAdresa()+"\n", textCharFormat_bold);
        cursor.insertText("Գ����� ������: ", textCharFormat);
        cursor.insertText(OrganizAdresa(), textCharFormat_bold);

        cursor.insertBlock(blockFormat);
        cursor.insertBlock(blockFormat);

        //��������� �������
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

        //���������� ����� �������
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
        tableCell.set(0,0,"����", textCharFormat);

        tableCell.set(0,1,"���������", textCharFormat);
        tableCell.set(0,3,"�-95", textCharFormat);
        tableCell.set(0,5,"�-92", textCharFormat);
        tableCell.set(0,7,"�-80", textCharFormat);
        tableCell.set(0,9,"���, ������-�����", textCharFormat);
        tableCell.set(0,11,"������, ���.", textCharFormat);

        tableCell.set(1,1,"�-���, �.", textCharFormat);
        tableCell.set(1,2,"����, ���.", textCharFormat);
        tableCell.set(1,3,"�-���, �.", textCharFormat);
        tableCell.set(1,4,"���� (���.)", textCharFormat);
        tableCell.set(1,5,"�-���, �.", textCharFormat);
        tableCell.set(1,6,"����, ���.", textCharFormat);
        tableCell.set(1,7,"�-���, �.", textCharFormat);
        tableCell.set(1,8,"����, ���.", textCharFormat);
        tableCell.set(1,9,"�-���, �.", textCharFormat);
        tableCell.set(1,10,"����, ���.", textCharFormat);

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
            // ����
                tableCell.set(row,0,xDate.toString("dd.MM"), textCharFormat);
                // ���������
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
                // �-95
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
                // �-92
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
                // �-80
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

                // ���, ������-�����
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

                // ������
                sumCol[11] += rowSum;
                tableCell.setDash(row, 11, rowSum, textCharFormat);

                postup->incPos();
        }

        row++;
        tableCell.set(row, 0, "�����", textCharFormat);
        for(int col = 1; col< colCount; col++)
            tableCell.setDash(row, col, sumCol[col], textCharFormat);

        //ϳ�����
        textCharFormat.setFontPointSize( 9 );
        cursor.movePosition(QTextCursor::End);
        cursor.insertFragment(pidpysy(13, textCharFormat, QPrinter::Portrait));

        delete postup;

        printform->printer()->setDocName("����� ���� �� �������� ������ ��� �� "+vDate.toString("MM.yyyy"));
        printform->show();
}
//--------------------utech--------------------utech--------------------utech--------------------
void UPrintDocs_APark::print_vidomistZakupivliPalnogoPoVodiyahZaMisyac(QDate vDate, int markaPalnogoId)
{
    printform = new UPrintForm(0, "³������ ������� �������� �� ����� �� "+vDate.toString("MM.yyyy"));
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
	cursor.insertText("�������� �������� ��������� \"�������� ��������\" "+QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm"), textCharFormat);
	blockFormat.setAlignment( Qt::AlignCenter );
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	textCharFormat_bold.setFontPointSize( 13 );
	cursor.insertText("²��̲���\n", textCharFormat_bold);
	textCharFormat_bold.setFontPointSize( 12 );
	cursor.insertText("������� �������� �� �����\n", textCharFormat_bold);
	cursor.insertText("�� "+monthlist[vDate.month()-1]+" "+QString::number(vDate.year())+" ����\n", textCharFormat_bold);
	cursor.insertText(OrganizName(), textCharFormat_bold);
	blockFormat.setAlignment( Qt::AlignLeft );
	cursor.insertBlock(blockFormat);
	query.exec("SELECT MarkaName FROM markaPalnogo WHERE id="+sqlStr(markaPalnogoId));
	query.next();
	textCharFormat_bold.setFontPointSize( 10 );
	textCharFormat.setFontPointSize( 10 );
	cursor.insertText("��� ��������: ", textCharFormat);
	cursor.insertText(query.value(0).toString(), textCharFormat_bold);
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	
	//��������� �������
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
	
	//���������� ����� �������
	textCharFormat.setFontPointSize( 9 );
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	textCharFormat_bold.setFontPointSize( 9 );
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	
	tableCell.setAlignment(Qt::AlignCenter);
	tableCell.set(0,0,"� �/�", textCharFormat);
	tableCell.set(0,1,"���.���.", textCharFormat);
	tableCell.set(0,2,"ϲ�", textCharFormat);
	tableCell.set(0,3,"�-��� ���.", textCharFormat);
	tableCell.set(0,4,markaPalnogoId==6?"��'��, �.���":"��'��, �.", textCharFormat);
	tableCell.set(0,5,"71 ���.", textCharFormat);
	tableCell.set(0,6,markaPalnogoId==6?"06/4 ���.":"06/1", textCharFormat);
	tableCell.set(0,7,"68 ���.", textCharFormat);
	
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
	    // "� �/�"
		tableCell.set(row,0,row, textCharFormat);
		// "���.���."
		tableCell.set(row,1,query.value(0).toInt(), textCharFormat);
		// "ϲ�"
		tableCell.setAlignment(Qt::AlignLeft);
		tableCell.set(row,2,query.value(1).toString()+" "+query.value(2).toString()+" "+query.value(3).toString(), textCharFormat);
		// "�-��� ����"
		tableCell.setAlignment(Qt::AlignRight);
		iVal = query.value(6).toInt();
		chekySum += iVal;
		tableCell.set(row,3,iVal, textCharFormat);
		// "��'��"
		dVal = query.value(4).toDouble();
		obyemSum += dVal;
		tableCell.set(row,4,dVal, textCharFormat);
		// "71 ���."
		suma = query.value(5).toDouble();
		sumaSum += suma;
		tableCell.set(row,5,suma, textCharFormat);
		// "68 ���."
		dVal = uDToM(suma / 6.0);
		pdvSum += dVal;
		tableCell.set(row,7,dVal, textCharFormat);
		// "6/01 ���...."
		dVal = suma - dVal;
		withoutPdvSum += dVal;
		tableCell.set(row,6,dVal, textCharFormat);
		
		postup->incPos();
	}
	
	table->mergeCells(row, 0, 1, 3);
	
	tableCell.set(row,0,"�����", textCharFormat);
	// ʳ������ ����
	tableCell.set(row,3,chekySum, textCharFormat);
	// "��'�� (�.���)"
	tableCell.set(row,4,uMToStr2(obyemSum), textCharFormat);
	// "71
	tableCell.set(row,5,uMToStr2(sumaSum), textCharFormat);
	// 6/01...
	tableCell.set(row,6,uMToStr2(withoutPdvSum), textCharFormat);
	// 68
	tableCell.set(row,7,uMToStr2(pdvSum), textCharFormat);
	
	//ϳ�����
	
	cursor.movePosition(QTextCursor::End);
	cursor.insertBlock(blockFormat);
	textCharFormat.setFontPointSize( 7 );
	cursor.insertText("* � �������� ���������� ������ ��䳿�, �� �������� ������� ����� ���������� �������� ����� ��������.", textCharFormat);
	cursor.insertBlock(blockFormat);
	textCharFormat.setFontPointSize( 10 );
	cursor.insertFragment(pidpysy(14, textCharFormat, QPrinter::Portrait));
	
	delete postup;
	
	printform->printer()->setDocName("³������ ������� �������� �� ����� �� "+vDate.toString("MM.yyyy"));
	printform->show();
}
//--------------------utech--------------------utech--------------------utech--------------------
void UPrintDocs_APark::print_vidomistZakupivliPalnogoPoVodiyahZaMisyacVRozriziRahunkiv(QDate vDate)
{
    printform = new UPrintForm(0, "³������ ������� �������� �� ����� � ����� ������� �� "+vDate.toString("MM.yyyy"));
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
	cursor.insertText("�������� � ���� ��������", textCharFormat);
	
	
	printform->printer()->setDocName("³������ ������� �������� �� ����� � ����� ������� �� "+vDate.toString("MM.yyyy"));
	printform->show();
}
//--------------------utech--------------------utech--------------------utech--------------------
void UPrintDocs_APark::print_reyestrChekivZaPalyvnoMastylniMaterialy(QDate vDate, QDate eDate, int partnerId, int markaPalnogoId)
{
    printform = new UPrintForm(0, "�Ū��� ���� � "+vDate.toString("dd.MM.yyyy")+" �� "+eDate.toString("dd.MM.yyyy"));
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
	cursor.insertText("�������� �������� ��������� \"�������� ��������\" "+QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm"), textCharFormat);
	blockFormat.setAlignment( Qt::AlignCenter );
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	textCharFormat_bold.setFontPointSize( 11 );
	cursor.insertText("�Ū���\n", textCharFormat_bold);
	cursor.insertText("���� �� ������� ������-�������� ��������\n", textCharFormat_bold);
	query.exec("SELECT Name FROM dovPartners WHERE id="+sqlStr(partnerId));
	query.next();
	cursor.insertText("�a: ", textCharFormat_bold);
	cursor.insertText(query.value(0).toString(), textCharFormat_bold);

	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	
	textCharFormat.setFontPointSize( 10 );
    textCharFormat_bold.setFontPointSize( 10 );
	blockFormat.setAlignment( Qt::AlignLeft );
	cursor.setBlockFormat( blockFormat );
    cursor.insertText("�������� ����������:\n", textCharFormat);
    cursor.insertText("������������� ���������� �����: ", textCharFormat);
    cursor.insertText(OrganizIPN()+"\n", textCharFormat_bold);
    cursor.insertText("����� �������� �������� ���: ", textCharFormat);
    cursor.insertText(OrganizSvidPDVNum()+"\n", textCharFormat_bold);
    cursor.insertText("�������� ������: ", textCharFormat);
    cursor.insertText(OrganizAdresa()+"\n", textCharFormat_bold);
    cursor.insertText("Գ����� ������: ", textCharFormat);
    cursor.insertText(OrganizAdresa(), textCharFormat_bold);
	//cursor.insertText("�������: ", textCharFormat);
   // cursor.insertText(Organiz()+"\n", textCharFormat_bold);	

    cursor.insertBlock(blockFormat);
    cursor.insertBlock(blockFormat);
	
	//��������� �������
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
	
	//���������� ����� �������
	textCharFormat.setFontPointSize( 8 );
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	textCharFormat_bold.setFontPointSize( 8 );
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	
	tableCell.setAlignment(Qt::AlignCenter);
	tableCell.set(0,0,"� �/�", textCharFormat);
	tableCell.set(0,1,"����", textCharFormat);
	tableCell.set(0,2,"��� ������", textCharFormat);
	tableCell.set(0,3,"� ���", textCharFormat);
	tableCell.set(0,4,"� ����", textCharFormat);
	tableCell.set(0,5,"�-��� �.", textCharFormat);
	tableCell.set(0,6,"ֳ�� �� 1 �.", textCharFormat);
	tableCell.set(0,7,"�������� ����", textCharFormat);
	tableCell.set(0,8,"���", textCharFormat);
	tableCell.set(0,9,"���� ��� ���", textCharFormat);
	
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
		// "ֳ��"
		tableCell.set(row,5,query.value(4).toDouble(), textCharFormat);
		// "�������� ����"
		tableCell.set(row,6,query.value(5).toDouble(), textCharFormat);
		// "���"
		dVal = query.value(6).toDouble();
		allSuma += dVal;
		tableCell.setDash(row,7,dVal, textCharFormat);
		// "��� ���"
		dVal = uDToM(query.value(7).toDouble());
		allPDV += dVal;
		tableCell.setDash(row,8,dVal, textCharFormat);
		
		dVal = uDToM(query.value(8).toDouble());
		allBezPDV += dVal;
		tableCell.setDash(row,9,dVal, textCharFormat);

		
		postup->incPos();
	}
	
	table->mergeCells(row, 0, 1, 7);
	
	tableCell.set(row,0,"�����", textCharFormat);
	// "�-���"
	tableCell.setDash(row,7,allSuma, textCharFormat);
	// "����"
	tableCell.setDash(row,8,allPDV, textCharFormat);
	
	tableCell.setDash(row,9,allBezPDV, textCharFormat);

	
	//ϳ�����
	cursor.movePosition(QTextCursor::End);
	cursor.insertBlock(blockFormat);
	textCharFormat.setFontPointSize( 9 );
	cursor.insertFragment(pidpysy(15, textCharFormat, QPrinter::Portrait));
	
	delete postup;
	
	printform->printer()->setDocName("����� ���� � "+vDate.toString("dd.MM.yyyy")+" �� "+eDate.toString("dd.MM.yyyy"));
	printform->show();
	
}
//--------------------utech--------------------utech--------------------utech--------------------
void UPrintDocs_APark::print_reyestrChekivVidPostachalnykaPoVyduPalnogo(QDate vDate, int partnerId, int markaPalnogoId)
{
	printform = new UPrintForm(0, "����� ���� �� "+vDate.toString("MM.yyyy"));
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
	cursor.insertText("�������� �������� ��������� \"�������� ��������\" "+QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm"), textCharFormat);
	blockFormat.setAlignment( Qt::AlignCenter );
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	textCharFormat_bold.setFontPointSize( 11 );
	cursor.insertText("�Ū���\n", textCharFormat_bold);
	cursor.insertText("������� ��������\n", textCharFormat_bold);
	cursor.insertText("�� "+monthlist[vDate.month()-1]+" "+QString::number(vDate.year())+" ����\n", textCharFormat_bold);
	cursor.insertText(OrganizName(), textCharFormat_bold);
	blockFormat.setAlignment( Qt::AlignLeft );
	cursor.insertBlock(blockFormat);
	query.exec("SELECT Name FROM dovPartners WHERE id="+sqlStr(partnerId));
	query.next();
	textCharFormat_bold.setFontPointSize( 10 );
	textCharFormat.setFontPointSize( 10 );
	cursor.insertText("������������: ", textCharFormat);
	cursor.insertText(query.value(0).toString(), textCharFormat_bold);
	query.exec("SELECT MarkaName FROM markaPalnogo WHERE id="+sqlStr(markaPalnogoId));
	query.next();
	cursor.insertBlock(blockFormat);
	cursor.insertText("��� ��������: ", textCharFormat);
	cursor.insertText(query.value(0).toString(), textCharFormat_bold);
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	
	//��������� �������
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
	
	//���������� ����� �������
	textCharFormat.setFontPointSize( 8 );
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	textCharFormat_bold.setFontPointSize( 8 );
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	
	tableCell.setAlignment(Qt::AlignCenter);
	tableCell.set(0,0,"� �/�", textCharFormat);
	tableCell.set(0,1,"���.���.", textCharFormat);
	tableCell.set(0,2,"ϲ�", textCharFormat);
	tableCell.set(0,3,"� ����", textCharFormat);
	tableCell.set(0,4,"����", textCharFormat);
	tableCell.set(0,5,"# ����.", textCharFormat);
	tableCell.set(0,6,"� ���.", textCharFormat);
	tableCell.set(0,7,"�-���", textCharFormat);
	tableCell.set(0,8,"����, ���", textCharFormat);
	
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
		// "� �/�"
		tableCell.set(row,0,row, textCharFormat);
		// ���.���."
		tableCell.set(row,1,query.value(0).toInt(), textCharFormat);
		// "ϲ�"
		tableCell.setAlignment(Qt::AlignLeft);
		tableCell.set(row,2,uPrizvIB(query.value(1).toString(), query.value(2).toString(), query.value(3).toString()), textCharFormat);
		// "� ����"
		tableCell.setAlignment(Qt::AlignRight);
		tableCell.set(row,3,query.value(4).toString(), textCharFormat);
		// "����"
		tableCell.set(row,4,!query.value(5).isNull() ? query.value(5).toDate().toString("dd.MM.yyyy") : "-", textCharFormat);
		// "# ����."
		tableCell.set(row,5,query.value(6).toString(), textCharFormat);
		// "� ���."
		tableCell.set(row,6,query.value(7).toString(), textCharFormat);
		// "�-���"
		dVal = query.value(8).toDouble();
		allKilkist += dVal;
		tableCell.setDash(row,7,dVal, textCharFormat);
		// "����"
		dVal = uDToM(query.value(9).toDouble());
		allSuma += dVal;
		tableCell.setDash(row,8,dVal, textCharFormat);
		
		postup->incPos();
	}
	
	table->mergeCells(row, 0, 1, 7);
	
	tableCell.set(row,0,"�����", textCharFormat);
	// "�-���"
	tableCell.setDash(row,7,allKilkist, textCharFormat);
	// "����"
	tableCell.setDash(row,8,allSuma, textCharFormat);
	
	//ϳ�����
	cursor.movePosition(QTextCursor::End);
	cursor.insertBlock(blockFormat);
	textCharFormat.setFontPointSize( 9 );
	cursor.insertFragment(pidpysy(14, textCharFormat, QPrinter::Portrait));
	
	delete postup;
	
	printform->printer()->setDocName("����� ���� �� "+vDate.toString("MM.yyyy"));
	printform->show();
}
//--------------------utech--------------------utech--------------------utech--------------------
