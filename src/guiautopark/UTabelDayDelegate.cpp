//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл виконання класу вікна налаштування програми
//
// Створений програмістами Компанії "Утех" 23.03.2010р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------
#include "UTabelDayDelegate.h"
#include "UAutoParkMeneger_APark.h"

#include <QtDebug>
#include <QSqlQuery>
//--------------------utech--------------------utech--------------------utech--------------------

/*
Малювання комірки таблиці табеля. Схема комірки в файлі tabelTableCell_1.dia,
який знаходиться в кореневій папці dia
*/
#include <QFont>

UTabelDayDelegate::UTabelDayDelegate(QObject *parent)
	: QItemDelegate(parent), mergin1(4), mergin2(2), spacingV(0), spacingH(1)
{
	font1.setFamily("Impact");
	font1.setPointSize(11);
	font2.setFamily("Arial");
	font2.setPointSize(9);
	
	QFontMetrics fm1(font1), fm2(font2);
	
	width1 = fm1.width("O");
	height1 = fm1.height();
	width2 = fm2.width("0");
	height2 = fm2.height();
	
	QSqlQuery query("SELECT id, Status_char, Status_color FROM pracivn_status");
	QColor color;
	int id;
	while (query.next()){
		id = query.value(0).toInt();
		color = QColor(query.value(2).toString());
		tabelChars.insert(id, query.value(1).toString());
		tabelColors.insert(id, color.isValid()?color:QColor(Qt::darkGray));
	}
}

void UTabelDayDelegate::paint(QPainter *painter,const QStyleOptionViewItem &option,const QModelIndex &index) const
{
	QStyleOptionViewItemV4 opt = setOptions(index, option);
	QRect xRect;
	UTabelDay d = index.data(Qt::EditRole).value<UTabelDay>();
	
	drawBackground(painter, opt, index);
	
	//Малювання букви
	painter->setPen(tabelColors.value(d.workType));
	painter->setFont(font1);
	xRect.setRect(opt.rect.x()+mergin1, opt.rect.y()+mergin1, width1*2, height1);
	painter->drawText(xRect, Qt::AlignLeft | Qt::AlignTop, tabelChars.value(d.workType));
	
	//Малювання стрічок часу
	if ((opt.state & QStyle::State_Selected) != QStyle::State_Selected)
		painter->setPen(opt.palette.text().color());
	else
		painter->setPen(opt.palette.highlightedText().color());
	
	painter->setFont(font2);
	xRect.setRect(opt.rect.x()+mergin1+width1*2+spacingH, opt.rect.y()+mergin2, width2*5, height2);
	painter->drawText(xRect, Qt::AlignRight | Qt::AlignTop, (d.rob>QTime(0,0)?d.rob.toString("h:mm"):"-"));
	
	xRect.setRect(opt.rect.x()+mergin1+width1*2+spacingH, opt.rect.y()+mergin2+height2+spacingV, width2*5, height2);
	painter->drawText(xRect, Qt::AlignRight | Qt::AlignTop, (d.nich>QTime(0,0)?d.nich.toString("h:mm"):"-"));
	
	xRect.setRect(opt.rect.x()+mergin1+width1*2+spacingH, opt.rect.y()+mergin2+2*height2+2*spacingV, width2*5, height2);
	painter->drawText(xRect, Qt::AlignRight | Qt::AlignTop, (d.sv>QTime(0,0)?d.sv.toString("h:mm"):"-"));
	
	//drawDisplay(painter, opt, opt.rect, str);
	drawFocus(painter, opt, opt.rect);
}

QSize UTabelDayDelegate::sizeHint(const QStyleOptionViewItem & option,const QModelIndex & index) const
{
	return QSize(mergin1+width1*2+spacingH+5*width2+mergin2, 2*mergin2+3*height2+2*spacingV);
}
