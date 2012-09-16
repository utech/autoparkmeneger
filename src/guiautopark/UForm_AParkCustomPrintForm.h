//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл декларації класу вікна реєстрації користувача
//
// Створений програмістами Компанії "Утех" 24.06.2011р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#ifndef UFORM_APARKCUSTOMPRINTFORM_APARK_H
#define UFORM_APARKCUSTOMPRINTFORM_APARK_H

#include <QtGui>
#include <QSettings>
#include <QDir>
#include <QtSql>

#include <UPrintForm>
#include <QPushButton>

#include "UAutoParkMeneger_APark.h"

//--------------------utech--------------------utech--------------------utech--------------------
class UForm_AParkCustomPrintForm : public UPrintForm
{
  Q_OBJECT

  public:
		UForm_AParkCustomPrintForm(QWidget *parent = 0, QString title = "", bool fullPage=false);
		virtual ~UForm_AParkCustomPrintForm();
		
  public slots:
		void pushButtonFirstPage_clicked();
		void pushButtonSecondPage_clicked();
  private:
		QPushButton *pushButtonFirstPage;
		QPushButton *pushButtonSecondPage;
};
//--------------------utech--------------------utech--------------------utech--------------------
#endif
