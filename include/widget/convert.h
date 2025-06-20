#pragma once
#include "qcontainerfwd.h"
#include "qnamespace.h"
#include "widget/line-input-widget/CheckState.h"
#include <string>

namespace base
{
	///
	/// @brief 将 QString 转换为 std::string.
	///
	/// @param qstr
	/// @return std::string
	///
	std::string to_string(QString const &qstr);

} // namespace base

namespace widget
{
	///
	/// @brief 将 std::string 转换为 QString.
	///
	/// @param str
	/// @return QString
	///
	QString ToQString(std::string const &str);

	QString ToQString(char const *str);

	///
	/// @brief 将 Qt::CheckState 转换为 widget::CheckState.
	///
	/// @param q_check_state
	/// @return widget::CheckState
	///
	widget::CheckState ToCheckState(Qt::CheckState const q_check_state);

	///
	/// @brief 将 widget::CheckState 转换为 Qt::CheckState.
	///
	/// @param check_state
	/// @return Qt::CheckState
	///
	Qt::CheckState ToQtCheckState(widget::CheckState const &check_state);

} // namespace widget
