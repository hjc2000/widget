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
#pragma region 事件
		base::Delegate<> _clicked_event;
		base::Delegate<> _pressed_event;
		base::Delegate<> _released_event;
		base::Delegate<> _enter_event;
		base::Delegate<> _leave_event;
#pragma endregion

		QPalette const _origin_palette;

		void ConnectSignal();

		virtual void paintEvent(QPaintEvent *event) override;
		virtual void enterEvent(QEnterEvent *event) override;
		virtual void leaveEvent(QEvent *event) override;

	public:
#pragma region 构造函数
		Button(QWidget *parent);
		Button(QWidget *parent, QString const &text);
#pragma endregion

#pragma region 事件
		base::IEvent<> &ClickedEvent();
		base::IEvent<> &PressedEvent();
		base::IEvent<> &ReleasedEvent();
		base::IEvent<> &EnterEvent();
		base::IEvent<> &LeaveEvent();
#pragma endregion

#pragma region 按钮文本
		QString Text() const;
		void SetText(QString const &value);
		void SetText(std::string const &value);
		void SetText(char const *value);
#pragma endregion
	};
} // namespace widget
