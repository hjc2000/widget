#include "Table.h"
#include <Table.CustomItemDelegate.h>
#include <Table.PrivateTable.h>
#include <Table.TableDataModel.h>

widget::Table::Table()
{
	_table = std::shared_ptr<PrivateTable>{new PrivateTable{}};
	_table_data_model = std::shared_ptr<TableDataModel>{new TableDataModel{}};

	_layout.AddWidget(_table.get());
}

void widget::Table::SetModel(std::shared_ptr<widget::ITableDataModel> const &model)
{
	_table->horizontalHeader()->setVisible(model->HasColumnTitle());
	_table->verticalHeader()->setVisible(model->HasRowTitle());

	_table_data_model = std::shared_ptr<TableDataModel>{new TableDataModel{model}};
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
