#include "InputWidget.h"

#pragma region 初始化方法

void widget::InputWidget::InitializeLayout()
{
	// 将控件添加到布局中
	_layout->addWidget(_line_edit);
	_layout->addWidget(_button);

	// 控件之间的间距。在这里就是设置输入框和提交按钮之间的间距。
	_layout->setSpacing(10);

	// 布局内的内容区域与布局边框的间距。实际上相当于网页中的盒子内边距。
	_layout->setContentsMargins(0, 0, 0, 0);
}

void widget::InputWidget::ConnectSignal()
{
	_button->ClickedEvent().Subscribe(
		[this]()
		{
			try
			{
				_submit_event.Invoke(_line_edit->text());
			}
			catch (std::exception const &e)
			{
			}
			catch (...)
			{
			}
		});

	connect(_line_edit,
			&QLineEdit::returnPressed,
			[this]()
			{
				try
				{
					_submit_event.Invoke(_line_edit->text());
				}
				catch (std::exception const &e)
				{
				}
				catch (...)
				{
				}
			});

	connect(_line_edit,
			&QLineEdit::textChanged,
			[this]()
			{
				try
				{
					_text_changed_event.Invoke(_line_edit->text());
				}
				catch (std::exception const &e)
				{
				}
				catch (...)
				{
				}
			});

	connect(_line_edit,
			&QLineEdit::textEdited,
			[this]()
			{
				try
				{
					_text_edited_event.Invoke(_line_edit->text());
				}
				catch (std::exception const &e)
				{
				}
				catch (...)
				{
				}
			});

	connect(_line_edit,
			&QLineEdit::editingFinished,
			[this]()
			{
				try
				{
					_editing_finished.Invoke(_line_edit->text());
				}
				catch (std::exception const &e)
				{
				}
				catch (...)
				{
				}
			});
}

#pragma endregion

widget::InputWidget::InputWidget(QWidget *parent)
	: QWidget(parent)
{
	_line_edit->setPlaceholderText("在此处输入内容后按回车或点击提交");

	// 输入框自适应缩放
	_line_edit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);

	// 按钮大小由内容决定
	_button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);

	{
		setAutoFillBackground(true);
		QPalette temp_palette = palette();
		temp_palette.setColor(QPalette::Window, QColor{255, 255, 255});
		setPalette(temp_palette);
	}

	InitializeLayout();
	ConnectSignal();
}

#pragma region 编辑框中的文本

QString widget::InputWidget::PlaceholderText() const
{
	return _line_edit->placeholderText();
}

void widget::InputWidget::SetPlaceholderText(QString const &value)
{
	_line_edit->setPlaceholderText(value);
}

QString widget::InputWidget::Text() const
{
	return _line_edit->text();
}

void widget::InputWidget::SetText(QString const &value)
{
	_line_edit->setText(value);
}

void widget::InputWidget::SetText(std::string const &value)
{
	SetText(QString{value.c_str()});
}

void widget::InputWidget::SetText(char const *value)
{
	SetText(QString{value});
}

#pragma endregion

#pragma region 按钮的文本

QString widget::InputWidget::ButtonText() const
{
	return _button->text();
}

void widget::InputWidget::SetButtonText(QString const &value) const
{
	_button->setText(value);
}

void widget::InputWidget::SetButtonText(std::string const &value) const
{
	SetButtonText(QString{value.c_str()});
}

void widget::InputWidget::SetButtonText(char const *value) const
{
	SetButtonText(QString{value});
}

#pragma endregion

#pragma region 事件

base::IEvent<QString const &> &widget::InputWidget::SubmitEvent()
{
	return _submit_event;
}

base::IEvent<QString const &> &widget::InputWidget::TextChangedEvent()
{
	return _text_changed_event;
}

base::IEvent<QString const &> &widget::InputWidget::TextEditedEvent()
{
	return _text_edited_event;
}

base::IEvent<QString const &> &widget::InputWidget::EditingFinishedEvent()
{
	return _editing_finished;
}

#pragma endregion
