#pragma once

#include "ob2types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \if English
 *
 * @brief Set the device's installation (go-live) callback
 * @brief After setting the callback, when a new device is admitted and the driver loading is completed, the set callback function will be called, and the user
 * can open the device through the callback information
 *
 * @param[in] context_handle context handle
 * @param[in] device_installed_cb Device installation callback function
 * @param[in] user_data User-defined data, which is returned as-is when device_installed_cb is called
 * @param[out] status Output function execution status
 *
 * \else
 *
 * @brief 设置设备安装（上线）回调
 * @brief 设置回调后，当有新设备接入并完成驱动加载后，会调用设置的回调函数，此时用户可以通过回调的信息打开设备
 *
 * @param[in] context_handle context 句柄
 * @param[in] device_installed_cb 设备安装回调函数
 * @param[in] user_data 用户自定义数据，会在调用 device_installed_cb 时原样返回
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_context_set_device_installed_callback(ob2_context_t context_handle, ob2_device_info_cb_t device_installed_cb, void *user_data, ob2_status_t *status);
#define ob2_device_set_installed_callback ob2_context_set_device_installed_callback

/**
 * \if English
 *
 * @brief Set a callback for device removal (disconnection).
 * @brief After the callback is set, when a device is disconnected, the set callback function is immediately called, and the callback function sends back the
 * information of the disconnected device.
 *
 * @attention If the disconnected device is an open-ended device, access to the device should be stopped immediately and the device should be turned off.
 *
 * @param[in] context_handle context handle
 * @param[in] device_removed_cb Callback function for device removal
 * @param[in] user_data User-defined data, which is returned as-is when device_removed_cb is called
 * @param[out] status Output function execution status
 *
 * \else
 *
 * @brief 设置设备移除（掉线）回调
 * @brief 设置回调后，当有设备出现掉线情况，会立即调用设置的回调函数，回调函数会传会掉线设备的信息。
 *
 * @attention 出现设备掉线后，如果掉线的设备是已打开的设备，应立即停止对该设备的访问，并关闭设备。
 *
 * @param[in] context_handle context 句柄
 * @param[in] device_removed_cb 设备移除回调函数
 * @param[in] user_data 用户自定义数据，会在调用 device_removed_cb 时原样返回
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_context_set_device_removed_callback(ob2_context_t context_handle, ob2_device_info_cb_t device_removed_cb, void *user_data, ob2_status_t *status);
#define ob2_device_set_removed_callback ob2_context_set_device_removed_callback

/**
 * \if English
 *
 * @brief Gets the number of installed (live) devices
 *
 * @param[in] context_handle context handle
 * @param[out] status Output function execution status
 * @return uint32_t Returns the number of devices currently installed
 *
 * \else
 *
 * @brief 获取已安装（上线）的设备数量
 *
 * @param[in] context_handle context 句柄
 * @param[out] status 返回函数调用状态
 * @return uint32_t 返回当前已安装的设备数量
 *
 * \endif
 */
uint32_t ob2_context_get_installed_device_count(ob2_context_t context_handle, ob2_status_t *status);
#define ob2_device_get_installed_count ob2_context_get_installed_device_count

/**
 * \if English
 *
 * @brief Get the installed device information by the index number
 *
 * @attention The @index number is in the range [0, count-1] (count is returned by @ref ob2_context_get_installed_device_count), passing in a numeric value
 * outside the range, the ::OB2_STATUS_LOGIC_ERROR will be returned via @status
 * @attention The installed device information only has some basic information (PID, SN, URL, etc.), and the detailed device information needs to be obtained
 * through the ob2_device_get_info interface after opening the device
 *
 * @param[in] context_handle context handle
 * @param[in] index The index number of the device
 * @param[out] status Output function execution status
 * @return ob2_device_installation_info_t Returns information about currently installed devices
 *
 * \else
 *
 * @brief 通过索引号获取安装设备信息
 *
 * @attention 索引号 @index 范围为 [0, count-1] (count 通过 @ref ob2_context_get_installed_device_count 返回），传入范围外的数值
 *  将通过 @status 返回 ::OB2_STATUS_LOGIC_ERROR
 * @attention 安装设备信息仅有一些基础信息（PID、SN、URL 等），详细的设备信息需要打开设备后通过 @ref ob2_device_get_info 接口获取
 *
 * @param[in] context_handle context 句柄
 * @param[in] index 设备索引号
 * @param[out] status 返回函数调用状态
 * @return ob2_device_installation_info_t 返回当前已安装的设备信息
 *
 * \endif
 */
