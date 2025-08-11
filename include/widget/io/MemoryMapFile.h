#pragma once
#include "base/filesystem/IMemoryMapFile.h"
#include "base/filesystem/Path.h"
#include "base/string/define.h"
#include "qdir.h"
#include "widget/convert.h"
#include <cstdint>
#include <memory>
#include <stdexcept>
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
		MemoryMapFile(base::Path const &path)
		{
			_file = std::shared_ptr<QFile>{new QFile{widget::ToQString(path.ToString())}};
			bool result = _file->open(QIODeviceBase::OpenModeFlag::ReadWrite);
			if (!result)
			{
				throw std::runtime_error{CODE_POS_STR + "打开失败。"};
			}
		}

		~MemoryMapFile()
		{
			for (uint8_t *address : _mapped_address_vector)
			{
				_file->unmap(address);
			}

			_file->close();
		}

		///
		/// @brief 将文件指定范围映射为进程地址空间中的内存块。
		///
		/// @param range
		/// @return
		///
		virtual void *Map(base::Range const &range) override
		{
			uint8_t *address = _file->map(range.Begin(), range.Size(), QFileDevice::MemoryMapFlag::NoOptions);
			if (address == nullptr)
			{
				throw std::runtime_error{CODE_POS_STR + "映射失败。"};
			}

			_mapped_address_vector.push_back(address);
			return address;
		}

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
