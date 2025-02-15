#pragma once
#include <base/delegate/Delegate.h>
#include <QApplication>
#include <QCoreApplication>
#include <QDebug>
#include <QEvent>
#include <QMainWindow>
#include <QPushButton>
#include <QSplitter>
#include <QVBoxLayout>
#include <QWidget>

namespace widget
{
	class MainWindow :
		public QMainWindow
	{
	public:
		MainWindow();
	};
} // namespace widget
