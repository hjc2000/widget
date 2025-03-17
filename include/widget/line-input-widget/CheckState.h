#pragma once
#include <widget/pch.h>

namespace widget
{
	/**
	 * @brief 选择框的选择状态。
	 *
	 */
	enum class CheckState
	{
		/**
		 * @brief 未选中
		 *
		 */
		Unchecked,

		/**
		 * @brief 部分选中
		 *
		 */
		PartiallyChecked,

		/**
		 * @brief 全部选中
		 *
		 */
		Checked,
	};
} // namespace widget
