//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл декларації класу вікна реєстрації користувача
//
// Створений програмістами Компанії "Утех" 23.03.2010р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#ifndef U_TABELDAYDELEGATE_H
#define U_TABELDAYDELEGATE_H

#include <QtGui>
#include <QTime>


class UTabelDayDelegate : public QItemDelegate
{	
   Q_OBJECT
  public:
	UTabelDayDelegate(QObject *parent = 0);
	void paint(QPainter *painter,const QStyleOptionViewItem &option,const QModelIndex &index) const;
	QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;
  private:
	QFont font1;
	QFont font2;
	int mergin1;
	int mergin2;
	int spacingV;
	int spacingH;
	int width1;
	int height1;
	int width2;
	int height2;
	QHash<unsigned char, QString> tabelChars;
	QHash<unsigned char, QColor> tabelColors;
};
#endif
