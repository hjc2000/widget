#pragma once
#include "Input.h"
#include "qboxlayout.h"
#include "qlabel.h"
#include "qvalidator.h"
#include "widget/Button.h"

namespace widget
{
	class RangeSubmit :
		public QWidget
	{
	private: // 控件
		QHBoxLayout _layout{this};
		widget::Input _left_edit{};
		widget::Input _right_edit{};
		QLabel _label{"-"};
		widget::Button _button{};

	private:
		QIntValidator _validator{0, INT_MAX};
		base::Delegate<> _submit_event;

	public:
		RangeSubmit();

	public: // 属性
		QString LeftText() const;
		std::string LeftTextStdString() const;
		QString RightText() const;
		std::string RightTextStdString() const;

	public: // 事件
		base::IEvent<> &SubmitEvent();
	};
} // namespace widget
