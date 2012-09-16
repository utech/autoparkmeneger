//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл декларації класу вікна реєстрації користувача
//
// Створений програмістами Компанії "Утех" 29.03.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#ifndef UMAINWINDOW_APARKPEREVEZ_H
#define UMAINWINDOW_APARKPEREVEZ_H

#include <QtGui>
#include <QtDebug>
#include <QSqlQuery>
#include <QMessageBox>

#include "UAutoParkMeneger_APark.h"

#include "ui_UMainWindow_AParkPerevez.h"

//--------------------utech--------------------utech--------------------utech--------------------
class UMainWindow_AParkPerevez : public QMainWindow
{
        Q_OBJECT

    public:
        UMainWindow_AParkPerevez(QWidget *parent = 0);
		~UMainWindow_AParkPerevez();
		
		void populateZmistTreeWidget();
		bool loadUserSession();
		void saveUserSession();
    public slots:
		void action_debugMessages_activated();
		void action_close_activated();
		
		void action_firmInfo_activated();
		void action_aboutProgram_activated();
		
		void treeWidget_zmist_itemDoubleClicked();
		void buttonCreateTabParts_clicked();
		void buttonDeleteTabParts_clicked();
		void tabWidget_parts_tabCloseRequested(int index);
		void populatePartsTabWidget(int tabWidgetType = UAutoPark::HelpWidget, 
								UAutoPark::UPerevezTabWidgetPartsWay tabWidgetActionType = UAutoPark::UpdateTab,
								bool showWarnings = true);
		void tabWidget_parts_currentChanged(int index);
	signals:
		void requestDebugWindow();
		void closeLoginSignal();
		void mainWindowClosed();
	
    private:
		Ui::UMainWindow_AParkPerevez ui;
	
};
//--------------------utech--------------------utech--------------------utech--------------------
#endif
