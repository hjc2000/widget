#pragma once
#include "base/filesystem/IMemoryMapFile.h"
#include "base/filesystem/Path.h"
#include "qdir.h"
#include <cstdint>
#include <memory>
#include <set>

namespace widget
{
	class MemoryMapFile final :
		public base::memory_map_file::IMemoryMapFile
	{
	private:
		std::shared_ptr<QFile> _file;
		std::set<uint8_t *> _mapped_address_set;

	public:
		MemoryMapFile(base::Path const &path);

		~MemoryMapFile();

		///
		/// @brief 将文件指定范围映射为进程地址空间中的内存块。
		///
		/// @note 指定的范围如果超过了文件范围，会自动扩大文件。
		///
		/// @param range
		/// @return
		///
		virtual base::Span Map(base::Range const &range) override;

		///
		/// @brief 取消映射。
		///
		/// @param address 传入 Map 方法返回的 base::Span 的 Buffer 属性。
		///
		virtual void UnMap(uint8_t *address) override;

		///
		/// @brief 取消所有映射。
		///
		///
		virtual void UnMapAll() override;

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
