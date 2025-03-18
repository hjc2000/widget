#pragma once
#include <base/delegate/Delegate.h>
#include <base/delegate/IEvent.h>
#include <widget/layout/HBoxLayout.h>
#include <widget/line-input-widget/CheckState.h>

namespace widget
{
	///
	/// @brief 选择框。
	///
	///
	class CheckBox :
		public QWidget
	{
	private:
		std::shared_ptr<QCheckBox> _check_box;
		widget::HBoxLayout _layout{this};

		base::Delegate<> _check_state_changed_event;

		void ConnectSignals();

	public:
		CheckBox();
		CheckBox(std::string const &text);

		///
		/// @brief 选择状态。
		///
		/// @return widget::CheckState
		///
		widget::CheckState CheckState() const;

		///
		/// @brief 设置选择状态。
		///
		/// @param value
		///
		void SetCheckState(widget::CheckState value);

		///
		/// @brief 选择状态改变事件。
		///
		/// @return base::IEvent<>&
		///
		base::IEvent<> &CheckStateChangedEvent();
	};
} // namespace widget
