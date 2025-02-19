#pragma once
#include <base/delegate/Delegate.h>
#include <QDateTimeEdit>
#include <QMainWindow>
#include <QVBoxLayout>
#include <widget/DateTimeRangeSubmit.h>
#include <widget/RangeSubmit.h>
#include <widget/Submit.h>
#include <widget/Table.h>

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
		QVBoxLayout _layout{&_central_widget};

		widget::RangeSubmit _button{};

	public:
		/**
		 * @brief Construct a new Main Window object
		 *
		 */
		MainWindow();
	};
} // namespace widget
