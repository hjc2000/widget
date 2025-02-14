#pragma once
#include <base/delegate/Delegate.h>
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

		void ConnectSignal();

	public:
		Button(QWidget *parent);
		Button(QWidget *parent, QString const &text);

#pragma region 事件
		base::IEvent<> &ClickedEvent();
		base::IEvent<> &PressedEvent();
#pragma endregion

#pragma region 按钮文本
		QString Text() const;
		void SetText(QString const &value);
		void SetText(std::string const &value);
		void SetText(char const *value);
#pragma endregion
	};
} // namespace widget
