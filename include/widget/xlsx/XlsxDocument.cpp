#include "XlsxDocument.h"
#include "widget/Conversion.h"
#include <qcontainerfwd.h>
#include <xlsxformat.h>

widget::XlsxDocument::XlsxDocument()
{
	_xlsx_writer = std::shared_ptr<QXlsx::Document>{new QXlsx::Document{}};
}

widget::XlsxDocument::XlsxDocument(QString const &file_path)
{
	_xlsx_writer = std::shared_ptr<QXlsx::Document>{new QXlsx::Document{file_path}};
}

void widget::XlsxDocument::Write(int row, int column, QString const &content)
{
	Write(row, column, content, QXlsx::Format{});
}

void widget::XlsxDocument::Write(int row, int column, std::string const &content)
{
	Write(row, column, content, QXlsx::Format{});
}

void widget::XlsxDocument::Write(int row, int column, char const *content)
{
	Write(row, column, content, QXlsx::Format{});
}

void widget::XlsxDocument::Write(int row, int column, QString const &content, QXlsx::Format const &format)
{
	QVariant value{content};
	_xlsx_writer->write(row, column, value, format);
}

void widget::XlsxDocument::Write(int row, int column, std::string const &content, QXlsx::Format const &format)
{
	QString qstring{content.c_str()};
	Write(row, column, qstring, format);
}

void widget::XlsxDocument::Write(int row, int column, char const *content, QXlsx::Format const &format)
{
	Write(row, column, QString{content}, format);
}

void widget::XlsxDocument::Load() const
{
	_xlsx_writer->load();
}

std::shared_ptr<QXlsx::Cell> widget::XlsxDocument::GetCellAt(int row, int column) const
{
	return _xlsx_writer->cellAt(row, column);
}

QString widget::XlsxDocument::ReadCellAsString(int row, int column) const
{
	auto cell = GetCellAt(row, column);
	auto value = cell->readValue();
	QString qstring = value.toString();
	return qstring;
}

std::string widget::XlsxDocument::ReadCellAsStdString(int row, int column) const
{
	QString qstring = ReadCellAsString(row, column);
	return widget::ToString(qstring);
}

void widget::XlsxDocument::Save() const
{
	_xlsx_writer->save();
}

void widget::XlsxDocument::SaveAsFile(QString const &file_path) const
{
	_xlsx_writer->saveAs(file_path);
}

void widget::XlsxDocument::SaveAsFile(std::string const &file_path) const
{
	SaveAsFile(QString{file_path.c_str()});
}

void widget::XlsxDocument::SaveAsFile(char const *file_path) const
{
	SaveAsFile(QString{file_path});
}
