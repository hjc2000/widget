#include "MainWindow.h"
#include "layout/Padding.h"
#include <iostream>

widget::MainWindow::MainWindow()
{
	setWindowTitle("test");
	setCentralWidget(&_box);

	_box.SetPadding(widget::Padding{10});

	_range_submit->SubmitEvent().Subscribe(
		[]()
		{
			std::cout << "提交" << std::endl;
		});
}
