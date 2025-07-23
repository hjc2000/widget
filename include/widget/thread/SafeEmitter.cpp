#include "SafeEmitter.h" // IWYU pragma: keep
#include "base/IDisposable.h"
#include "base/string/define.h"
#include <exception>
#include <iostream>

widget::SafeEmitter::~SafeEmitter()
{
	Dispose();
}

void widget::SafeEmitter::Dispose()
{
	if (_disposed)
	{
		return;
	}

	_disposed = true;

	// 清理消息队列中已经有的信号，避免本对象析构后仍然触发回调访问本对象。
	QCoreApplication::removePostedEvents(this, QEvent::MetaCall);

	_callback.Dispose();
}

void widget::SafeEmitter::Emit()
{
	if (_disposed)
	{
		throw base::ObjectDisposedException{CODE_POS_STR + "对象已经释放，禁止发射信号。"};
	}

	QMetaObject::invokeMethod(this, [this]()
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

base::IEvent<> &widget::SafeEmitter::CallbackEvent()
{
	return _callback;
}
