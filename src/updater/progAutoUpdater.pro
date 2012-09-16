#DEFINES += U_DEVELOP
VERSION = 1.0.1

CONFIG		+= release
CONFIG		-= debug debug_and_release debug_and_release_target

TEMPLATE = app
win32:TARGET = updater
unix:TARGET = updater.bin
DEPENDPATH += .
INCLUDEPATH += .
QT += network

RESOURCES += ../images/UAutoParkUpdaterImg.qrc
HEADERS += UProgUpdaterDialog.h \
		UProgUpdaterApi.h
FORMS += UProgUpdaterDialog.ui
SOURCES += main.cpp \
	UProgUpdaterDialog.cpp \
	UProgUpdaterApi.cpp

RC_FILE =   ../images/autoParkProgIcon.rc
DESTDIR = ../../bin
UI_DIR = .

win32{
  OBJECTS_DIR = ../../tmp/updater/windows
  MOC_DIR = ../../tmp/updater/windows
  UI_HEADERS_DIR = ../../tmp/updater/windows
  UI_SOURCES_DIR = ../../tmp/updater/windows
  RCC_DIR = ../../tmp/updater/windows
}

unix{
  OBJECTS_DIR = ../../tmp/updater/linux
  MOC_DIR = ../../tmp/updater/linux
  UI_HEADERS_DIR = ../../tmp/updater/linux
  UI_SOURCES_DIR = ../../tmp/updater/linux
  RCC_DIR = ../../tmp/updater/linux
}

contains(DEFINES,U_DEVELOP) {
  CONFIG += console
}
