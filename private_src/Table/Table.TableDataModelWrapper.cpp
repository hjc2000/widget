#include "Table.TableDataModelWrapper.h"

widget::Table::TableDataModelWrapper::TableDataModelWrapper(std::shared_ptr<widget::ITableDataModel> const &model)
	: _model(model)
{
}

int widget::Table::TableDataModelWrapper::rowCount(QModelIndex const &parent) const
{
	try
	{
		if (_model == nullptr)
		{
			return 0;
		}

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
	try
	{
		if (_model == nullptr)
		{
			return 0;
		}

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
	try
	{
		if (_model == nullptr)
		{
			return QVariant{};
		}

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
	try
	{
		if (_model == nullptr)
		{
			return QVariant{};
		}

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
	if (column < 0 || column > columnCount())
	{
		return;
	}

	_table_sorting_paremeter = widget::TableSortingParameter{column, order};

	try
	{
		if (_model == nullptr)
		{
			return;
		}

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
