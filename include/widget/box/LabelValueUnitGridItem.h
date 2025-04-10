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
							   std::shared_ptr<QWidget> unit)
		{
		}
	};
} // namespace widget
