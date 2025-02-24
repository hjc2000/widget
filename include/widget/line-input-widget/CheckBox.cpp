#include "CheckBox.h"
#include "CheckState.h"
#include "qcheckbox.h"
#include "qnamespace.h"
#include <base/string/define.h>
#include <exception>
#include <iostream>
#include <widget/Conversion.h>

void widget::CheckBox::ConnectSignals()
{
	connect(_check_box.get(),
			&QCheckBox::checkStateChanged,
			[this](Qt::CheckState q_check_state)
			{
				try
				{
					widget::CheckState check_state{};
					check_state << q_check_state;
					_check_state_changed.Invoke(check_state);
				}
				catch (std::exception const &e)
				{
					std::cerr << CODE_POS_STR + e.what() << std::endl;
				}
				catch (...)
				{
					std::cerr << CODE_POS_STR + "发生了未知异常。" << std::endl;
				}
			});
}

widget::CheckBox::CheckBox()
{
	_check_box = std::shared_ptr<QCheckBox>{new QCheckBox{}};
	ConnectSignals();
}

widget::CheckBox::CheckBox(std::string const &text)
{
	_check_box = std::shared_ptr<QCheckBox>{new QCheckBox{
		text.c_str(),
		nullptr,
	}};

	ConnectSignals();
}

widget::CheckState widget::CheckBox::CheckState() const
{
	widget::CheckState check_state{};
	check_state << _check_box->checkState();
	return check_state;
}

void widget::CheckBox::SetCheckState(widget::CheckState value)
{
	Qt::CheckState q_check_state{};
	q_check_state << value;
	_check_box->setCheckState(q_check_state);
}
