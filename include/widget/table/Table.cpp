#include "Table.h"
#include <Table.CustomItemDelegate.h>
#include <Table.PrivateTable.h>

widget::Table::Table()
{
	_table = std::shared_ptr<PrivateTable>{new PrivateTable{}};
	_layout.AddWidget(_table.get());
}

void widget::Table::SetModel(QAbstractItemModel *model)
{
	_table->setModel(model);
}

void widget::Table::SetModel(QAbstractItemModel *model, std::vector<QHeaderView::ResizeMode> resize_modes)
{
	_table->setModel(model, resize_modes);
}

void widget::Table::DataModelHasChanged()
{
	_table->DataModelHasChanged();
}

void widget::Table::SetResizeModes(std::vector<QHeaderView::ResizeMode> resize_modes)
{
	_table->SetResizeModes(resize_modes);
}
