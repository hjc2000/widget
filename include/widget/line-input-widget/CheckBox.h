#pragma once
#include "qcheckbox.h"
#include "qwidget.h"
#include <base/delegate/Delegate.h>
#include <memory>
#include <string>
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
		base::Delegate<widget::CheckState> _check_state_changed;

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
	};
} // namespace widget
