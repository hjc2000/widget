#include "StreamIODevice.h" // IWYU pragma: keep
#include <iostream>

qint64 widget::StreamIODevice::readData(char *data, qint64 maxlen)
{
	try
	{
		base::Span span{
			reinterpret_cast<uint8_t *>(data),
			maxlen,
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
		base::ReadOnlySpan span{
			reinterpret_cast<uint8_t const *>(data),
			len,
		};

		_stream->Write(span);
		return len;
	}
	catch (std::exception const &e)
	{
		std::cerr << CODE_POS_STR + e.what() << std::endl;
		return -1;
	}
}
