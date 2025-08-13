#include "DateTimeEdit.h" // IWYU pragma: keep

void widget::DateTimeEdit::ConnectSignal()
{
	{
		QMetaObject::Connection connection =
			connect(_edit.get(),
					&QDateTimeEdit::dateTimeChanged,
					[this](QDateTime const &date_time)
					{
						_submit_event.Invoke();
					});

		_connections.push_back(connection);
	}
}

widget::DateTimeEdit::DateTimeEdit()
{
	_edit->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);

	// 设置当前日期和时间
	_edit->setDateTime(QDateTime::currentDateTime());

	// 设置显示格式
	_edit->setDisplayFormat("yyyy-MM-dd hh:mm:ss");

	ConnectSignal();
}

void widget::DateTimeEdit::Dispose()
{
	if (_disposed)
	{
		return;
	}

	_disposed = true;

	_submit_event.Dispose();

	for (QMetaObject::Connection &connection : _connections)
	{
		disconnect(connection);
	}

	QCoreApplication::removePostedEvents(this);
}

void widget::DateTimeEdit::SetInvalidInputStyle(bool is_invalid)
{
	if (is_invalid)
	{
		_edit->setStyleSheet("border: 2px solid red;");
	}
	else
	{
		// 恢复默认样式
		_edit->setStyleSheet("");
	}
}
