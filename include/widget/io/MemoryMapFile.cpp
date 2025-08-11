#include "MemoryMapFile.h" // IWYU pragma: keep
#include <memory>

std::shared_ptr<base::memory_map_file::IMemoryMapFile> base::memory_map_file::OpenOrCreate(base::Path const &path)
{
	return std::shared_ptr<widget::MemoryMapFile>{new widget::MemoryMapFile{path}};
}
