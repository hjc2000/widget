#pragma once
#include "qnamespace.h"
#include <type_traits>

namespace widget
{
	///
	/// @brief 选择框的选择状态。
	///
	///
	enum class CheckState
	{
		///
		/// @brief 未选中
		///
		///
		Unchecked,

		///
		/// @brief 部分选中
		///
		///
		PartiallyChecked,

		///
		/// @brief 全部选中
		///
		///
		Checked,
	};

	///
	/// @brief 将 Qt::CheckState 转换为 widget::CheckState.
	///
	/// @param q_check_state
	///
	/// @return
	///
	template <typename T>
		requires(std::is_same_v<T, widget::CheckState>)
	constexpr T Convert(Qt::CheckState value)
	{
		switch (value)
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
	template <typename T>
		requires(std::is_same_v<T, Qt::CheckState>)
	constexpr T Convert(widget::CheckState value)
	{
		switch (value)
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
