#pragma once

namespace widget
{
	///
	/// @brief 表示网格中的位置。
	///
	///
	class GridPosition
	{
	private:
		int _row = 0;
		int _column = 0;
		int _row_span = 1;
		int _column_span = 1;

	public:
		GridPosition() = default;

		explicit GridPosition(int row, int column, int row_span, int column_span);

		int Row() const;

		int Column() const;

		int RowSpan() const;

		int ColumnSpan() const;
	};
} // namespace widget
