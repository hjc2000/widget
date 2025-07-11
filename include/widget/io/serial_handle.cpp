#include "serial_handle.h" // IWYU pragma: keep

///
/// @brief 扫描可用的串口。
///
/// @return std::vector<std::string>
///
std::vector<std::string> base::serial::scan_serials();

/* #region open */

///
/// @brief 通过串口名称打开串口。
///
/// @param name 串口名称。
///		@note 通用操作系统中使用这种方式。
///
/// @return std::shared_ptr<base::serial::serial_handle>
///
std::shared_ptr<base::serial::serial_handle> base::serial::open(std::string const &name);

///
/// @brief 通过串口 ID 打开串口。
///
/// @param id 串口 ID.
/// 	@note 单片机中使用这种方式。例如想要打开 UART1 就传入 1.
///
/// @return std::shared_ptr<base::serial::serial_handle>
///
std::shared_ptr<base::serial::serial_handle> base::serial::open(uint32_t id);

/* #endregion */

/* #region 启动串口 */

///
/// @brief 启动串口。
///
/// @param h
/// @param direction
/// @param baud_rate
/// @param data_bits
/// @param parity
/// @param stop_bits
/// @param hardware_flow_control
///
void base::serial::start(base::serial::serial_handle &h,
						 base::serial::Direction direction,
						 base::serial::BaudRate const &baud_rate,
						 base::serial::DataBits const &data_bits,
						 base::serial::Parity parity,
						 base::serial::StopBits stop_bits,
						 base::serial::HardwareFlowControl hardware_flow_control);

/* #endregion */

/* #region 串口属性 */

///
/// @brief 获取串口名称。
///
/// @param h
/// @return std::string
///
std::string base::serial::name(base::serial::serial_handle &h);

///
/// @brief 数据传输方向。
///
/// @param h
/// @return base::serial::Direction
///
base::serial::Direction base::serial::direction(base::serial::serial_handle &h);

///
/// @brief 波特率。
///
/// @param h
/// @return uint32_t
///
uint32_t base::serial::baud_rate(base::serial::serial_handle &h);

///
/// @brief 数据位的个数。
///
/// @param h
/// @return uint8_t
///
uint8_t base::serial::data_bits(base::serial::serial_handle &h);

///
/// @brief 校验位。
///
/// @param h
/// @return base::serial::Parity
///
base::serial::Parity base::serial::parity(base::serial::serial_handle &h);

///
/// @brief 停止位个数。
///
/// @param h
/// @return base::serial::StopBits
///
base::serial::StopBits base::serial::stop_bits(base::serial::serial_handle &h);

///
/// @brief 硬件流控。
///
/// @param h
/// @return base::serial::HardwareFlowControl
///
base::serial::HardwareFlowControl base::serial::hardware_flow_control(base::serial::serial_handle &h);

/* #endregion */

///
/// @brief 从串口读取数据
///
/// @param h
/// @param span
///
/// @return int32_t 成功读取的字节数。永远不应该返回 0. 应该将本函数实现为等同 Stream
/// 的 Read 方法。
///
int32_t base::serial::read(base::serial::serial_handle &h, base::Span const &span);

///
/// @brief 向串口写入数据。
///
/// @param h
/// @param span
///
void base::serial::write(base::serial::serial_handle &h, base::ReadOnlySpan const &span);

///
/// @brief 冲洗串口。
///
/// @param h
///
void base::serial::flush(base::serial::serial_handle &h);
