#include "test_qxlsx.h"
#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QtCore>
#include <QtGlobal>
#include <QVariant>
#include <widget/xlsx/XlsxDocument.h>
#include <xlsxdocument.h>
#include <xlsxworkbook.h>

void widget::test_qxlsx()
{
	int argc = 1;

	char *argv[] = {
		const_cast<char *>("Hello World"),
		nullptr,
	};

	QCoreApplication app(argc, argv);

	{
		// 创建表格
		widget::XlsxDocument xlsxW{"Test.xlsx"};
		xlsxW.Write(1, 1, "Hello Qt!");
		xlsxW.Save();
		qDebug() << "[debug] current directory is " << QDir::currentPath();
	}

	{
		// 读取
		widget::XlsxDocument xlsxR{"Test.xlsx"};
		xlsxR.Load();
		qDebug() << "[debug] success to load xlsx file.";
		qDebug() << xlsxR.ReadCellAsString(1, 1);
	}
}
