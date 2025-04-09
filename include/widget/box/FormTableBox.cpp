#include "FormTableBox.h"
#include "GridBoxItem.h"

/* #region 构造函数 */

widget::FormTableBox::FormTableBox()
{
	_layout.AddWidget(&_box);

	// 第 0 列的增长因子为 0，不允许增长，而是根据内容调整大小。
	_box.SetColumnStretch(0, 0);

	// 第 1 列的增长因子为 1.
	//
	// 凡是增长因子不为 0 的，都会根据因子的比例去分配剩余的宽度。
	// 这里一共 2 列，其中第 0 列增长因子为 0，所以第 1 列就占据所有剩余宽度。
	_box.SetColumnStretch(1, 1);

	// 让表单中每一行从顶端开始一行一行往下排列。
	_box.SetAlignment(Qt::AlignmentFlag::AlignTop);
}

widget::FormTableBox::FormTableBox(std::initializer_list<widget::FormTableBoxItem> const &items)
	: FormTableBox()
{
	try
	{
		SetItem(items);
	}
	catch (std::exception const &e)
	{
		throw new std::runtime_error{CODE_POS_STR + e.what()};
	}
}

/* #endregion */

void widget::FormTableBox::SetItem(int row, widget::FormTableBoxItem const &item)
{
	if (item.LeftWidget() == nullptr)
	{
		throw new std::runtime_error{CODE_POS_STR + "item.LeftWidget() 不能为空指针。"};
	}

	if (item.RightWidget() == nullptr)
	{
		throw new std::runtime_error{CODE_POS_STR + "item.RightWidget() 不能为空指针。"};
	}

	try
	{
		// 水平展开，充满表单网格，
		//
		// 垂直固定高度，防止垂直方向将表单盒子撑开，使得表单盒子充满父容器，
		// 然后每一行非常高。
		item.LeftWidget()->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
		item.RightWidget()->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);

		_box.SetItem(widget::GridBoxItem{row, 0, item.LeftWidget()});
		_box.SetItem(widget::GridBoxItem{row, 1, item.RightWidget()});
	}
	catch (std::exception const &e)
	{
		throw std::runtime_error{CODE_POS_STR + e.what()};
	}
	catch (...)
	{
		throw std::runtime_error{CODE_POS_STR + "未知的异常。"};
	}
}

void widget::FormTableBox::SetItem(std::initializer_list<widget::FormTableBoxItem> const &items)
{
	int i = 0;

	try
	{
		for (widget::FormTableBoxItem const &item : items)
		{
			SetItem(i++, item);
		}
	}
	catch (std::exception const &e)
	{
		std::string message = CODE_POS_STR +
							  std::format("添加到第 {} 个项目时引发异常", i) +
							  e.what();

		throw new std::runtime_error{message};
	}
}

void widget::FormTableBox::RemoveItem(int row)
{
	_box.RemoveWidget(row, 0);
	_box.RemoveWidget(row, 1);
}

void widget::FormTableBox::ClearItems()
{
	_box.ClearWidgets();
}

widget::Padding widget::FormTableBox::Padding() const
{
	return _box.Padding();
}

void widget::FormTableBox::SetPadding(widget::Padding const &value)
{
	_box.SetPadding(value);
}
