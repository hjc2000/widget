#include "MainWindow.h"
#include <iostream>

widget::MainWindow::MainWindow()
{
	setWindowTitle("test");
	setCentralWidget(&_central_widget);

	_layout.AddWidget(&_range_submit, 0, 0);
	_layout.AddWidget(&_check_box, 0, 1);
	_layout.SetColumnStretch(0, 1);

	_range_submit.SubmitEvent().Subscribe(
		[]()
		{
			std::cout << "点击事件被处理了。" << std::endl;
		});
}
