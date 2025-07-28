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
		FixSizeSpacingBlock(int size)
			: QWidget(nullptr)
		{
			setFixedSize(size, size);
		}

		FixSizeSpacingBlock(int width, int height)
			: QWidget(nullptr)
		{
			setFixedSize(width, height);
		}
	};

} // namespace widget
