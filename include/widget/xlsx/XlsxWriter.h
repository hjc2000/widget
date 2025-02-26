#pragma once
#include "qobject.h"
#include "xlsxformat.h"
#include <memory>
#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QtCore>
#include <QtGlobal>
#include <QVariant>
#include <xlsxdocument.h>
#include <xlsxworkbook.h>

namespace widget
{
	class XlsxWriter
	{
	private:
		std::shared_ptr<QXlsx::Document> _xlsx_writer{new QXlsx::Document{}};

	public:
		void Write(int row, int column, QString const &content);

		void Write(int row, int column, std::string const &content);

		void Write(int row, int column, QString const &content, QXlsx::Format const &format);

		void Write(int row, int column, std::string const &content, QXlsx::Format const &format);
	};
} // namespace widget
