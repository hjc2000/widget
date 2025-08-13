#pragma once
#include "base/delegate/Delegate.h"
#include "base/delegate/IEvent.h"
#include "base/IDisposable.h"
#include "base/math/interval/ClosedInterval.h"
#include "base/time/TimePointSinceEpoch.h"
#include "qcoreapplication.h"
#include "QDateTimeEdit"
#include "QHBoxLayout"
#include "QLabel"
#include "qwindowdefs.h"
#include "widget/layout/HBoxLayout.h"
#include <memory>
#include <vector>

namespace widget
{
	///
	/// @brief 日期时间范围提交控件。
	///
	///
	class DateTimeRangeSubmit final :
		public QWidget,
		public base::IDisposable
	{
	private:
		bool _disposed = false;
		widget::HBoxLayout _layout{this};
		std::shared_ptr<QDateTimeEdit> _left_edit{new QDateTimeEdit{}};
		std::shared_ptr<QDateTimeEdit> _right_edit{new QDateTimeEdit{}};

		///
		/// @brief 两个日期输入框之间的短横线。
		///
		///
		std::shared_ptr<QLabel> _label{new QLabel{"-"}};

		base::TimePointSinceEpoch _min{std::chrono::nanoseconds{INT64_MIN}};
		base::TimePointSinceEpoch _max{std::chrono::nanoseconds{INT64_MAX}};

		base::Delegate<> _submit_event;

		std::vector<QMetaObject::Connection> _connections;

		void ConnectSignal();

		void OnLeftDateTimeChanged();

		void OnRightDateTimeChanged();

	public:
		DateTimeRangeSubmit();

		///
		/// @brief
		///
		/// @param min 允许输入的时间点最小值。
		/// @param max 允许输入的时间点最大值。
		///
		DateTimeRangeSubmit(base::TimePointSinceEpoch const &min,
							base::TimePointSinceEpoch const &max)
			: widget::DateTimeRangeSubmit()
		{
			_min = min;
			_max = max;
		}

		~DateTimeRangeSubmit()
		{
			Dispose();
		}

		///
		/// @brief 处置对象，让对象准备好结束生命周期。类似于进入 “准备后事” 的状态。
		///
		/// @note 注意，对象并不是析构了，并不是完全无法访问，它仍然允许访问，仍然能执行一些
		/// 符合 “准备后事” 的工作。
		///
		virtual void Dispose() override
		{
			if (_disposed)
			{
				return;
			}

			_disposed = true;

			_submit_event.Dispose();

			for (QMetaObject::Connection &connection : _connections)
			{
				disconnect(connection);
			}

			QCoreApplication::removePostedEvents(this);
		}

		///
		/// @brief 提交事件。
		///
		/// @note 提交后可以读取日期范围。
		///
		/// @return
		///
		base::IEvent<> &SubmitEvent()
		{
			return _submit_event;
		}

		/* #region 日期时间数据 */

		///
		/// @brief 左侧日期时间输入框的时间点。
		///
		/// @return
		///
		base::TimePointSinceEpoch LeftTimePoint() const
		{
			QDateTime selectedDateTime = _left_edit->dateTime();
			return base::TimePointSinceEpoch{std::chrono::seconds{selectedDateTime.toSecsSinceEpoch()}};
		}

		///
		/// @brief 右侧日期时间输入框的时间点。
		///
		/// @return
		///
		base::TimePointSinceEpoch RightTimePoint() const
		{
			QDateTime selectedDateTime = _right_edit->dateTime();
			return base::TimePointSinceEpoch{std::chrono::seconds{selectedDateTime.toSecsSinceEpoch()}};
		}

		///
		/// @brief 获取区间。
		///
		/// @return
		///
		base::ClosedInterval<base::TimePointSinceEpoch> Interval() const
		{
			return base::ClosedInterval<base::TimePointSinceEpoch>{LeftTimePoint(), RightTimePoint()};
		}

		/* #endregion */

		/* #region 输入非法样式 */

		///
		/// @brief 设置左边输入框的输入非法样式。
		///
		/// @param is_invalid 为 true 打开非法样式，为 false 恢复成正常样式。
		///
		void SetLeftInvalidInputStyle(bool is_invalid)
		{
			if (is_invalid)
			{
				_left_edit->setStyleSheet("border: 2px solid red;");
			}
			else
			{
				// 恢复默认样式
				_left_edit->setStyleSheet("");
			}
		}

		///
		/// @brief 设置右边输入框的输入非法样式。
		///
		/// @param is_invalid 为 true 打开非法样式，为 false 恢复成正常样式。
		///
		void SetRightInvalidInputStyle(bool is_invalid)
		{
			if (is_invalid)
			{
				_right_edit->setStyleSheet("border: 2px solid red;");
			}
			else
			{
				// 恢复默认样式
				_right_edit->setStyleSheet("");
			}
		}

		/* #endregion */
	};

} // namespace widget
