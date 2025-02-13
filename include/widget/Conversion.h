#pragma once
#include <QtCore>
#include <string>

namespace widget
{
	/// @brief 将 QString 转换为 utf8 的 std::string.
	/// @param qstr
	/// @return
	std::string ToString(QString const &qstr);
} // namespace widget
