#pragma once
#include "base/string/define.h"
#include "qwidget.h"
#include <memory>
#include <stdexcept>

namespace widget
{
	///
	/// @brief 含有标签、数据、单位三列的网格项。
	///
	///
	class LabelDataUnitGridItem
	{
	private:
		int _row = 0;
		int _column = 0;
		std::shared_ptr<QWidget> _label{};
		std::shared_ptr<QWidget> _data{};
		std::shared_ptr<QWidget> _unit{};

	public:
		LabelDataUnitGridItem(int row,
							  int column,
							  std::shared_ptr<QWidget> label,
							  std::shared_ptr<QWidget> data,
							  std::shared_ptr<QWidget> unit)
		{
			if (label == nullptr)
			{
				throw std::invalid_argument{CODE_POS_STR + "禁止传入空指针。"};
			}

			if (data == nullptr)
			{
				throw std::invalid_argument{CODE_POS_STR + "禁止传入空指针。"};
			}

			if (unit == nullptr)
			{
				throw std::invalid_argument{CODE_POS_STR + "禁止传入空指针。"};
			}

			_row = row;
			_column = column;
			_label = label;
			_data = data;
			_unit = unit;

			_label->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
			_data->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
			_unit->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
		}

		int Row() const
		{
			return _row;
		}

		int Column() const
		{
			return _column;
		}

		std::shared_ptr<QWidget> Lable() const
		{
			return _label;
		}

		std::shared_ptr<QWidget> Data() const
		{
			return _data;
		}

		std::shared_ptr<QWidget> Unit() const
		{
			return _unit;
		}
	};

} // namespace widget
