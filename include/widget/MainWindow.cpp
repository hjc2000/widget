#include "MainWindow.h"
#include "dialog/Dialog.h"
#include "widget/layout/Padding.h"

widget::MainWindow::MainWindow()
{
	setWindowTitle("test");
	setCentralWidget(_vbox.get());
	_vbox->SetPadding(widget::Padding{10});

	_button->ClickedEvent() += []()
	{
		widget::Dialog dialog;
		dialog.ShowModal();
	};

	_light->SetState(base::Enum::SwitchState::On);
}