ob2_device_installation_info_t ob2_context_get_installed_device_info(ob2_context_t context_handle, uint32_t index, ob2_status_t *status);
#define ob2_device_get_installation_info ob2_context_get_installed_device_info

/**
 * \if English
 *
 * @brief Turn on the device by index number
 * @brief A device represents a communication connection to a physical device through which it can be accessed and controlled.
 *
 * @attention The @index number is in the range [0, count-1] (count is returned by @ref ob2_context_get_installed_device_count), passing in a numeric value
 * outside the range The ::OB2_STATUS_LOGIC_ERROR will be returned via @status
 * @attention It is not safe to open a device through the index number, and a new device installation or a device disconnection may cause the device bound to
 * the @index number to change, and may even cause the index to go out of range and report an error.
 * @ref ob2_context_open_device_by_serial_number and @ref ob2_context_open_device_by_url function are recommended.
 * @attention After the device is successfully opened, if you no longer need to access the device, you need to call @ref ob2_device_close to close and release
 * the device handle, otherwise it will cause a memory leak.
 *
 * @param[in] context_handle  context handle
 * @param[in] index The index number of the device. The default device (the first device in an installed device) can be opened by passing in
 * ::OB2_DEFAULT_DEVICE
 * @param[out] status Output function execution status
 * @return ob2_device_t Returns an open device handle
 *
 * \else
 *
 * @brief 通过索引号打开设备
 * @brief 设备代表着与物理设备的通信连接，可通过设备访问和控制物理设备。
 *
 * @attention 索引号 @index 范围为 [0, count-1] (count 通过 @ref ob2_context_get_installed_device_count 返回），传入范围外的数值
 *  将通过 @status 返回 ::OB2_STATUS_LOGIC_ERROR 。
 * @attention 通过索引号打开设备是不安全的，新设备安装或设备掉线都可能会导致索引号绑定的设备发生改变，甚至可能会导致 @index 超出范围而报错。
 *  推荐使用 @ref ob2_context_open_device_by_serial_number 和 @ref ob2_context_open_device_by_url 接口。
 * @attention 成功打开设备后，如果不需要再对设备进行访问，需要调用 @ref ob2_device_close 关闭并释放设备句柄，否则会导致内存泄漏。
 *
 * @param[in] context_handle  context 句柄
 * @param[in] index 设备索引号。可通过传入 ::OB2_DEFAULT_DEVICE 打开默认设备（已安装的设备中第一个设备）
 * @param[out] status 返回函数调用状态
 * @return ob2_device_t 返回已打开的设备句柄
 *
 * \endif
 */
ob2_device_t ob2_context_open_device(ob2_context_t context_handle, uint32_t index, ob2_status_t *status);
#define ob2_device_open ob2_context_open_device

/**
 * \if English
 *
 * @brief Turn on the device by serial number
 *
 * @attention If no match for @serial_number is found among the installed devices, a @status is returned with ::OB2_STATUS_RUNTIME_ERROR and a device handle
 * returned as NULL.
 * @attention After the device is successfully opened, if you no longer need to access the device, you need to call @ref ob2_device_close to close and release
 * the device handle, otherwise it will cause a memory leak.
 *
 * @param[in] context_handle  context handle
 * @param[in] serial_number The serial number of the device, which can be obtained through the device installation information or through the serial number
 * pasted on the device body
 * @param[out] status Output function execution status
 * @return ob2_device_t Returns a device handle that has been opened
 *
 * \else
 *
 * @brief 通过序列号打开设备
 *
 * @attention 如果已安装的设备中未找到与 @serial_number 相匹配的设备将会通过 @status 返回 ::OB2_STATUS_RUNTIME_ERROR ，同时返回设备句柄为 NULL。
 * @attention 成功打开设备后，如果不需要再对设备进行访问，需要调用 @ref ob2_device_close 关闭并释放设备句柄，否则会导致内存泄漏。
 *
 * @param[in] context_handle  context 句柄
 * @param[in] serial_number 设备序列号，可通过设备安装信息获取或通过设备机身粘贴的序列号获取
 * @param[out] status 返回函数调用状态
 * @return ob2_device_t 返回已打开的设备句柄
 *
 * \endif
 */
