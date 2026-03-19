#pragma once
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

		void Clear()
		{
			_resources.clear();
		}
	};

} // namespace widget
