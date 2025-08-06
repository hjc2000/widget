#pragma once
#include "base/math/RowCount.h"
#include "base/math/RowIndex.h"
#include "QString"

namespace widget
{
	class RowRemovedEventArgs
	{
	private:
		base::RowIndex _row_index;
		base::RowCount _row_count;

	public:
		RowRemovedEventArgs(base::RowIndex const &row_index, base::RowCount const &row_count)
		{
			_row_index = row_index;
			_row_count = row_count;
		}

		base::RowIndex RowIndex() const
		{
			return _row_index;
		}

		base::RowCount RowCount() const
		{
			return _row_count;
		}
	};

} // namespace widget
