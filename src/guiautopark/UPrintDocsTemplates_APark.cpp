//--------------------utech--------------------utech--------------------utech--------------------
//
// ��������� ������������ ������ "����" 23.04.2009�.
// � ���� ���������������� ���������� �������� QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#include "UPrintDocs_APark.h"

#include <UPopulateTextTableCells>
#include <UPostupForm>
#include <USqlAccessible>
#include <math.h>
#include "UDifFunc.h"
#include "UAutoParkMeneger_APark.h"

//--------------------utech--------------------utech--------------------utech--------------------
QTextDocumentFragment UPrintDocs_APark::create_backSideLystkaRegulyarnostiRuhu()
{
	QTextDocument * doc = new QTextDocument(); 
	
	//����� ���������
	QTextBlockFormat blockFormat;
	QTextTableCell cell;
	QTextCharFormat textCharFormat, textCharFormat_bold, textCharFormat_small;
	QFont fnt = textCharFormat_bold.font();
	fnt.setBold(true);
	textCharFormat_bold.setFont(fnt);
	
	QTextCursor cursor(doc), cellCursor;
	blockFormat.setAlignment( Qt::AlignLeft );
	cursor.setBlockFormat( blockFormat );
	textCharFormat_bold.setFontPointSize( 10 );
	textCharFormat_small.setFontPointSize( 5 );
	cursor.insertText("��� ����������� �� ����� ������������� ������� _______________________________", textCharFormat_bold);
	blockFormat.setAlignment( Qt::AlignHCenter );
	cursor.insertBlock(blockFormat);
	cursor.insertText(" ", textCharFormat_small);
	cursor.insertBlock(blockFormat);
	//��������� �������
	QTextTableFormat tableFormat;
	QVector<QTextLength> constraints;
	constraints << QTextLength(QTextLength::FixedLength, 250);
	constraints << QTextLength(QTextLength::FixedLength, 70);
	constraints << QTextLength(QTextLength::FixedLength, 70);
	constraints << QTextLength(QTextLength::FixedLength, 70);
	constraints << QTextLength(QTextLength::FixedLength, 70);
	constraints << QTextLength(QTextLength::FixedLength, 100);
	constraints << QTextLength(QTextLength::FixedLength, 100);
		
	tableFormat.setColumnWidthConstraints(constraints);
	tableFormat.setCellSpacing(0);
	tableFormat.setCellPadding(3);
	QTextTable *table = cursor.insertTable(18, 7, tableFormat);
	UPopulateCell tableCell(table);
	
	blockFormat.setBottomMargin(0);
	blockFormat.setTopMargin(0);
	
	table->mergeCells(0, 0, 3, 1);
	table->mergeCells(0, 1, 1, 4);
	table->mergeCells(1, 1, 1, 2);
	table->mergeCells(1, 3, 1, 2);
	
	table->mergeCells(0, 5, 3, 1);
	table->mergeCells(0, 6, 3, 1);
	
	//���������� ����� �������
	textCharFormat.setFontPointSize( 9 );
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	textCharFormat_bold.setFontPointSize( 9 );
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	
	tableCell.setAlignment(Qt::AlignCenter);
	tableCell.set(0,0,"�������", textCharFormat);
	tableCell.set(0,1,"��� ����������� � ����", textCharFormat);
	tableCell.set(0,5,"ϳ���� �� ����� ������� ����������", textCharFormat);
	tableCell.set(0,6,"³����� ������� ����������", textCharFormat);
	tableCell.set(1,1,"� ������� ��������", textCharFormat);
	tableCell.set(1,3,"� ���������� ��������", textCharFormat);
	tableCell.set(2,1,"�� ����.", textCharFormat);
	tableCell.set(2,2,"����.", textCharFormat);
	tableCell.set(2,3,"�� ����.", textCharFormat);
	tableCell.set(2,4,"����.", textCharFormat);
	
	cursor.movePosition(QTextCursor::End);
	blockFormat.setAlignment( Qt::AlignLeft );
	cursor.insertBlock(blockFormat);
	cursor.insertText(" ", textCharFormat_small);
	cursor.insertBlock(blockFormat);
	textCharFormat_bold.setFontPointSize( 10 );
	cursor.insertText("				˳����� ��������� _____________________", textCharFormat_bold);
	
	QTextDocumentFragment resultFragment(doc);
	
	delete doc;
	return resultFragment; 
}
//--------------------utech--------------------utech--------------------utech--------------------
QTextDocumentFragment UPrintDocs_APark::create_lystokRegulyarnostiRuhu(int id)
{
	QTextDocument * doc = new QTextDocument(); 
	
	QSqlQuery query, xQuery;
	query.exec("SELECT l.Auto_id, l.Vodiy_Id, l.Marshrut_id, l.GrafikNum, l.ZminaNum, \
					l.ReisyCount, mt.VytrPalnNaBezdor, l.BrygadaNum, l.VyizdDate, l.ZaizdDate, \
					l.Nochivlya, l.PlanNaZminu, l.MarkaPalnogo_id, l.PlanNormaPalnogo, \
					l.CinaPalnogo, r.GarajNumber, r.nomernyiZnak, m.MarkaName, l.CinaPalnogo, \
					n.Prizv, n.Imia, n.Pobatk, mt.MarshrutNapryamok, mt.ChasVyizdu, \
					r.MarkaAuto_id, m.MarkaRozm \
				FROM (((lystregulyarnostiruhu l \
				LEFT JOIN ruhomyiSklad r ON r.GarajNumber=l.Auto_id) \
				LEFT JOIN markaPalnogo m ON m.id=l.MarkaPalnogo_id) \
				LEFT JOIN npr n ON n.id=l.Vodiy_Id) \
				LEFT JOIN marshruty mt ON mt.KodMarshrutu=l.Marshrut_id \
											and l.GrafikNum=mt.GrafikNum \
											and l.ZminaNum=mt.ZminaNum \
				WHERE l.id="+QString::number(id));
	query.seek(0);
	//����� ���������
	QTextBlockFormat blockFormat;
	QTextTableCell cell;
	QTextCharFormat textCharFormat, textCharFormat_bold, textCharFormat_small;
	QFont fnt = textCharFormat_bold.font();
	fnt.setBold(true);
	textCharFormat_bold.setFont(fnt);
	
	QTextCursor cursor(doc), cellCursor;
	blockFormat.setAlignment( Qt::AlignLeft );
	cursor.setBlockFormat( blockFormat );
	textCharFormat_bold.setFontPointSize( 12 );
	cursor.insertText(OrganizShortName(), textCharFormat_bold);
	textCharFormat_small.setFontPointSize( 5 );
	textCharFormat_bold.setFontPointSize( 11 );
	textCharFormat.setFontPointSize( 11 );
	blockFormat.setAlignment( Qt::AlignRight );
	cursor.insertBlock(blockFormat);
	cursor.insertText((query.value(10).toInt()==2?QString("\"Ͳ�\"							"):QString("")), textCharFormat_bold);
	cursor.insertText("�������      ", textCharFormat);
	cursor.insertText(query.value(7).toString(), textCharFormat_bold);
	cursor.insertBlock(blockFormat);
	cursor.insertText(" ", textCharFormat_small);
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	blockFormat.setAlignment( Qt::AlignHCenter );
	cursor.insertBlock(blockFormat);
	textCharFormat_bold.setFontPointSize( 12 );
	cursor.insertText("������ ����������Ҳ ���� ��������", textCharFormat_bold);
	textCharFormat_bold.setFontPointSize( 11 );
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	blockFormat.setAlignment( Qt::AlignCenter );
	cursor.insertBlock(blockFormat);
	cursor.insertText("���� �����:  ", textCharFormat);
	cursor.insertText(query.value(8).toDate().toString("dd.MM.yyyy"), textCharFormat_bold);
	cursor.insertText("    �����:  ", textCharFormat);
	cursor.insertText(query.value(9).toDate().toString("dd.MM.yyyy"), textCharFormat_bold);
	blockFormat.setAlignment( Qt::AlignLeft );
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	
	//��������� �������, ��� ����� - ��������
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
	
	tableCell.set(0,0, "�������:  ", textCharFormat);
	tableCell.insertText("������. ����  ", textCharFormat);
	tableCell.insertText(query.value(16).toString(), textCharFormat_bold);
	tableCell.insertText(",    �����  ", textCharFormat);
	xQuery.exec("SELECT MarkaName, MarkaShyfr FROM markaauto WHERE id="+query.value(24).toString());
	if (xQuery.next())
		tableCell.insertText(xQuery.value(0).toString()+" "+xQuery.value(1).toString(), textCharFormat_bold);
	tableCell.set(0,1, query.value(15).toString(), textCharFormat_bold);
	tableCell.insertText("\n", textCharFormat);
	tableCell.insertText("\n", textCharFormat);
	
	tableCell.set(1,0, "����:  ", textCharFormat);
	tableCell.insertText(query.value(19).toString()+" "+query.value(20).toString()+" "+query.value(21).toString(), textCharFormat_bold);
	tableCell.set(1,1, query.value(1).toString(), textCharFormat_bold);
	tableCell.insertText("\n", textCharFormat);
	tableCell.insertText("\n", textCharFormat);
	
	tableCell.set(2,0, "�������:  ", textCharFormat);
	tableCell.insertText("    ����.  ", textCharFormat);
	tableCell.insertText(query.value(22).toString(), textCharFormat_bold);
	tableCell.insertText("    �����  ", textCharFormat);
	tableCell.insertText(query.value(5).toString(), textCharFormat_bold);
	tableCell.set(2,1, query.value(2).toString()+"."+query.value(3).toString()+"."+query.value(4).toString(), textCharFormat_bold);
	
	cursor.movePosition(QTextCursor::End);
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	cursor.insertText("���� �� ����: ", textCharFormat);
	cursor.insertText(uMToStr2(query.value(11).toDouble()), textCharFormat_bold);
	cursor.insertText(" ���.", textCharFormat);
	
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	cursor.insertText("���� ��������: ", textCharFormat);
	cursor.insertText(query.value(17).toString(), textCharFormat_bold);
	cursor.insertText(" (�����: ", textCharFormat);
	int planVytrPaln = qRound(query.value(13).toDouble());
	cursor.insertText(QString::number(planVytrPaln).replace('.',','), textCharFormat_bold);
	double cinaPalnogo = query.value(14).toDouble();
	if (cinaPalnogo>0.009){
		cursor.insertText(") x (����:  "+uMToStr2(cinaPalnogo), textCharFormat);
		cursor.insertText(") = (�������: "+uMToStr2(planVytrPaln*cinaPalnogo), textCharFormat);
		cursor.insertText(")", textCharFormat);
	}
	else{
		cursor.insertText(") x (����:  __________________", textCharFormat);
		cursor.insertText(") = (�������: __________________", textCharFormat);
		cursor.insertText(")", textCharFormat);
	}
	
	cursor.insertBlock(blockFormat);
	blockFormat.setAlignment( Qt::AlignCenter );
	cursor.insertBlock(blockFormat);
	cursor.insertText("��� �����   ", textCharFormat);
	cursor.insertText(query.value(23).toTime().toString("hh:mm"), textCharFormat_bold);
	blockFormat.setAlignment( Qt::AlignLeft );
	cursor.insertBlock(blockFormat);
	cursor.insertText(" ", textCharFormat_small);
	
	//��������� �������
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
	
	UWorkMonth wMonth(query.value(8).toDate());
	QSqlQuery q;
	q.exec("SELECT sum(PlanNaZminu), sum(VartProdKvytkiv), sum(VartProdKvytkivAutoStat), \
					sum(PlanRozhidPalnogo), sum(FactRozhidPalnogo), sum(zapravkaZaGotivku) \
				FROM shlyahovyilyst \
				WHERE VodiyTabelNum_id="+query.value(1).toString()+" \
					and ToZvitDate BETWEEN date("+sqlStr(wMonth.begDate())+") \
						AND date("+sqlStr(wMonth.endDate())+")");
	q.next();
	double plan = q.value(0).toDouble();
	double fact = q.value(1).toDouble() + q.value(2).toDouble();
	
	double PlanRozhidPalnogo = q.value(3).toDouble();
	double FactRozhidPalnogo = q.value(4).toDouble();
	double zapravkaZaGotivku = q.value(5).toDouble();
	double planSumaZapravku;
	
	double vidhObyem;
	double vidhSuma;
	
	if (FactRozhidPalnogo > 0.009){
		planSumaZapravku = zapravkaZaGotivku * PlanRozhidPalnogo / FactRozhidPalnogo;
		vidhObyem = uDToM(PlanRozhidPalnogo - FactRozhidPalnogo);
		vidhSuma = uDToM(planSumaZapravku - zapravkaZaGotivku);
	}
	else{
		vidhObyem = 0;
		vidhSuma = 0;
	}
		
	
	QString vidhObyemStr;
	QString vidhSumaStr;
	
	if (vidhObyem>=0.01)
		vidhObyemStr = "+"+uMToStr2(vidhObyem);
	else if (vidhObyem<=-0.01)
		vidhObyemStr = "-"+uMToStr2(fabs(vidhObyem));
	else
		vidhObyemStr = "0,00";
	
	if (vidhSuma>=0.01)
		vidhSumaStr = "+"+uMToStr2(vidhSuma);
	else if (vidhSuma<=-0.01)
		vidhSumaStr = "-"+uMToStr2(fabs(vidhSuma));
	else
		vidhSumaStr = "0,00";
	
	tableCell.setAlignment(Qt::AlignCenter);
	table->mergeCells(0,3,1,2);
	tableCell.set(0,0,"������� �������", textCharFormat);
	tableCell.set(0,1,"�������� �������", textCharFormat);
	tableCell.set(0,2,"³��������", textCharFormat);
	tableCell.set(0,3,"³�������� �� ��������", textCharFormat);
	//tableCell.set(0,4,"����. ����", textCharFormat);
	tableCell.set(1,0,plan, textCharFormat);
	tableCell.set(1,1,fact, textCharFormat);
	tableCell.set(1,2,fact - plan, textCharFormat);
	tableCell.set(1,3,vidhObyemStr+" "+query.value(25).toString(), textCharFormat);
	tableCell.set(1,4,vidhSumaStr+" ���.", textCharFormat);
	
	cursor.movePosition(QTextCursor::End);
	blockFormat.setAlignment( Qt::AlignLeft );
	cursor.insertBlock(blockFormat);
	
	QTextDocumentFragment resultFragment(doc);
	
	delete doc;
	return resultFragment; 
}
//--------------------utech--------------------utech--------------------utech--------------------
QTextDocumentFragment UPrintDocs_APark::create_kartkuOblikuVykonPlanu(QDate vDate, int vodiyTabNum)
{
	QTextDocument * doc = new QTextDocument(); 
	QSqlQuery query;
	
	//����� ���������
	QTextBlockFormat blockFormat;
	QTextTableCell cell;
	QTextCharFormat textCharFormat, textCharFormat_bold, textCharFormat_small;
	QFont fnt = textCharFormat_bold.font();
	fnt.setBold(true);
	textCharFormat_bold.setFont(fnt);
	
	QTextCursor cursor(doc), cellCursor;
	blockFormat.setAlignment( Qt::AlignRight );
	cursor.setBlockFormat( blockFormat );
	textCharFormat.setFontPointSize( 8 );
	cursor.insertText("�������� �������� ��������� \"�������� ��������\" "+QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm"), textCharFormat);
	cursor.insertBlock(blockFormat);
	blockFormat.setAlignment( Qt::AlignCenter );
	cursor.insertBlock(blockFormat);
	textCharFormat_bold.setFontPointSize( 12 );
	textCharFormat.setFontPointSize( 12 );
	cursor.insertText(OrganizShortName(), textCharFormat_bold);
	cursor.insertBlock(blockFormat);
	cursor.insertText("������ ��˲�� ��������� �����", textCharFormat_bold);
	blockFormat.setAlignment( Qt::AlignRight );
	cursor.insertBlock(blockFormat);
	cursor.insertText("  �� "+vDate.toString("yyyy")+" ��", textCharFormat);
	blockFormat.setAlignment( Qt::AlignLeft );
	cursor.insertBlock(blockFormat);
	cursor.insertText("  ���� ", textCharFormat);
	query.exec("SELECT Prizv, Imia, Pobatk FROM npr WHERE id="+QString::number(vodiyTabNum));
	query.seek(0);
	cursor.insertText(query.value(0).toString()+" "+query.value(1).toString()+" "+query.value(2).toString()+"  ["+QString::number(vodiyTabNum)+"]", textCharFormat_bold);
	cursor.insertBlock(blockFormat);
	
	//��������� �������
	QTextTableFormat tableFormat;
	QVector<QTextLength> constraints;
	constraints << QTextLength(QTextLength::FixedLength, 100);
	constraints << QTextLength(QTextLength::FixedLength, 110);
	constraints << QTextLength(QTextLength::FixedLength, 110);
	constraints << QTextLength(QTextLength::FixedLength, 80);
	constraints << QTextLength(QTextLength::FixedLength, 110);
	constraints << QTextLength(QTextLength::FixedLength, 60);
	constraints << QTextLength(QTextLength::FixedLength, 60);
	constraints << QTextLength(QTextLength::FixedLength, 60);
		
	tableFormat.setColumnWidthConstraints(constraints);
	tableFormat.setCellSpacing(0);
	tableFormat.setCellPadding(2);
	QTextTable *table = cursor.insertTable(34, 8, tableFormat);
	
	UPopulateCell tableCell(table);
	
	blockFormat.setBottomMargin(0);
	blockFormat.setTopMargin(0);
	
	//���������� ����� �������
	textCharFormat.setFontPointSize( 11 );
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	textCharFormat_bold.setFontPointSize( 10 );
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	
	table->mergeCells(0,0,2,1);
	table->mergeCells(0,1,1,2);
	table->mergeCells(0,3,2,1);
	table->mergeCells(0,4,2,1);
	table->mergeCells(0,5,2,1);
	table->mergeCells(0,6,2,1);
	table->mergeCells(0,7,2,1);
	
	tableCell.setAlignment(Qt::AlignCenter);
	tableCell.set(0,0,"̳����", textCharFormat);
	tableCell.set(0,1,"��������� ����� �������", textCharFormat);
	tableCell.set(1,1,"����", textCharFormat);
	tableCell.set(1,2,"��������", textCharFormat);
	tableCell.set(0,3,"% ���������", textCharFormat);
	tableCell.set(0,4,"����� ���� +\n �������� -", textCharFormat);
	tableCell.set(0,5,"", textCharFormat);
	tableCell.set(0,6,"", textCharFormat);
	tableCell.set(0,7,"", textCharFormat);
	
	tableCell.setAlignment(Qt::AlignLeft);
	tableCell.set(2,0,"ѳ����", textCharFormat);
	tableCell.set(3,0,"�����", textCharFormat);
	tableCell.set(4,0,"��������", textCharFormat);
	tableCell.set(5,0,"1 �������", textCharFormat_bold);
	tableCell.set(6,0,"������", textCharFormat);
	tableCell.set(7,0,"�������", textCharFormat);
	tableCell.set(8,0,"�������", textCharFormat);
	tableCell.set(9,0,"2 �������", textCharFormat_bold);
	tableCell.set(10,0,"�� 6 ������", textCharFormat_bold);
	tableCell.set(11,0,"������", textCharFormat);
	tableCell.set(12,0,"�������", textCharFormat);
	tableCell.set(13,0,"��������", textCharFormat);
	tableCell.set(14,0,"3 �������", textCharFormat_bold);
	tableCell.set(15,0,"�� 9 ������", textCharFormat_bold);
	tableCell.set(16,0,"�������", textCharFormat);
	tableCell.set(17,0,"��������", textCharFormat);
	tableCell.set(18,0,"�������", textCharFormat);
	tableCell.set(19,0,"4 �������", textCharFormat_bold);
	tableCell.set(20,0,"г����", textCharFormat_bold);
	
	//���������� ����� �������
	query.exec("CREATE TEMPORARY TABLE tempMonths( \
					month TINYINT PRIMARY KEY, \
					beginDate DATE, \
					endDate DATE \
				)");
	QDate beginDate(vDate.year(),1,26), endDate(vDate.year(),1,25);
	beginDate = beginDate.addMonths(-1);
	for (int month=1; month<=vDate.month(); month++){
		query.exec("INSERT INTO tempMonths (month, beginDate, endDate) \
					VALUES ("+QString::number(month)+", '"+beginDate.toString("yyyy-MM-dd")+"', '"+endDate.toString("yyyy-MM-dd")+"')");
		beginDate = beginDate.addMonths(1);
		endDate = endDate.addMonths(1);
	}
	query.exec("SELECT tempMonths.month, sum(s.PlanNaZminu), \
						sum(s.VartProdKvytkiv+s.vartProdKvytkivAutoStat) \
				FROM tempMonths \
				LEFT JOIN (SELECT * FROM shlyahovyiLyst \
						WHERE VodiyTabelNum_id="+QString::number(vodiyTabNum)+") AS s \
					ON s.ToZvitDate BETWEEN tempMonths.beginDate AND tempMonths.endDate \
				GROUP BY tempMonths.month");
	double plan = 0,
			planKvart = 0,
			planYear = 0,
			fact = 0,
			factKvart = 0,
			factYear = 0;
	int row = 1;
	while (query.next()){
		++ row;
		
		plan = qRound(100*query.value(1).toDouble())/100.0;
		fact = qRound(100*query.value(2).toDouble())/100.0;
		planKvart += plan;
		factKvart += fact;
		planYear += plan;
		factYear += fact;
		tableCell.setAlignment(Qt::AlignRight);
		tableCell.setDash(row,1,plan, textCharFormat);
		tableCell.setDash(row,2,fact, textCharFormat);
		if (plan != 0)
			tableCell.setDash(row,3,qRound(fact*10000/plan)/100.0, textCharFormat);
		else
			tableCell.set(row,3,"-", textCharFormat);
		if (fact-plan > 0)
			tableCell.set(row,4,"+"+QString::number(fact-plan), textCharFormat);
		else if (fact-plan == 0)
			tableCell.set(row,4,"-", textCharFormat);
		else
			tableCell.set(row,4,fact-plan, textCharFormat);
		
		//������ �������
		if (query.value(0).toInt() == 3){
			++row;
			plan = planKvart;
			fact = factKvart;
			tableCell.setDash(row,1,plan, textCharFormat_bold);
			tableCell.setDash(row,2,fact, textCharFormat_bold);
			if (plan != 0)
				tableCell.setDash(row,3,qRound(fact*10000/plan)/100.0, textCharFormat_bold);
			else
				tableCell.set(row,3,"-", textCharFormat_bold);
			if (fact-plan > 0)
				tableCell.set(row,4,"+"+QString::number(fact-plan), textCharFormat_bold);
			else if (fact-plan == 0)
				tableCell.set(row,4,"-", textCharFormat_bold);
			else
				tableCell.set(row,4,fact-plan, textCharFormat_bold);
			
			planKvart = 0;
			factKvart = 0;
		}
		
		//���� ������� + 6 ������ + 9 ������ + ��
		if ((query.value(0).toInt() == 6) || (query.value(0).toInt() == 9) || (query.value(0).toInt() == 12)){
			++row;
			plan = planKvart;
			fact = factKvart;
			tableCell.setDash(row,1,plan, textCharFormat_bold);
			tableCell.setDash(row,2,fact, textCharFormat_bold);
			if (plan != 0)
				tableCell.setDash(row,3,qRound(fact*10000/plan)/100.0, textCharFormat_bold);
			else
				tableCell.set(row,3,"-", textCharFormat_bold);
			if (fact-plan > 0)
				tableCell.set(row,4,"+"+QString::number(fact-plan), textCharFormat_bold);
			else if (fact-plan == 0)
				tableCell.set(row,4,"-", textCharFormat_bold);
			else
				tableCell.set(row,4,fact-plan, textCharFormat_bold);
			
			planKvart = 0;
			factKvart = 0;
			
			++row;
			plan = planYear;
			fact = factYear;
			tableCell.setDash(row,1,plan, textCharFormat_bold);
			tableCell.setDash(row,2,fact, textCharFormat_bold);
			if (plan != 0)
				tableCell.setDash(row,3,qRound(fact*10000/plan)/100.0, textCharFormat_bold);
			else
				tableCell.set(row,3,"-", textCharFormat_bold);
			if (fact-plan > 0)
				tableCell.set(row,4,"+"+QString::number(fact-plan), textCharFormat_bold);
			else if (fact-plan == 0)
				tableCell.set(row,4,"-", textCharFormat_bold);
			else
				tableCell.set(row,4,fact-plan, textCharFormat_bold);
		}
	}
	
	query.exec("DROP TEMPORARY TABLE IF EXISTS tempMonths");
	
	cursor.movePosition(QTextCursor::End);
	blockFormat.setAlignment( Qt::AlignLeft );
	cursor.insertBlock(blockFormat);
	
	cursor.insertFragment(pidpysy(2, textCharFormat));
	
	QTextDocumentFragment resultFragment(doc);
	
	delete doc;
	return resultFragment; 
}
//--------------------utech--------------------utech--------------------utech--------------------
QTextDocumentFragment UPrintDocs_APark::create_kartkaRobotyVodiya(QDate vDate, int vodiyTabNum)
{
	QTextDocument * doc = new QTextDocument(); 
	
	QSqlQuery query;
	QString pibStr = "-";
	query.exec("SELECT Prizv, Imia, Pobatk FROM npr WHERE id="+sqlStr(vodiyTabNum));
	if (query.next())
		pibStr = query.value(0).toString()+" "+query.value(1).toString()+" "+query.value(2).toString();
	
	int columnCount=19;
	UWorkMonth wMonth(vDate.year(), vDate.month());
	
	QTextCursor cursor(doc);
	QTextBlockFormat blockFormat;
	QTextTableCell cell;
	QTextCharFormat textCharFormat, textCharFormat_bold, textCharFormat_small;
	QFont fnt = textCharFormat_bold.font();
	fnt.setBold(true);
	textCharFormat_bold.setFont(fnt);
	
	blockFormat.setAlignment( Qt::AlignRight );
	cursor.setBlockFormat( blockFormat );
	textCharFormat.setFontPointSize( 8 );
	cursor.insertText("�������� �������� ��������� \"�������� ��������\" "+QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm")+". � ������� \"����\", ���: www.utech.com.ua", textCharFormat);
	textCharFormat_bold.setFontPointSize( 11 );
	textCharFormat_small.setFontPointSize( 5 );
	blockFormat.setAlignment( Qt::AlignCenter );
	cursor.insertBlock(blockFormat);
	query.exec("SELECT id, Prizv, Imia, Pobatk FROM npr WHERE id="+sqlStr(vodiyTabNum));
	cursor.insertText("������ ������ ���� �� ����� � "+wMonth.begDate().toString("dd.MM.yyyy")+" �� "+wMonth.endDate().toString("dd.MM.yyyy")+"�.", textCharFormat_bold);
	blockFormat.setAlignment( Qt::AlignLeft );
	textCharFormat_bold.setFontPointSize( 10 );
	cursor.insertBlock(blockFormat);
	cursor.insertText(" ", textCharFormat_small);
	
	//��������� �������
	QTextTableFormat tableFormat;
	QVector<QTextLength> constraints;
	constraints << QTextLength(QTextLength::FixedLength, 20);
	constraints << QTextLength(QTextLength::FixedLength, 40);
	constraints << QTextLength(QTextLength::FixedLength, 200);
	constraints << QTextLength(QTextLength::FixedLength, 30);
	constraints << QTextLength(QTextLength::FixedLength, 50);
	constraints << QTextLength(QTextLength::FixedLength, 50);
	constraints << QTextLength(QTextLength::FixedLength, 50);
	constraints << QTextLength(QTextLength::FixedLength, 40);
	constraints << QTextLength(QTextLength::FixedLength, 30);
	constraints << QTextLength(QTextLength::FixedLength, 30);
	constraints << QTextLength(QTextLength::FixedLength, 60);
	constraints << QTextLength(QTextLength::FixedLength, 60);
	constraints << QTextLength(QTextLength::FixedLength, 60);
	constraints << QTextLength(QTextLength::FixedLength, 60);
	constraints << QTextLength(QTextLength::FixedLength, 40);
	constraints << QTextLength(QTextLength::FixedLength, 40);
	constraints << QTextLength(QTextLength::FixedLength, 60);
	constraints << QTextLength(QTextLength::FixedLength, 60);
	constraints << QTextLength(QTextLength::FixedLength, 60);
		
	tableFormat.setColumnWidthConstraints(constraints);
	tableFormat.setCellSpacing(0);
	tableFormat.setCellPadding(1);
	tableFormat.setHeaderRowCount(2);
	tableFormat.setBorder(0.5);
	QTextTable *table = cursor.insertTable(3, columnCount, tableFormat);
	UPopulateCell tableCell(table);
	
	blockFormat.setBottomMargin(0);
	blockFormat.setTopMargin(0);
	
	//���������� ����� �������
	table->mergeCells(0,0,1,columnCount);
	tableCell.setAlignment(Qt::AlignLeft);
	tableCell.set(0,0,"["+QString::number(vodiyTabNum)+"] "+pibStr, textCharFormat_bold);
	
	textCharFormat.setFontPointSize( 9 );
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	textCharFormat_bold.setFontPointSize( 8.5 );
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	
	tableCell.setAlignment(Qt::AlignCenter);
	tableCell.set(1,0,"� �/�", textCharFormat);
	tableCell.set(1,1,"����", textCharFormat);
	tableCell.set(1,2,"��������", textCharFormat);
	tableCell.set(1,3,"�� � ���.", textCharFormat);
	tableCell.set(1,4,"���. � �����", textCharFormat);
	tableCell.set(1,5,"������ / ������", textCharFormat);
	tableCell.set(1,6,"����� ���.", textCharFormat);
	tableCell.set(1,7,"����-����", textCharFormat);
	tableCell.set(1,8,"ϳ���. ���.", textCharFormat);
	tableCell.set(1,9,"�� � ���.", textCharFormat);
	tableCell.set(1,10,"������� ����.", textCharFormat);
	tableCell.set(1,11,"������� ����.", textCharFormat);
	tableCell.set(1,12,"� �.�. ������� ����", textCharFormat);
	tableCell.set(1,13,"� �.�. ������� ��", textCharFormat);
	tableCell.set(1,14,"³����.", textCharFormat);
	tableCell.set(1,15,"% �����.", textCharFormat);
	tableCell.set(1,16,"������ �����. �� ����", textCharFormat);
	tableCell.set(1,17,"������ �����. ����.", textCharFormat);
	tableCell.set(1,18,"����. ���.", textCharFormat);
	
	int row=1;
	
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignTop);
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignTop);
	
	int dniVRobotiAll=0,
		godNaLiniyiAll=0,
		godPoGrafikuAll=0,
		pasajyryAll=0,
		dniVRozAll=0,
		pilgovykyCountAll=0;
	double probigZagAll=0,
			vyruchkaPlanAll=0,
			vyruchkaFactAll=0,
			vyruchkaVodAll=0,
			vyruchkaASAll=0,
			palnePoNormiAll=0,
			palneFactAll=0,
			zapravkaZaGotivkuAll=0;
	
	query.exec("SELECT date(s.DataVyizdu), m.MarshrutNapryamok, concat(m.KodMarshrutu,'.',m.GrafikNum,'.',m.ZminaNum), s.VodiyTabelNum_id, if(s.TypPoNochivli_id=2,2,1) AS dniVRob, \
					time_to_sec(if (s.ChasVNaryadi IS NULL, 0,s.ChasVNaryadi )) \
											+ time_to_sec(if (s.ChasVRezervi IS NULL, 0,s.ChasVRezervi )) AS godNaLiniyi, \
					time_to_sec(if (s.ChasVRezervi IS NULL, 0,s.ChasVRezervi )) AS godVRezerviAndZamovl, \
					s.ZagalnProbig AS probigZagaln, \
					s.ZagalnProbig-s.NulyovyiProbig AS plantyiProbig, s.KilkProdKvytkiv+s.KilkProdKvytkivAutoStat AS pasajyry, \
					if(s.TypPoNochivli_id=2,1,0) AS dniVRozizdi, s.PlanNaZminu AS vyruchkaPlanova, s.ZapravkaZaGotivku, \
					s.PilgoviPasajyry AS pilgPasajyry, s.PlanRozhidPalnogo AS rozhidPalnogoPoNormi, \
					s.FactRozhidPalnogo AS rozhidPalnogoFact, s.VartProdKvytkiv AS vyruchkaFact, \
					s.VartProdKvytkivAutoStat AS vyruchkaFactAS \
				FROM \
					shlyahovyiLyst s \
				LEFT JOIN marshruty m \
					ON s.KodMarshrutu_id = m.KodMarshrutu \
						and s.GrafikNum = m.GrafikNum \
						and s.ZminaNum = m.ZminaNum \
				WHERE date(s.ToZvitDate) BETWEEN date('"+wMonth.begDate().toString("yyyy-MM-dd")+"') \
							AND date('"+wMonth.endDate().toString("yyyy-MM-dd")+"') \
						and s.VodiyTabelNum_id="+sqlStr(vodiyTabNum)+" \
				ORDER BY s.DataVyizdu");
	int iVal;
	double dVal;
	
	while (query.next()){
		++row;
		table->insertRows(row, 1);
		
		QString str;
		tableCell.setAlignment(Qt::AlignCenter);
		tableCell.set(row,0,row-1, textCharFormat);
		tableCell.setAlignment(Qt::AlignRight);
		tableCell.set(row,1,query.value(0).toDate().toString("dd.MM"), textCharFormat);
		tableCell.setAlignment(Qt::AlignLeft);
		tableCell.set(row,2,"["+query.value(2).toString()+"] "+query.value(1).toString(), textCharFormat);
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
		iVal = query.value(9).toInt();
		pasajyryAll += iVal;
		tableCell.setDash(row,7,iVal, textCharFormat);
		iVal = query.value(13).toInt();
		pilgovykyCountAll += iVal;
		tableCell.setDash(row,8,iVal, textCharFormat);
		iVal = query.value(10).toInt();
		dniVRozAll += iVal;
		tableCell.setDash(row,9,iVal, textCharFormat);
		dVal = query.value(11).toDouble();
		vyruchkaPlanAll += dVal;
		tableCell.setDash(row,10,dVal, textCharFormat);
		dVal = query.value(16).toDouble() + query.value(17).toDouble();
		vyruchkaFactAll += dVal;
		tableCell.setDash(row,11,dVal, textCharFormat);
		
		dVal = query.value(16).toDouble();
		vyruchkaVodAll += dVal;
		tableCell.setDash(row,12,dVal, textCharFormat);
		dVal = query.value(17).toDouble();
		vyruchkaASAll += dVal;
		tableCell.setDash(row,13,dVal, textCharFormat);
		
		tableCell.setDash(row,14,query.value(16).toDouble() + query.value(17).toDouble() - query.value(11).toDouble(), textCharFormat);
		if (query.value(11).toDouble() != 0)
			tableCell.setDash(row,15,qRound((query.value(16).toDouble() + query.value(17).toDouble())*10000/query.value(11).toDouble())/100.0, textCharFormat);
		else
			tableCell.set(row,15,"-", textCharFormat);
		
		dVal = query.value(14).toDouble();
		palnePoNormiAll += dVal;
		tableCell.setDash(row,16,dVal, textCharFormat);
		dVal = query.value(15).toDouble();
		palneFactAll += dVal;
		tableCell.setDash(row,17,dVal, textCharFormat);
		
		dVal = query.value(12).toDouble();
		zapravkaZaGotivkuAll += dVal;
		tableCell.setDash(row,18,dVal, textCharFormat);
	}
	
	++row;
	
	table->mergeCells(row,0,1,3);
	tableCell.setAlignment(Qt::AlignLeft);
	tableCell.set(row,0,"  ������ �� �����", textCharFormat_bold);
	
	tableCell.setAlignment(Qt::AlignRight);
	tableCell.setDash(row,3,dniVRobotiAll, textCharFormat_bold);
	tableCell.set(row,4,secToTime(godNaLiniyiAll), textCharFormat_bold);
	tableCell.set(row,5,secToTime(godPoGrafikuAll), textCharFormat_bold);
	tableCell.setDash(row,6,probigZagAll, textCharFormat_bold);
	tableCell.setDash(row,7,pasajyryAll, textCharFormat_bold);
	tableCell.setDash(row,8,pilgovykyCountAll, textCharFormat_bold);
	tableCell.setDash(row,9,dniVRozAll, textCharFormat_bold);
	tableCell.setDash(row,10,vyruchkaPlanAll, textCharFormat_bold);
	tableCell.setDash(row,11,vyruchkaFactAll, textCharFormat_bold);
	
	tableCell.setDash(row,12,vyruchkaVodAll, textCharFormat_bold);
	tableCell.setDash(row,13,vyruchkaASAll, textCharFormat_bold);
	
	tableCell.setDash(row,14,vyruchkaFactAll-vyruchkaPlanAll, textCharFormat_bold);
	if (vyruchkaPlanAll != 0)
		tableCell.setDash(row,15,qRound(vyruchkaFactAll*10000/vyruchkaPlanAll)/100.0, textCharFormat_bold);
	else
		tableCell.set(row,15,"-", textCharFormat_bold);
	
	tableCell.setDash(row,16,palnePoNormiAll, textCharFormat_bold);
	tableCell.setDash(row,17,palneFactAll, textCharFormat_bold);
	tableCell.setDash(row,18,zapravkaZaGotivkuAll, textCharFormat_bold);
	
	cursor.movePosition(QTextCursor::End);
	cursor.insertFragment(pidpysy(1, textCharFormat, QPrinter::Landscape));
	
	QTextDocumentFragment resultFragment(doc);
	
	delete doc;
	return resultFragment; 
}
//--------------------utech--------------------utech--------------------utech--------------------
QTextDocumentFragment UPrintDocs_APark::pidpysy(int dockId, QTextCharFormat textCharFormat, QPrinter::Orientation orient)
{
	QSqlQuery query;
	query.exec("SELECT count(*) FROM printDocsSigns WHERE PrintDoc_id="+sqlStr(dockId));
	query.next();
	int rowCount = query.value(0).toInt();
	if (!rowCount)
		return QTextDocumentFragment();
	
	QTextDocument * doc = new QTextDocument();
	QTextCursor cursor(doc);
	QTextBlockFormat textBlockFormat;
	QTextTableCell cell;
	
	cursor.insertText("\n\n\n", textCharFormat);
	
	//��������� �������, ��� ������, ��� ����� ��������
	QTextTableFormat tableFormat;
	QVector<QTextLength> constraints;
	if (orient == QPrinter::Landscape) { //��������
		constraints << QTextLength(QTextLength::FixedLength, 60);
		constraints << QTextLength(QTextLength::FixedLength, 300);
		constraints << QTextLength(QTextLength::FixedLength, 250);
		constraints << QTextLength(QTextLength::FixedLength, 200);
	}
	else { //���������
		constraints << QTextLength(QTextLength::FixedLength, 30);
		constraints << QTextLength(QTextLength::FixedLength, 270);
		constraints << QTextLength(QTextLength::FixedLength, 200);
		constraints << QTextLength(QTextLength::FixedLength, 200);
	}
	
	tableFormat.setColumnWidthConstraints(constraints);
	tableFormat.setCellSpacing(0);
	tableFormat.setCellPadding(1);
	tableFormat.setBorder(0);
	QTextTable *table = cursor.insertTable(rowCount, 4, tableFormat);
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignTop);
	
	query.exec("SELECT users.Prizv, users.Imya, users.PoBatk, users.PosadaName \
				FROM printDocsSigns LEFT JOIN users ON printDocsSigns.User_id=users.id \
				WHERE PrintDoc_id="+sqlStr(dockId)+" \
				ORDER BY SortOrder");
	for (int row=0; query.next() && row<rowCount; row++){
		//������
		cell = table->cellAt(row, 1);
		cell.setFormat(textCharFormat);
		cursor = cell.firstCursorPosition();
		textBlockFormat.setAlignment( Qt::AlignLeft );
		cursor.setBlockFormat( textBlockFormat );
		cursor.insertText(query.value(3).toString(),textCharFormat);
		
		//�������� ������
		cell = table->cellAt(row, 2);
		cell.setFormat(textCharFormat);
		cursor = cell.firstCursorPosition();
		textBlockFormat.setAlignment( Qt::AlignCenter );
		cursor.setBlockFormat( textBlockFormat );
		cursor.insertText("________________",textCharFormat);
		if (row+1 != rowCount) //������� �������� ����� �� � ������� ������
			cursor.insertText("\n\n",textCharFormat);
		
		//ϲ�
		cell = table->cellAt(row, 3);
		cell.setFormat(textCharFormat);
		cursor = cell.firstCursorPosition();
		textBlockFormat.setAlignment( Qt::AlignLeft );
		cursor.setBlockFormat( textBlockFormat );
		cursor.insertText(uPrizvIB(query.value(0).toString(),
											query.value(1).toString(),
											query.value(2).toString()),textCharFormat);
	}
	
	QTextDocumentFragment resultFragment(doc);
	delete doc;
	return resultFragment; 
}
//--------------------utech--------------------utech--------------------utech--------------------
