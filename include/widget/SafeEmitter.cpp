#include "SafeEmitter.h"

widget::SafeEmitter::SafeEmitter()
{
	connect(this,
			&SafeEmitter::clicked,
			[this]()
			{
				_callback.Invoke();
			});
}

void widget::SafeEmitter::Emit()
{
	QMetaObject::invokeMethod(this,
							  "clicked",
							  Qt::QueuedConnection,
							  Q_ARG(bool, false));
}

base::IEvent<> &widget::SafeEmitter::CallbackEvent()
{
	return _callback;
}
