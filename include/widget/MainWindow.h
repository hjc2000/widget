#pragma once
#include "box/VBox.h"
#include "qcheckbox.h"
#include "qwindowdefs.h"
#include <base/delegate/Delegate.h>
#include <memory>
#include <QCheckBox >
#include <QDateTimeEdit>
#include <QMainWindow>
#include <QVBoxLayout>
#include <widget/box/VBox.h>
#include <widget/layout/FormTableLayout.h>
#include <widget/layout/GridLayout.h>
#include <widget/layout/VBoxLayout.h>
#include <widget/line-input-widget/DateTimeRangeSubmit.h>
#include <widget/line-input-widget/RangeSubmit.h>
#include <widget/line-input-widget/Submit.h>

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
		std::shared_ptr<widget::RangeSubmit> _range_submit{new widget::RangeSubmit{}};
		std::shared_ptr<QCheckBox> _check_box{new QCheckBox{"选择框"}};

		widget::VBox _box{_range_submit, _check_box};

	public:
		/**
		 * @brief Construct a new Main Window object
		 *
		 */
		MainWindow();
	};
} // namespace widget
