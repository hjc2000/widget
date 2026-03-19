#pragma once
#include <cstdint>
#include <memory>
#include <vector>

namespace widget
{
	class ThreadResourceManager final
	{
	private:
		std::vector<std::shared_ptr<void>> _resources{};

	public:
		void Add(std::shared_ptr<void> const &resource)
		{
			_resources.push_back(resource);
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
