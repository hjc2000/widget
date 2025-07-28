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

	///
	/// @brief 将 Qt::CheckState 转换为 widget::CheckState.
	///
	/// @param q_check_state
	///
	/// @return
	///
	inline widget::CheckState ToCheckState(Qt::CheckState const q_check_state)
	{
		switch (q_check_state)
		{
		case Qt::CheckState::Checked:
			{
				return widget::CheckState::Checked;
			}
		case Qt::CheckState::PartiallyChecked:
			{
				return widget::CheckState::PartiallyChecked;
			}
		default:
		case Qt::CheckState::Unchecked:
			{
				return widget::CheckState::Unchecked;
			}
		}
	}

	///
	/// @brief 将 widget::CheckState 转换为 Qt::CheckState.
	///
	/// @param check_state
	///
	/// @return
	///
	inline Qt::CheckState ToQtCheckState(widget::CheckState const &check_state)
	{
		switch (check_state)
		{
		case widget::CheckState::Checked:
			{
				return Qt::CheckState::Checked;
			}
		case widget::CheckState::PartiallyChecked:
			{
				return Qt::CheckState::PartiallyChecked;
			}
		default:
		case widget::CheckState::Unchecked:
			{
				return Qt::CheckState::Unchecked;
			}
		}
	}

} // namespace widget
