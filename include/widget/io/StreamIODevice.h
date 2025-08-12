#pragma once
#include "base/stream/Stream.h"
#include "base/string/define.h"
#include "QIODevice"

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

		virtual qint64 readData(char *data, qint64 maxlen) override;

		virtual qint64 writeData(char const *data, qint64 len) override;

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
