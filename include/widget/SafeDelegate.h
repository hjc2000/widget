#pragma once
#include "base/container/SafeQueue.h"
#include "base/delegate/Delegate.h"
#include "base/delegate/IEvent.h"
#include "base/IIdToken.h"
#include "QPushButton"
#include "qpushbutton.h"
#include <functional>

namespace widget
{
	///
	/// @brief 安全发射器，可以在后台线程安全地向 UI 线程发射事件。
	///
	///
	class SafeEmitter :
		QPushButton
	{
	private:
		base::Delegate<> _callback;
		QMetaObject::Connection _connection;

	public:
		///
		/// @brief 构造一个安全发射器。
		///
		///
		SafeEmitter();

		~SafeEmitter();

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
		public base::IEvent<Args...>
	{
	private:
		base::Delegate<Args...> _delegate;
		base::SafeQueue<std::function<void()>> _capture_func_queue;
		widget::SafeEmitter _safe_emiter;
		base::SpIIdToken _token;

	public:
		SafeDelegate()
		{
			_token = _safe_emiter.CallbackEvent() += [this]()
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
			_safe_emiter.CallbackEvent() -= _token;
		}

		///
		/// @brief 订阅事件。
		///
		/// @param func
		/// @return std::shared_ptr<typename base::IIdToken> 用来取消订阅的 token.
		///
		virtual base::SpIIdToken Subscribe(std::function<void(Args...)> const &func) override
		{
			return _delegate.Subscribe(func);
		}

		///
		/// @brief 取消订阅事件。
		///
		/// @param token 传入由 Subscribe 方法返回的 token.
		///
		virtual void Unsubscribe(base::SpIIdToken const &token) override
		{
			_delegate.Unsubscribe(token);
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
