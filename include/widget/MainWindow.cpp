#include "MainWindow.h"
#include <iostream>

widget::MainWindow::MainWindow()
{
	setWindowTitle("test");
	setCentralWidget(&_central_widget);

	_layout.SetItem(0, "输入：", &_range_submit);
	_layout.SetItem(1, "输入：", &_check_box);

	_range_submit.SubmitEvent().Subscribe(
		[]()
		{
			std::cout << "点击事件被处理了。" << std::endl;
		});
}
