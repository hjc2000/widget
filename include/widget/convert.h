#pragma once
#include "qcontainerfwd.h"
#include <string>

namespace base
{
	///
	/// @brief 将 QString 转换为 std::string.
	///
	/// @param qstr
	/// @return
	///
	inline std::string to_string(QString const &qstr)
	{
		// 使用 toUtf8() 将 QString 转换为 QByteArray
		QByteArray utf8Bytes = qstr.toUtf8();

		// 将 QByteArray 转换为 std::string
		return std::string{utf8Bytes.constData(), static_cast<size_t>(utf8Bytes.size())};
	}

} // namespace base

namespace widget
{
	///
	/// @brief 将 std::string 转换为 QString.
	///
	/// @param str
	/// @return
	///
	inline QString ToQString(std::string const &str)
	{
		return QString{str.c_str()};
	}

	inline QString ToQString(char const *str)
	{
		return QString{str};
	}

} // namespace widget
