#include "RangeSubmit.h" // IWYU pragma: keep

widget::RangeSubmit::RangeSubmit()
{
	setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
	_layout.AddWidget(_grid_box);

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
