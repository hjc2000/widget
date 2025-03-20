#include "XlsxDocumentEditor.h"
#include "qcontainerfwd.h"
#include "widget/Conversion.h"
#include "xlsxdocument.h"

widget::XlsxDocumentEditor::XlsxDocumentEditor(QString const &file_path)
{
	_file_path = file_path;
	_xlsx_writer = std::shared_ptr<QXlsx::Document>{new QXlsx::Document{file_path}};
}

widget::XlsxDocumentEditor::XlsxDocumentEditor(std::shared_ptr<QIODevice> const &io_device)
{
	_io_device = io_device;
	_xlsx_writer = std::shared_ptr<QXlsx::Document>{new QXlsx::Document{io_device.get()}};
}

/* #region Write */

void widget::XlsxDocumentEditor::Write(int row, int column, QString const &content)
{
	Write(row, column, content, QXlsx::Format{});
}

void widget::XlsxDocumentEditor::Write(int row, int column, std::string const &content)
{
	Write(row, column, content, QXlsx::Format{});
}

void widget::XlsxDocumentEditor::Write(int row, int column, char const *content)
{
	Write(row, column, content, QXlsx::Format{});
}

void widget::XlsxDocumentEditor::Write(int row, int column, QString const &content, QXlsx::Format const &format)
{
	QVariant value{content};
	bool result = _xlsx_writer->write(row, column, value, format);
	if (!result)
	{
		throw std::runtime_error{CODE_POS_STR + "写入失败。"};
	}
}

void widget::XlsxDocumentEditor::Write(int row, int column, std::string const &content, QXlsx::Format const &format)
{
	QString qstring{content.c_str()};
	Write(row, column, qstring, format);
}

void widget::XlsxDocumentEditor::Write(int row, int column, char const *content, QXlsx::Format const &format)
{
	Write(row, column, QString{content}, format);
}

void widget::XlsxDocumentEditor::Write(widget::ITableDataModel const &model)
{
	Write(model, QXlsx::Format{});
}

void widget::XlsxDocumentEditor::Write(widget::ITableDataModel const &model, QXlsx::Format const &format)
{
	Write(model, format, format, format);
}

void widget::XlsxDocumentEditor::Write(widget::ITableDataModel const &model,
									   QXlsx::Format const &column_title_format,
									   QXlsx::Format const &row_title_format,
									   QXlsx::Format const &data_format)
{
	int xlsx_column_index_offset = 1;
	if (model.HasRowTitle())
	{
		xlsx_column_index_offset = 2;
	}

	int xlsx_row_index_offset = 1;
	if (model.HasColumnTitle())
	{
		xlsx_row_index_offset = 2;
	}

	if (model.HasColumnTitle())
	{
		// 写入列标题
		for (int i = 0; i < model.ColumnCount(); i++)
		{
			QString title = model.ColumnTitle(i);

			Write(1,
				  i + xlsx_column_index_offset,
				  title,
				  column_title_format);
		}
	}

	if (model.HasRowTitle())
	{
		// 写入行标题
		for (int i = 0; i < model.RowCount(); i++)
		{
			QString title = model.RowTitle(i);

			Write(i + xlsx_row_index_offset,
				  1,
				  title,
				  row_title_format);
		}
	}

	for (int i = 0; i < model.RowCount(); i++)
	{
		for (int j = 0; j < model.ColumnCount(); j++)
		{
			Write(i + xlsx_row_index_offset,
				  j + xlsx_column_index_offset,
				  model.Data(i, j),
				  data_format);
		}
	}
}

/* #endregion */

/* #region 加载、保存文件 */

void widget::XlsxDocumentEditor::Load() const
{
	bool result = _xlsx_writer->load();
	if (!result)
	{
		throw std::runtime_error{CODE_POS_STR + "加载失败。"};
	}
}

void widget::XlsxDocumentEditor::Save() const
{
	if (_io_device == nullptr)
	{
		bool result = _xlsx_writer->saveAs(_file_path);
		if (!result)
		{
			throw std::runtime_error{CODE_POS_STR + "保存失败。"};
		}
	}
	else
	{
		bool result = _xlsx_writer->saveAs(_io_device.get());
		if (!result)
		{
			throw std::runtime_error{CODE_POS_STR + "保存失败。"};
		}
	}
}

/* #endregion */

std::shared_ptr<QXlsx::Cell> widget::XlsxDocumentEditor::GetCellAt(int row, int column) const
{
	return _xlsx_writer->cellAt(row, column);
}

QString widget::XlsxDocumentEditor::ReadCellAsString(int row, int column) const
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

std::string widget::XlsxDocumentEditor::ReadCellAsStdString(int row, int column) const
{
	QString qstring = ReadCellAsString(row, column);
	return widget::ToString(qstring);
}

QXlsx::Worksheet *widget::XlsxDocumentEditor::CurrentWorksheet() const
{
	QXlsx::Worksheet *sheet = _xlsx_writer->currentWorksheet();
	return sheet;
}
