#pragma once
#include "qboxlayout.h"
#include "qlabel.h"
#include "qlineedit.h"
#include "qvalidator.h"
#include "widget/Button.h"

namespace widget
{
	class RangeSubmit :
		public QWidget
	{
	private:
		QHBoxLayout _layout{this};
		QLineEdit _left_edit{};
		QLineEdit _right_edit{};
		QLabel _label{"-"};
		widget::Button _button{"提交"};
		base::Delegate<> _submit_event;

		QIntValidator _validator{0, INT_MAX};

	public:
		RangeSubmit();

		QString LeftText() const;
		std::string LeftTextStdString() const;
		QString RightText() const;
		std::string RightTextStdString() const;
		base::IEvent<> &SubmitEvent();
	};
} // namespace widget
