#pragma once
#include <widget/pch.h>

namespace widget
{
	class FusionApplication :
		public QApplication
	{
	public:
		FusionApplication();
		FusionApplication(int &argc, char **argv);
	};
} // namespace widget
