#pragma once
#include "qwidget.h"
#include <memory>

namespace widget
{
	class LabelValueUnitGridItem
	{
	private:
		std::shared_ptr<QWidget> _label{};
		std::shared_ptr<QWidget> _data{};
		std::shared_ptr<QWidget> _unit{};

	public:
		LabelValueUnitGridItem(std::shared_ptr<QWidget> label,
							   std::shared_ptr<QWidget> data,
							   std::shared_ptr<QWidget> unit);

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
