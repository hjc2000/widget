#include "MainWindow.h"
#include "layout/Padding.h"

widget::MainWindow::MainWindow()
{
	setWindowTitle("test");
	setCentralWidget(_vbox.get());

	_vbox->SetPadding(widget::Padding{10});
}
