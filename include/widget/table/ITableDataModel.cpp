#include "ITableDataModel.h"
#include <string>

QString widget::ITableDataModel::RowTitle(int row) const
{
	std::string str = "行 " + std::to_string(row);
	return QString{str.c_str()};
}

QString widget::ITableDataModel::ColumnTitle(int column) const
{
	std::string str = "列 " + std::to_string(column);
	return QString{str.c_str()};
}
