#pragma once
#include "qcontainerfwd.h"
#include "qimage.h"
#include "xlsxcell.h"
#include <memory>
#include <QCoreApplication>
#include <QDir>
#include <widget/table/ITableDataModel.h>
#include <xlsxdocument.h>
#include <xlsxformat.h>
#include <xlsxworkbook.h>

namespace widget
{
	/**
	 * @brief xlsx 文档。
	 *
	 */
	class XlsxDocument
	{
	private:
		std::shared_ptr<QXlsx::Document> _xlsx_writer;
		std::shared_ptr<QIODevice> _io_device;
		QString _file_path = "temp.xlsx";

	public:
		/**
		 * @brief 打开指定路径的表格。
		 *
		 * @note 如果文件不存在，则会创建。
		 *
		 * @param file_path
		 */
		XlsxDocument(QString const &file_path);

		/**
		 * @brief 绑定一个 IO 设备。将从此 IO 设备读取表格或写入表格。
		 *
		 * @param io_device
		 */
		XlsxDocument(std::shared_ptr<QIODevice> const &io_device);

	public:
		/**
		 * @brief 写入一个单元格。
		 *
		 * @param row
		 * @param column
		 * @param content
		 */
		void Write(int row, int column, QString const &content);

		/**
		 * @brief 写入一个单元格。
		 *
		 * @param row
		 * @param column
		 * @param content
		 */
		void Write(int row, int column, std::string const &content);

		/**
		 * @brief 写入一个单元格。
		 *
		 * @param row
		 * @param column
		 * @param content
		 */
		void Write(int row, int column, char const *content);

		/**
		 * @brief 写入一个单元格。
		 *
		 * @param row
		 * @param column
		 * @param content
		 * @param format
		 */
		void Write(int row, int column, QString const &content, QXlsx::Format const &format);

		/**
		 * @brief 写入一个单元格。
		 *
		 * @param row
		 * @param column
		 * @param content
		 * @param format
		 */
		void Write(int row, int column, std::string const &content, QXlsx::Format const &format);

		/**
		 * @brief 写入一个单元格。
		 *
		 * @param row
		 * @param column
		 * @param content
		 * @param format
		 */
		void Write(int row, int column, char const *content, QXlsx::Format const &format);

		/**
		 * @brief 写入一个表格数据模型。
		 *
		 * @param model
		 */
		void Write(widget::ITableDataModel const &model);

		/**
		 * @brief 写入一个表格数据模型。
		 *
		 * @param model
		 * @param format
		 */
		void Write(widget::ITableDataModel const &model, QXlsx::Format const &format);

		/**
		 * @brief 写入一个表格数据模型。
		 *
		 * @param model
		 * @param column_title_format
		 * @param row_title_format
		 * @param data_format
		 */
		void Write(widget::ITableDataModel const &model,
				   QXlsx::Format const &column_title_format,
				   QXlsx::Format const &row_title_format,
				   QXlsx::Format const &data_format);

	public:
		/**
		 * @brief 加载 xlsx 文件。
		 *
		 */
		void Load() const;

		/**
		 * @brief 获取指定位置的单元格。
		 *
		 * @param row
		 * @param column
		 * @return std::shared_ptr<QXlsx::Cell>
		 */
		std::shared_ptr<QXlsx::Cell> GetCellAt(int row, int column) const;

		/**
		 * @brief 将指定单元格的内容作为字符串读出来。
		 *
		 * @param row
		 * @param column
		 * @return QString
		 */
		QString ReadCellAsString(int row, int column) const;

		/**
		 * @brief 将指定单元格的内容作为字符串读出来。
		 *
		 * @param row
		 * @param column
		 * @return std::string
		 */
		std::string ReadCellAsStdString(int row, int column) const;

	public:
		/**
		 * @brief 获取当前工作表。
		 *
		 * @return QXlsx::Worksheet*
		 */
		QXlsx::Worksheet *CurrentWorksheet() const;

	public:
		/**
		 * @brief 保存文件。
		 *
		 */
		void Save() const;
	};
} // namespace widget
