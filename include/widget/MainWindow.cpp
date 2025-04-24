#include "MainWindow.h"
#include "base/embedded/led/parameter.h"
#include "base/math/Size.h"
#include "dialog/Dialog.h"
#include "widget/button/Button.h"
#include "widget/layout/Padding.h"
#include <memory>

widget::MainWindow::MainWindow()
{
	setWindowTitle("test");
	setCentralWidget(_vbox.get());
	_vbox->SetPadding(widget::Padding{10});

	_button->ClickedEvent() += []()
	{
		widget::Dialog dialog;
		dialog.SetContent(std::shared_ptr<widget::Button>{new widget::Button{}});
		dialog.ShowModal(base::Size{1020, 720});
	};

	_light->SetState(base::led::State::On);
}
