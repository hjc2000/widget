#include "Button.h"

/* #region 事件处理函数 */

void widget::Button::enterEvent(QEnterEvent *event)
{
	_palette_before_enter_event = palette();

	QPushButton::enterEvent(event);
	QPalette temp_palette = palette();
	temp_palette.setColor(QPalette::Button, QColor{150, 190, 230});
	setPalette(temp_palette);

	try
	{
		_enter_event.Invoke();
	}
	catch (std::exception const &e)
	{
		std::cerr << CODE_POS_STR + e.what() << std::endl;
	}
	catch (...)
	{
	}
}

void widget::Button::leaveEvent(QEvent *event)
{
	QPushButton::leaveEvent(event);
	setPalette(_palette_before_enter_event);

	try
	{
		_leave_event.Invoke();
	}
	catch (std::exception const &e)
	{
		std::cerr << CODE_POS_STR + e.what() << std::endl;
	}
	catch (...)
	{
	}
}

/* #endregion */
