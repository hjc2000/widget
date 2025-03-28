#include "MainWindow.h"
#include "widget/layout/Padding.h"

widget::MainWindow::MainWindow()
{
	setWindowTitle("test");
	setCentralWidget(_box.get());
	_box->SetPadding(widget::Padding{10});
}
