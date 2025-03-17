#pragma once
#include "box/VBox.h"
#include <base/delegate/Delegate.h>
#include <QCheckBox >
#include <QDateTimeEdit>
#include <QMainWindow>
#include <QVBoxLayout>
#include <widget/box/HBox.h>
#include <widget/box/VBox.h>
#include <widget/layout/FormTableLayout.h>
#include <widget/layout/GridLayout.h>
#include <widget/layout/VBoxLayout.h>
#include <widget/line-input-widget/CheckBox.h>
#include <widget/line-input-widget/DateTimeRangeSubmit.h>
#include <widget/line-input-widget/RangeSubmit.h>
#include <widget/line-input-widget/Submit.h>
#include <widget/pch.h>

namespace widget
{
	/**
	 * @brief 主窗口。
	 *
	 */
	class MainWindow :
		public QMainWindow
	{
	private:
		std::shared_ptr<widget::CheckBox> _check_box{new widget::CheckBox{"选择"}};

		std::shared_ptr<widget::VBox> _vbox{new widget::VBox{
			_check_box,
		}};

	public:
		/**
		 * @brief Construct a new Main Window object
		 *
		 */
		MainWindow();
	};
} // namespace widget
