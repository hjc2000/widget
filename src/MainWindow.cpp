#include "MainWindow.h"
#include <base/string/Parse.h>
#include <QAbstractTableModel>
#include <QHeaderView>
#include <QLineEdit>
#include <QPainter>
#include <QStyledItemDelegate>
#include <QTableView>
#include <string>
#include <widget/Button.h>
#include <widget/Conversion.h>
#include <widget/InputWidget.h>

namespace
{
	class MyTableModel :
		public QAbstractTableModel
	{
	public:
		MyTableModel(QTableView *parent)
			: QAbstractTableModel(parent)
		{
		}

		virtual int rowCount(QModelIndex const &parent = QModelIndex{}) const override
		{
			return 200;
		}

		virtual int columnCount(QModelIndex const &parent = QModelIndex{}) const override
		{
			return 3;
		}

		virtual QVariant data(QModelIndex const &index, int role = Qt::DisplayRole) const override
		{
			if (role == Qt::DisplayRole)
			{
				return QVariant{QString{"Cell (%1, %2)"}.arg(index.row()).arg(index.column())};
			}

			return QVariant{};
		}

		virtual QVariant headerData(int section,
									Qt::Orientation orientation,
									int role = Qt::DisplayRole) const override
		{
			if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
			{
				return QString("Column %1").arg(section + 1);
			}

			return QAbstractTableModel::headerData(section, orientation, role);
		}
	};
} // namespace

widget::MainWindow::MainWindow()
{
	setWindowTitle("test");

	// 创建一个中央部件
	QWidget *centralWidget = new QWidget{this};
	setCentralWidget(centralWidget);

	QHBoxLayout *layout = new QHBoxLayout{centralWidget};
	layout->setAlignment(Qt::Alignment{Qt::AlignmentFlag::AlignTop | Qt::AlignmentFlag::AlignLeft});

	// 创建 QTableView 和模型
	QTableView *tableView = new QTableView{centralWidget};
	MyTableModel *model = new MyTableModel{tableView};
	tableView->setModel(model);
	layout->addWidget(tableView);

	// 获取水平头视图并设置拉伸模式
	QHeaderView *header = tableView->horizontalHeader();
	header->setSectionResizeMode(QHeaderView::Stretch); // 均分宽度并拉伸

	tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
	tableView->setSelectionMode(QAbstractItemView::SingleSelection);

	// 设置样式表，将焦点矩形的颜色和背景颜色设置为蓝色
	tableView->setStyleSheet("QTableView::item:focus {"
							 "   background-color: blue;" // 设置焦点背景颜色为蓝色
							 "   color: white;"           // 可选：设置文本颜色为白色以提高对比度
							 "}");

	// 在第 2 列的每个单元格中添加 QPushButton
	for (int row = 0; row < model->rowCount(); ++row)
	{
		widget::Button *button = new widget::Button{this};
		tableView->setIndexWidget(model->index(row, 1), button);

		button->EnterEvent().Subscribe(
			[button]()
			{
				button->SetText("666");
			});

		button->LeaveEvent().Subscribe(
			[button]()
			{
				button->SetText("777");
			});
	}

	// // 添加一些按钮到布局中作为示例
	// QPushButton *button1 = new QPushButton{"按钮 1", centralWidget};
	// layout->addWidget(button1);

	// QPushButton *button2 = new QPushButton{"按钮 2", centralWidget};
	// layout->addWidget(button2);

	// QPushButton *button3 = new QPushButton{"按钮 3", centralWidget};
	// layout->addWidget(button3);

	// widget::InputWidget *w = new widget::InputWidget{centralWidget};
	// layout->addWidget(w);

	// w->SubmitEvent().Subscribe(
	// 	[this, w](QString const &text)
	// 	{
	// 		std::string str;
	// 		str << w->Text();

	// 		int64_t num = base::ParseInt64(str);
	// 		w->SetText(std::to_string(num + 1));
	// 	});
}
