#pragma once
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

namespace widget
{
	class InputWidget :
		public QWidget
	{
	public:
		InputWidget(QWidget *parent = nullptr)
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
} // namespace widget
