#pragma once
#include "qnamespace.h"
#include "qvariant.h"
#include <memory>
#include <widget/table/ITableDataModel.h>
#include <widget/table/Table.h>

class widget::Table::TableDataModel :
	public QAbstractTableModel
{
private:
	std::shared_ptr<widget::ITableDataModel> _model;

public:
	TableDataModel() = default;
	TableDataModel(std::shared_ptr<widget::ITableDataModel> model);

public:
	virtual int rowCount(QModelIndex const &parent = QModelIndex{}) const override;

	virtual int columnCount(QModelIndex const &parent = QModelIndex{}) const override;

	virtual QVariant data(QModelIndex const &index, int role = Qt::DisplayRole) const override;

	virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

	virtual void sort(int column, Qt::SortOrder order) override;

public:
	/**
	 * @brief 模型改变后如果 UI 没有更新，可以尝试调用本方法。
	 *
	 */
	void ModelHasChanged();
};
