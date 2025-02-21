#pragma once
#include "layout/Padding.h"
#include "qcheckbox.h"
#include <base/delegate/Delegate.h>
#include <QCheckBox >
#include <QDateTimeEdit>
#include <QMainWindow>
#include <QVBoxLayout>
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
		/// @brief 主窗口中心区域控件。
		QWidget _central_widget{};

		/// @brief 布局控件。
		widget::GridLayout _layout{&_central_widget};

		widget::RangeSubmit _range_submit{};
		QCheckBox _check_box{"选择框"};

	public:
		/**
		 * @brief Construct a new Main Window object
		 *
		 */
		MainWindow();
	};
} // namespace widget
