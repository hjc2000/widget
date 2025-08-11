#pragma once
#include "base/delegate/Delegate.h"
#include "base/delegate/IEvent.h"
#include "base/IDisposable.h"
#include "base/string/define.h"
#include "QCheckBox"
#include "qcoreapplication.h"
#include "QWidget"
#include "widget/layout/HBoxLayout.h"
#include "widget/line-input-widget/CheckState.h"
#include <iostream>
#include <vector>

namespace widget
{
	///
	/// @brief 选择框。
	///
	///
	class CheckBox final :
		public QWidget,
		public base::IDisposable
	{
	private:
		bool _disposed = false;
		std::shared_ptr<QCheckBox> _check_box;
		widget::HBoxLayout _layout{this};

		base::Delegate<> _check_state_changed_event;

		std::vector<QMetaObject::Connection> _connections;

		void ConnectSignals()
		{
			QMetaObject::Connection connection;

			connection = connect(_check_box.get(),
								 &QCheckBox::checkStateChanged,
								 [this](Qt::CheckState q_check_state)
								 {
									 try
									 {
										 _check_state_changed_event.Invoke();
									 }
									 catch (std::exception const &e)
									 {
										 std::cerr << CODE_POS_STR + e.what() << std::endl;
									 }
									 catch (...)
									 {
										 std::cerr << CODE_POS_STR + "发生了未知异常。" << std::endl;
									 }
								 });

			_connections.push_back(connection);
		}

	public:
		CheckBox()
		{
			_check_box = std::shared_ptr<QCheckBox>{new QCheckBox{}};
			_layout.AddWidget(_check_box.get());

			ConnectSignals();
		}

		CheckBox(std::string const &text)
		{
			_check_box = std::shared_ptr<QCheckBox>{new QCheckBox{
				text.c_str(),
				nullptr,
			}};

			_layout.AddWidget(_check_box.get());

			ConnectSignals();
		}

		~CheckBox()
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

			_check_state_changed_event.Dispose();

			for (QMetaObject::Connection &connection : _connections)
			{
				disconnect(connection);
			}

			QCoreApplication::removePostedEvents(this);
		}

		///
		/// @brief 选择状态。
		///
		/// @return
		///
		widget::CheckState CheckState() const
		{
			return widget::Convert<widget::CheckState>(_check_box->checkState());
		}

		///
		/// @brief 设置选择状态。
		///
		/// @param value
		///
		void SetCheckState(widget::CheckState value)
		{
			_check_box->setCheckState(widget::Convert<Qt::CheckState>(value));
		}

		///
		/// @brief 选择状态改变事件。
		///
		/// @return
		///
		base::IEvent<> &CheckStateChangedEvent()
		{
			return _check_state_changed_event;
		}
	};

} // namespace widget
