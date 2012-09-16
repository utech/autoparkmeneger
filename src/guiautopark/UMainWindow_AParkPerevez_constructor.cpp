//--------------------utech--------------------utech--------------------utech--------------------
//
// Файл виконання класу вікна налаштування програми
//
// Створений програмістами Компанії "Утех" 29.03.2009р.
// У класі використовуються компоненти бібліотеки QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#include "UMainWindow_AParkPerevez.h"
#include "UDialogRegisterUser_APark.h"

//--------------------utech--------------------utech--------------------utech--------------------
UMainWindow_AParkPerevez::UMainWindow_AParkPerevez(QWidget *parent)
        : QMainWindow(parent)
{
    ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose, true);
	setWindowTitle("\"Автопарк менеджер\" в."+QString(UAutoPark::version())+" -> Користувач:  "+UDialogRegisterUser::registeredUserName());
	
	QToolButton *tButton = new QToolButton(ui.tabWidget_parts);
	tButton->setIcon(QIcon(":/icontexto_webdev_pack/icontexto_webdev_pack/icontexto-webdev-add-032x032.png"));
	tButton->setAutoRaise(true);
	connect(tButton, SIGNAL(clicked(bool)), this, SLOT(buttonCreateTabParts_clicked()));
	ui.tabWidget_parts->setCornerWidget( tButton, Qt::TopLeftCorner );
	tButton = new QToolButton(ui.tabWidget_parts);
	tButton->setIcon(QIcon(":/icontexto_webdev_pack/icontexto_webdev_pack/icontexto-webdev-remove-032x032.png"));
	tButton->setAutoRaise(true);
	connect(tButton, SIGNAL(clicked(bool)), this, SLOT(buttonDeleteTabParts_clicked()));
	ui.tabWidget_parts->setCornerWidget( tButton, Qt::TopRightCorner );
	connect(ui.tabWidget_parts, SIGNAL(tabCloseRequested(int)), this, SLOT(tabWidget_parts_tabCloseRequested(int)));
	
	populateZmistTreeWidget();
	if (!loadUserSession())
		populatePartsTabWidget(UAutoPark::HelpWidget);
	
		//Connectors
	connect(ui.treeWidget_zmist, SIGNAL(activated (const QModelIndex &)), this, SLOT(treeWidget_zmist_itemDoubleClicked()));
	connect(ui.tabWidget_parts, SIGNAL(currentChanged(int)), this, SLOT(tabWidget_parts_currentChanged(int)));
	
	connect(ui.action_debugMessages, SIGNAL(activated()), this, SLOT(action_debugMessages_activated()));
	connect(ui.action_close, SIGNAL(activated()), this, SLOT(action_close_activated()));
	
	connect(ui.action_firmInfo, SIGNAL(activated()), this, SLOT(action_firmInfo_activated()));
	connect(ui.action_aboutProgram, SIGNAL(activated()), this, SLOT(action_aboutProgram_activated()));
}
//--------------------utech--------------------utech--------------------utech--------------------
UMainWindow_AParkPerevez::~UMainWindow_AParkPerevez()
{
	saveUserSession();
	emit mainWindowClosed();
}
//--------------------utech--------------------utech--------------------utech--------------------
