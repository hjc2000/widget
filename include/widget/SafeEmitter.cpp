#include "SafeEmitter.h"
#include "base/string/define.h"
#include <exception>

widget::SafeEmitter::SafeEmitter()
{
	connect(this,
			&SafeEmitter::clicked,
			[this]()
			{
				try
				{
					_callback.Invoke();
				}
				catch (std::exception const &e)
				{
					std::cerr << CODE_POS_STR << e.what() << std::endl;
				}
				catch (...)
				{
					std::cerr << CODE_POS_STR << "未知的异常。" << std::endl;
				}
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
