#pragma once
#include <base/delegate/Delegate.h>
#include <base/delegate/IEvent.h>
#include <base/time/TimePointSinceEpoch.h>
#include <QDateTimeEdit>
#include <QHBoxLayout>
#include <QLabel>
#include <widget/Button.h>

namespace widget
{
	/**
	 * @brief 日期时间范围提交控件。
	 *
	 */
	class DateTimeRangeSubmit :
		public QWidget
	{
	private:
		QHBoxLayout _layout{this};
		QDateTimeEdit _left_edit{};
		QDateTimeEdit _right_edit{};

		/**
		 * @brief 两个日期输入框之间的短横线。
		 *
		 */
		QLabel _label{"-"};

		/**
		 * @brief 提交按钮。点击后触发事件。
		 *
		 */
		widget::Button _button{"提交"};

		base::Delegate<> _submit_event;

	public:
		/**
		 * @brief Construct a new Date Time Range Submit object
		 *
		 */
		DateTimeRangeSubmit();

		/**
		 * @brief 提交事件。提交按钮被点击后触发。此时可以读取日期范围。
		 *
		 * @return base::IEvent<>&
		 */
		base::IEvent<> &SubmitEvent();

		/**
		 * @brief 左侧日期时间输入框的时间点。
		 *
		 * @return base::TimePointSinceEpoch
		 */
		base::TimePointSinceEpoch LeftTimePoint() const;

		/**
		 * @brief 右侧日期时间输入框的时间点。
		 *
		 * @return base::TimePointSinceEpoch
		 */
		base::TimePointSinceEpoch RightTimePoint() const;
	};
} // namespace widget
