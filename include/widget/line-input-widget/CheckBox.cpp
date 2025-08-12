#include "CheckBox.h" // IWYU pragma: keep
#include "base/string/define.h"
#include <iostream>

void widget::CheckBox::ConnectSignals()
{
	QMetaObject::Connection connection;

	connection = connect(_check_box.get(),
						 &QCheckBox::checkStateChanged,
						 [this](Qt::CheckState q_check_state)
						 {
							 try
							 {
								 _check_state_changed_event.Invoke();
							 }
							 catch (std::exception const &e)
							 {
								 std::cerr << CODE_POS_STR + e.what() << std::endl;
							 }
							 catch (...)
							 {
								 std::cerr << CODE_POS_STR + "发生了未知异常。" << std::endl;
							 }
						 });

	_connections.push_back(connection);
}
