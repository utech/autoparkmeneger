//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл декларації класу вікна реєстрації користувача
//
// Створений програмістами Компанії "Утех" 29.03.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#ifndef UFORM_APARKROZRAHSUMYKOMPENSPOPILGAH_H
#define UFORM_APARKROZRAHSUMYKOMPENSPOPILGAH_H

#include <QtGui>
#include <QSettings>
#include <QDir>
#include <QtSql>

#include "UAutoParkMeneger_APark.h"
#include "ui_UForm_AParkRozrahSumyKompensPoPilgah.h"

#include <UTableWidgetSqlExt>
//--------------------utech--------------------utech--------------------utech--------------------

//--------------------utech--------------------utech--------------------utech--------------------
class UForm_AParkRozrahSumyKompensPoPilgah : public UAParkTabWidget
{
  Q_OBJECT

  public:
		UForm_AParkRozrahSumyKompensPoPilgah(int tWType, QWidget *parent = 0);
		~UForm_AParkRozrahSumyKompensPoPilgah();
		
		void populateToolBar(QToolBar * tBar);
  public slots:
		void pushButton_create_clicked();
		void pushButton_delete_clicked();
		void pushButton_avtozapovn_clicked();
		void populateDovidnykValues(QTableWidgetItem *item);
		
		void action_printSumaKompensPoPilgah_activated();
  private:
		Ui::UForm_AParkRozrahSumyKompensPoPilgah ui;
		
		UDataFormView *twExt;
};
//--------------------utech--------------------utech--------------------utech--------------------
#endif
