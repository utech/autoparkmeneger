include(../../salary/src/project_files.pri)
include(../../ugurtsklad/src/ugurtsklad.pro)
include(../../UtechLib/UtechLib.pri)

TEMPLATE = app
VERSION = 1.0.8
unix:TARGET = autopark.bin
win32:TARGET = autopark
DEPENDPATH += $$PWD/. $$PWD/.. $$PWD/guiautopark $$PWD/additional $$PWD/images . ..

CONFIG		+= release
CONFIG		-= debug debug_and_release debug_and_release_target

INCLUDEPATH += . ..

QT +=   sql

# Input
HEADERS += UDialogRegisterUser_APark.h \
			UDifFunc_APark.h \
			UAutoParkMeneger_APark.h \
			UDialogChangePassword_APark.h \
			UMainWindow_AParkPerevez.h \
			UForm_AParkRuhomyiSklad.h \
			UForm_AParkMarshruty.h \
			UForm_AParkShlyahovyiLyst.h \
			UForm_AParkLystokRegulyarnostiRuhu.h \
			UForm_AParkMarkyAuto.h \
			UForm_AParkCinaPalnogo.h \
			UPrintDocs_APark.h \
			UForm_AParkHelpWidget.h \
			UForm_AParkTOLog.h \
			UForm_AParkProbigInfo.h \
			UDialog_AParkDateFilter.h \
			UDialog_AParkAutobusDateFilter.h \
			UForm_AParkPracivnyky.h \
			UDialog_AParkMarshrutTypeDateFilter.h \
			UForm_AParkKartkyOblikuVykonannyaPlanu.h \
			UForm_AParkRozrahSumyKompensPoPilgah.h \
			UForm_AParkPlanNaZminu.h \
			UForm_AParkEditTabelWidget.h \
			UForm_AParkEditTabelPidrozdilivWidget.h \
			UDialog_AParkEditTabelCell.h \
			UTabelDayDelegate.h \
			UForm_AParkSvyatkoviDni.h \
			UForm_AParkKartkyRobotyVodiyiv.h \
			UForm_AParkDocumentsView.h \
			UForm_AParkEditSumTabelWidget.h \
			UDialog_AParkChooseNumber.h \
			UForm_AParkZarplataAgentski.h \
			UForm_AParkDocumentsView_PlanovyiViddil.h \
			UForm_AParkCloseMonthes.h \
			UForm_AParkPrintDocksSigns.h \
			UForm_AParkPalneManagement.h \
			UForm_AParkCustomPrintForm.h \
			UDialog_AParkMarkaPalnogoDateFilter.h \
			UDialog_AParkPartnerDateFilter.h \
			UDialog_AParkPartnerMarkaPalnogoDateFilter.h \
			UForm_AParkPartnery.h \
			UExport_APark.h
FORMS += UDialogRegisterUser_APark.ui \
			UDialogChangePassword_APark.ui \
			UMainWindow_AParkPerevez.ui \
			UForm_AParkRuhomyiSklad.ui \
			UForm_AParkMarshruty.ui \
			UForm_AParkShlyahovyiLyst.ui \
			UForm_AParkLystokRegulyarnostiRuhu.ui \
			UForm_AParkMarkyAuto.ui \
			UForm_AParkCinaPalnogo.ui \
			UForm_AParkHelpWidget.ui \
			UForm_AParkTOLog.ui \
			UForm_AParkProbigInfo.ui \
			UDialog_AParkDateFilter.ui \
			UDialog_AParkAutobusDateFilter.ui \
			UForm_AParkPracivnyky.ui \
			UDialog_AParkMarshrutTypeDateFilter.ui \
			UForm_AParkKartkyOblikuVykonannyaPlanu.ui \
			UForm_AParkRozrahSumyKompensPoPilgah.ui \
			UForm_AParkPlanNaZminu.ui \
			UForm_AParkEditTabelWidget.ui \
			UForm_AParkEditTabelPidrozdilivWidget.ui \
			UDialog_AParkEditTabelCell.ui \
			UForm_AParkSvyatkoviDni.ui \
			UForm_AParkKartkyRobotyVodiyiv.ui \
			UForm_AParkDocumentsView.ui \
			UDialog_AParkChooseNumber.ui \
			UForm_AParkZarplataAgentski.ui \
			UForm_AParkDocumentsView_PlanovyiViddil.ui \
			UForm_AParkCloseMonthes.ui \
			UForm_AParkPrintDocksSigns.ui \
			UForm_AParkPalneManagement.ui \
			UDialog_AParkMarkaPalnogoDateFilter.ui \
			UDialog_AParkPartnerDateFilter.ui \
			UDialog_AParkPartnerMarkaPalnogoDateFilter.ui \
			UForm_AParkPartnery.ui
