#include "RangeSubmit.h"

widget::RangeSubmit::RangeSubmit()
{
	setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
	_layout.AddWidget(_grid_box.get());

	_left_edit->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
	_label->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
	_right_edit->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);

	_grid_box->SetColumnStretch(0, 1);
	_grid_box->SetColumnStretch(1, 0);
	_grid_box->SetColumnStretch(2, 1);

	{
		setAutoFillBackground(true);
		QPalette temp_palette = palette();
		temp_palette.setColor(QPalette::Window, QColor{240, 240, 240});
		setPalette(temp_palette);
	}

	{
		// 订阅事件
		_left_edit->TextChangingFinishedEvent().Subscribe([this](QString const &text)
														  {
															  _submit_event.Invoke();
														  });

		_right_edit->TextChangingFinishedEvent().Subscribe([this](QString const &text)
														   {
															   _submit_event.Invoke();
														   });
	}
}

/* #region 输入框的文本 */

QString widget::RangeSubmit::LeftText() const
{
	return _left_edit->Text();
}

void widget::RangeSubmit::SetLeftText(QString const &value)
{
	_left_edit->SetText(value);
}

void widget::RangeSubmit::SetLeftText(std::string const &value)
{
	_left_edit->SetText(value);
}

void widget::RangeSubmit::SetLeftText(char const *value)
{
	_left_edit->SetText(value);
}

QString widget::RangeSubmit::RightText() const
{
	return _right_edit->Text();
}

void widget::RangeSubmit::SetRightText(QString const &value)
{
	_right_edit->SetText(value);
}

/* #endregion */

void widget::RangeSubmit::SetLeftInvalidInputStyle(bool is_invalid)
{
	_left_edit->SetInvalidInputStyle(is_invalid);
}

void widget::RangeSubmit::SetRightInvalidInputStyle(bool is_invalid)
{
	_right_edit->SetInvalidInputStyle(is_invalid);
}
