//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл декларації класу вікна реєстрації користувача
//
// Створений програмістами Компанії "Утех" 29.03.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#ifndef UAUTOPARKMENEGER_APark_H
#define UAUTOPARKMENEGER_APark_H

#ifdef Q_OS_LINUX
	#define U_PROG_CHAR_CODING "WINDOWS-1251"
#endif
#ifdef Q_OS_WIN32
	#define U_PROG_CHAR_CODING "CP1251"
#endif

#include <QDate>
#include <QStringList>
#include <QWidget>
#include <QToolBar>
#include <QSqlQuery>
#include <USqlAccessible>
#include <QtDebug>

//--------------------utech--------------------utech--------------------utech--------------------
class UAutoPark : public QObject
{
  Q_OBJECT
  Q_ENUMS(UPrograms)
  Q_ENUMS(UAccess)
  Q_ENUMS(UUserLog)
  Q_ENUMS(UPerevezTabWidgetParts)
  Q_ENUMS(UPerevezTabWidgetPartsWay)
  private:
	UAutoPark(){
		
	};
  public:
	enum UPrograms {NoProgram=0, ProgramPerevez=1, ProgramZarplata=2, ProgramSklad=3};
	//static const char **ProgramsList;
	
	enum UAccess {AccessDenyed=0, ReadOnly=1, WriteOnly=2, ReadWrite=3};
	enum UUserLog {LoginSuccessful=1, CloseLogin=2, WrongPassword=101, ProgramAccessDenyed=102};
	enum UPerevezTabWidgetParts{NoWidget=0, 
								HelpWidget=1, 
								RuhomyiSkladWidget=2, 
								MarshrutyWidget=3,
								ShlyahovyiLystWidget=4,
								LystokRegulyarnostiRuhuWidget=5,
								PalneWidget=6,
								TOLogWidget=7,
								ProbigInfoWidget=8,
								PerelikPracivnykiv=9,
								KartkyOblikuVykonPlanu=10,
								ZvitPoPilgovomuProizdu=11,
								MarkaAutoWidget=12,
								PlanNaZminuWidget=13,
								EditTabelWidget=14,
								SvyatkoviDniWidget=15,
								KartkyRobotyVodiyivWidget=16,
								DocumentsViewWidget=17,
								EditSumTabelWidget=18,
								EditZarplataAgentski=19,
								DocumentsViewWidget_PlanovyiViddil=20,
								MonthCloseWidget=21,
								PrintDocksSignsWidget=22,
								PalneManagementWidget=23,
								PartneryWidget=24,
								EditTabelPidrozdilivWidget=25
	};
	enum UPerevezTabWidgetPartsWay{CreateTab=0, UpdateTab=1};
	
	static const char* version();
	static int dbVersion();
	static QTime reshtaChasu();
	static double cinaPalnogo(short palneId, QDate dt = QDate::currentDate());
	//static double planNaZminu(int Marshrut_id, QDate dt = QDate::currentDate());
	static double planNaZminu(int kodMarshrutu, short grafikNum, short zminaNum, QDate dt = QDate::currentDate(),
								double cinaPalnogo=0, double kilkPalnogo=0);
};
//--------------------utech--------------------utech--------------------utech--------------------
class UAutoParkPrograms
{
  public:
	UAutoParkPrograms();
	QStringList ProgramsList;
};
//--------------------utech--------------------utech--------------------utech--------------------
class UPerevezTabWidgetPartsNames
{
  public:
	UPerevezTabWidgetPartsNames();
	QStringList PartsNames;
};
//--------------------utech--------------------utech--------------------utech--------------------
class UAParkTabWidget : public QWidget
{
	Q_OBJECT
  public:
	UAParkTabWidget(int tWType, QWidget* parent = 0) : QWidget(parent), _tabWidgetType(tWType){};
	~UAParkTabWidget(){emit mainWindowClosed();};
	virtual void populateToolBar(QToolBar * tBar){};
	inline int tabWidgetType(){return _tabWidgetType;};
  protected:
	int _tabWidgetType;
  signals:
	void mainWindowClosed();
};
//--------------------utech--------------------utech--------------------utech--------------------
class UWorkMonth
{
  public:
	UWorkMonth(short year, short month);
	UWorkMonth(QDate date);
	QDate begDate();
	QDate endDate();
  private:
	QDate _begDate;
	QDate _endDate;
};
//--------------------utech--------------------utech--------------------utech--------------------
struct UTabelDay
{
	short workType; //Тип присутності: на роботі, відпустка, лікарняні і т.д.
	QTime rob;
	QTime sv;
	QTime nich;
};
Q_DECLARE_METATYPE(UTabelDay)
//--------------------utech--------------------utech--------------------utech--------------------
#endif
