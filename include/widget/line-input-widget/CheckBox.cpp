#include "CheckBox.h"
#include <widget/Conversion.h>

void widget::CheckBox::ConnectSignals()
{
	connect(_check_box.get(),
			&QCheckBox::checkStateChanged,
			[this](Qt::CheckState q_check_state)
			{
				try
				{
					_check_state_changed_event.Invoke();
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
	_layout.AddWidget(_check_box.get());

	ConnectSignals();
}

widget::CheckBox::CheckBox(std::string const &text)
{
	_check_box = std::shared_ptr<QCheckBox>{new QCheckBox{
		text.c_str(),
		nullptr,
	}};

	_layout.AddWidget(_check_box.get());

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

base::IEvent<> &widget::CheckBox::CheckStateChangedEvent()
{
	return _check_state_changed_event;
}
