#pragma once
#include "widget/IndependentQWidget.h"

namespace widget
{
	///
	/// @brief 固定大小的空白块。
	///
	///
	class FixSizeSpacingBlock :
		public widget::IndependentQWidget
	{
	public:
		///
		/// @brief 构造宽高相等的空白块。
		///
		/// @param size
		///
		FixSizeSpacingBlock(int size)
		{
			setFixedSize(size, size);
		}

		///
		/// @brief 构造指定宽高的空白块。
		///
		/// @param width
		/// @param height
		///
		FixSizeSpacingBlock(int width, int height)
		{
			setFixedSize(width, height);
		}
	};

} // namespace widget
