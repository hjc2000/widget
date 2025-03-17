#include "ITableDataModel.h"

QString widget::ITableDataModel::RowTitle(int row) const
{
	std::string str = std::to_string(row);
	return QString{str.c_str()};
}

QString widget::ITableDataModel::ColumnTitle(int column) const
{
	std::string str = std::to_string(column);
	return QString{str.c_str()};
}
