#pragma once
#include "base/container/SafeQueue.h"
#include "base/delegate/Delegate.h"
#include "base/delegate/IEvent.h"
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

	public:
		///
		/// @brief 构造一个安全发射器。
		///
		///
		SafeEmitter();

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

	template <typename... Args>
	class SafeDelegate :
		public base::IEvent<Args...>
	{
	private:
		widget::SafeEmitter _safe_emiter;
		base::Delegate<Args...> _delegate;
		base::SafeQueue<std::function<void()>> _capture_func_queue;

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
		/// @brief 调用所有订阅的函数
		/// @param ...args
		///
		void Invoke(Args... args)
		{
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
			Invoke(args...);
		}
	};
} // namespace widget
