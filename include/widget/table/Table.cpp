#include "Table.h"
#include "Table.PrivateTable.h"
#include "Table.TableDataModelWrapper.h"

widget::Table::Table()
{
	_table = std::shared_ptr<PrivateTable>{new PrivateTable{}};
	_layout.AddWidget(_table.get());
}

/* #region 数据模型 */

void widget::Table::SetModel(std::shared_ptr<widget::ITableDataModel> const &model)
{
	// 有列标题则让水平的表格头可见。
	_table->horizontalHeader()->setVisible(model->HasColumnTitle());

	// 有行标题则让垂直的表格头可见。
	_table->verticalHeader()->setVisible(model->HasRowTitle());

	_table_data_model = std::shared_ptr<TableDataModelWrapper>{new TableDataModelWrapper{model}};
	_table->setModel(_table_data_model.get());
	_table->DataModelHasChanged();
}

void widget::Table::SetModel(std::shared_ptr<widget::ITableDataModel> const &model,
							 std::vector<QHeaderView::ResizeMode> resize_modes)
{
	SetModel(model);
	SetResizeModes(resize_modes);
}

/* #endregion */

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

void widget::Table::SetResizeModes(std::vector<QHeaderView::ResizeMode> resize_modes)
{
	_table->SetResizeModes(resize_modes);
}

/* #region 数据更新 */

void widget::Table::DataModelHasChanged()
{
	_table->DataModelHasChanged();
}

void widget::Table::RowsInserted(int row, int count)
{
	_table_data_model->RowsInserted(row, count);
}

void widget::Table::RowInserted(int row)
{
	RowsInserted(row, 1);
}

void widget::Table::RowsRemoved(int row, int count)
{
	_table_data_model->RowsRemoved(row, count);
}

void widget::Table::RowRemoved(int row)
{
	RowsRemoved(row, 1);
}

/* #endregion */
