#pragma once
#include "base/delegate/Delegate.h"
#include "base/delegate/IEvent.h"
#include "base/IDisposable.h"
#include "qobject.h"
#include "QPushButton"
#include <atomic>

namespace widget
{
	///
	/// @brief 安全发射器，可以在后台线程安全地向 UI 线程发射事件。
	///
	///
	class SafeEmitter final :
		private QObject,
		public base::IDisposable
	{
	private:
		base::Delegate<> _callback;
		std::atomic_bool _disposed = false;

	public:
		///
		/// @brief 析构时会自动 Dispose.
		///
		///
		~SafeEmitter()
		{
			Dispose();
		}

		///
		/// @brief 释放后会断开信号连接，防止新的信号调用槽函数，然后清理事件队列中已经排队
		/// 的信号，从而保证本函数调用后，不会再发生回调。
		///
		/// 此外，还会释放 CallbackEvent, 清理其中订阅的所有委托。
		///
		virtual void Dispose() override
		{
			if (_disposed)
			{
				return;
			}

			_disposed = true;

			// 清理消息队列中已经有的信号，避免本对象析构后仍然触发回调访问本对象。
			QCoreApplication::removePostedEvents(this, QEvent::MetaCall);

			_callback.Dispose();
		}

		///
		/// @brief 在后台线程中安全地发射信号到前台。
		///
		///
		void Emit();

		///
		/// @brief 后台线程发射了信号就会触发此回调事件。
		///
		/// @return
		///
		base::IEvent<> &CallbackEvent()
		{
			return _callback;
		}
	};

} // namespace widget
