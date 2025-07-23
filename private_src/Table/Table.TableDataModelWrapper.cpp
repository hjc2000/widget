#include "Table.TableDataModelWrapper.h"
#include "base/math/PositionRange.h"
#include "base/math/RowCount.h"
#include "base/math/RowIndex.h"
#include "base/string/define.h"
#include <iostream>
#include <stdexcept>
#include <string>

/* #region 订阅、取消订阅来自 widget::ITableDataModel 的事件 */

void widget::Table::TableDataModelWrapper::SubscribeEvents()
{
	_model_reset_event_token = _model->ModelRestEvent() += [this]()
	{
		beginResetModel();
		endResetModel();
	};

	_row_inserted_event_token = _model->RowInsertedEvent() += [this](widget::ITableDataModel::RowInsertedEventArgs const &args)
	{
		beginInsertRows(QModelIndex{},
						args.RowIndex().Value(),
						args.RowIndex().Value() + args.RowCount().Value() - 1);

		endInsertRows();
	};

	_row_removed_event_token = _model->RowRemovedEvent() += [this](base::RowIndex const &row_index, base::RowCount const &row_count)
	{
		beginRemoveRows(QModelIndex{},
						row_index.Value(),
						row_index.Value() + row_count.Value() - 1);

		endRemoveRows();
	};

	_data_change_event_token = _model->DataChangeEvent() += [this](base::PositionRange<int32_t> const &range)
	{
		auto start = createIndex(range.Start().Y(), range.Start().X());
		auto end = createIndex(range.End().Y(), range.End().X());
		dataChanged(start, end);
	};
}

void widget::Table::TableDataModelWrapper::UnsubscribeEvents()
{
	_model->ModelRestEvent() -= _model_reset_event_token;
	_model->RowInsertedEvent() -= _row_inserted_event_token;
	_model->RowRemovedEvent() -= _row_removed_event_token;
	_model->DataChangeEvent() -= _data_change_event_token;
}

/* #endregion */

/* #region 生命周期 */

widget::Table::TableDataModelWrapper::TableDataModelWrapper(std::shared_ptr<widget::ITableDataModel> const &model)
{
	if (model == nullptr)
	{
		throw std::invalid_argument{CODE_POS_STR + "禁止传入空指针。"};
	}

	_model = model;
	SubscribeEvents();
}

widget::Table::TableDataModelWrapper::~TableDataModelWrapper()
{
	UnsubscribeEvents();
}

/* #endregion */

/* #region 实现 QAbstractTableModel */

int widget::Table::TableDataModelWrapper::rowCount(QModelIndex const &parent) const
{
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

QVariant widget::Table::TableDataModelWrapper::headerData(int section,
														  Qt::Orientation orientation,
														  int role) const
{
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
	if (column < 0 || column >= columnCount())
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
}

/* #endregion */

widget::TableSortingParameter widget::Table::TableDataModelWrapper::CurrentSortingParameter() const
{
	return _table_sorting_paremeter;
}

widget::ITableDataModel &widget::Table::TableDataModelWrapper::InnerModel() const
{
	return *_model;
}
