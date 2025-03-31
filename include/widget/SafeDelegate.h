#pragma once
#include "base/container/SafeQueue.h"
#include "base/delegate/Delegate.h"
#include "base/delegate/IEvent.h"
#include "base/IDisposable.h"
#include "base/IIdToken.h"
#include "base/string/define.h"
#include "QPushButton"
#include "qpushbutton.h"
#include <atomic>
#include <functional>
#include <stdexcept>

namespace widget
{
	///
	/// @brief 安全发射器，可以在后台线程安全地向 UI 线程发射事件。
	///
	///
	class SafeEmitter final :
		private QPushButton,
		public base::IDisposable
	{
	private:
		base::Delegate<> _callback;
		QMetaObject::Connection _connection;
		std::atomic_bool _disposed = false;

	public:
		///
		/// @brief 构造一个安全发射器。
		///
		///
		SafeEmitter();

		///
		/// @brief 析构时会自动 Dispose.
		///
		///
		~SafeEmitter();

		///
		/// @brief 释放后会断开信号连接，防止新的信号调用槽函数，然后清理事件队列中已经排队
		/// 的信号，从而保证本函数调用后，不会再发生回调。
		///
		/// 此外，还会释放 CallbackEvent, 清理其中订阅的所有委托。
		///
		virtual void Dispose() override;

		///
		/// @brief 在后台线程中安全地发射信号到前台。
		///
		///
		void Emit();

		///
		/// @brief 后台线程发射了信号就会触发此回调事件。
		///
		/// @return base::IEvent<>&
		///
		base::IEvent<> &CallbackEvent();
	};

	///
	/// @brief 安全委托。
	///
	///
	template <typename... Args>
	class SafeDelegate :
		public base::IEvent<Args...>,
		public base::IDisposable
	{
	private:
		std::atomic_bool _disposed = false;
		base::Delegate<Args...> _delegate;
		base::SafeQueue<std::function<void()>> _capture_func_queue;
		widget::SafeEmitter _safe_emiter;

	public:
		SafeDelegate()
		{
			_safe_emiter.CallbackEvent() += [this]()
			{
				std::function<void()> capture_func;
				bool dequeue_result = _capture_func_queue.TryDequeue(capture_func);
				if (dequeue_result && capture_func)
				{
					capture_func();
				}
			};
		}

		~SafeDelegate()
		{
			Dispose();
		}

		///
		/// @brief 主动释放对象，让对象不再能够工作。
		///
		///
		virtual void Dispose() override
		{
			if (_disposed)
			{
				return;
			}

			_disposed = true;

			_safe_emiter.Dispose();
			_delegate.Dispose();
			_capture_func_queue.Clear();
		}

		///
		/// @brief 订阅事件。
		///
		/// @param func
		/// @return std::shared_ptr<typename base::IIdToken> 用来取消订阅的 token.
		///
		virtual base::SpIIdToken Subscribe(std::function<void(Args...)> const &func) override
		{
			try
			{
				return _delegate.Subscribe(func);
			}
			catch (std::exception const &e)
			{
				throw std::runtime_error{CODE_POS_STR + e.what()};
			}
			catch (...)
			{
				throw std::runtime_error{CODE_POS_STR + "未知的异常。"};
			}
		}

		///
		/// @brief 取消订阅事件。
		///
		/// @param token 传入由 Subscribe 方法返回的 token.
		///
		virtual void Unsubscribe(base::SpIIdToken const &token) override
		{
			try
			{
				_delegate.Unsubscribe(token);
			}
			catch (std::exception const &e)
			{
				throw std::runtime_error{CODE_POS_STR + e.what()};
			}
			catch (...)
			{
				throw std::runtime_error{CODE_POS_STR + "未知的异常。"};
			}
		}

		///
		/// @brief 调用所有订阅的函数。
		///
		/// @note 可以在后台线程中安全地调用，调用后委托将交给 UI 线程执行。
		/// 本函数会立刻返回，不会执行委托。
		///
		/// @param ...args
		///
		void InvokeAsync(Args... args)
		{
			if (_disposed)
			{
				throw base::ObjectDisposedException{CODE_POS_STR + "释放后无法调用。"};
			}

			try
			{
				// 将参数按值捕获，在 lambda 里面调用委托。
				// 将 lmabda 交给 std::function 后将 std::function 入队，在后台线程发射信号后
				// qt 就会将该信号加入 UI 线程的消息队列中排队。排到了之后从队列中取出 std::function
				// 执行。
				std::function<void()> capture_func = [this, ... args = std::forward<Args>(args)]()
				{
					_delegate.Invoke(args...);
				};

				_capture_func_queue.Enqueue(capture_func);
				_safe_emiter.Emit();
			}
			catch (std::exception const &e)
			{
				throw std::runtime_error{CODE_POS_STR + e.what()};
			}
			catch (...)
			{
				throw std::runtime_error{CODE_POS_STR + "未知的异常。"};
			}
		}

		///
		/// @brief 伪函数
		/// @param ...args
		///
		void operator()(Args... args)
		{
			InvokeAsync(args...);
		}
	};
} // namespace widget
