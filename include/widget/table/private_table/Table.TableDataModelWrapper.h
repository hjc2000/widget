#pragma once
#include "base/IIdToken.h"
#include "widget/table/ITableDataModel.h"
#include "widget/table/Table.h"
#include "widget/table/TableSortingParameter.h"
#include <memory>

///
/// @brief 本库对外暴露的表格类 widget::Table 使用的是 widget::ITableDataModel，
/// 本类将 widget::ITableDataModel 对象包装为 QAbstractTableModel，这样才能被 qt
/// 表格类 QTableView 使用。
///
class widget::Table::TableDataModelWrapper final :
	public QAbstractTableModel
{
private:
	widget::Table::PrivateTable *_table_view = nullptr;
	std::shared_ptr<widget::ITableDataModel> _model;
	widget::TableSortingParameter _table_sorting_paremeter{};

	/* #region 订阅、取消订阅来自 widget::ITableDataModel 的事件 */

	base::SpIIdToken _model_reset_event_token;
	base::SpIIdToken _row_inserted_event_token;
	base::SpIIdToken _row_removed_event_token;
	base::SpIIdToken _data_change_event_token;

	///
	/// @brief 订阅 widget::ITableDataModel 对象的事件。
	///
	///
	void SubscribeEvents();

	///
	/// @brief 取消订阅 widget::ITableDataModel 对象的事件。
	///
	///
	void UnsubscribeEvents();

	/* #endregion */

public:
	///
	/// @brief 传入一个 widget::ITableDataModel 对象以被本对象包装。
	///
	/// @param model 要被包装的 widget::ITableDataModel 对象。禁止传入空指针。
	/// 传入空指针会引发异常。
	///
	TableDataModelWrapper(widget::Table::PrivateTable *table_view, std::shared_ptr<widget::ITableDataModel> const &model);

	~TableDataModelWrapper();

	/* #region 实现 QAbstractTableModel */

	///
	/// @brief 表格的行数。
	///
	/// @param parent
	///
	/// @return
	///
	virtual int rowCount(QModelIndex const &parent = QModelIndex{}) const override;

	///
	/// @brief 表格的列数。
	///
	/// @param parent
	///
	/// @return
	///
	virtual int columnCount(QModelIndex const &parent = QModelIndex{}) const override;

	virtual QVariant data(QModelIndex const &index, int role = Qt::DisplayRole) const override;

	virtual QVariant headerData(int section,
								Qt::Orientation orientation,
								int role = Qt::DisplayRole) const override;

	///
	/// @brief 排序回调。用户点击表头后，qt 框架会回调本方法。
	///
	/// @param column
	/// @param order
	///
	virtual void sort(int column, Qt::SortOrder order) override;

	/* #endregion */

	///
	/// @brief 当前的表格排序参数。
	///
	/// @note 每次 sort 方法被调用，都会记录参数。如果 sort 方法从来没被调用过，则是默认参数。
	///
	/// @return
	///
	widget::TableSortingParameter CurrentSortingParameter() const;

	///
	/// @brief 获取被本对象包装的 widget::ITableDataModel 对象。
	///
	/// @return
	///
	widget::ITableDataModel &InnerModel() const;
};
