#include "Dialog.h"

widget::Dialog::Dialog()
{
}

widget::Dialog::Dialog(std::string const &title)
{
	setWindowTitle(title.c_str());
}

void widget::Dialog::ShowModal()
{
	exec();
}

void widget::Dialog::ShowModal(base::Size const &size)
{
	resize(size.XSize(), size.YSize());
	exec();
}
