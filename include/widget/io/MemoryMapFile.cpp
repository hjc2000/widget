#include "MemoryMapFile.h" // IWYU pragma: keep
#include "base/string/define.h"
#include "widget/convert.h"
#include <memory>
#include <stdexcept>

std::shared_ptr<base::memory_map_file::IMemoryMapFile> base::memory_map_file::OpenOrCreate(base::Path const &path)
{
	return std::shared_ptr<widget::MemoryMapFile>{new widget::MemoryMapFile{path}};
}

widget::MemoryMapFile::MemoryMapFile(base::Path const &path)
{
	_file = std::shared_ptr<QFile>{new QFile{widget::ToQString(path.ToString())}};
	bool result = _file->open(QIODeviceBase::OpenModeFlag::ReadWrite);
	if (!result)
	{
		throw std::runtime_error{CODE_POS_STR + "打开失败。"};
	}
}

widget::MemoryMapFile::~MemoryMapFile()
{
	UnMapAll();
	_file->close();
}

base::Span widget::MemoryMapFile::Map(base::Range const &range)
{
	if (_file->size() < range.End())
	{
		Resize(range.End());
	}

	uint8_t *address = _file->map(range.Begin(),
								  range.Size(),
								  QFileDevice::MemoryMapFlag::NoOptions);

	if (address == nullptr)
	{
		throw std::runtime_error{CODE_POS_STR + "映射失败。"};
	}

	_mapped_address_set.insert(address);
	base::Span ret{address, range.Size()};
	return ret;
}

void widget::MemoryMapFile::UnMap(uint8_t *address)
{
	auto it = _mapped_address_set.find(address);
	if (it == _mapped_address_set.end())
	{
		throw std::invalid_argument{CODE_POS_STR + "非法地址。"};
	}

	_file->unmap(address);
	_mapped_address_set.erase(address);
}

void widget::MemoryMapFile::UnMapAll()
{
	for (uint8_t *address : _mapped_address_set)
	{
		_file->unmap(address);
	}
}
