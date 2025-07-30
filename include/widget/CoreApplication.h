#pragma once
#include "QApplication"
#include "widget/plugin.h" // IWYU pragma: keep

namespace widget
{
	class CoreApplication :
		public QApplication
	{
	public:
		CoreApplication();

		CoreApplication(int &argc, char **argv);
	};

} // namespace widget
