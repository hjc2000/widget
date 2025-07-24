#pragma once

namespace widget
{
	///
	/// @brief 内边距。
	///
	///
	class Padding
	{
	private:
		int _left = 0;
		int _top = 0;
		int _right = 0;
		int _bottom = 0;

	public:
		///
		/// @brief 无参构造函数。左上右下 4 个内边距都是 0.
		///
		///
		constexpr Padding() = default;

		///
		/// @brief 左上右下 4 个边距设置为相同的值。
		///
		/// @param value
		///
		constexpr Padding(int value)
			: Padding(value, value, value, value)
		{
		}

		///
		/// @brief 分别设置左上右下 4 个边距。
		///
		/// @param left
		/// @param top
		/// @param right
		/// @param bottom
		///
		constexpr Padding(int left, int top, int right, int bottom)
			: _left(left),
			  _top(top),
			  _right(right),
			  _bottom(bottom)
		{
		}

		constexpr int Left() const
		{
			return _left;
		}

		constexpr int Top() const
		{
			return _top;
		}

		constexpr int Right() const
		{
			return _right;
		}

		constexpr int Bottom() const
		{
			return _bottom;
		}
	};

} // namespace widget
