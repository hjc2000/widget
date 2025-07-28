#pragma once
#include "base/stream/Stream.h"
#include "base/string/define.h"
#include "QIODevice"
#include <iostream>

namespace widget
{
	///
	/// @brief 将 base::Stream 包装成 QIODevice
	///
	///
	class StreamIODevice final :
		public QIODevice
	{
	private:
		std::shared_ptr<base::Stream> _stream;

		virtual qint64 readData(char *data, qint64 maxlen) override
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

		virtual qint64 writeData(char const *data, qint64 len) override
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

	public:
		///
		/// @brief 构造函数。
		///
		/// @param stream 传入一个流，将被包装成 QIODevice.
		///
		StreamIODevice(std::shared_ptr<base::Stream> const &stream)
			: _stream(stream)
		{
			if (_stream == nullptr)
			{
				throw std::invalid_argument{CODE_POS_STR + "stream 不能是空指针。"};
			}
		}
	};

} // namespace widget
