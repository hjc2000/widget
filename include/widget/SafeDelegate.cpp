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
	// 析构时需要断开所有信号，避免等本对象析构后，在队列中排队的信号触发了，
	// lambda 表达式的槽函数访问本对象字段。
	disconnect(_connection);

	// 因为只连接了一个信号，理论上 disconnect(_connection) 就行了，这里是为了做笔记，
	// 通过下面这种方式，传入 nullptr, 可以断开来自 this 的所有信号的连接。
	disconnect(this, nullptr, nullptr, nullptr);
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
