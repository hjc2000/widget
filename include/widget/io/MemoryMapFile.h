#pragma once
#include "base/filesystem/IMemoryMapFile.h"
#include "base/filesystem/Path.h"
#include "qdir.h"
#include <cstdint>
#include <memory>
#include <vector>

namespace widget
{
	class MemoryMapFile final :
		public base::memory_map_file::IMemoryMapFile
	{
	private:
		std::shared_ptr<QFile> _file;
		std::vector<uint8_t *> _mapped_address_vector;

	public:
		MemoryMapFile(base::Path const &path);

		~MemoryMapFile();

		///
		/// @brief 将文件指定范围映射为进程地址空间中的内存块。
		///
		/// @param range
		/// @return
		///
		virtual void *Map(base::Range const &range) override;

		///
		/// @brief 调整文件大小。
		///
		/// @param size
		///
		virtual void Resize(int64_t size) override
		{
			_file->resize(size);
		}
	};

} // namespace widget
