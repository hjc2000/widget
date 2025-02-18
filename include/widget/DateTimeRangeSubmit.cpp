#include "DateTimeRangeSubmit.h"

widget::DateTimeRangeSubmit::DateTimeRangeSubmit()
{
	{
		_left_edit.setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);

		// 设置当前日期和时间
		_left_edit.setDateTime(QDateTime::currentDateTime());

		// 设置显示格式
		_left_edit.setDisplayFormat("yyyy-MM-dd hh:mm:ss");
	}

	{
		_right_edit.setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);

		// 设置当前日期和时间
		_right_edit.setDateTime(QDateTime::currentDateTime());

		// 设置显示格式
		_right_edit.setDisplayFormat("yyyy-MM-dd hh:mm:ss");
	}

	{
		_layout.addWidget(&_left_edit);
		_layout.addWidget(&_right_edit);
		_layout.addWidget(&_button);

		// 控件之间的间距。
		_layout.setSpacing(10);

		// 布局内的内容区域与布局边框的间距。实际上相当于网页中的盒子内边距。
		_layout.setContentsMargins(0, 0, 0, 0);
	}

	{
		setAutoFillBackground(true);
		QPalette temp_palette = palette();
		temp_palette.setColor(QPalette::Window, QColor{255, 255, 255});
		setPalette(temp_palette);
	}
}
