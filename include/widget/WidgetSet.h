#pragma once
#include "base/container/ISet.h"
#include "base/container/Set.h"
#include "qwidget.h"
#include <memory>

namespace widget
{
	class WidgetSet final :
		public base::ISet<std::shared_ptr<QWidget>>
	{
	private:
		base::Set<std::shared_ptr<QWidget>> _set;

	public:
		/* #region 接口 */

		using base::ISet<std::shared_ptr<QWidget>>::Add;

		///
		/// @brief 向集合中添加一个元素。
		///
		/// @param item
		///
		/// @return 如果集合中原本没有该元素，则添加成功，返回 true, 否则返回 false.
		///
		virtual bool Add(std::shared_ptr<QWidget> const &item) override
		{
			return _set.Add(item);
		}

		///
		/// @brief 移除指定的元素。
		///
		/// @param item
		///
		/// @return 集合中有该元素，移除成功则返回 true, 否则返回 false.
		///
		virtual bool Remove(std::shared_ptr<QWidget> const &item) override
		{
			item->setParent(nullptr);
			return _set.Remove(item);
		}

		///
		/// @brief 清空元素。
		///
		/// @return
		///
		virtual void Clear() override
		{
			for (std::shared_ptr<QWidget> const &item : _set)
			{
				item->setParent(nullptr);
			}

			_set.Clear();
		}

		///
		/// @brief 检查是否存在指定元素。
		///
		/// @param item
		///
		/// @return
		///
		virtual bool Contains(std::shared_ptr<QWidget> const &item) const override
		{
			return _set.Contains(item);
		}

		///
		/// @brief 元素个数。
		///
		/// @return
		///
		virtual int64_t Count() const override
		{
			return _set.Count();
		}

		using base::IEnumerable<std::shared_ptr<QWidget> const>::GetEnumerator;

		///
		/// @brief 获取非 const 迭代器
		///
		/// @return
		///
		virtual std::shared_ptr<base::IEnumerator<std::shared_ptr<QWidget> const>> GetEnumerator() override
		{
			return _set.GetEnumerator();
		}

		/* #endregion */
	};

} // namespace widget
