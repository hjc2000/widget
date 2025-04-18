#include "test_qxlsx.h"
#include "widget/xlsx/XlsxDocumentEditor.h"

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
		widget::XlsxDocumentEditor xlsxW{"Test.xlsx"};
		xlsxW.Write(1, 1, "Hello Qt!");
		xlsxW.Save();
		qDebug() << "[debug] current directory is " << QDir::currentPath();
	}

	{
		// 读取
		widget::XlsxDocumentEditor xlsxR{"Test.xlsx"};
		xlsxR.Load();
		qDebug() << "[debug] success to load xlsx file.";
		qDebug() << xlsxR.ReadCellAsString(1, 1);
	}
}
