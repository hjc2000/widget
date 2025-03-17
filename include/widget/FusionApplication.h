#pragma once
#include <QApplication>

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
