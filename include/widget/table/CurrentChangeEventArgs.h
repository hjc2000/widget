#pragma once

namespace widget
{
	class CurrentChangeEventArgs
	{
	private:
		QModelIndex _current;
		QModelIndex _previous;

	public:
		CurrentChangeEventArgs(QModelIndex const &current,
							   QModelIndex const &previous)
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
