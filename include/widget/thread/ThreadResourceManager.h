#pragma once
#include "base/container/Dictionary.h"
#include <cstdint>
#include <memory>

namespace widget
{
	///
	/// @brief 线程资源。
	///
	/// @note 只能在后台线程操作的且托管给后台线程的资源的管理器。
	/// 这些资源将在线程函数返回后销毁。
	///
	/// @note 后台线程会不断执行队列中的任务，执行到一个任务时，会向任务函数
	/// 传递本类对象。
	///
	class ThreadResourceManager final
	{
	private:
		base::Dictionary<int64_t, std::shared_ptr<void>> _resources{};

	public:
		///
		/// @brief 添加资源。
		///
		/// @param id 资源的 ID.
		/// @param resource 资源。
		///
		void Add(int64_t id, std::shared_ptr<void> const &resource)
		{
			_resources.Add(id, resource);
		}

		///
		/// @brief 获取资源。
		///
		/// @note 需要自行对应好 ID 和对象，避免将资源强制转换为错误的类型。
		///
		/// @param index
		/// @return
		///
		template <typename T>
		T &Get(int64_t index)
		{
			return *std::static_pointer_cast<T>(_resources.Get(index));
		}

		///
		/// @brief 移除资源。
		///
		/// @param index
		///
		void Remove(int64_t index)
		{
			_resources.Remove(index);
		}

		///
		/// @brief 清空所有资源。
		///
		void Clear()
		{
			_resources.Clear();
		}
	};

} // namespace widget
