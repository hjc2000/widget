#pragma once
#include "box/FormTableBox.h"
#include "indicator/IndicatorLight.h"
#include "QCheckBox"
#include "QDateTimeEdit"
#include "QMainWindow"
#include "QVBoxLayout"
#include "widget/box/FormTableBoxItem.h"
#include "widget/box/VBox.h"
#include "widget/button/Button.h"
#include "widget/line-input-widget/Input.h"
#include <memory>

namespace widget
{
	///
	/// @brief 主窗口。
	///
	///
	class MainWindow :
		public QMainWindow
	{
	private:
		std::shared_ptr<widget::FormTableBox> _form_table_box{new widget::FormTableBox{
			widget::FormTableBoxItem{
				std::shared_ptr<widget::Button>{new widget::Button{"6"}},
				std::shared_ptr<widget::Input>{new widget::Input{}},
			},
			widget::FormTableBoxItem{
				std::shared_ptr<widget::Button>{new widget::Button{"66666666666666666666"}},
				std::shared_ptr<widget::Input>{new widget::Input{}},
			},
		}};

		std::shared_ptr<widget::Button> _button{new widget::Button{}};
		std::shared_ptr<widget::IndicatorLight> _light{new widget::IndicatorLight{}};

		std::shared_ptr<widget::VBox> _vbox{new widget::VBox{
			_button,
			_light,
			_form_table_box,
		}};

	public:
		MainWindow();
	};
} // namespace widget
