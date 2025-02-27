#include "XlsxDocument.h"
#include "widget/Conversion.h"
#include <base/string/define.h>
#include <qcontainerfwd.h>
#include <stdexcept>
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
	bool result = _xlsx_writer->write(row, column, value, format);
	if (!result)
	{
		throw std::runtime_error{CODE_POS_STR + "写入失败。"};
	}
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

void widget::XlsxDocument::Write(widget::ITableDataModel const &model, QXlsx::Format const &format)
{
	int xlsx_column_start_index = 1;
	if (model.HasRowTitle())
	{
		xlsx_column_start_index = 2;
	}

	int xlsx_row_start_index = 1;
	if (model.HasColumnTitle())
	{
		xlsx_row_start_index = 2;
	}

	// 写入列标题
	for (int i = xlsx_column_start_index; i < model.ColumnCount(); i++)
	{
	}
}

void widget::XlsxDocument::Load() const
{
	bool result = _xlsx_writer->load();
	if (!result)
	{
		throw std::runtime_error{CODE_POS_STR + "加载失败。"};
	}
}

std::shared_ptr<QXlsx::Cell> widget::XlsxDocument::GetCellAt(int row, int column) const
{
	return _xlsx_writer->cellAt(row, column);
}

QString widget::XlsxDocument::ReadCellAsString(int row, int column) const
{
	auto cell = GetCellAt(row, column);
	if (cell == nullptr)
	{
		return QString{};
	}

	auto value = cell->readValue();
	QString qstring = value.toString();
	return qstring;
}

std::string widget::XlsxDocument::ReadCellAsStdString(int row, int column) const
{
	QString qstring = ReadCellAsString(row, column);
	return widget::ToString(qstring);
}

QXlsx::Worksheet *widget::XlsxDocument::CurrentWorksheet() const
{
	QXlsx::Worksheet *sheet = _xlsx_writer->currentWorksheet();
	return sheet;
}

void widget::XlsxDocument::Save() const
{
	bool result = _xlsx_writer->save();
	if (!result)
	{
		throw std::runtime_error{CODE_POS_STR + "保存失败。"};
	}
}

void widget::XlsxDocument::SaveAsFile(QString const &file_path) const
{
	bool result = _xlsx_writer->saveAs(file_path);
	if (!result)
	{
		throw std::runtime_error{CODE_POS_STR + "另存为 \"" + widget::ToString(file_path) + "\" 失败。"};
	}
}

void widget::XlsxDocument::SaveAsFile(std::string const &file_path) const
{
	SaveAsFile(QString{file_path.c_str()});
}

void widget::XlsxDocument::SaveAsFile(char const *file_path) const
{
	SaveAsFile(QString{file_path});
}
