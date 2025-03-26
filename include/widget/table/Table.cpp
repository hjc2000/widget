#include "Table.h"
#include "Table.PrivateTable.h"
#include "Table.TableDataModelWrapper.h"

void widget::Table::SubscribeEvent()
{
	if (_table_data_model == nullptr)
	{
		return;
	}

	if (_table_data_model->InnerModel() == nullptr)
	{
		return;
	}

	_model_reset_event_token = _table_data_model->InnerModel()->ModelRestEvent() += [this]()
	{
		_table->ResizeColumnsToContent();
	};

	_row_inserted_event_token = _table_data_model->InnerModel()->RowInsertedEvent() +=
		[this](base::RowIndex const &row_index, base::RowCount const &row_count)
	{
		_table->ResizeColumnsToContent();
	};

	_row_removed_event_token = _table_data_model->InnerModel()->RowRemovedEvent() +=
		[this](base::RowIndex const &row_index, base::RowCount const &row_count)
	{
		_table->ResizeColumnsToContent();
	};

	_data_change_event_token = _table_data_model->InnerModel()->DataChangeEvent() += [this](base::PositionRange const &range)
	{
		_table->ResizeColumnsToContent();
	};
}

void widget::Table::UnsubscribeEvent()
{
	if (_table_data_model == nullptr)
	{
		return;
	}

	if (_table_data_model->InnerModel() == nullptr)
	{
		return;
	}

	_table_data_model->InnerModel()->ModelRestEvent() -= _model_reset_event_token;
	_table_data_model->InnerModel()->RowInsertedEvent() -= _row_inserted_event_token;
	_table_data_model->InnerModel()->RowRemovedEvent() -= _row_removed_event_token;
	_table_data_model->InnerModel()->DataChangeEvent() -= _data_change_event_token;
}

widget::Table::Table()
{
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

	UnsubscribeEvent();
	_table_data_model = std::shared_ptr<TableDataModelWrapper>{new TableDataModelWrapper{model}};
	_table->setModel(_table_data_model.get());
	SubscribeEvent();

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

void widget::Table::SetResizeModes(std::vector<QHeaderView::ResizeMode> resize_modes)
{
	_table->SetResizeModes(resize_modes);
}
