#include "Table.TableDataModelWrapper.h"
#include "base/string/define.h"
#include <string>

widget::Table::TableDataModelWrapper::TableDataModelWrapper(std::shared_ptr<widget::ITableDataModel> const &model)
	: _model(model)
{
}

int widget::Table::TableDataModelWrapper::rowCount(QModelIndex const &parent) const
{
	if (_model == nullptr)
	{
		return 0;
	}

	try
	{
		return _model->RowCount();
	}
	catch (std::exception const &e)
	{
		std::cerr << CODE_POS_STR + e.what() << std::endl;
	}
	catch (...)
	{
		std::cerr << CODE_POS_STR + "发生了未知异常。" << std::endl;
	}

	return 0;
}

int widget::Table::TableDataModelWrapper::columnCount(QModelIndex const &parent) const
{
	if (_model == nullptr)
	{
		return 0;
	}

	try
	{
		return _model->ColumnCount();
	}
	catch (std::exception const &e)
	{
		std::cerr << CODE_POS_STR + e.what() << std::endl;
	}
	catch (...)
	{
		std::cerr << CODE_POS_STR + "发生了未知异常。" << std::endl;
	}

	return 0;
}

QVariant widget::Table::TableDataModelWrapper::data(QModelIndex const &index, int role) const
{
	if (_model == nullptr)
	{
		return QVariant{};
	}

	try
	{
		if (role != Qt::ItemDataRole::DisplayRole)
		{
			return QVariant{};
		}

		return QVariant{_model->Data(index.row(), index.column())};
	}
	catch (std::exception const &e)
	{
		std::cerr << CODE_POS_STR + e.what() << std::endl;
	}
	catch (...)
	{
		std::cerr << CODE_POS_STR + "发生了未知异常。" << std::endl;
	}

	return QVariant{};
}

QVariant widget::Table::TableDataModelWrapper::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (_model == nullptr)
	{
		return QVariant{};
	}

	try
	{
		if (role != Qt::ItemDataRole::DisplayRole)
		{
			return QVariant{};
		}

		if (orientation == Qt::Orientation::Vertical && _model->HasRowTitle())
		{
			return QVariant{_model->RowTitle(section)};
		}

		if (orientation == Qt::Orientation::Horizontal && _model->HasColumnTitle())
		{
			return QVariant{_model->ColumnTitle(section)};
		}

		return QVariant{};
	}
	catch (std::exception const &e)
	{
		std::cerr << CODE_POS_STR + e.what() << std::endl;
	}
	catch (...)
	{
		std::cerr << CODE_POS_STR + "发生了未知异常。" << std::endl;
	}

	return QVariant{};
}

void widget::Table::TableDataModelWrapper::sort(int column, Qt::SortOrder order)
{
	if (_model == nullptr)
	{
		return;
	}

	if (column < 0 || column > columnCount())
	{
		std::cout << CODE_POS_STR << "尝试以列号：" << std::to_string(column) << " 排序，不存在该列，返回。" << std::endl;
		return;
	}

	_table_sorting_paremeter = widget::TableSortingParameter{column, order};

	try
	{
		_model->Sort(column, order == Qt::SortOrder::AscendingOrder);
	}
	catch (std::exception const &e)
	{
		std::cerr << CODE_POS_STR + e.what() << std::endl;
	}
	catch (...)
	{
		std::cerr << CODE_POS_STR + "发生了未知异常。" << std::endl;
	}

	// 排序完成后通知视图刷新
	dataChanged(createIndex(0, 0),
				createIndex(rowCount() - 1, columnCount() - 1));
}

widget::TableSortingParameter widget::Table::TableDataModelWrapper::CurrentSortingParameter() const
{
	return _table_sorting_paremeter;
}

void widget::Table::TableDataModelWrapper::RowsInserted(int row, int count)
{
	beginInsertRows(QModelIndex{}, row, row + count - 1);
	endInsertRows();
}

void widget::Table::TableDataModelWrapper::RowsRemoved(int row, int count)
{
	beginRemoveRows(QModelIndex{}, row, row + count - 1);
	endRemoveRows();
}
