#include "Input.h"

/* #region 对外提供事件 */

base::IEvent<QString const &> &widget::Input::TextChangedEvent()
{
	return _text_changed_event;
}

base::IEvent<QString const &> &widget::Input::TextChangingFinishedEvent()
{
	return _text_changing_finished_event;
}

base::IEvent<QString const &> &widget::Input::TextEditedEvent()
{
	return _text_edited_event;
}

base::IEvent<QString const &> &widget::Input::TextEditingFinishedEvent()
{
	return _text_editing_finished_event;
}

/* #endregion */

void widget::Input::SetInvalidInputStyle(bool is_invalid)
{
	if (is_invalid)
	{
		_line_edit.setStyleSheet("border: 2px solid red;");
	}
	else
	{
		// 恢复默认样式
		_line_edit.setStyleSheet("");
	}
}
