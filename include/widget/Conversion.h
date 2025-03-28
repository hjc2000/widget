#pragma once
#include "qcontainerfwd.h"
#include "qnamespace.h"
#include "widget/line-input-widget/CheckState.h"
#include <string>

namespace std
{
	std::string to_string(QString const &qstr);
} // namespace std

///
/// @brief 将 utf8 的 std::string 转为 QString.
///
/// @param out
/// @param in
/// @return QString&
///
QString &operator<<(QString &out, std::string const &in);

///
/// @brief 将 Qt::CheckState 转换为 widget::CheckState.
///
/// @param out
/// @param in
/// @return widget::CheckState&
///
widget::CheckState &operator<<(widget::CheckState &out, Qt::CheckState const &in);

///
/// @brief 将 widget::CheckState 转换为 Qt::CheckState.
///
/// @param out
/// @param in
/// @return Qt::CheckState&
///
Qt::CheckState &operator<<(Qt::CheckState &out, widget::CheckState const &in);
