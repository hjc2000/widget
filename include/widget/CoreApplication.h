#pragma once
#include "QApplication"

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
