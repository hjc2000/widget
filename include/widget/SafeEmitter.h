#pragma once
#include "base/delegate/Delegate.h"
#include "base/delegate/IEvent.h"
#include "QPushButton"
#include "qpushbutton.h"

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
		base::Delegate<Args...> _delegate;
		mutable std::shared_ptr<base::IMutex> _lock = base::CreateIMutex();

	public:
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
		void Invoke(Args... args) const
		{
			base::LockGuard g{*_lock};
			_delegate.Invoke(args...);
		}

		///
		/// @brief 伪函数
		/// @param ...args
		///
		void operator()(Args... args) const
		{
			Invoke(args...);
		}
	};
} // namespace widget
