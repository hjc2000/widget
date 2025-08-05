#include "Table.TableDataModelWrapper.h"
#include "base/math/PositionRange.h"
#include "base/math/RowCount.h"
#include "base/math/RowIndex.h"
#include "base/string/define.h"
#include "qscrollbar.h"
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

		// 插入行后需要进行像素补偿，防止视窗内的行发生移动。
		// 我写了一篇博客：
		// https://blog.csdn.net/qq_36148047/article/details/149935903?sharetype=blogdetail&sharerId=149935903&sharerefer=PC&sharesource=qq_36148047&spm=1011.2480.3001.8118
		if (_table_view->verticalScrollBar()->maximum() == 0)
		{
			return;
		}

		int first_visible_row = _table_view->rowAt(0);
		if (args.RowIndex().Value() > first_visible_row)
		{
			return;
		}

		// 插入点的行的当前像素位置。
		int start_row_position = _table_view->rowViewportPosition(args.RowIndex().Value());

		// 插入后获取原来的插入点处的行的现在的像素位置。
		int end_row_position = _table_view->rowViewportPosition(args.RowIndex().Value() + args.RowCount().Value());

		// 通过定时器延迟执行滚动条调整。等到表格重绘后执行滚动才能滚到正确的位置。
		QTimer::singleShot(
			0,
			this,
			[this, end_row_position, start_row_position]
			{
				int delta_position = end_row_position - start_row_position;
				int new_scroll_bar_position = _table_view->verticalScrollBar()->value() + delta_position;
				_table_view->verticalScrollBar()->setValue(new_scroll_bar_position);
			});
	};

	_row_removed_event_token = _model->RowRemovedEvent() += [this](widget::ITableDataModel::RowRemovedEventArgs const &args)
	{
		beginRemoveRows(QModelIndex{},
						args.RowIndex().Value(),
						args.RowIndex().Value() + args.RowCount().Value() - 1);

		endRemoveRows();

		// 删除行后需要进行像素补偿，防止视窗内的行发生移动。
		if (_table_view->verticalScrollBar()->maximum() == 0)
		{
			return;
		}

		int first_visible_row = _table_view->rowAt(0);
		if (args.RowIndex().Value() > first_visible_row)
		{
			return;
		}

		int start_row_position = _table_view->rowViewportPosition(args.RowIndex().Value());

		int end_row_position = _table_view->rowViewportPosition(args.RowIndex().Value() + args.RowCount().Value());

		// 通过定时器延迟执行滚动条调整。等到表格重绘后执行滚动才能滚到正确的位置。
		QTimer::singleShot(
			0,
			this,
			[this, end_row_position, start_row_position]
			{
				int delta_position = end_row_position - start_row_position;
				int new_scroll_bar_position = _table_view->verticalScrollBar()->value() - delta_position;
				_table_view->verticalScrollBar()->setValue(new_scroll_bar_position);
			});
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

widget::Table::TableDataModelWrapper::TableDataModelWrapper(QTableView *table_view,
															std::shared_ptr<widget::ITableDataModel> const &model)
{
	if (model == nullptr)
	{
		throw std::invalid_argument{CODE_POS_STR + "禁止传入空指针。"};
	}

	_table_view = table_view;
	_model = model;
	SubscribeEvents();
}

widget::Table::TableDataModelWrapper::~TableDataModelWrapper()
{
	UnsubscribeEvents();
}

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