ob2_device_t ob2_context_open_device_by_serial_number(ob2_context_t context_handle, const char *serial_number, ob2_status_t *status);
#define ob2_device_open_by_serial_number ob2_context_open_device_by_serial_number

/**
 * \if English
 *
 * @brief Open the device by URL
 *
 * @attention The URL is the path assigned by the operating system after the device is connected to the host, and is the unique identification of the device
 * installed on the current host. But the same device is on different hosts or even the same one The URL may be different depending on the time and interface
 * access of the host.
 * @attention If no match for @url is found among the installed devices, a @status is returned with ::OB2_STATUS_RUNTIME_ERROR and a device handle returned as
 * NULL.
 * @attention After the device is successfully opened, if you no longer need to access the device, you need to call @ref ob2_device_close to close and release
 * the device handle, otherwise it will cause a memory leak.
 *
 * @param[in] context_handle  context handle
 * @param[in] url The path to the device installation
 * @param[out] status Output function execution status
 * @return ob2_device_t Returns a device handle that has been opened
 *
 * \else
 *
 * @brief 通过 URL 打开设备
 *
 * @attention URL 是设备接入主机后由操作系统分配的路径，是再当前主机上已安装的设备的唯一标识。但是同一台设备在不同主机甚至同一台
 *  主机不同时间和不同接口接入，URL 都可能会不一样。
 * @attention 如果已安装的设备中未找到与 @url 相匹配的设备将会通过 @status 返回 ::OB2_STATUS_RUNTIME_ERROR ，同时返回设备句柄为 NULL。
 * @attention 成功打开设备后，如果不需要再对设备进行访问，需要调用 @ref ob2_device_close 关闭并释放设备句柄，否则会导致内存泄漏。
 *
 * @param[in] context_handle  context 句柄
 * @param[in] url 设备安装路径
 * @param[out] status 返回函数调用状态
 * @return ob2_device_t 返回已打开的设备句柄
 *
 * \endif
 */
ob2_device_t ob2_context_open_device_by_url(ob2_context_t context_handle, const char *url, ob2_status_t *status);
#define ob2_device_open_by_url ob2_context_open_device_by_url

/**
 * \if English
 *
 * @brief Turn on the network device
 *
 * @attention Network devices are not among the installed devices, and you cannot determine whether the network devices are online through the installed device
 * information, so users need to ensure that the device is online.
 * @attention If the incoming @address and @port fail to connect to the device, a @status is returned with ::OB2_STATUS_RUNTIME_ERROR and the device handle is
 * returned as NULL.
 * @attention  After the device is successfully opened, if you no longer need to access the device, you need to call @ref ob2_device_close to close and release
 * the device handle, otherwise it will cause a memory leak.
 *
 * @param[in] context_handle  context handle
 * @param[in] address The address of the network device, the IP address string of the IPv4 protocol, in the format: "192.168.1.10"
 * @param[in] port The port of the network device, the default port of the device is 8090
 * @param[out] status Output function execution status
 * @return ob2_device_t Returns a device handle that has been opened
 *
 * \else
 *
 * @brief 打开网络设备
 *
 * @attention 网络设备不在已安装设备之列，不能通过已安装设备信息确定网络设备是否在线，所以需要用户自行确保设备已上线。
 * @attention 如果传入的 @address 和 @port 未能连接到设备，将会通过 @status 返回 ::OB2_STATUS_RUNTIME_ERROR ，同时返回设备句柄为 NULL。
 * @attention 成功打开设备后，如果不需要再对设备进行访问，需要调用 @ref ob2_device_close 关闭并释放设备句柄，否则会导致内存泄漏。
 *
 * @param[in] context_handle  context 句柄
 * @param[in] address 网络设备地址，IPv4 协议 IP 地址字符串，格式如："192.168.1.10"
 * @param[in] port 网络设备端口，设备默认端口为 8090
 * @param[out] status 返回函数调用状态
 * @return ob2_device_t 返回已打开的设备句柄
 *
 * \endif
 */
ob2_device_t ob2_context_open_net_device(ob2_context_t context_handle, const char *address, uint32_t port, ob2_status_t *status);
#define ob2_net_device_open ob2_context_open_net_device

