//--------------------utech--------------------utech--------------------utech--------------------
//
// ���� ���������� ����� ���� ��������� �����������
//
// ��������� ������������ ������ "����" 28.12.2011�.
// � ���� ���������������� ���������� �������� QT4.x
//
//--------------------utech--------------------utech--------------------utech--------------------

#ifndef UEXPORT_APARK_H
#define UEXPORT_APARK_H

#include <QtSql>
#include <QDate>

class AParkExport
{
public:
    static bool exportCheckivVExcel(QDate dt, int zaprId, QString pathToExport);
};

//--------------------utech--------------------utech--------------------utech--------------------
#endif
