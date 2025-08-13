#pragma once
#include "base/IDisposable.h"
#include "qdatetimeedit.h"
#include "qwidget.h"
#include "widget/layout/HBoxLayout.h"

namespace widget
{
	class DateTimeEdit final :
		public QWidget,
		public base::IDisposable
	{
	private:
		bool _disposed = false;
		widget::HBoxLayout _layout{this};
		std::shared_ptr<QDateTimeEdit> _line_edit{new QDateTimeEdit{}};

	public:
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
		}
	};

} // namespace widget