/**
 * \if English
 *
 * @brief Turn off the device
 *
 * @param[in] device_handle The device handle that needs to be closed
 * @param[out] status Output function execution status
 *
 * \else
 *
 * @brief 关闭设备
 *
 * @param[in] device_handle 需要关闭的设备句柄
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_device_close(ob2_device_t device_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Get information about the device
 * @brief Compared with the device installation information, this interface can obtain more detailed information (firmware version number, device name, device
 * technology type, etc.) through the opened device
 *
 * @param[in] device_handle Device handle
 * @param[out] status Output function execution status
 * @return ob2_device_info_t Returns information for the device
 *
 * \else
 *
 * @brief 获取设备信息
 * @brief 相对于设备安装信息，本接口能够通过已打开的设备获取到更详细的信息（固件版本号、设备名称、设备技术类型等）
 *
 * @param[in] device_handle 设备句柄
 * @param[out] status 返回函数调用状态
 * @return ob2_device_info_t 返回设备信息
 *
 * \endif
 */
ob2_device_info_t ob2_device_get_info(ob2_device_t device_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Upgrade the device firmware
 *
 * @attention After the firmware is upgraded, you need to restart the device (some devices will restart automatically)
 *
 * @param[in] device_handle Device handle
 * @param[in] firmware_file_path The firmware address of the device
 * @param[in] callback Upgrade status callback
 * @param[in] user_data User-defined data is returned as is when the callback function is called
 * @param[in] enable_async_mode Asynchronous mode enabled (true: the call to this interface will return immediately, and a new thread will be opened in the SDK
 * to continue to complete the upgrade task; false: This interface will block execution until the upgrade task is completed or fails to exit)
 * @param[out] status Output function execution status
 *
 * \else
 *
 * @brief 升级设备固件
 *
 * @attention 固件升级完后需要重启设备（部分设备会自动重启）
 *
 * @param[in] device_handle 设备句柄
 * @param[in] firmware_file_path 设备固件地址
 * @param[in] callback 升级状态回调
 * @param[in] user_data 用户自定义数据，会在调用回调函数时原样返回
 * @param[in] enable_async_mode 异步模式使能（true：本接口调用会立即返回，SDK 内部会新开线程继续完成升级任务；
 *  false：本接口会阻塞式执行，直到升级任务完成或失败退出）
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_device_update_firmware(ob2_device_t device_handle, const char *firmware_file_path, ob2_firmware_update_state_cb_t callback, void *user_data,
                                ob2_enable_ctrl_t enable_async_mode, ob2_status_t *status);

/**
 * \if English
 *
 * @brief The device restarts
 * @brief Triggering a device restart will cause the device to be abnormal and then reinstalled
 *
 * @attention When this interface is called, the device is removed, so do not access the original device handle anymore, but shut down the device immediately.
 * After the device restarts successfully, reinstall successfully, and then reopen the device to obtain a new device handle.
 *
 * @param[in] device_handle Device handle
 * @param[out] status Output function execution status
 *
 * \else
 *
 * @brief 设备重启
 * @brief 触发设备重启，会导致设备异常然后重新安装
 *
 * @attention 调用本接口后，设备会被移除，所以不要再对原设备句柄进行访问，而是立即关闭设备。
 *  待设备重启完成后重新安装成功，再重新打开设备获取新的设备句柄。
 *
 * @param[in] device_handle 设备句柄
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_device_reboot(ob2_device_t device_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Synchronize the device clock
 * @brief After the device boots, the device clock starts clocking from zero. Through this interface, the device can be assigned the time to synchronize the
 * device clock with the host clock
 *
 * @attention Due to the problem of device clock accuracy, the clock synchronization error between the host and the device may increase after a certain period
 * of time after clock synchronization, so it is recommended that according to the application scenario. This interface can be called regularly to synchronize
 * the device clock.
 *
 * @param device_handle Device handle
 * @param status Output function execution status
 *
 * \else
 *
 * @brief 同步设备时钟
 * @brief 设备启动后，设备时钟会从零开始计时。通过本接口，可实现向设备授时，使设备时钟与主机时钟同步
 *
 * @attention 由于设备时钟精度问题，时钟同步后经过一定时间主机与设备的时钟同步误差可能会加大，所以建议依据应用场景，
 *  可定时调用本接口同步设备时钟。
 *
 * @param device_handle 设备句柄
 * @param status 返回函数调用状态
 *
 * \endif
 */
void ob2_device_sync_clock_with_host(ob2_device_t device_handle, ob2_status_t *status);

#ifdef __cplusplus
}
#endif