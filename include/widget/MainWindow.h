#pragma once
#include "QCheckBox"
#include "QDateTimeEdit"
#include "QMainWindow"
#include "QVBoxLayout"
#include "widget/box/VBox.h"
#include "widget/button/Button.h"
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
		std::shared_ptr<widget::Button> _button{new widget::Button{}};

		std::shared_ptr<widget::VBox> _vbox{new widget::VBox{
			_button,
		}};

	public:
		MainWindow();
	};
} // namespace widget
