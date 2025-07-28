#include "Submit.h"

void widget::Submit::SetButtonText(std::string const &value)
{
	SetButtonText(QString{value.c_str()});
}

void widget::Submit::SetButtonText(char const *value)
{
	SetButtonText(QString{value});
}

base::IEvent<QString const &> &widget::Submit::SubmitEvent()
{
	return _submit_event;
}

void widget::Submit::HideSubmissionButton()
{
	_button.hide();
}

void widget::Submit::ShowSubmissionButton()
{
	_button.show();
}

bool widget::Submit::SubmissionButtonVisibility() const
{
	return !_button.isHidden();
}

void widget::Submit::SetSubmissionButtonVisibility(bool value)
{
	if (SubmissionButtonVisibility())
	{
		HideSubmissionButton();
	}
	else
	{
		ShowSubmissionButton();
	}
}
