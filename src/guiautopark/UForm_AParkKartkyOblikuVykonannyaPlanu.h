//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл декларації класу вікна реєстрації користувача
//
// Створений програмістами Компанії "Утех" 29.03.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#ifndef UFORM_APARKKARTKYOBLICUVYKONANNYAPLANU_H
#define UFORM_APARKKARTKYOBLICUVYKONANNYAPLANU_H

#include <QtGui>
#include <QSettings>
#include <QDir>
#include <QtSql>

#include "UAutoParkMeneger_APark.h"
#include "ui_UForm_AParkKartkyOblikuVykonannyaPlanu.h"
//--------------------utech--------------------utech--------------------utech--------------------
class UForm_AParkKartkyOblikuVykonannyaPlanu : public UAParkTabWidget
{
  Q_OBJECT

  public:
		UForm_AParkKartkyOblikuVykonannyaPlanu(int tWType, QWidget *parent = 0);
		~UForm_AParkKartkyOblikuVykonannyaPlanu();
		
		void populateToolBar(QToolBar * tBar);
  public slots:
		void populateVodiyiTable();
		
		void action_printKartkyOblikuVykonPlanu_activated();
  private:
		Ui::UForm_AParkKartkyOblikuVykonannyaPlanu ui;
};
//--------------------utech--------------------utech--------------------utech--------------------
#endif
