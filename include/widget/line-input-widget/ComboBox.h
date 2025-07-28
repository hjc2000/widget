#pragma once
#include "qcombobox.h"
#include "qwidget.h"
#include "widget/layout/VBoxLayout.h"

namespace widget
{
	class ComboBox :
		public QWidget
	{
	private:
		widget::VBoxLayout _layout{this};
		QComboBox _combo_box{};

	public:
		ComboBox()
		{
			_layout.AddWidget(&_combo_box);
		}
	};

} // namespace widget
