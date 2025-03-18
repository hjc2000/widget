#include "Table.h"
#include <Table.CustomItemDelegate.h>
#include <Table.PrivateTable.h>
#include <Table.TableDataModelWrapper.h>

widget::Table::Table()
{
	_table = std::shared_ptr<PrivateTable>{new PrivateTable{}};
	_layout.AddWidget(_table.get());
}

void widget::Table::SetModel(std::shared_ptr<widget::ITableDataModel> const &model)
{
	// 有列标题则让水平的表格头可见。
	_table->horizontalHeader()->setVisible(model->HasColumnTitle());

	// 有行标题则让垂直的表格头可见。
	_table->verticalHeader()->setVisible(model->HasRowTitle());

	_table_data_model = std::shared_ptr<TableDataModelWrapper>{new TableDataModelWrapper{model}};
	_table->setModel(_table_data_model.get());
}

void widget::Table::SetModel(std::shared_ptr<widget::ITableDataModel> const &model,
							 std::vector<QHeaderView::ResizeMode> resize_modes)
{
	SetModel(model);
	SetResizeModes(resize_modes);
}

void widget::Table::DataModelHasChanged()
{
	_table->DataModelHasChanged();
}

void widget::Table::SetResizeModes(std::vector<QHeaderView::ResizeMode> resize_modes)
{
	_table->SetResizeModes(resize_modes);
}
