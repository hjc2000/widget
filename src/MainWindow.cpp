#include "MainWindow.h"
#include <QLineEdit>

class CustomWidget :
	public QWidget
{
public:
	CustomWidget(QWidget *parent = nullptr)
		: QWidget(parent)
	{
		// 创建水平布局
		QHBoxLayout *layout = new QHBoxLayout(this);

		// 创建输入框
		QLineEdit *lineEdit = new QLineEdit(this);
		lineEdit->setPlaceholderText("Enter text here...");
		lineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred); // 输入框自适应缩放

		// 创建按钮
		QPushButton *button = new QPushButton("Submit", this);
		button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred); // 按钮大小由内容决定

		// 将控件添加到布局中
		layout->addWidget(lineEdit);
		layout->addWidget(button);

		// 设置布局的间距和边距
		layout->setSpacing(10);                     // 控件之间的间距
		layout->setContentsMargins(10, 10, 10, 10); // 布局与窗口边缘的距离
	}
};

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

	CustomWidget *w = new CustomWidget{centralWidget};
	layout->addWidget(w);

	connect(button1,
			&QPushButton::clicked,
			[this]()
			{
				close();
			});
}
