#include "SafeDelegate.h"
#include "base/string/define.h"
#include <exception>

widget::SafeEmitter::SafeEmitter()
{
	_connection = connect(this,
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

widget::SafeEmitter::~SafeEmitter()
{
	disconnect(_connection);

	// 因为只连接了一个信号，理论上 disconnect(_connection) 就行了，这里是为了做笔记，
	// 通过下面这种方式，传入 nullptr, 可以断开来自 this 的所有信号的连接。
	disconnect(this, nullptr, nullptr, nullptr);

	// 除了断开连接，避免新的信号调用槽函数以外，还需要清理消息队列中已经有的信号，因为断开
	// 连接不影响已经排队的信号，它们仍然会调用槽函数。
	QCoreApplication::removePostedEvents(this, QEvent::MetaCall);
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
