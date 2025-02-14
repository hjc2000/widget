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

/// @brief 将 QString 转换为 utf8 的 std::string.
/// @param out
/// @param in
/// @return
std::string &operator<<(std::string &out, QString const &in);

/// @brief 将 utf8 的 std::string 转为 QString.
/// @param out
/// @param in
/// @return
QString &operator<<(QString &out, std::string const &in);
