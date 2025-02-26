#pragma once
#include "qcontainerfwd.h"
#include <memory>
#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <qobject.h>
#include <QtCore>
#include <QtGlobal>
#include <QVariant>
#include <string>
#include <xlsxdocument.h>
#include <xlsxformat.h>
#include <xlsxworkbook.h>

namespace widget
{
	/**
	 * @brief xlsx 文件写入器。
	 *
	 */
	class XlsxWriter
	{
	private:
		std::shared_ptr<QXlsx::Document> _xlsx_writer{new QXlsx::Document{}};

	public:
		void Write(int row, int column, QString const &content);

		void Write(int row, int column, std::string const &content);

		void Write(int row, int column, char const *content);

		void Write(int row, int column, QString const &content, QXlsx::Format const &format);

		void Write(int row, int column, std::string const &content, QXlsx::Format const &format);

		void Write(int row, int column, char const *content, QXlsx::Format const &format);

	public:
		void SaveAsFile(QString const &file_name);

		void SaveAsFile(std::string const &file_name);

		void SaveAsFile(char const *file_name);
	};
} // namespace widget
