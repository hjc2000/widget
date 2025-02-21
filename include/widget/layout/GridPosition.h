#pragma once

namespace widget
{
	/**
	 * @brief 表示网格中的位置。
	 *
	 */
	class GridPosition
	{
	private:
		int _row = 0;
		int _column = 0;
		int _row_span = 1;
		int _column_span = 1;

	public:
		GridPosition() = default;

		explicit GridPosition(int row, int column, int row_span, int column_span)
		{
			_row = row;
			_column = column;
			_row_span = row_span;
			_column_span = column_span;
		}

	public:
		int Row() const
		{
			return _row;
		}

		int Column() const
		{
			return _column;
		}

		int RowSpan() const
		{
			return _row_span;
		}

		int ColumnSpan() const
		{
			return _column_span;
		}
	};
} // namespace widget
