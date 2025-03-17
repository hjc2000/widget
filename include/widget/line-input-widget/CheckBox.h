#pragma once
#include <base/delegate/Delegate.h>
#include <base/delegate/IEvent.h>
#include <widget/layout/HBoxLayout.h>
#include <widget/line-input-widget/CheckState.h>

namespace widget
{
	/**
	 * @brief 选择框。
	 *
	 */
	class CheckBox :
		public QWidget
	{
	private:
		std::shared_ptr<QCheckBox> _check_box;
		widget::HBoxLayout _layout{this};

	public:
		base::Delegate<> _check_state_changed_event;

		void ConnectSignals();

	public:
		/**
		 * @brief Construct a new Check Box object
		 *
		 */
		CheckBox();

		/**
		 * @brief Construct a new Check Box object
		 *
		 * @param text 选择框右侧的文本。
		 */
		CheckBox(std::string const &text);

	public:
		/**
		 * @brief 选中状态。
		 *
		 * @return widget::CheckState
		 */
		widget::CheckState CheckState() const;

		/**
		 * @brief 设置选中状态。
		 *
		 * @param value
		 */
		void SetCheckState(widget::CheckState value);

	public:
		/**
		 * @brief 选择状态改变事件。
		 *
		 * @return base::IEvent<>&
		 */
		base::IEvent<> &CheckStateChangedEvent();
	};
} // namespace widget
