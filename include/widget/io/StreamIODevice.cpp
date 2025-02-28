#include "StreamIODevice.h"
#include "base/stream/ReadOnlySpan.h"
#include "base/stream/Span.h"
#include "base/string/define.h"
#include <cstdint>
#include <exception>
#include <iostream>
#include <stdexcept>

qint64 widget::StreamIODevice::readData(char *data, qint64 maxlen)
{
	try
	{
		int32_t size = std::min<int64_t>(INT32_MAX, maxlen);

		base::Span span{
			reinterpret_cast<uint8_t *>(data),
			size,
		};

		return _stream->Read(span);
	}
	catch (std::exception const &e)
	{
		std::cerr << CODE_POS_STR + e.what() << std::endl;
		return -1;
	}
}

qint64 widget::StreamIODevice::writeData(char const *data, qint64 len)
{
	try
	{
		int64_t have_written = 0;

		while (have_written < len)
		{
			int32_t size = std::min<int64_t>(INT32_MAX, len - have_written);

			base::ReadOnlySpan span{
				reinterpret_cast<uint8_t const *>(data + have_written),
				size,
			};

			_stream->Write(span);
			have_written += size;
		}

		return have_written;
	}
	catch (std::exception const &e)
	{
		std::cerr << CODE_POS_STR + e.what() << std::endl;
		return -1;
	}
}

widget::StreamIODevice::StreamIODevice(std::shared_ptr<base::Stream> const &stream)
	: _stream(stream)
{
	if (_stream == nullptr)
	{
		throw std::invalid_argument{CODE_POS_STR + "stream 不能是空指针。"};
	}
}
