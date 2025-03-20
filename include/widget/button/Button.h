#pragma once
#include "base/delegate/Delegate.h"
#include "QPushButton"

namespace widget
{
	///
	/// @brief 按钮。
	///
	///
	class Button :
		public QPushButton
	{
	private:
		///
		/// @brief 触发 enter 事件前的样式。在 enter 事件处理函数的一开始就记录到本字段中。
		///
		///
		QPalette _palette_before_enter_event;

		///
		/// @brief 触发 pressed 事件前的样式。在 pressed 事件处理函数地一开始就记录到本字段中。
		///
		///
		QPalette _palette_before_pressed_event;

		void ConnectSignal();

		/* #region 对外提供事件 */

		base::Delegate<> _clicked_event;
		base::Delegate<> _pressed_event;
		base::Delegate<> _released_event;
		base::Delegate<> _enter_event;
		base::Delegate<> _leave_event;

		/* #endregion */

		/* #region 本类的事件处理函数 */

		virtual void enterEvent(QEnterEvent *event) override;
		virtual void leaveEvent(QEvent *event) override;
		void OnClicked();
		void OnPressed();
		void OnReleased();

		/* #endregion */

	public:
		Button();
		Button(QString const &text);

		/* #region 对外提供事件 */

		///
		/// @brief 按钮点击事件。
		///
		/// @return base::IEvent<>&
		///
		base::IEvent<> &ClickedEvent();

		///
		/// @brief 鼠标按钮按下，没有释放时触发的事件。
		///
		/// @return base::IEvent<>&
		///
		base::IEvent<> &PressedEvent();

		///
		/// @brief 鼠标按钮从按下状态变成释放状态时触发的事件。
		///
		/// @return base::IEvent<>&
		///
		base::IEvent<> &ReleasedEvent();

		///
		/// @brief 鼠标进入按钮时触发的事件。
		///
		/// @return base::IEvent<>&
		///
		base::IEvent<> &EnterEvent();

		///
		/// @brief 鼠标离开按钮时触发的事件。
		///
		/// @return base::IEvent<>&
		///
		base::IEvent<> &LeaveEvent();

		/* #endregion */

		/* #region 文本 */

		///
		/// @brief 按钮的文本。
		///
		/// @return QString
		///
		QString Text() const;

		///
		/// @brief 设置按钮的文本。
		///
		/// @param value
		///
		void SetText(QString const &value);

		///
		/// @brief 设置按钮的文本。
		///
		/// @param value
		///
		void SetText(std::string const &value);

		///
		/// @brief 设置按钮的文本。
		///
		/// @param value
		///
		void SetText(char const *value);

		/* #endregion */
	};
} // namespace widget
