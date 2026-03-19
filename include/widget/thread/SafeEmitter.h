#pragma once
#include "base/delegate/Delegate.h"
#include "base/delegate/IEvent.h"
#include "base/IDisposable.h"
#include "base/string/define.h"
#include "qobject.h"
#include <atomic>
#include <exception>
#include <iostream>

namespace widget
{
	///
	/// @brief 安全发射器，可以在后台线程安全地向 UI 线程发射事件。
	///
	class SafeEmitter final :
		private QObject,
		public base::IDisposable
	{
	private:
		base::Delegate<> _callback;
		std::atomic_bool _disposed = false;

	public:
		SafeEmitter() = default;

		///
		/// @brief 析构时会自动 Dispose.
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
		/// @warning 本方法只能在本对象所在的线程调用。
		///
		virtual void Dispose() override
		{
			if (_disposed)
			{
				return;
			}

			_disposed = true;

			///
			/// @brief 清理消息队列中已经有的信号，避免本对象析构后仍然触发回调访问本对象。
			///
			/// @param receiver 这里传入了 this, 即本对象是接收者。QCoreApplication::removePostedEvents
			/// 收到 this 后，会遍历 this 所在线程的消息队列，删除发送给 this 的所有消息。注意，接收者
			/// 不是 this 的消息会被保留。
			///
			QCoreApplication::removePostedEvents(this, QEvent::MetaCall);

			_callback.Dispose();
		}

		///
		/// @brief 在后台线程中安全地发射信号到前台。
		///
		void Emit()
		{
			if (_disposed)
			{
				throw base::ObjectDisposedException{CODE_POS_STR + "对象已经释放，禁止发射信号。"};
			}

			///
			/// @brief
			///
			/// @param object this 是一个 QObject, 具有线程亲和性。在此参数中传入 this,
			/// 则 QMetaObject::invokeMethod 会将 lambda 表达式发送给 this
			/// 对象所在的线程的消息循环中执行。因此，后台线程调用 SafeEmitter::Emit 时，
			/// 就实现了将任务放到指定线程的消息循环中排队执行的目标。
			///
			/// @param function 这里传入了 lambda 表达式。此 lambda 表达式会被送给 this
			/// 所在的线程的消息循环中，等排队排到了之后就会被 this 所在的线程调用。
			/// 即 SafeEmitter::Emit 的作用是发一个任务出去，叫别的线程帮忙执行，自己不亲自执行。
			///
			/// @param type 发送的信号类型。或者说发送的任务加入 this 所在线程的消息循环的方式。
			/// Qt::QueuedConnection 表示在互斥锁的保护下将 lambda 表达式任务塞入它的队列中，
			/// 后台线程要用这种方式向它发送任务才是安全的。
			///
			QMetaObject::invokeMethod(
				this,
				[this]()
				{
					if (_disposed)
					{
						return;
					}

					try
					{
						_callback.Invoke();
					}
					catch (std::exception const &e)
					{
						std::cerr << CODE_POS_STR << e.what() << std::endl;
					}
					catch (...)
					{
						std::cerr << CODE_POS_STR << "未知的异常。" << std::endl;
					}
				},
				Qt::QueuedConnection);
		}

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
