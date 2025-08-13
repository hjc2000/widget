#pragma once
#include "base/delegate/Delegate.h"
#include "base/IDisposable.h"
#include "base/time/TimePointSinceEpoch.h"
#include "qdatetimeedit.h"
#include "qwidget.h"
#include "widget/layout/HBoxLayout.h"
#include <vector>

namespace widget
{
	class DateTimeEdit final :
		public QWidget,
		public base::IDisposable
	{
	private:
		bool _disposed = false;
		widget::HBoxLayout _layout{this};
		std::shared_ptr<QDateTimeEdit> _edit{new QDateTimeEdit{}};

		base::Delegate<> _submit_event;
		std::vector<QMetaObject::Connection> _connections;

		void ConnectSignal();

	public:
		DateTimeEdit();

		~DateTimeEdit()
		{
			Dispose();
		}

		///
		/// @brief 处置对象，让对象准备好结束生命周期。类似于进入 “准备后事” 的状态。
		///
		/// @note 注意，对象并不是析构了，并不是完全无法访问，它仍然允许访问，仍然能执行一些
		/// 符合 “准备后事” 的工作。
		///
		virtual void Dispose() override;

		///
		/// @brief 提交事件。
		///
		/// @return
		///
		base::IEvent<> &SubmitEvent()
		{
			return _submit_event;
		}

		///
		/// @brief 日期时间输入框的时间点。
		///
		/// @return
		///
		base::TimePointSinceEpoch TimePoint() const
		{
			QDateTime selectedDateTime = _edit->dateTime();
			return base::TimePointSinceEpoch{std::chrono::seconds{selectedDateTime.toSecsSinceEpoch()}};
		}

		///
		/// @brief 设置输入框的输入非法样式。
		///
		/// @param is_invalid 为 true 打开非法样式，为 false 恢复成正常样式。
		///
		void SetInvalidInputStyle(bool is_invalid);
	};

} // namespace widget
