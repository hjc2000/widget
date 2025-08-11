#include "SafeEmitter.h" // IWYU pragma: keep
#include "base/string/define.h"
#include <exception>
#include <iostream>

void widget::SafeEmitter::Emit()
{
	if (_disposed)
	{
		throw base::ObjectDisposedException{CODE_POS_STR + "对象已经释放，禁止发射信号。"};
	}

	QMetaObject::invokeMethod(
		this, [this]()
		{
			if (_disposed)
			{
				return;
			}

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
		},
		Qt::QueuedConnection);
}
