#pragma once
#include "qwidget.h"

namespace widget
{
	///
	/// @brief 固定大小的空白块。
	///
	///
	class FixSizeSpacingBlock :
		public QWidget
	{
	public:
		///
		/// @brief 构造宽高相等的空白块。
		///
		/// @param size
		///
		FixSizeSpacingBlock(int size)
			: QWidget(nullptr)
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
			: QWidget(nullptr)
		{
			setFixedSize(width, height);
		}
	};

} // namespace widget
