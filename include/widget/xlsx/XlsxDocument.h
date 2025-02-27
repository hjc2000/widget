#pragma once
#include "qcontainerfwd.h"
#include "xlsxcell.h"
#include <memory>
#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <qobject.h>
#include <QtCore>
#include <QtGlobal>
#include <QVariant>
#include <string>
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

	public:
		/**
		 * @brief 无参构造函数，创建一个临时表格。
		 *
		 */
		XlsxDocument();

		/**
		 * @brief 打开指定路径的表格。
		 *
		 * @note 如果文件不存在，则会创建。
		 *
		 * @param file_path
		 */
		XlsxDocument(QString const &file_path);

	public:
		void Write(int row, int column, QString const &content);

		void Write(int row, int column, std::string const &content);

		void Write(int row, int column, char const *content);

		void Write(int row, int column, QString const &content, QXlsx::Format const &format);

		void Write(int row, int column, std::string const &content, QXlsx::Format const &format);

		void Write(int row, int column, char const *content, QXlsx::Format const &format);

		void Write(widget::ITableDataModel const &model, QXlsx::Format const &format);

	public:
		void Load() const;

		std::shared_ptr<QXlsx::Cell> GetCellAt(int row, int column) const;

		QString ReadCellAsString(int row, int column) const;

		std::string ReadCellAsStdString(int row, int column) const;

	public:
		QXlsx::Worksheet *CurrentWorksheet() const;

	public:
		void Save() const;

		void SaveAsFile(QString const &file_path) const;

		void SaveAsFile(std::string const &file_path) const;

		void SaveAsFile(char const *file_path) const;
	};
} // namespace widget
