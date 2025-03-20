#pragma once
#include "QCheckBox"
#include "QDateTimeEdit"
#include "QMainWindow"
#include "QVBoxLayout"
#include "widget/box/VBox.h"
#include "widget/line-input-widget/CheckBox.h"

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
		std::shared_ptr<widget::CheckBox> _check_box{new widget::CheckBox{"选择"}};

		std::shared_ptr<widget::VBox> _vbox{new widget::VBox{
			_check_box,
		}};

	public:
		MainWindow();
	};
} // namespace widget
