//--------------------utech--------------------utech--------------------utech--------------------
//
// ���� ���������� ����� ���� ��������� �����������
//
// ��������� ������������ ������ "����" 29.03.2009�.
// � ���� ���������������� ���������� �������� QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#ifndef UDIFFUNC_APARK_H
#define UDIFFUNC_APARK_H

#include <QtSql>
#include <QtGui>
#include <QVariant>
#include <QSettings>
#include <QString>

bool connectToDB();
QVariant readSetting(QString settingPath, QString settingName, QString iniFileName = "autopark.ini");
void writeSetting(QVariant val, QString settingPath, QString settingName, QString iniFileName = "autopark.ini");
QString encrypt(QString str);
QString decrypt(QString str);
bool writeUserLog(int userId, int ProgramId, int UserOperId, QString prymitka = "");
void castControls(QObject *obj, bool isAct);

//--------------------utech--------------------utech--------------------utech--------------------
#endif
