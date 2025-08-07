#pragma once

namespace widget
{
	///
	/// @brief 表格的当前选中项发生改变的事件参数。
	///
	///
	class CurrentChangeEventArgs
	{
	private:
		QModelIndex _current;
		QModelIndex _previous;

	public:
		///
		/// @brief
		///
		/// @param current 当前的 “当前选中项”。
		/// @param previous 上一次的 “当前选中项”。
		///
		CurrentChangeEventArgs(QModelIndex const &current, QModelIndex const &previous)
		{
			_current = current;
			_previous = previous;
		}

		QModelIndex Current() const
		{
			return _current;
		}

		QModelIndex Previous() const
		{
			return _previous;
		}
	};

} // namespace widget
