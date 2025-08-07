#include "Table.h"
#include "base/math/ColumnIndex.h"
#include "base/string/define.h"
#include "qevent.h"
#include "Table.CustomItemDelegate.h"
#include "Table.HeaderView.h"
#include "Table.PrivateTable.h"
#include "Table.TableDataModelWrapper.h"
#include "VerticalScrollEventArgs.h"
#include <stdexcept>

void widget::Table::SetColumnHeaderStyle()
{
	// 允许用户移动列
	_column_header_view->setSectionsMovable(true);

	// 允许用户点击列头
	_column_header_view->setSectionsClickable(true);

	// 允许用户调整列宽。
	_column_header_view->setSectionResizeMode(QHeaderView::Interactive);
}

/* #region 订阅、取消订阅事件 */

void widget::Table::SubscribeEvents()
{
	_table->CurrentChangeEvent() += [this](widget::Table::CurrentChangeEventArgs const &args)
	{
		if (_row_header_view == nullptr)
		{
			return;
		}

		_row_header_view->SetSelectedIndex(args.Current().row());
		_column_header_view->SetSelectedIndex(args.Current().column());
		update();
	};

	_table->WheelEvent() += [this](QWheelEvent const &event)
	{
		if (VerticalScrollBar()->value() <= VerticalScrollBar()->minimum() ||
			VerticalScrollBar()->value() >= VerticalScrollBar()->maximum())
		{
			// 没有滚动到顶部或底部时，交给滚动条的滚动值改变事件来触发 _vertical_scroll_event,
			// 滚动到顶部或底部时才有这里的滚轮事件触发 _vertical_scroll_event.

			widget::VerticalScrollDirection direction = widget::VerticalScrollDirection::Down;
			if (event.angleDelta().y() > 0)
			{
				direction = widget::VerticalScrollDirection::Up;
			}

			widget::VerticalScrollEventArgs args{direction};
			_vertical_scroll_event.Invoke(args);

			if (_table_data_model != nullptr)
			{
				_table_data_model->InnerModel().OnVerticalScroll(args);
			}
		}
	};

	_table->VerticalScrollBarValueChangeEvent() += [this](int value)
	{
		static int last_value = 0;
		widget::VerticalScrollDirection direction = widget::VerticalScrollDirection::Down;

		if (VerticalScrollBar()->value() < last_value)
		{
			direction = widget::VerticalScrollDirection::Up;
		}

		last_value = value;

		widget::VerticalScrollEventArgs args{direction};
		_vertical_scroll_event.Invoke(args);

		if (_table_data_model != nullptr)
		{
			_table_data_model->InnerModel().OnVerticalScroll(args);
		}
	};
}

/* #endregion */

widget::Table::Table()
{
	// PrivateTable 的大小调整策略为撑开。会填满父容器。
	_table = std::shared_ptr<PrivateTable>{new PrivateTable{}};
	_row_header_view = std::shared_ptr<HeaderView>{new HeaderView{Qt::Orientation::Vertical}};
	_column_header_view = std::shared_ptr<HeaderView>{new HeaderView{Qt::Orientation::Horizontal}};

	_layout.AddWidget(_table.get());

	SubscribeEvents();
	SetColumnHeaderStyle();
}

widget::Table::~Table()
{
	_vertical_scroll_event.Dispose();

	_table->Dispose();
}

void widget::Table::SetModel(std::shared_ptr<widget::ITableDataModel> const &model)
{
	if (model == nullptr)
	{
		_table->setModel(nullptr);
		_table->horizontalHeader()->setVisible(false);
		_table->verticalHeader()->setVisible(false);
		return;
	}

	model->SetParentTable(this);
	_table_data_model = std::shared_ptr<TableDataModelWrapper>{new TableDataModelWrapper{_table.get(), model}};
	_table->setModel(_table_data_model.get());
	_table->setVerticalHeader(_row_header_view.get());
	_table->setHorizontalHeader(_column_header_view.get());

	// 设置行列标题的可见性
	{
		// 有列标题则让水平的表格头可见。
		_table->horizontalHeader()->setVisible(model->HasColumnTitle());

		// 有行标题则让垂直的表格头可见。
		_table->verticalHeader()->setVisible(model->HasRowTitle());
	}
}

/* #region 排序 */

bool widget::Table::IsSortingEnabled() const
{
	return _table->isSortingEnabled();
}

void widget::Table::EnableSorting(bool enable)
{
	_table->setSortingEnabled(enable);
}

widget::TableSortingParameter widget::Table::CurrentSortingParameter() const
{
	if (_table_data_model == nullptr)
	{
		return widget::TableSortingParameter{};
	}

	return _table_data_model->CurrentSortingParameter();
}

void widget::Table::Sort(widget::TableSortingParameter const &parameter)
{
	if (_table_data_model == nullptr)
	{
		return;
	}

	_table->sortByColumn(parameter.Column(), parameter.Order());
}

