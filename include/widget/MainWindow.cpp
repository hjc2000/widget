#include "MainWindow.h"
#include <iostream>

widget::MainWindow::MainWindow()
{
	setWindowTitle("test");
	setCentralWidget(&_central_widget);
	_layout.addWidget(&_button);

	_button.SubmitEvent().Subscribe(
		[]()
		{
			std::cout << "点击事件被处理了。" << std::endl;
		});
}
