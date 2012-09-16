//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл декларації класу вікна реєстрації користувача
//
// Створений програмістами Компанії "Утех" 29.03.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#ifndef UFORM_APARKHELPWIDGET_H
#define UFORM_APARKHELPWIDGET_H

#include <QtGui>
#include <QSettings>
#include <QDir>
#include <QtSql>

#include "UAutoParkMeneger_APark.h"
#include "ui_UForm_AParkHelpWidget.h"

#include <UTableWidgetSqlExt>
//--------------------utech--------------------utech--------------------utech--------------------

//--------------------utech--------------------utech--------------------utech--------------------
class UForm_AParkHelpWidget : public UAParkTabWidget
{
  Q_OBJECT

  public:
		UForm_AParkHelpWidget(int tWType, QWidget *parent = 0);
		~UForm_AParkHelpWidget();
		
		void populateToolBar(QToolBar * tBar);
  public slots:
		
  private:
		Ui::UForm_AParkHelpWidget ui;
};
//--------------------utech--------------------utech--------------------utech--------------------
#endif