void widget::Table::Sort(int column, Qt::SortOrder order)
{
	if (_table_data_model == nullptr)
	{
		return;
	}

	_table->sortByColumn(column, order);
}

/* #endregion */

/* #region 列宽 */

void widget::Table::SetColumnResizeModes(std::vector<QHeaderView::ResizeMode> resize_modes)
{
	if (_table_data_model == nullptr)
	{
		throw std::runtime_error{CODE_POS_STR + "需要先设置表格数据模型。"};
	}

	QHeaderView *header = _table->horizontalHeader();
	if (header == nullptr)
	{
		return;
	}

	int count = std::min(header->count(), static_cast<int>(resize_modes.size()));
	for (int i = 0; i < count; ++i)
	{
		header->setSectionResizeMode(i, resize_modes[i]);
	}
}

void widget::Table::ResizeColumnsToContents()
{
	if (_table_data_model == nullptr)
	{
		throw std::runtime_error{CODE_POS_STR + "需要先设置表格数据模型。"};
	}

	_table->resizeColumnsToContents();
}

int widget::Table::ColumnWidth(int column_index) const
{
	if (_table_data_model == nullptr)
	{
		throw std::runtime_error{CODE_POS_STR + "需要先设置表格数据模型。"};
	}

	if (column_index < 0 || column_index > _table_data_model->InnerModel().ColumnCount())
	{
		throw std::out_of_range{CODE_POS_STR + "列索引超出范围。"};
	}

	return _table->columnWidth(column_index);
}

void widget::Table::SetColumnWidth(base::ColumnIndex const &index, int width)
{
	if (_table_data_model == nullptr)
	{
		throw std::runtime_error{CODE_POS_STR + "需要先设置表格数据模型。"};
	}

	if (index.Value() < 0 || index.Value() > _table_data_model->InnerModel().ColumnCount())
	{
		throw std::out_of_range{CODE_POS_STR + "列索引超出范围。"};
	}

	_table->setColumnWidth(index.Value(), width);
}

void widget::Table::SetColumnWidth(int width)
{
	if (_table_data_model == nullptr)
	{
		throw std::runtime_error{CODE_POS_STR + "需要先设置表格数据模型。"};
	}

	for (int i = 0; i < _table_data_model->InnerModel().ColumnCount(); i++)
	{
		_table->setColumnWidth(i, width);
	}
}

void widget::Table::SetColumnWidth(std::vector<int> const &widths)
{
	if (_table_data_model == nullptr)
	{
		throw std::runtime_error{CODE_POS_STR + "需要先设置表格数据模型。"};
	}

	int column_count = std::min<int>(_table_data_model->InnerModel().ColumnCount(), static_cast<int>(widths.size()));
	for (int i = 0; i < column_count; i++)
	{
		_table->setColumnWidth(i, widths[i]);
	}
}

/* #endregion */

widget::Padding widget::Table::ItemPadding() const
{
	return _table->ItemPadding();
}

void widget::Table::SetItemPadding(widget::Padding const &value)
{
	_table->SetItemPadding(value);
}

widget::Padding widget::Table::RowHeaderPadding() const
{
	return _row_header_view->Padding();
}

void widget::Table::SetRowHeaderPadding(widget::Padding const &value)
{
	_row_header_view->SetPadding(value);
	update();
}

Qt::AlignmentFlag widget::Table::RowHeaderTextAlignment() const
{
	return _row_header_view->TextAlignment();
}

void widget::Table::SetRowHeaderTextAlignment(Qt::AlignmentFlag value)
{
	_row_header_view->SetTextAlignment(value);
	update();
}

void widget::Table::SetItemColumnAlignments(std::vector<Qt::AlignmentFlag> const &alignments)
{
	_table->CustomItemDelegate().SetColumnAlignments(alignments);
	update();
}

int widget::Table::FirstVisibleRowIndex() const
{
	return _table->FirstVisibleRowIndex();
}

QScrollBar *widget::Table::VerticalScrollBar() const
{
	return _table->verticalScrollBar();
}

int widget::Table::RowViewportPosition(int row) const
{
	return _table->rowViewportPosition(row);
}

/* #region 事件 */

base::IEvent<base::Position<int32_t> const &> &widget::Table::DoubleClickEvent()
{
	return _table->DoubleClickEvent();
}

base::IEvent<widget::Table::CurrentChangeEventArgs const &> &widget::Table::CurrentChangeEvent()
{
	return _table->CurrentChangeEvent();
}

base::IEvent<QWheelEvent const &> &widget::Table::WheelEvent()
{
	return _table->WheelEvent();
}

base::IEvent<int> &widget::Table::VerticalScrollBarValueChangeEvent()
{
	return _table->VerticalScrollBarValueChangeEvent();
}

/* #endregion */
