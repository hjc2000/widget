#include "Table.h"
#include "base/math/ColumnIndex.h"
#include "base/string/define.h"
#include "Table.HeaderView.h"
#include "Table.PrivateTable.h"
#include "Table.TableDataModelWrapper.h"
#include <stdexcept>

widget::Table::Table()
{
	// PrivateTable 的大小调整策略为撑开。会填满父容器。
	_table = std::shared_ptr<PrivateTable>{new PrivateTable{}};
	_layout.AddWidget(_table.get());
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

	_table_data_model = std::shared_ptr<TableDataModelWrapper>{new TableDataModelWrapper{model}};
	_row_header_view = std::shared_ptr<HeaderView>{new HeaderView{Qt::Orientation::Vertical}};
	_table->setModel(_table_data_model.get());
	_table->setVerticalHeader(_row_header_view.get());

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

void widget::Table::SetColumnResizeModes(std::vector<QHeaderView::ResizeMode> resize_modes)
{
	if (_table_data_model == nullptr)
	{
		throw std::runtime_error{CODE_POS_STR + "需要先设置表格数据模型。"};
	}

	_table->SetResizeModes(resize_modes);
}

/* #region 列宽 */

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

/* #region 事件 */

base::IEvent<base::Position const &> &widget::Table::DoubleClickEvent()
{
	return _table->DoubleClickEvent();
}

/* #endregion */
