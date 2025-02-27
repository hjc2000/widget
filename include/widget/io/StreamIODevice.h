#pragma once
#include <base/stream/Stream.h>
#include <memory>
#include <qiodevice.h>

namespace widget
{
	/**
	 * @brief 将 base::Stream 包装成 QIODevice
	 *
	 */
	class StreamIODevice :
		public QIODevice
	{
	private:
		std::shared_ptr<base::Stream> _stream;

		virtual qint64 readData(char *data, qint64 maxlen) override;

		virtual qint64 writeData(char const *data, qint64 len) override;

	public:
		StreamIODevice(std::shared_ptr<base::Stream> const &stream);
	};
} // namespace widget
