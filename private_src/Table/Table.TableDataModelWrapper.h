#pragma once
#include <widget/table/ITableDataModel.h>
#include <widget/table/Table.h>
#include <widget/table/TableSortingParameter.h>

///
/// @brief 本库对外暴露的表格类 widget::Table 使用的是 widget::ITableDataModel，
/// 本类将 widget::ITableDataModel 对象包装为 QAbstractTableModel，这样才能被 qt
/// 表格类 QTableView 使用。
///
class widget::Table::TableDataModelWrapper :
	public QAbstractTableModel
{
private:
	std::shared_ptr<widget::ITableDataModel> _model;
	widget::TableSortingParameter _table_sorting_paremeter{};

public:
	TableDataModelWrapper(std::shared_ptr<widget::ITableDataModel> const &model);

	///
	/// @brief 表格的行数。
	///
	/// @param parent
	/// @return int
	///
	virtual int rowCount(QModelIndex const &parent = QModelIndex{}) const override;

	///
	/// @brief 表格的列数。
	///
	/// @param parent
	/// @return int
	///
	virtual int columnCount(QModelIndex const &parent = QModelIndex{}) const override;

	virtual QVariant data(QModelIndex const &index, int role = Qt::DisplayRole) const override;
	virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

	///
	/// @brief 排序回调。用户点击表头后，qt 框架会回调本方法。
	///
	/// @param column
	/// @param order
	///
	virtual void sort(int column, Qt::SortOrder order) override;

	///
	/// @brief 当前的表格排序参数。
	///
	/// @note 每次 sort 方法被调用，都会记录参数。如果 sort 方法从来没被调用过，则是默认参数。
	///
	/// @return widget::TableSortingParameter
	///
	widget::TableSortingParameter CurrentSortingParameter() const;
};
