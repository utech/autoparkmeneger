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
#include <UNumberToStringConverter>
#include "UForm_AParkCustomPrintForm.h"

//--------------------utech--------------------utech--------------------utech--------------------
void UPrintDocs_APark::print_monthTabel(short year, short month, int pidrozdilId)
{
	printform = new UPrintForm(0, "������ �� "+QString::number(month)+"."+QString::number(year));
	
	QSqlQuery query;
	UWorkMonth wMonth(year, month);
	int iter;
	const short daysInMonth = wMonth.begDate().daysTo(wMonth.endDate()) + 1;
	const short columnCount= 16 + daysInMonth;
	query.exec(QString("SELECT count(*) FROM npr WHERE %1").arg(pidrozdilId == -1 ? "Posada_id=10" : "Pidrozdil_id="+sqlStr(pidrozdilId)));
	query.next();
	const int wCount = query.value(0).toInt();
	
	//�������� ����������� ����� ����������
	query.exec("SELECT Znach FROM budjetni_normu WHERE id=19");
	bool needNadurochni = false;
	if ( query.next() && (query.value(0).toDouble() > 0.009) )
		needNadurochni = true;
	
	QList<QDate> svList;
	query.exec("SELECT CDate FROM svyatkovidni \
				WHERE CDate BETWEEN date("+sqlStr(wMonth.begDate())+") \
					and date("+sqlStr(wMonth.endDate())+")");
	while (query.next())
		svList << query.value(0).toDate();
	
	UPostupForm *postup = new UPostupForm(0, wCount);
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
	blockFormat.setAlignment( Qt::AlignLeft );
	cursor.insertBlock(blockFormat);
	textCharFormat.setFontPointSize( 9 );
	cursor.insertText("										     ����������:", textCharFormat);
	cursor.insertBlock(blockFormat);
        cursor.insertText("										�������� "+OrganizName(), textCharFormat);
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	cursor.insertText("										________________________ ������� �.�.", textCharFormat);
	
	
	blockFormat.setAlignment( Qt::AlignCenter );
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	
	textCharFormat_bold.setFontPointSize( 12 );
	textCharFormat_small.setFontPointSize( 5 );
	cursor.insertText("������ ��˲�� ������������ �������� ����", textCharFormat_bold);
	textCharFormat_bold.setFontPointSize( 11 );
	textCharFormat.setFontPointSize( 11 );
	cursor.insertBlock(blockFormat);
	cursor.insertText("�� "+monthlist.at(month-1)+" "+QString::number(year)+" ����", textCharFormat_bold);
	blockFormat.setAlignment( Qt::AlignLeft );
	cursor.insertBlock(blockFormat);
	cursor.insertText("ϳ���������, ����������:  ", textCharFormat);
	cursor.insertText(OrganizName(), textCharFormat_bold);
	cursor.insertBlock(blockFormat);
	cursor.insertText("���, ������, �������  ", textCharFormat);
	if (pidrozdilId == -1) {
		cursor.insertText("��䳿", textCharFormat_bold);
	}
	else {
		query.exec("SELECT Name FROM pidrozdily_salary WHERE id = "+sqlStr(pidrozdilId));
		query.next();
		cursor.insertText(query.value(0).toString(), textCharFormat_bold);
	}
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	
	//��������� �������
	QTextTableFormat tableFormat;
	QVector<QTextLength> constraints;
	constraints << QTextLength(QTextLength::FixedLength, 20);
	constraints << QTextLength(QTextLength::FixedLength, 90);
	constraints << QTextLength(QTextLength::FixedLength, 25);
	for (iter=0; iter<columnCount-6; iter++)
		constraints << QTextLength(QTextLength::FixedLength, 20);
	constraints << QTextLength(QTextLength::FixedLength, 30); //������ �������� ����
	constraints << QTextLength(QTextLength::FixedLength, 20); //���
	constraints << QTextLength(QTextLength::FixedLength, 20); //����������
		
	tableFormat.setColumnWidthConstraints(constraints);
	tableFormat.setCellSpacing(0);
	tableFormat.setCellPadding(0.5);
	tableFormat.setBorder(0.5);
	tableFormat.setHeaderRowCount(2);
	QTextTable *table = cursor.insertTable(3 + wCount, columnCount, tableFormat);
	UPopulateCell tableCell(table);
	
	blockFormat.setBottomMargin(0);
	blockFormat.setTopMargin(0);
	
	//���������� ����� �������
	textCharFormat.setFontPointSize( 8 );
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	textCharFormat_bold.setFontPointSize( 8 );
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	
	QTextCharFormat textCharFormatBottom = textCharFormat;
	textCharFormatBottom.setVerticalAlignment(QTextCharFormat::AlignBottom);
	
	int col=0;
	tableCell.setAlignment(Qt::AlignCenter);
	table->mergeCells(0,0,2,1);
	table->mergeCells(0,1,2,1);
	table->mergeCells(0,2,2,1);
	table->mergeCells(0,3,1,daysInMonth);
	table->mergeCells(0,3+daysInMonth,1,4);
	table->mergeCells(0,3+4+daysInMonth,1,5);
	table->mergeCells(0,3+4+5+daysInMonth,2,1);
	table->mergeCells(0,3+4+5+1+daysInMonth,1,3);
	
	tableCell.set(0,col,"� � �", textCharFormat);
	tableCell.set(0,++col,"��������, ��'�, �� �������", textCharFormat);
	tableCell.set(0,++col,"���. ��-���", textCharFormat);
	tableCell.set(0,++col,"����� �����", textCharFormat);
	for (iter=0; iter<daysInMonth; iter++){
		QDate dt = wMonth.begDate().addDays(iter);
		if (svList.contains(dt))
			tableCell.set(1,col++,QString::number(dt.day())+" ��", textCharFormat_bold);
		else
			tableCell.set(1,col++,QString::number(dt.day())+" "+dt.toString("ddd"), textCharFormat);
	}
	tableCell.set(0,col,"�� ����", textCharFormat);
	tableCell.set(1,col,verticalTextToImage("����. ������", textCharFormatBottom), textCharFormatBottom);
	tableCell.set(1,++col,verticalTextToImage("������. �������", textCharFormatBottom), textCharFormatBottom);
	tableCell.set(1,++col,verticalTextToImage("���.��������,���.", textCharFormatBottom), textCharFormatBottom);
	tableCell.set(1,++col,verticalTextToImage("����������,���.", textCharFormatBottom), textCharFormatBottom);
	tableCell.set(0,++col,"�� ������ /���. ��/", textCharFormat);
	tableCell.set(1,col,verticalTextToImage("������ ���.", textCharFormatBottom), textCharFormatBottom);
	tableCell.set(1,++col,verticalTextToImage("���.� ��.� ���.", textCharFormatBottom), textCharFormatBottom);
	tableCell.set(1,++col,verticalTextToImage("�������", textCharFormatBottom), textCharFormatBottom);
	//tableCell.set(1,++col,verticalTextToImage("������ ����.���.", textCharFormatBottom), textCharFormatBottom);
	tableCell.set(1,++col,verticalTextToImage("� ����.����.", textCharFormatBottom), textCharFormatBottom);
	tableCell.set(1,++col,verticalTextToImage("�������", textCharFormatBottom), textCharFormatBottom);
	tableCell.set(0,++col,verticalTextToImage("������ � ������� ��", textCharFormatBottom), textCharFormatBottom);
	tableCell.set(0,++col,"³����-������� �����", textCharFormat);
	tableCell.set(1,col,verticalTextToImage("������", textCharFormatBottom), textCharFormatBottom);
	tableCell.set(1,++col,verticalTextToImage("���", textCharFormatBottom), textCharFormatBottom);
	tableCell.set(1,++col,verticalTextToImage("����������", textCharFormatBottom), textCharFormatBottom);
	
	textCharFormat.setFontPointSize( 7 );
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignTop);
	textCharFormat_bold.setFontPointSize( 7 );
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignTop);
	QTextCharFormat textCharFormat_header = textCharFormat;
	textCharFormat_header.setFontPointSize( 8 );
	
	int allWorkTime=0, allNichTime=0, allSvTime=0, allVidpusk=0, allRodVidpusk=0, allLikarn=0, allWorkDays=0, 
			allNadurochni=0, allCilozmProstDays=0, allProgulyDays=0, allNeyavkaZakon=0, allNeyavkaAdmDays=0,
			allRemontAvtobusaTime=0, allStajuvannyaTime=0;
	
	QSqlQuery wQuery(QString("SELECT id, Prizv, Imia, Pobatk FROM npr WHERE %1 \
						ORDER BY Naparnyky, Prizv, Imia, Pobatk")
						.arg(pidrozdilId == -1 ? "Posada_id=10" : "Pidrozdil_id="+sqlStr(pidrozdilId)));
	int row=1;
	iter=0;
	for (; iter<wCount and wQuery.next(); ++iter){
		row++;
		QString nprStr;
		nprStr = wQuery.value(1).toString();
		if (wQuery.value(2).toString().size() > 0){
			nprStr += QString(" %1.").arg(wQuery.value(2).toString().at(0));
			if (wQuery.value(3).toString().size() > 0)
				nprStr += QString(" %1.").arg(wQuery.value(3).toString().at(0));
		}
		
		col = 0;
		//"� � �"
		tableCell.setAlignment(Qt::AlignCenter);
		tableCell.set(row,col,iter+1, textCharFormat_header);
		//"��������, ��'�, �� �������"
		tableCell.setAlignment(Qt::AlignLeft);
		tableCell.set(row,++col,nprStr, textCharFormat_header);
		//"���. �����"
		tableCell.setAlignment(Qt::AlignCenter);
		tableCell.set(row,++col,wQuery.value(0).toString(), textCharFormat_header);
		
		int curWorkTime=0, curNichTime=0, curSvTime=0, curVidpusk=0, curRodVidpusk=0, curLikarn=0, curWorkDays=0, 
			curNadurochni=0, curCilozmProstDays=0, curProgulyDays=0, curNeyavkaZakon=0, curNeyavkaAdmDays=0,
			curRemontAvtobusaTime=0, curStajuvannyaTime=0;
		
		query.exec("SELECT t.Cur_Date, t.Pracivn_status_id, t.God_zag, t.God_nichni, t.God_sv, \
						s.Status_char \
					FROM tabel t \
					LEFT JOIN pracivn_status s ON s.id=t.Pracivn_status_id \
					WHERE t.npr_id="+sqlStr(wQuery.value(0).toInt())+" \
						and t.Cur_Date BETWEEN date("+sqlStr(wMonth.begDate())+") \
							and date("+sqlStr(wMonth.endDate())+")");
		while (query.next()){
			col = 3 + wMonth.begDate().daysTo(query.value(0).toDate());
			
			if ((query.value(1).toInt() == 1) || (query.value(1).toInt() == 5)){
				if (timeToMinute(query.value(2).toTime())>0){
					//������� ���
					tableCell.setAlignment(Qt::AlignRight);
					tableCell.set(row,col,query.value(2).toTime().toString("h:mm"), textCharFormat);
					
					curWorkDays++;
					int iVal = query.value(2).toTime().hour() * 60 + query.value(2).toTime().minute();	
					curWorkTime += iVal;
					if ( needNadurochni && (iVal > 480) ) //��� ������ �� ��� ����� -> ��������
						curNadurochni += iVal - 480;
					curNichTime += query.value(3).toTime().hour() * 60 + query.value(3).toTime().minute();
					curSvTime += query.value(4).toTime().hour() * 60 + query.value(4).toTime().minute();
				}
			}
			else if (query.value(1).toInt() == 13){
				//������ ��������
				if (timeToMinute(query.value(2).toTime())>0){
					tableCell.setAlignment(Qt::AlignCenter);
					tableCell.set(row,col,query.value(5).toString(), textCharFormat_bold);
					
					curWorkDays++;
					
					int iVal = query.value(2).toTime().hour() * 60 + query.value(2).toTime().minute();	
					curRemontAvtobusaTime += iVal;
					/*if (iVal > 480) //��� ������ �� ��� ����� -> ��������
						curNadurochni += iVal - 480;
					curNichTime += query.value(3).toTime().hour() * 60 + query.value(3).toTime().minute();
					curSvTime += query.value(4).toTime().hour() * 60 + query.value(4).toTime().minute();*/
				}
			}
			else if (query.value(1).toInt() == 19){ //������ ��������
				if (timeToMinute(query.value(2).toTime())>0){
					tableCell.setAlignment(Qt::AlignCenter);
					tableCell.set(row,col,query.value(5).toString(), textCharFormat_bold);
					
					curWorkDays++;
					
					int iVal = query.value(2).toTime().hour() * 60 + query.value(2).toTime().minute();	
					curStajuvannyaTime += iVal;
					/*if (iVal > 480) //��� ������ �� ��� ����� -> ��������
						curNadurochni += iVal - 480;
					curNichTime += query.value(3).toTime().hour() * 60 + query.value(3).toTime().minute();
					curSvTime += query.value(4).toTime().hour() * 60 + query.value(4).toTime().minute();*/
				}
			}
			else{
				//����� ���� ����������
				tableCell.setAlignment(Qt::AlignCenter);
				tableCell.set(row,col,query.value(5).toString(), textCharFormat_bold);
				
				switch (query.value(1).toInt()){
					case 3  : curVidpusk++; break;
					case 8  : curRodVidpusk++; break;
					case 2  : curLikarn++; break;
					case 12 : curCilozmProstDays++; break;
					case 14 : curProgulyDays++; break;
					case 6  : curNeyavkaZakon++; break;
					case 17 : curNeyavkaAdmDays++; break;
				}
			}
		}
		
		//���������� ��������� ������ ��������� ����������
		col = 3+daysInMonth;
		tableCell.setAlignment(Qt::AlignRight);
		tableCell.setDash(row,col,curWorkDays, textCharFormat);
		col += 1;
		tableCell.setDash(row,col,curCilozmProstDays, textCharFormat);
		col += 1;
		tableCell.set(row,col,secToTime(curRemontAvtobusaTime), textCharFormat);
		
		col += 1;
		tableCell.set(row,col,secToTime(curStajuvannyaTime), textCharFormat);
		
		col += 1;
		tableCell.setDash(row,col,curVidpusk, textCharFormat);
		col += 1;
		tableCell.setDash(row,col,curRodVidpusk, textCharFormat);
		col += 1;
		tableCell.setDash(row,col,curLikarn, textCharFormat);
		//col += 1;
		//tableCell.setDash(row,col,curNeyavkaZakon, textCharFormat);
		col += 1;
		tableCell.setDash(row,col,curNeyavkaAdmDays, textCharFormat);
		col += 1;
		tableCell.setDash(row,col,curProgulyDays, textCharFormat);
		col += 1;
		tableCell.set(row,col,secToTime(curSvTime), textCharFormat);
		
		col += 1;
		tableCell.set(row,col,secToTime(curWorkTime), textCharFormat);
		col += 1;
		tableCell.set(row,col,secToTime(curNichTime), textCharFormat);
		col += 1;
		tableCell.set(row,col,secToTime(curNadurochni), textCharFormat);
		
		allWorkTime += curWorkTime;
		allNichTime += curNichTime;
		allSvTime += curSvTime;
		allVidpusk += curVidpusk;
		allRodVidpusk += curRodVidpusk;
		allLikarn += curLikarn;
		allWorkDays += curWorkDays;
		allNadurochni += curNadurochni;
		allCilozmProstDays += curCilozmProstDays;
		allProgulyDays += curProgulyDays;
		allNeyavkaZakon += curNeyavkaZakon;
		allNeyavkaAdmDays += curNeyavkaAdmDays;
		allRemontAvtobusaTime += curRemontAvtobusaTime;
		allStajuvannyaTime += curStajuvannyaTime;
		
		postup->incPos();
	}
	
	//���������� ��������� ������ ������
	++row;
	col = 3+daysInMonth;
	table->mergeCells(row,0,1,col);
	// �����
	tableCell.setAlignment(Qt::AlignLeft);
	tableCell.set(row,0,"�����", textCharFormat_header);
	
	tableCell.setAlignment(Qt::AlignCenter);
	tableCell.set(row,col,verticalTextToImage(QString::number(allWorkDays), textCharFormat), textCharFormat);
	col += 1;
	tableCell.set(row,col,verticalTextToImage(QString::number(allCilozmProstDays), textCharFormat), textCharFormat);
	col += 1;
	tableCell.set(row,col,verticalTextToImage(secToTime(allRemontAvtobusaTime), textCharFormat), textCharFormat);
	
	col += 1;
	tableCell.set(row,col,verticalTextToImage(secToTime(allStajuvannyaTime), textCharFormat), textCharFormat);
	
	col += 1;
	tableCell.set(row,col,verticalTextToImage(QString::number(allVidpusk), textCharFormat), textCharFormat);
	col += 1;
	tableCell.set(row,col,verticalTextToImage(QString::number(allRodVidpusk), textCharFormat), textCharFormat);
	col += 1;
	tableCell.set(row,col,verticalTextToImage(QString::number(allLikarn), textCharFormat), textCharFormat);
	//col += 1;
	//tableCell.setDash(row,col,allNeyavkaZakon, textCharFormat);
	col += 1;
	tableCell.set(row,col,verticalTextToImage(QString::number(allNeyavkaAdmDays), textCharFormat), textCharFormat);
	col += 1;
	tableCell.set(row,col,verticalTextToImage(QString::number(allProgulyDays), textCharFormat), textCharFormat);
	col += 1;
	tableCell.set(row,col,verticalTextToImage(secToTime(allSvTime), textCharFormat), textCharFormat);
	
	col += 1;
	tableCell.set(row,col,verticalTextToImage(secToTime(allWorkTime), textCharFormat), textCharFormat);
	col += 1;
	tableCell.set(row,col,verticalTextToImage(secToTime(allNichTime), textCharFormat), textCharFormat);
	col += 1;
	tableCell.set(row,col,verticalTextToImage(secToTime(allNadurochni), textCharFormat), textCharFormat);
	
	//������� ���������
	cursor.movePosition(QTextCursor::End);
	
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	
	constraints.clear();
	constraints << QTextLength(QTextLength::FixedLength, 310);
	constraints << QTextLength(QTextLength::FixedLength, 310);
	constraints << QTextLength(QTextLength::FixedLength, 310);
		
	tableFormat.setColumnWidthConstraints(constraints);
	tableFormat.setCellSpacing(0);
	tableFormat.setCellPadding(0.5);
	tableFormat.setBorder(0);
	tableFormat.setHeaderRowCount(0);
	table = cursor.insertTable(2, 3, tableFormat);
	tableCell.setTextTable(table);
	table->mergeCells(0,0,1,3);
	
	tableCell.setAlignment(Qt::AlignLeft);
	textCharFormat.setFontPointSize(9);
	tableCell.set(0,0,"      ���������� � �����:\n", textCharFormat);
	
	tableCell.set(1,0,"�  - ������ ��", textCharFormat);
	tableCell.insertText("\n�� - ˳�������, ��������� ���������������", textCharFormat);
	tableCell.insertText("\n�� - ������ ��������", textCharFormat);
	tableCell.insertText("\n�  - ³��������", textCharFormat);
	tableCell.insertText("\n�� - �� ��� �������", textCharFormat);
	tableCell.insertText("\n�� - ������ � ������� ��", textCharFormat);
	tableCell.set(1,1,"�� - �������� �������� ������� (������� ����'����)", textCharFormat);
	tableCell.insertText("\n�� - ������� ����������", textCharFormat);
	tableCell.insertText("\n�� - ³������� � ��'���� � ������", textCharFormat);
	tableCell.insertText("\n�� - ϳ����� ������ �������", textCharFormat);
	tableCell.insertText("\n�� - ������������� ������ ������", textCharFormat);
	tableCell.insertText("\n�  - ֳ������ ������", textCharFormat);
	tableCell.set(1,2,"�� - �������", textCharFormat);
	tableCell.insertText("\n�� - �������", textCharFormat);
	tableCell.insertText("\n�� - ��������", textCharFormat);
	tableCell.insertText("\n�� - ������ ������ ������", textCharFormat);
	tableCell.insertText("\n�  - ������� � ������� �����������", textCharFormat);
	tableCell.insertText("\n�  - ϳ����� ��� ���. � ��������� ������� �����", textCharFormat);
	
	
	
	//ϳ�����
	textCharFormat.setFontPointSize( 9 );
	cursor.movePosition(QTextCursor::End);
	cursor.insertFragment(pidpysy(9, textCharFormat, QPrinter::Landscape));
	/*
	cursor.insertBlock(blockFormat);
	cursor.insertText("\n\n\n	�������� ���						������� �.�.", textCharFormat);
	cursor.insertText("\n\n\n	�������� ���					���� �.�.", textCharFormat);
	cursor.insertText("\n\n\n	������� ��������� ��					�������� �.�.", textCharFormat);
	cursor.insertText("\n\n\n	��������� �����������					��� �.�.", textCharFormat);
	cursor.insertText("\n\n\n	��������� ��					������ �.�.", textCharFormat);
	*/
	
	printform->printer()->setDocName("������ �� "+QString::number(month)+"."+QString::number(year));
	printform->printer()->setOrientation(QPrinter::Landscape);
	printform->printer()->setPageMargins( 3, 5, 4, 10, QPrinter::Millimeter );
	printform->show();
	delete postup;
}
//--------------------utech--------------------utech--------------------utech--------------------
void UPrintDocs_APark::print_zvitProPerevezPilgPasajyriv(QDate vDate)
{
	printform = new UPrintForm(0, "��� ��� ����������� �������� ��������");
	
	QSqlQuery query;
	UWorkMonth wMonth(vDate.year(), vDate.month());
	int columnCount=3;
	
	QTextCursor cursor(printform->document());
	QTextBlockFormat blockFormat;
	QTextTableCell cell;
	QTextCharFormat textCharFormat, textCharFormat_bold, textCharFormat_small, textCharFormat_italic ;
	QFont fnt = textCharFormat_bold.font();
	fnt.setBold(true);
	textCharFormat_bold.setFont(fnt);
	textCharFormat_italic.setFontItalic(true);
	
	blockFormat.setAlignment( Qt::AlignRight );
	cursor.setBlockFormat( blockFormat );
	textCharFormat.setFontPointSize( 7 );
	cursor.insertText("�������� �������� ��������� \"�������� ��������\" "+QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm"), textCharFormat);
	blockFormat.setAlignment( Qt::AlignCenter );
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	
	textCharFormat_bold.setFontPointSize( 13 );
	textCharFormat_small.setFontPointSize( 5 );
	cursor.insertText("�²�\n��� ����������� �������� �������� ������\n"+OrganizName()+
					"\n� "+wMonth.begDate().toString("dd.MM.yyyy")+"�. �� "+wMonth.endDate().toString("dd.MM.yyyy")+"�.", textCharFormat_bold);
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	
	//��������� �������
	QTextTableFormat tableFormat;
	QVector<QTextLength> constraints;
	constraints << QTextLength(QTextLength::FixedLength, 120);
	constraints << QTextLength(QTextLength::FixedLength, 250);
	constraints << QTextLength(QTextLength::FixedLength, 250);
		
	tableFormat.setColumnWidthConstraints(constraints);
	tableFormat.setBorderBrush(QColor(Qt::black));
	tableFormat.setAlignment(Qt::AlignCenter);
	tableFormat.setCellSpacing(0);
	tableFormat.setCellPadding(2);
	tableFormat.setBorder(0.5);
	tableFormat.setHeaderRowCount(1);
	QTextTable *table = cursor.insertTable(2, columnCount, tableFormat);
	UPopulateCell tableCell(table);
	
	blockFormat.setBottomMargin(0);
	blockFormat.setTopMargin(0);
	
	//���������� ����� �������
	textCharFormat.setFontPointSize( 12 );
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	textCharFormat_bold.setFontPointSize( 12 );
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	textCharFormat_italic.setFontPointSize( 12 );
	textCharFormat_italic.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	
	QTextCharFormat textCharFormatBottom = textCharFormat;
	textCharFormatBottom.setVerticalAlignment(QTextCharFormat::AlignBottom);
	
	tableCell.setAlignment(Qt::AlignCenter);
	tableCell.set(0,0,"� �/�", textCharFormat_italic);
	tableCell.set(0,1,"�������", textCharFormat_italic);
	tableCell.set(0,2,"ʳ������", textCharFormat_italic);
	
	textCharFormat.setFontPointSize( 12 );
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignTop);
	textCharFormat_bold.setFontPointSize( 12 );
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignTop);
	
	query.exec("SELECT npr.BrygadaNum, sum(s.PilgoviPasajyry) FROM shlyahovyiLyst s \
				LEFT JOIN npr on npr.id=s.VodiyTabelNum_id \
				WHERE s.PilgoviPasajyry>0 \
					and s.ToZvitDate BETWEEN date("+sqlStr(wMonth.begDate())+") and date("+sqlStr(wMonth.endDate())+") \
				GROUP BY npr.BrygadaNum \
				ORDER BY npr.BrygadaNum");
	int row=0;
	int allPilgovyky=0, iVal;
	while(query.next()){
		row++;
		table->insertRows(row,1);
		
		tableCell.setAlignment(Qt::AlignCenter);
		//"� �/�"
		tableCell.set(row,0,row, textCharFormat);
		//"�������"
		tableCell.set(row,1,query.value(0).toInt(), textCharFormat);
		tableCell.setAlignment(Qt::AlignCenter);
		//"ʳ������"
		iVal = query.value(1).toInt();
		allPilgovyky += iVal;
		tableCell.setDash(row,2,iVal, textCharFormat);
	}
	
	row++;
	table->mergeCells(row,0,1,2);
	tableCell.setAlignment(Qt::AlignCenter);
	tableCell.set(row,0,"����� �� ����������", textCharFormat);
	tableCell.setDash(row,2,allPilgovyky, textCharFormat);
	
	//ϳ�����
	cursor.movePosition(QTextCursor::End);
	cursor.insertFragment(pidpysy(10, textCharFormat));
	
	printform->printer()->setDocName("��� ��� ����������� �������� ��������");
	printform->printer()->setPageMargins( 10, 10, 10, 10, QPrinter::Millimeter );
	printform->show();
}
//--------------------utech--------------------utech--------------------utech--------------------
void UPrintDocs_APark::print_planyValovyhDohodiv(QDate vDate)
{
	printform = new UPrintForm(0, "����� ������� ������ �� "+QString::number(vDate.month())+"."+QString::number(vDate.year()));
	
	QSqlQuery query;
	QSqlQuery xQuery;
	
    query.exec("SELECT count(*) \
				FROM ((marshruty \
				LEFT JOIN ruhomyiSklad ON marshruty.RuhomyiSkald_garNum = RuhomyiSklad.GarajNumber) \
				LEFT JOIN markaPalnogo ON RuhomyiSklad.MarkaPalnogo_Id = markaPalnogo.Id)");
	query.next();
	int rowCount = query.value(0).toInt();
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
	blockFormat.setAlignment( Qt::AlignLeft );
	cursor.insertBlock(blockFormat);
	textCharFormat.setFontPointSize( 9 );
	cursor.insertText("						����������:", textCharFormat);
	cursor.insertBlock(blockFormat);
	cursor.insertText("					   ������ �������� "+OrganizName(), textCharFormat);
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	cursor.insertText("					   ________________________ ������� �.�.", textCharFormat);
	
	blockFormat.setAlignment( Qt::AlignCenter );
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	
	textCharFormat_bold.setFontPointSize( 12 );
	textCharFormat_small.setFontPointSize( 5 );
	cursor.insertText("����\n������� ������ �� "+OrganizName(), textCharFormat_bold);
	textCharFormat_bold.setFontPointSize( 11 );
	textCharFormat.setFontPointSize( 11 );
	cursor.insertBlock(blockFormat);
	cursor.insertText("�� _______________________ "+QString::number(vDate.year())+" ����", textCharFormat_bold);
	blockFormat.setAlignment( Qt::AlignLeft );
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	cursor.insertText("��������� � "+vDate.toString("dd.MM.yyyy")+" �.", textCharFormat_bold);
	cursor.insertBlock(blockFormat);
	
	//ֳ�� �� ������
	cursor.insertBlock(blockFormat);
	
	textCharFormat.setFontPointSize( 10 );
	cursor.insertText("     ֳ�� �� ������, ���.", textCharFormat);
	query.exec("SELECT id, MarkaName, MarkaRozm FROM markaPalnogo ORDER BY id");
	while (query.next()) {
		double cinaPalnogo = 0;
		xQuery.exec("SELECT cinaPalnogo.Cina FROM cinaPalnogoDate \
					LEFT JOIN cinaPalnogo ON cinaPalnogo.cinaPalnogoDate_id=cinaPalnogoDate.id \
					WHERE CDate <= date("+sqlStr(vDate)+") \
						and cinaPalnogo.Palne_id="+query.value(0).toString()+" \
					ORDER BY CDate DESC LIMIT 1");
		if (xQuery.next())
			cinaPalnogo = xQuery.value(0).toDouble();
		
		cursor.insertBlock(blockFormat);
		cursor.insertText("        - "+query.value(1).toString()+", "+query.value(2).toString()+" :	"
							+uMToStr2(cinaPalnogo)+" ���.", textCharFormat);
	}
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	
	//��������� �������
	QTextTableFormat tableFormat;
	QVector<QTextLength> constraints;
	constraints << QTextLength(QTextLength::FixedLength, 25);
	constraints << QTextLength(QTextLength::FixedLength, 60);
	constraints << QTextLength(QTextLength::FixedLength, 130);
	constraints << QTextLength(QTextLength::FixedLength, 60);
	constraints << QTextLength(QTextLength::FixedLength, 60);
	constraints << QTextLength(QTextLength::FixedLength, 60);
	constraints << QTextLength(QTextLength::FixedLength, 60);
	constraints << QTextLength(QTextLength::FixedLength, 60);
	constraints << QTextLength(QTextLength::FixedLength, 60);
	constraints << QTextLength(QTextLength::FixedLength, 60);
	constraints << QTextLength(QTextLength::FixedLength, 60);
		
	tableFormat.setColumnWidthConstraints(constraints);
	tableFormat.setBorderBrush(QColor(Qt::black));
	tableFormat.setAlignment(Qt::AlignCenter);
	tableFormat.setCellSpacing(0);
	tableFormat.setCellPadding(2);
	tableFormat.setBorder(0.5);
	tableFormat.setHeaderRowCount(2);
	QTextTable *table = cursor.insertTable(rowCount + 2, 11, tableFormat);
	UPopulateCell tableCell(table);
	
	blockFormat.setBottomMargin(0);
	blockFormat.setTopMargin(0);
	
	//���������� ����� �������
	textCharFormat.setFontPointSize( 9 );
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	textCharFormat_bold.setFontPointSize( 9 );
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	
	QTextCharFormat textCharFormatBottom = textCharFormat;
	textCharFormatBottom.setVerticalAlignment(QTextCharFormat::AlignBottom);
	
	tableCell.setAlignment(Qt::AlignCenter);
	
	table->mergeCells(0,0,2,1);
	table->mergeCells(0,1,1,2);
	table->mergeCells(0,3,2,1);
	table->mergeCells(0,4,2,1);
	table->mergeCells(0,5,1,6);
	
	tableCell.set(0,0,"� �/�", textCharFormat);
	tableCell.set(0,1,"��������", textCharFormat);
	
	tableCell.set(1,1,"���", textCharFormat);
	tableCell.set(1,2,"��������", textCharFormat);
	
	tableCell.set(0,3,"����", textCharFormat);
	tableCell.set(0,4,"�������, ���.", textCharFormat);
	tableCell.set(0,5,"������", textCharFormat);
	tableCell.set(1,5,"�����", textCharFormat);
	tableCell.set(1,6,"����. �����.", textCharFormat);
	tableCell.set(1,7,"����. �� 100 ��.", textCharFormat);
	tableCell.set(1,8,"����. �� �������", textCharFormat);
	tableCell.set(1,9,"ֳ��, ���.", textCharFormat);
	tableCell.set(1,10,"����, ���.", textCharFormat);
	
	textCharFormat.setFontPointSize( 9 );
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignTop);
	textCharFormat_bold.setFontPointSize( 9 );
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignTop);
	
	query.exec("SELECT marshruty.id, ruhomyiSklad.id, markaPalnogo.id, ruhomyiSklad.GarajNumber, \
					marshruty.KodMarshrutu,	marshruty.MarshrutNapryamok, marshruty.GrafikNum, \
					marshruty.ZminaNum, marshruty.DovjynaMarshrutu, ruhomyiSklad.RozhidPalnogo, \
					markaPalnogo.MarkaRozm, markaPalnogo.MarkaName, marshruty.VytrPalnNaBezdor \
				FROM ((marshruty \
				LEFT JOIN ruhomyiSklad ON marshruty.RuhomyiSkald_garNum = RuhomyiSklad.GarajNumber) \
				LEFT JOIN markaPalnogo ON RuhomyiSklad.MarkaPalnogo_Id = markaPalnogo.Id) \
                ORDER BY marshruty.KodMarshrutu, marshruty.GrafikNum, marshruty.ZminaNum");
	int row=2;
	int iter=0;
	while (query.next()){
		iter++;
		
		double dovjMarshrutu = query.value(8).toDouble();
		double rozhidNa100Km = query.value(9).toDouble();
		double rozhidPalnNaMarshrut = qRound(dovjMarshrutu * rozhidNa100Km / 100 + query.value(12).toDouble());
		double cinaPalnogo = 0;
		double vyruchka = 0;
		
		xQuery.exec("SELECT cinaPalnogo.Cina FROM cinaPalnogoDate \
					LEFT JOIN cinaPalnogo ON cinaPalnogo.cinaPalnogoDate_id=cinaPalnogoDate.id \
					WHERE CDate <= date("+sqlStr(vDate)+") \
						and cinaPalnogo.Palne_id="+query.value(2).toString()+" \
					ORDER BY CDate DESC LIMIT 1");
		if (xQuery.next())
			cinaPalnogo = xQuery.value(0).toDouble();
		
		xQuery.exec("SELECT Plan FROM planNaZminuDate \
					LEFT JOIN planNaZminu ON planNaZminuDate.id=planNaZminu.planNaZminuDate_id \
					WHERE planNaZminuDate.CDate <= date("+sqlStr(vDate)+") \
						and planNaZminu.Marshrut_id="+query.value(0).toString()+" \
					ORDER BY planNaZminuDate.CDate DESC LIMIT 1");
		if (xQuery.next())
			vyruchka = xQuery.value(0).toDouble();
		
		double sumaZaPalneNaMarshrut = uDToM(rozhidPalnNaMarshrut * cinaPalnogo);
		//��� ������������ ����� �� ���� �� ������� (������ � ���� �������) �������� �� ��������� ������� ������ �������
		vyruchka += ceil(sumaZaPalneNaMarshrut + vyruchka) - (sumaZaPalneNaMarshrut + vyruchka);
		
		//��/�
		tableCell.setAlignment(Qt::AlignCenter);
		tableCell.set(row,0,iter, textCharFormat);
			//�������
		//���
		tableCell.setAlignment(Qt::AlignLeft);
		tableCell.set(row,1,query.value(4).toString()+"."+query.value(6).toString()+"."
						+query.value(7).toString(), textCharFormat);
		//��������
		tableCell.set(row,2,query.value(5).toString(), textCharFormat);
		//����
		tableCell.setAlignment(Qt::AlignRight);
		tableCell.set(row,3,vyruchka+sumaZaPalneNaMarshrut, textCharFormat);
		//�������, ���.
		tableCell.set(row,4,vyruchka, textCharFormat);
			//������
		//�����
		tableCell.setAlignment(Qt::AlignCenter);
		tableCell.set(row,5,query.value(11).toString()+", "+query.value(10).toString(), textCharFormat);
		//����. �����.
		tableCell.setAlignment(Qt::AlignRight);
		tableCell.set(row,6,QString::number(dovjMarshrutu), textCharFormat);
		//����. �� 100 ��.
		tableCell.set(row,7,QString::number(rozhidNa100Km), textCharFormat);
		//����. �� �����.
		tableCell.set(row,8,rozhidPalnNaMarshrut, textCharFormat);
		//ֳ��, ���.
		tableCell.set(row,9,cinaPalnogo, textCharFormat);
		//����, ���.
		tableCell.set(row,10,sumaZaPalneNaMarshrut, textCharFormat);
		
		row++;
		postup->incPos();
	}
	
	//ϳ�����
	cursor.movePosition(QTextCursor::End);
	textCharFormat.setFontPointSize( 10 );
	cursor.insertFragment(pidpysy(11, textCharFormat, QPrinter::Landscape));
	
	delete postup;
	printform->printer()->setDocName("����� ������� ������ �� "+QString::number(vDate.month())+"."+QString::number(vDate.year()));
	printform->printer()->setPageMargins( 10, 10, 10, 10, QPrinter::Millimeter );
	printform->show();
	
}
//--------------------utech--------------------utech--------------------utech--------------------
void UPrintDocs_APark::print_VidomistMarshrutivVDen(QDate vDate)
{
	printform = new UPrintForm(0, "³������ ��������� ����� ������� �� �������� ��������");
	
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
	cursor.insertText("�������� �������� ��������� \"�������� ��������\" "+QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm"), textCharFormat);
	blockFormat.setAlignment( Qt::AlignCenter );
	cursor.insertBlock(blockFormat);
	textCharFormat_bold.setFontPointSize( 11 );
	textCharFormat_small.setFontPointSize( 5 );
	cursor.insertText("²��̲���\n ��������� ����� ������� �� �������� �������� ������ ����������\n������ �� "+vDate.toString("dd.MM.yyyy"), textCharFormat_bold);
	blockFormat.setAlignment( Qt::AlignHCenter );
	cursor.insertBlock(blockFormat);
	cursor.insertText(" ", textCharFormat_small);
	cursor.insertBlock(blockFormat);
	//��������� �������
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
	
	//���������� ����� �������
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
	tableCell.set(0,0,"�������", textCharFormat);
	tableCell.set(0,1,"������� �� ����", textCharFormat);
	tableCell.set(1,1,"����.", textCharFormat);
	tableCell.set(1,2,"����.", textCharFormat);
	tableCell.set(1,3,"²����.", textCharFormat);
	tableCell.set(1,4,"%", textCharFormat);
	tableCell.set(0,5,"������ �������� �� ����", textCharFormat);
	tableCell.set(1,5,"�� ���̲", textCharFormat);
	tableCell.set(1,6,"�� �̲��", textCharFormat);
	tableCell.set(1,7,"²����.", textCharFormat);
	tableCell.set(0,8,"������� � ������� �����", textCharFormat);
	tableCell.set(1,8,"����.", textCharFormat);
	tableCell.set(1,9,"����.", textCharFormat);
	tableCell.set(1,10,"²����.", textCharFormat);
	tableCell.set(1,11,"%", textCharFormat);
	tableCell.set(0,12,"������ �������� � ������� �����", textCharFormat);
	tableCell.set(1,12,"�� ���̲", textCharFormat);
	tableCell.set(1,13,"�� �̲��", textCharFormat);
	tableCell.set(1,14,"²����.", textCharFormat);
	
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
	//������������� ������ ��䳿�
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
		//������� �� ����
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
		//������� �������� �� ����
		plan = qRound(pokaznQuery.value(2).toDouble()*100)/100.0;
		fact = qRound(pokaznQuery.value(3).toDouble()*100)/100.0;
		planPalnogoVDen += plan;
		factPalnogoVDen += fact;
		tableCell.setDash(row,5,plan, textCharFormat);
		tableCell.setDash(row,6,fact, textCharFormat);
		tableCell.setDash(row,7,fact-plan, textCharFormat);
		//������� � �����
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
		//������� �������� �� �����
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
	tableCell.set(row,0,"������", textCharFormat_bold);
	//������� �� ����
	tableCell.setAlignment(Qt::AlignRight);
	tableCell.setDash(row,1,planVyruchkyVDen, textCharFormat);
	tableCell.setDash(row,2,factVyruchkyVDen, textCharFormat);
	tableCell.setDash(row,3,factVyruchkyVDen-planVyruchkyVDen, textCharFormat);
	if (planVyruchkyVDen != 0)
		tableCell.setDash(row,4,qRound(factVyruchkyVDen*10000/planVyruchkyVDen)/100.0, textCharFormat);
	else
		tableCell.set(row,4,"-", textCharFormat);
	//������� �������� �� ����
	tableCell.setDash(row,5,planPalnogoVDen, textCharFormat);
	tableCell.setDash(row,6,factPalnogoVDen, textCharFormat);
	tableCell.setDash(row,7,factPalnogoVDen-planPalnogoVDen, textCharFormat);
	//������� � �����
	tableCell.setDash(row,8,planVyruchkyVMisyac, textCharFormat);
	tableCell.setDash(row,9,factVyruchkyVMisyac, textCharFormat);
	tableCell.setDash(row,10,factVyruchkyVMisyac-planVyruchkyVMisyac, textCharFormat);
	if (planVyruchkyVMisyac != 0)
		tableCell.setDash(row,11,qRound(factVyruchkyVMisyac*10000/planVyruchkyVMisyac)/100.0, textCharFormat);
	else
		tableCell.set(row,11,"-", textCharFormat);
	//������� �������� �� �����
	tableCell.setDash(row,12,planPalnogoVMisyac, textCharFormat);
	tableCell.setDash(row,13,factPalnogoVMisyac, textCharFormat);
	tableCell.setDash(row,14,factPalnogoVMisyac-planPalnogoVMisyac, textCharFormat);
	
	cursor.movePosition(QTextCursor::End);
	blockFormat.setAlignment( Qt::AlignLeft );
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	
	query.exec("SELECT count(*) FROM shlyahovyiLyst WHERE date(ToZvitDate)='"+vDate.toString("yyyy-MM-dd")+"'");
	query.next();
	cursor.insertText("ʳ������ �������� ����� �� ����: "+query.value(0).toString()+".", textCharFormat);
	cursor.setBlockFormat( blockFormat );
	cursor.insertBlock(blockFormat);
	query.exec("SELECT count(*) FROM shlyahovyiLyst \
				WHERE date(ToZvitDate) BETWEEN '"+begMonthDate.toString("yyyy-MM-dd")+"' \
									AND '"+vDate.toString("yyyy-MM-dd")+"'");
	query.next();
	cursor.insertText("ʳ������ �������� ����� � ������� �����: "+query.value(0).toString()+".", textCharFormat);
	
	cursor.insertFragment(pidpysy(5, textCharFormat, QPrinter::Landscape));
	
	printform->printer()->setOrientation(QPrinter::Landscape);
	printform->printer()->setDocName("³������ ��������� ����� ������� �� �������� ��������");
	printform->printer()->setPageMargins( 4, 10, 4, 20, QPrinter::Millimeter );
	printform->show();
}
//--------------------utech--------------------utech--------------------utech--------------------
void UPrintDocs_APark::print_zvitVykorystannyaKoshtivPalne(int zvitId)
{
    printform = new UForm_AParkCustomPrintForm(0, "���� ��� ������������ ����� �� ������");
	printform->printer()->setPaperSize(QPrinter::A5);
	printform->printer()->setPageMargins( 4, 3, 3, 3, QPrinter::Millimeter );
	
	QString xStr;
	QDate xDate;
	
	QSqlQuery zQuery;
	zQuery.exec("SELECT zvitKupivliPalnogo.CDate, zvitKupivliPalnogo.MarkaPalnogo_id, zvitKupivliPalnogo.ZvitNum, \
						zOrders.cnt, zOrders.Kilk, zOrders.Suma, zvitKupivliPalnogo.Npr_id \
				FROM zvitKupivliPalnogo \
				LEFT JOIN (SELECT zvitKupivliPalnogo_id, count(*) AS cnt, sum(Kilkist) AS Kilk, sum(Suma) AS Suma \
							FROM zvitKupivliPalnogoOrders GROUP BY zvitKupivliPalnogo_id) AS zOrders \
					ON zOrders.zvitKupivliPalnogo_id = zvitKupivliPalnogo.id \
				WHERE zvitKupivliPalnogo.id="+sqlStr(zvitId));
	zQuery.next();
	
	QSqlQuery nprQuery;
	nprQuery.exec("SELECT Prizv, Imia, Pobatk, Iden_kod FROM npr WHERE id="+sqlStr(zQuery.value(6).toInt()));
	nprQuery.next();
	
	UPopulateCell tableCell(0);
	QTextTableFormat tableFormat;
	QVector<QTextLength> constraints;
	QTextTable *table;
	QTextTable *tableIndPodNum;
	QTextTable *internalTable;
	UPopulateCell *pCell;
	
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
	
	//��������� �������� ������� �����������
	constraints.clear();
	constraints << QTextLength(QTextLength::FixedLength, 350);
	constraints << QTextLength(QTextLength::FixedLength, 150);
		
	tableFormat.setColumnWidthConstraints(constraints);
	tableFormat.setCellSpacing(0);
	tableFormat.setCellPadding(1);
	tableFormat.setBorder(0);
	table = cursor.insertTable(1, 2, tableFormat);
	tableCell.setTextTable(table);
	
	blockFormat.setBottomMargin(0);
	blockFormat.setTopMargin(0);
	
	textCharFormat.setFontPointSize( 7 );
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	textCharFormat_bold.setFontPointSize( 7 );
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	
	tableCell.setAlignment(Qt::AlignLeft);
	tableCell.set(0,1,"�����������\n����� �������� ���������\n����������� ������\n23.12.2010 � 996", textCharFormat);
	
	cursor.movePosition(QTextCursor::End);
	blockFormat.setAlignment( Qt::AlignCenter );
	cursor.insertBlock(blockFormat);
	//cursor.insertBlock(blockFormat);
	
	textCharFormat.setFontPointSize( 8.5 );
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	textCharFormat_bold.setFontPointSize( 8.5 );
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	
	cursor.insertText("��� ��� ������������ �����, ������� �� ����������\n��� �� ��� �", textCharFormat_bold);
	xStr = zQuery.value(2).toString();
	xDate = zQuery.value(0).toDate();
	cursor.insertText(xStr.size() > 0 ? xStr : "_____", textCharFormat_bold);
	cursor.insertText(QString(" ��") + (xDate.isValid() ? xDate.toString("dd.MM.yyyy") : "\"___\"__________20___") + QString("����"), textCharFormat_bold);
	
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	
	textCharFormat.setFontPointSize( 7.5 );
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	textCharFormat_bold.setFontPointSize( 7.5 );
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	
	// ��������� ���������ί �������� ������� � ������ ���������
	constraints.clear();
	constraints << QTextLength(QTextLength::FixedLength, 240);
	constraints << QTextLength(QTextLength::FixedLength, 220);
	constraints << QTextLength(QTextLength::FixedLength, 40);	
	
	tableFormat.setColumnWidthConstraints(constraints);
	tableFormat.setCellSpacing(0);
	tableFormat.setCellPadding(1);
	tableFormat.setBorder(0);
	table = cursor.insertTable(1, 3, tableFormat);
	tableCell.setTextTable(table);
	
	blockFormat.setBottomMargin(0);
	blockFormat.setTopMargin(0);
	
	textCharFormat.setFontPointSize( 7 );
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	textCharFormat_bold.setFontPointSize( 7 );
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	
	tableCell.setAlignment(Qt::AlignCenter);
	// ���������� ����������� ������� "�������� ...
	tableCell.set(0,2,verticalTextToImage("�������� ��������� �� �������� �� ______________�����.���", textCharFormat), textCharFormat);
	tableCell.insertImage(verticalTextToImage("_______20___���� �� ����______���. ���������_____ ϳ����", textCharFormat));
	
	textCharFormat.setFontPointSize( 7.5 );
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	textCharFormat_bold.setFontPointSize( 7.5 );
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	
	// ���������� ˲�ί ������� �������� �������
	cell = table->cellAt(0, 0);
	cursor = cell.firstCursorPosition();
	blockFormat.setAlignment( Qt::AlignLeft );
	cursor.setBlockFormat( blockFormat );
	
	cursor.insertText("������������ ����������� ������ ", textCharFormat);
	cursor.insertText(OrganizName(), textCharFormat_bold);
	
	cursor.insertText("��� �� ������\n", textCharFormat);
	//������� ���� ������
		constraints.clear();
		constraints << QTextLength(QTextLength::FixedLength, 17);
		constraints << QTextLength(QTextLength::FixedLength, 17);
		constraints << QTextLength(QTextLength::FixedLength, 17);
		constraints << QTextLength(QTextLength::FixedLength, 17);
		constraints << QTextLength(QTextLength::FixedLength, 17);
		constraints << QTextLength(QTextLength::FixedLength, 17);
		constraints << QTextLength(QTextLength::FixedLength, 17);
		constraints << QTextLength(QTextLength::FixedLength, 17);
		tableFormat.setColumnWidthConstraints(constraints);
		tableFormat.setAlignment(Qt::AlignLeft);
		tableFormat.setCellSpacing(0);
		tableFormat.setCellPadding(0.5);
		tableFormat.setBorder(1);
		tableFormat.setBorderBrush(QColor(Qt::black));
		tableIndPodNum = cursor.insertTable(1, 8, tableFormat);
		pCell = new UPopulateCell(tableIndPodNum);
		pCell->setAlignment( Qt::AlignCenter);
		textCharFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
		pCell->setTextCharFormat(textCharFormat_bold);
		xStr = OrganizEDRPOU();
		if (xStr.size() > 7){
			for (int i = 0; i < 8; i++)
			    pCell->set(0, i, xStr.at(i));
		}
		delete pCell;
	
	cursor = cell.lastCursorPosition();
	blockFormat.setAlignment( Qt::AlignLeft );
	cursor.insertBlock(blockFormat);
	cursor.insertText("³���      ������", textCharFormat);
	blockFormat.setAlignment( Qt::AlignCenter );
	cursor.insertBlock(blockFormat);
	cursor.insertText("����", textCharFormat_bold);
	blockFormat.setAlignment( Qt::AlignLeft );
	cursor.insertBlock(blockFormat);
	cursor.insertText("ϲ� ", textCharFormat);
	cursor.insertText(nprQuery.value(0).toString()+" "+nprQuery.value(1).toString().at(0)+"."+nprQuery.value(2).toString().at(0)+".", textCharFormat_bold);
	cursor.insertBlock(blockFormat);
	cursor.insertText("���������� ����� (����, ����� ��������)", textCharFormat);
	
	//������� ���������� �����
		constraints.clear();
		constraints << QTextLength(QTextLength::FixedLength, 17);
		constraints << QTextLength(QTextLength::FixedLength, 17);
		constraints << QTextLength(QTextLength::FixedLength, 17);
		constraints << QTextLength(QTextLength::FixedLength, 17);
		constraints << QTextLength(QTextLength::FixedLength, 17);
		constraints << QTextLength(QTextLength::FixedLength, 17);
		constraints << QTextLength(QTextLength::FixedLength, 17);
		constraints << QTextLength(QTextLength::FixedLength, 17);
		constraints << QTextLength(QTextLength::FixedLength, 17);
		constraints << QTextLength(QTextLength::FixedLength, 17);
		tableFormat.setColumnWidthConstraints(constraints);
		tableFormat.setAlignment(Qt::AlignLeft);
		tableFormat.setCellSpacing(0);
		tableFormat.setCellPadding(0.5);
		tableFormat.setBorder(1);
		tableFormat.setBorderBrush(QColor(Qt::black));
		tableIndPodNum = cursor.insertTable(1, 10, tableFormat);
		pCell = new UPopulateCell(tableIndPodNum);
		pCell->setAlignment( Qt::AlignCenter);
		textCharFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
		pCell->setTextCharFormat(textCharFormat_bold);
		xStr = nprQuery.value(3).toString();
		if (xStr.size() > 9){
			for (int i = 0; i < 10; i++)
			    pCell->set(0, i, xStr.at(i));
		}
		delete pCell;
	
	cursor = cell.lastCursorPosition();
	blockFormat.setAlignment( Qt::AlignLeft );
	cursor.insertBlock(blockFormat);
	cursor.insertText("����������� ������", textCharFormat);
	cursor.insertBlock(blockFormat);
	cursor.insertText("�������� �� ������", textCharFormat_bold);
	
	//��������� �������� �������
	constraints.clear();
	constraints << QTextLength(QTextLength::FixedLength, 150);
	constraints << QTextLength(QTextLength::FixedLength, 60);
		
	tableFormat.setColumnWidthConstraints(constraints);
	tableFormat.setCellSpacing(0);
	tableFormat.setCellPadding(1);
	tableFormat.setBorder(0.5);
	internalTable = cursor.insertTable(11, 2, tableFormat);
	tableCell.setTextTable(internalTable);
	
	//internalTable->mergeCells(0, 0, 2, 1);
	internalTable->mergeCells(2, 0, 2, 1);
	internalTable->mergeCells(7, 0, 3, 1);
	
	textCharFormat.setFontPointSize( 6.5 );
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	textCharFormat_bold.setFontPointSize( 6.5 );
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	
	tableCell.setTextCharFormat(textCharFormat);
	tableCell.setAlignment( Qt::AlignCenter );
	tableCell.set(0,1,"����");
	tableCell.setAlignment( Qt::AlignLeft );
	tableCell.set(1,0,"������� ������������ ������");
	tableCell.set(2,0,"�����������\n��������  (�� ����, � �� ����)");
	tableCell.set(4,0,"1.");
	tableCell.set(5,0,"2.");
	tableCell.set(6,0,"3.");
	tableCell.set(7,0,"   ������ ��������\n���������\n�������");
	tableCell.set(10,0,"�����������");
	
	
	// ���������� ����ί ������� �������� �������
	textCharFormat.setFontPointSize( 7.5 );
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	textCharFormat_bold.setFontPointSize( 7.5 );
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	
	cell = table->cellAt(0, 1);
	cursor = cell.firstCursorPosition();
	blockFormat.setAlignment( Qt::AlignLeft );
	cursor.setBlockFormat( blockFormat );
	
	cursor.insertText("��� ����������� � ���", textCharFormat);
	cursor.insertBlock(blockFormat);
	cursor.insertText(numberToString(uMToStr2(zQuery.value(5).toDouble())), textCharFormat_bold);
	cursor.insertBlock(blockFormat);
	cursor.insertText("������� ______________", textCharFormat);
	cursor.insertBlock(blockFormat);
	xDate = zQuery.value(0).toDate();
	cursor.insertText((xDate.isValid() ? xDate.toString("dd.MM.yyyy") : "\"___\"__________20___") + QString("����"), textCharFormat);
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	cursor.insertText("��� ���������", textCharFormat);
	cursor.insertBlock(blockFormat);
	cursor.insertText(uMToStr2(zQuery.value(5).toDouble())+" ���.", textCharFormat_bold);
	cursor.insertBlock(blockFormat);
	cursor.insertText((xDate.isValid() ? xDate.toString("dd.MM.yyyy") : "\"___\"__________20___") + QString("����"), textCharFormat);
	cursor.insertBlock(blockFormat);
	cursor.insertText("��������� ______________", textCharFormat);
	
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	
	//��������� �������� �������
	constraints.clear();
	constraints << QTextLength(QTextLength::FixedLength, 60);
	constraints << QTextLength(QTextLength::FixedLength, 60);
	constraints << QTextLength(QTextLength::FixedLength, 60);
	constraints << QTextLength(QTextLength::FixedLength, 25);
		
	tableFormat.setColumnWidthConstraints(constraints);
	tableFormat.setCellSpacing(0);
	tableFormat.setCellPadding(1);
	tableFormat.setBorder(0.5);
	internalTable = cursor.insertTable(11, 4, tableFormat);
	tableCell.setTextTable(internalTable);
	
	internalTable->mergeCells(0, 2, 1, 2);
	
	tableCell.setTextCharFormat(textCharFormat);
	tableCell.setAlignment( Qt::AlignCenter );
	tableCell.set(0,0,"�����");
	tableCell.set(0,1,"������");
	tableCell.set(0,2,"����");
	
	// �����
	tableCell.setAlignment( Qt::AlignCenter );
	tableCell.set(1,1,"71", textCharFormat_bold);
	double dVal = zQuery.value(5).toDouble();
	tableCell.setAlignment( Qt::AlignRight );
	tableCell.set(1,2,(int) dVal, textCharFormat_bold);
	tableCell.set(1,3,qRound( (dVal - ((int) dVal)) * 100), textCharFormat_bold);
	// ���� ��� ���
	tableCell.setAlignment( Qt::AlignCenter );
	QString buhRah;
	switch (zQuery.value(1).toInt()) {
	    case 6:
		    buhRah = "06/4";
			break;
		case 8:
		    buhRah = "06/5";
			break;
		default:
		    buhRah = "06/1";
	}
	
	tableCell.set(2,0, buhRah, textCharFormat_bold);
	double pdv = uDToM(zQuery.value(5).toDouble() / 6);
	dVal = zQuery.value(5).toDouble() - pdv;
	tableCell.setAlignment( Qt::AlignRight );
	tableCell.set(2,2,(int) dVal, textCharFormat_bold);
	tableCell.set(2,3,qRound( (dVal - ((int) dVal)) * 100), textCharFormat_bold);
	// �����
	tableCell.setAlignment( Qt::AlignCenter );
	tableCell.set(3,0,"68", textCharFormat_bold);
	dVal = pdv;
	tableCell.setAlignment( Qt::AlignRight );
	tableCell.set(3,2,(int) dVal, textCharFormat_bold);
	tableCell.set(3,3,qRound( (dVal - ((int) dVal)) * 100), textCharFormat_bold);
	
	// ʳ���� ���������� �������� �������
	
	cursor.movePosition(QTextCursor::End);
	blockFormat.setAlignment( Qt::AlignLeft );
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	cursor.insertText("������� ", textCharFormat);
	cursor.insertText(zQuery.value(3).toString(), textCharFormat_bold);
	cursor.insertText(" ���������", textCharFormat);
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	cursor.insertText("___________________   ____________________________________________________________", textCharFormat);
	cursor.insertBlock(blockFormat);
	cursor.insertText("������� �������� � ��� _____________���.     �� ������� ������� �_____��__________20___����", textCharFormat);
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	cursor.insertText("\"___\"__________20___     ϳ���� ________________ ������ ��������� �������� �� ������", textCharFormat);
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	cursor.insertText("��� ����������� ���� ������ ���������� ����� �������� �����, �� ���� ������� ��������� ����� ����������:\n"
					"���� ������� = ����������� ���� * ������ �������������\n"
					"(����� 167.1 ����� 167 ����������� ������� ������) : 100.\n"
					"���� ������� _____ (���.) = �� ��������� ���� ____________ (���.) * 15 : 100.\n"
					"ϳ���� �����, �� ������ ���������� __________    ���� ��������� ���������� \"___\"__________20___����\n"
					"���� ������� _____ (���.) = �� ��������� ���� ____________ (���.) * 15 : 100.\n"
					"ϳ���� �����, �� ������ ���������� __________    ���� ��������� ���������� \"___\"__________20___����\n"
					"� ����������� ������������: ����� ____________________________________ ���� ____________"
	
		, textCharFormat);
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	
	textCharFormat.setFontPointSize( 7 );
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	textCharFormat_bold.setFontPointSize( 7 );
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	
	cursor.insertText("* ���� �� ����� �������� ��� �������� ���, �� ����� ��� ������ ����������� ����������"
					"�� ��������� ������������ ������ ������ ������ �������� ������� �� ��������� ��� �� ���������"
					"����� �������� ��������� ������ � ����� ������ � �������."
	
		, textCharFormat);
		
	
	//  - - - - - - - - - - - - - - - - - - - - 
	// ������� 2
	
	blockFormat.setPageBreakPolicy(QTextFormat::PageBreak_AlwaysBefore	);
	cursor.insertBlock(blockFormat);
	blockFormat.setPageBreakPolicy(QTextFormat::PageBreak_Auto);
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	
	constraints.clear();
	constraints << QTextLength(QTextLength::FixedLength, 30);
	constraints << QTextLength(QTextLength::FixedLength, 60);
	constraints << QTextLength(QTextLength::FixedLength, 230);
	constraints << QTextLength(QTextLength::FixedLength, 70);
	constraints << QTextLength(QTextLength::FixedLength, 70);
	constraints << QTextLength(QTextLength::FixedLength, 40);	
	
	int rowCount = zQuery.value(3).toInt();
	
	tableFormat.setColumnWidthConstraints(constraints);
	tableFormat.setCellSpacing(0);
	tableFormat.setCellPadding(1);
	tableFormat.setBorder(0.5);
	tableFormat.setBorderBrush(QColor(Qt::black));
	table = cursor.insertTable(2 + rowCount, 6, tableFormat);
	tableCell.setTextTable(table);
	
	blockFormat.setBottomMargin(0);
	blockFormat.setTopMargin(0);
	
	textCharFormat.setFontPointSize( 7 );
	textCharFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	textCharFormat_bold.setFontPointSize( 7 );
	textCharFormat_bold.setVerticalAlignment(QTextCharFormat::AlignMiddle);
	
	tableCell.setAlignment(Qt::AlignCenter);
	tableCell.set(0,0,"� �/�");
	tableCell.set(0,1,"���� �����.");
	tableCell.set(0,2,"����, �� �� � �� ������ ����� ���������\n���������");
	tableCell.set(0,3,"�-���");
	tableCell.set(0,4,"����");
	tableCell.set(0,5,"�����\n�������");
	
	zQuery.exec("SELECT CDate, DocNum, Kilkist, Suma FROM apark_14608.zvitKupivliPalnogoOrders z \
				WHERE ZvitKupivliPalnogo_id = "+sqlStr(zvitId)+" \
				ORDER BY id");
	
	int row;
	double kilkistSum = 0, sumaSum = 0;
	for (row = 1; row <= rowCount && zQuery.next(); row++) {
	    // "� �/�"
		tableCell.setAlignment(Qt::AlignCenter);
		tableCell.set(row,0,row);
	    // "���� �����."
		tableCell.setAlignment(Qt::AlignRight);
		tableCell.set(row,1,zQuery.value(0).toDate().toString("dd.MM.yy"));
	    // "����, �� �� � �� ������ ����� ���������\n���������"
		tableCell.setAlignment(Qt::AlignLeft);
                tableCell.set(row,2,"��� �"+zQuery.value(1).toString());
	    // "�-���"
		tableCell.setAlignment(Qt::AlignRight);
		dVal = uDToM(zQuery.value(2).toDouble());
		kilkistSum += dVal;
		tableCell.set(row,3,uMToStr2(dVal));
	    // "����"
		dVal = uDToM(zQuery.value(3).toDouble());
		sumaSum += dVal;
		tableCell.set(row,4,uMToStr2(dVal));
	    // "�����\n�������"
		tableCell.set(row,5,"");
	}
	
	table->mergeCells(row, 0, 1, 3);
	tableCell.setAlignment(Qt::AlignRight);
	tableCell.set(row,0,"�����");
	tableCell.set(row,3,uMToStr2(kilkistSum));
	tableCell.set(row,4,uMToStr2(sumaSum));
	
	
	cursor.movePosition(QTextCursor::End);
	blockFormat.setAlignment( Qt::AlignLeft );
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	cursor.insertBlock(blockFormat);
	
	cursor.insertText("    ϳ���� ������� ����� __________________________________________________", textCharFormat);
	cursor.insertText((xDate.isValid() ? xDate.toString("dd.MM.yyyy") : "\"___\"__________20___") + QString("����"), textCharFormat);
	
	printform->printer()->setDocName("���� ��� ������������ ����� �� ������");
	printform->show();
}
//--------------------utech--------------------utech--------------------utech--------------------
