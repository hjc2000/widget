#include "XlsxWriter.h"
#include "qcontainerfwd.h"
#include "xlsxformat.h"

void widget::XlsxWriter::Write(int row, int column, QString const &content)
{
	Write(row, column, content, QXlsx::Format{});
}

void widget::XlsxWriter::Write(int row, int column, std::string const &content)
{
	Write(row, column, content, QXlsx::Format{});
}

void widget::XlsxWriter::Write(int row, int column, QString const &content, QXlsx::Format const &format)
{
	QVariant value{content};
	_xlsx_writer->write(row, column, value, format);
}

void widget::XlsxWriter::Write(int row, int column, std::string const &content, QXlsx::Format const &format)
{
	QString qstring{content.c_str()};
	Write(row, column, qstring, format);
}
