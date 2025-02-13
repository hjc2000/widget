#include "MainWindow.h"

widget::MainWindow::MainWindow()
{
	setWindowTitle("带有侧边栏的 Hello World");

	// 创建一个中央部件
	QWidget *centralWidget = new QWidget{this};

	// 设置中央部件
	setCentralWidget(centralWidget);

	QHBoxLayout *layout = new QHBoxLayout{centralWidget};
	layout->setAlignment(Qt::Alignment{Qt::AlignmentFlag::AlignTop | Qt::AlignmentFlag::AlignLeft});

	// 添加一些按钮到布局中作为示例
	QPushButton *button1 = new QPushButton{"按钮 1", centralWidget};
	layout->addWidget(button1);

	QPushButton *button2 = new QPushButton{"按钮 2", centralWidget};
	layout->addWidget(button2);

	QPushButton *button3 = new QPushButton{"按钮 3", centralWidget};
	layout->addWidget(button3);

	connect(button1,
			&QPushButton::clicked,
			[this]()
			{
				close();
			});
}
