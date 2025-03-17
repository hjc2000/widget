#pragma once
#include <widget/table/ITableDataModel.h>
#include <widget/table/Table.h>

///
/// @brief 本库对外暴露的表格类 widget::Table 使用的是 widget::ITableDataModel，
/// 本类将 widget::ITableDataModel 对象包装为 QAbstractTableModel，这样才能被 qt
/// 表格类 QTableView 使用。
///
class widget::Table::TableDataModel :
	public QAbstractTableModel
{
private:
	std::shared_ptr<widget::ITableDataModel> _model;

public:
	TableDataModel(std::shared_ptr<widget::ITableDataModel> const &model);

	virtual int rowCount(QModelIndex const &parent = QModelIndex{}) const override;
	virtual int columnCount(QModelIndex const &parent = QModelIndex{}) const override;

	virtual QVariant data(QModelIndex const &index, int role = Qt::DisplayRole) const override;
	virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

	virtual void sort(int column, Qt::SortOrder order) override;
};
