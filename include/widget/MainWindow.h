#pragma once
#include "box/FormTableBox.h"
#include "QCheckBox"
#include "QDateTimeEdit"
#include "QMainWindow"
#include "QVBoxLayout"
#include "widget/box/FormTableBoxItem.h"
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
		std::shared_ptr<widget::FormTableBox> _box{new widget::FormTableBox{
			widget::FormTableBoxItem{
				std::shared_ptr<widget::Button>{new widget::Button{"6"}},
				std::shared_ptr<widget::Input>{new widget::Input{}},
			},
			widget::FormTableBoxItem{
				std::shared_ptr<widget::Button>{new widget::Button{"66666666666666666666"}},
				std::shared_ptr<widget::Input>{new widget::Input{}},
			},
		}};

	public:
		MainWindow();
	};
} // namespace widget
