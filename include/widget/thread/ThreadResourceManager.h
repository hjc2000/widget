#pragma once
#include <cstdint>
#include <map>
#include <memory>
#include <utility>

namespace widget
{
	class ThreadResourceManager final
	{
	private:
		std::map<int64_t, std::shared_ptr<void>> _resources{};

	public:
		void Add(int64_t id, std::shared_ptr<void> const &resource)
		{
			_resources.insert(std::pair<int64_t, std::shared_ptr<void>>{id, resource});
		}

		template <typename T>
		T &Get(int64_t index)
		{
			return *std::static_pointer_cast<T>(_resources[index]);
		}

		void Clear()
		{
			_resources.clear();
		}
	};

} // namespace widget
