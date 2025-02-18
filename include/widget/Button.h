#pragma once
#include <base/delegate/Delegate.h>
#include <QPalette>
#include <QPushButton>
#include <QWidget>
#include <string>

namespace widget
{
	/// @brief 按钮
	class Button :
		public QPushButton
	{
	private:
		base::Delegate<> _clicked_event;
		base::Delegate<> _pressed_event;
		base::Delegate<> _released_event;
		base::Delegate<> _enter_event;
		base::Delegate<> _leave_event;

		/// @brief 构造函数中记录的原始样式。
		QPalette _origin_palette;

		/// @brief 触发 enter 事件前的样式。在 enter 事件处理函数的一开始就记录到本字段中。
		QPalette _palette_before_enter_event;

		/// @brief 触发 pressed 事件前的样式。在 pressed 事件处理函数地一开始就记录到本字段中。
		QPalette _palette_before_pressed_event;

		void ConnectSignal();

		virtual void enterEvent(QEnterEvent *event) override;
		virtual void leaveEvent(QEvent *event) override;

	public:
		Button();
		Button(QString const &text);

		base::IEvent<> &ClickedEvent();
		base::IEvent<> &PressedEvent();
		base::IEvent<> &ReleasedEvent();
		base::IEvent<> &EnterEvent();
		base::IEvent<> &LeaveEvent();

		QString Text() const;
		void SetText(QString const &value);
		void SetText(std::string const &value);
		void SetText(char const *value);
	};
} // namespace widget
