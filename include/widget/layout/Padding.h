#pragma once
#include <widget/pch.h>

namespace widget
{
	/**
	 * @brief 内边距。
	 *
	 */
	class Padding
	{
	private:
		int _left = 0;
		int _top = 0;
		int _right = 0;
		int _bottom = 0;

	public:
		/**
		 * @brief 无参构造函数。左上右下 4 个内边距都是 0.
		 *
		 */
		Padding() = default;

		/**
		 * @brief 左上右下 4 个边距设置为相同的值。
		 *
		 * @param value
		 */
		Padding(int value);

		/**
		 * @brief 分别设置左上右下 4 个边距。
		 *
		 * @param left
		 * @param top
		 * @param right
		 * @param bottom
		 */
		Padding(int left, int top, int right, int bottom);

		int Left() const;
		int Top() const;
		int Right() const;
		int Bottom() const;
	};
} // namespace widget
