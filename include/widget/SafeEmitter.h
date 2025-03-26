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
} // namespace widget
