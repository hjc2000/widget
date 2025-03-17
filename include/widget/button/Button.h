#pragma once
#include <widget/pch.h>

#include <base/delegate/Delegate.h>
#include <QPushButton>

namespace widget
{
	/**
	 * @brief 按钮。
	 *
	 */
	class Button :
		public QPushButton
	{
	private:
		/**
		 * @brief 构造函数中记录的原始样式。
		 *
		 */
		QPalette _origin_palette;

		/**
		 * @brief 触发 enter 事件前的样式。在 enter 事件处理函数的一开始就记录到本字段中。
		 *
		 */
		QPalette _palette_before_enter_event;

		/**
		 * @brief 触发 pressed 事件前的样式。在 pressed 事件处理函数地一开始就记录到本字段中。
		 *
		 */
		QPalette _palette_before_pressed_event;

		void ConnectSignal();

	private:
		// 事件

		base::Delegate<> _clicked_event;
		base::Delegate<> _pressed_event;
		base::Delegate<> _released_event;
		base::Delegate<> _enter_event;
		base::Delegate<> _leave_event;

		virtual void enterEvent(QEnterEvent *event) override;
		virtual void leaveEvent(QEvent *event) override;

	public:
		// 生命周期

		/**
		 * @brief Construct a new Button object
		 *
		 */
		Button();

		/**
		 * @brief Construct a new Button object
		 *
		 * @param text
		 */
		Button(QString const &text);

	public:
		// 事件

		/**
		 * @brief 按钮点击事件。
		 *
		 * @return base::IEvent<>&
		 */
		base::IEvent<> &ClickedEvent();

		/**
		 * @brief 鼠标按钮按下，没有释放时触发的事件。
		 *
		 * @return base::IEvent<>&
		 */
		base::IEvent<> &PressedEvent();

		/**
		 * @brief 鼠标按钮从按下状态变成释放状态时触发的事件。
		 *
		 * @return base::IEvent<>&
		 */
		base::IEvent<> &ReleasedEvent();

		/**
		 * @brief 鼠标进入按钮时触发的事件。
		 *
		 * @return base::IEvent<>&
		 */
		base::IEvent<> &EnterEvent();

		/**
		 * @brief 鼠标离开按钮时触发的事件。
		 *
		 * @return base::IEvent<>&
		 */
		base::IEvent<> &LeaveEvent();

	public:
		// Text

		/**
		 * @brief 按钮的文本。
		 *
		 * @return QString
		 */
		QString Text() const;

		/**
		 * @brief 设置按钮的文本。
		 *
		 * @param value
		 */
		void SetText(QString const &value);

		/**
		 * @brief 设置按钮的文本。
		 *
		 * @param value
		 */
		void SetText(std::string const &value);

		/**
		 * @brief 设置按钮的文本。
		 *
		 * @param value
		 */
		void SetText(char const *value);
	};
} // namespace widget
