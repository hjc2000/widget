#pragma once
#include "base/math/Interval.h"
#include <base/delegate/Delegate.h>
#include <base/delegate/IEvent.h>
#include <base/time/TimePointSinceEpoch.h>
#include <chrono>
#include <cstdint>
#include <QDateTimeEdit>
#include <QHBoxLayout>
#include <QLabel>
#include <widget/button/Button.h>
#include <widget/layout/HBoxLayout.h>

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
		widget::HBoxLayout _layout{this};
		QDateTimeEdit _left_edit{};
		QDateTimeEdit _right_edit{};

		/**
		 * @brief 两个日期输入框之间的短横线。
		 *
		 */
		QLabel _label{"-"};

	private:
		base::TimePointSinceEpoch _min{std::chrono::nanoseconds{INT64_MIN}};
		base::TimePointSinceEpoch _max{std::chrono::nanoseconds{INT64_MAX}};
		base::Delegate<> _submit_event;

		void ConnectSignal();

	public:
		/**
		 * @brief Construct a new Date Time Range Submit object
		 *
		 */
		DateTimeRangeSubmit();

		/**
		 * @brief Construct a new Date Time Range Submit object
		 *
		 * @param min 允许输入的时间点最小值。
		 * @param max 允许输入的时间点最大值。
		 */
		DateTimeRangeSubmit(base::TimePointSinceEpoch const &min,
							base::TimePointSinceEpoch const &max);

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

		/**
		 * @brief 获取区间。
		 *
		 * @return base::ClosedInterval<base::TimePointSinceEpoch>
		 */
		base::ClosedInterval<base::TimePointSinceEpoch> Interval() const;

	public: // 输入非法
		/**
		 * @brief 设置左边输入框的输入非法样式。
		 *
		 * @param is_invalid 为 true 打开非法样式，为 false 恢复成正常样式。
		 */
		void SetLeftInvalidInputStyle(bool is_invalid);

		/**
		 * @brief 设置右边输入框的输入非法样式。
		 *
		 * @param is_invalid 为 true 打开非法样式，为 false 恢复成正常样式。
		 */
		void SetRightInvalidInputStyle(bool is_invalid);
	};
} // namespace widget