SOURCES += main_APark.cpp \
           UDialogRegisterUser_APark.cpp \
		   UDifFunc_APark.cpp \
		   UDialogChangePassword_APark.cpp \
		   UAutoParkMeneger_APark.cpp \
		   UMainWindow_AParkPerevez.cpp \
		   UMainWindow_AParkPerevez_constructor.cpp \
		   UMainWindow_AParkPerevez_actions.cpp \
		   UForm_AParkRuhomyiSklad.cpp \
		   UForm_AParkMarshruty.cpp \
		   UForm_AParkShlyahovyiLyst.cpp \
		   UForm_AParkLystokRegulyarnostiRuhu.cpp \
		   UForm_AParkMarkyAuto.cpp \
		   UForm_AParkCinaPalnogo.cpp \
		   UPrintDocs_APark.cpp \
		   UPrintDocs_APark_2.cpp \
		   UPrintDocs_APark_3.cpp \
		   UPrintDocsTemplates_APark.cpp \
		   UForm_AParkHelpWidget.cpp \
		   UForm_AParkTOLog.cpp \
		   UForm_AParkProbigInfo.cpp \
		   UDialog_AParkDateFilter.cpp \
		   UDialog_AParkAutobusDateFilter.cpp \
		   UForm_AParkPracivnyky.cpp \
		   UDialog_AParkMarshrutTypeDateFilter.cpp \
		   UForm_AParkKartkyOblikuVykonannyaPlanu.cpp \
		   UForm_AParkRozrahSumyKompensPoPilgah.cpp \
		   UForm_AParkPlanNaZminu.cpp \
		   UForm_AParkEditTabelWidget.cpp \
		   UForm_AParkEditTabelPidrozdilivWidget.cpp \
		   UDialog_AParkEditTabelCell.cpp \
		   UTabelDayDelegate.cpp \
		   UForm_AParkSvyatkoviDni.cpp \
		   UForm_AParkKartkyRobotyVodiyiv.cpp \
		   UForm_AParkDocumentsView.cpp \
		   UForm_AParkEditSumTabelWidget.cpp \
		   UDialog_AParkChooseNumber.cpp \
		   UForm_AParkZarplataAgentski.cpp \
		   UForm_AParkDocumentsView_PlanovyiViddil.cpp \
		   UForm_AParkCloseMonthes.cpp \
		   UForm_AParkPrintDocksSigns.cpp \
		   UForm_AParkPalneManagement.cpp \
		   UForm_AParkCustomPrintForm.cpp \
		   UDialog_AParkMarkaPalnogoDateFilter.cpp \
		   UDialog_AParkPartnerDateFilter.cpp \
		   UDialog_AParkPartnerMarkaPalnogoDateFilter.cpp \
		   UForm_AParkPartnery.cpp \
		   UExport_APark.cpp
		   
#Salary
SOURCES -= main_salary.cpp
RC_FILE -=   salaryProgIcon.rc 

#Sklad
SOURCES -= main_sklad.cpp
HEADERS -= UForm_RozrahZDebitoramy.ui
RC_FILE -=   prog_icon.rc


#libXL configuration
win32 {
    
    INCLUDEPATH += $$PWD/3rd/libxl-3.2.3/include_cpp
    LIBS += $$PWD/3rd/libxl-3.2.3/lib/libxl.lib

    #QMAKE_POST_LINK +=$$quote(cmd /c copy /y ..\..\..\bin\libxl.dll .)

}
else {

    INCLUDEPATH += $$PWD/3rd/libxl-3.2.3-linux/include_cpp
    LIBS += $$PWD/../lib/libxl.so

    QMAKE_LFLAGS_DEBUG += "-Wl,-rpath,../lib"
    QMAKE_LFLAGS_RELEASE += "-Wl,-rpath,../lib"
}


RESOURCES += UAutoParkImg.qrc

RC_FILE =   images/autoParkProgIcon.rc
DESTDIR =   ../bin

win32{
  OBJECTS_DIR = ../tmp/win
  MOC_DIR = ../tmp/win
  UI_HEADERS_DIR = ../tmp/win
  UI_SOURCES_DIR = ../tmp/win
  RCC_DIR = ../tmp/win
}
unix{
  OBJECTS_DIR = ../tmp/linux
  MOC_DIR = ../tmp/linux
  UI_HEADERS_DIR = ../tmp/linux
  UI_SOURCES_DIR = ../tmp/linux
  RCC_DIR = ../tmp/linux
}
