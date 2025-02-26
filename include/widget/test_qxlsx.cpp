#include "test_qxlsx.h"
#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QtCore>
#include <QtGlobal>
#include <QVariant>
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

	//--------------------------------------
	// [1]  Writing excel file(*.xlsx)

	QXlsx::Document xlsxW;

	int row = 1;
	int col = 1; //

	// xlsxW.write("A1", "Hello Qt!"); // write "Hello Qt!" to cell(A,1). it's shared string.
	QVariant writeValue = QString("Hello Qt!");
	xlsxW.write(row, col, writeValue);

	if (xlsxW.saveAs("Test.xlsx")) // save the document as 'Test.xlsx'
	{
		qDebug() << "[debug] success to write xlsx file";
	}
	else
	{
		qDebug() << "[debug][error] failed to write xlsx file";
		exit(-1);
	}

	qDebug() << "[debug] current directory is " << QDir::currentPath();

	//--------------------------------------
	// [2] Reading excel file(*.xlsx)

	QXlsx::Document xlsxR("Test.xlsx");
	if (xlsxR.load()) // load excel file
	{
		qDebug() << "[debug] success to load xlsx file.";

		auto cell = xlsxR.cellAt(row, col); // get cell pointer.
		if (cell != NULL)
		{
			QVariant var =
				cell->readValue();                      // read cell value (number(double), QDateTime, QString ...)
			qDebug() << "[debug] cell(1,1) is " << var; // Display value. It is 'Hello Qt!'.
		}
		else
		{
			qDebug() << "[debug][error] cell(1,1) is not set.";
			exit(-2);
		}
	}
	else
	{
		qDebug() << "[debug][error] failed to load xlsx file.";
	}
}
