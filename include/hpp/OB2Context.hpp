#pragma once

#include "OB2Types.hpp"
#include "OB2Device.hpp"

extern "C" {
#include "h/ob2context.h"
}

#include <memory>

namespace ob2 {

/**
 * \if English
 *
 * @brief SDK context is used for the lifecycle management of the SDK, and the loading and initialization of all modules within the SDK and thread creation
 * depend on the creation of context.
 *
 * \else
 *
 * @brief SDK context (上下文)，用于 SDK 的生命周期管理，SDK 内部所有模块的加载及初始化，线程创建都依赖 context 的创建。
 *
 * \endif
 */
class context {
public:
    /**
     * \if English
     *
     * @brief The context constructor
     *
     * @param config_file_path path to the configuration file; The default value is ::OB2_DEFAULT_SDK_CONFIG_FILE_PATH, in which case the SDK loads the
     * configuration file from the default path (./OrbbecSDKConfig_v1.0.xml).
     *
     * \else
     *
     * @brief context 构造函数
     *
     * @param config_file_path 配置文件路径；默认值为 ::OB2_DEFAULT_SDK_CONFIG_FILE_PATH ，此时 SDK 会从默认路径（./OrbbecSDKConfig_v1.0.xml）加载配置文件。
     *
     * \endif
     */
    context(std::string config_file_path = OB2_DEFAULT_SDK_CONFIG_FILE_PATH) : m_device_installed_callback(nullptr), m_device_removed_callback(nullptr) {
        ob2_status_t status;
        m_context_handle = ob2_create_context_with_config(config_file_path.c_str(), &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

    /**
     * \if English
     *
     * @brief Context destructor
     *
     * \else
     *
     * @brief Context 析构函数
     *
     * \endif
     */
    virtual ~context() noexcept {
        ob2_status_t status;
        if(m_context_handle != nullptr) {
            ob2_release_context(m_context_handle, &status);
        }
    }

public:
    /**
     * \if English
     *
     * @brief Obtain the version number of the SDK
     *
     * @return ob2_version_t Returns the version number of the SDK
     *
     * \else
     *
     * @brief 获取 SDK 版本号
     *
     * @return ob2_version_t 返回 SDK 版本号
     *
     * \endif
     */
    static ob2_version_t get_version() noexcept {
        return ob2_get_version();
    }

    /**
     * \if English
     *
     * @brief Gets the core version number of the SDK
     *
     * @return ob2_version_t Returns the version number of the SDK
     *
     * \else
     *
     * @brief 获取 SDK 核心版本号
     *
     * @return ob2_version_t 返回 SDK 版本号
     *
     * \endif
     */
    static ob2_version_t get_core_version() noexcept {
        return ob2_get_core_version();
    }

    /**
     * \if English
     *
     * @brief Set the level of the log
     * @brief You can filter out some unnecessary log output by setting the log level, and the default level is ::OB2_LOG_SEVERITY_INFO
     *
     * @param[in] logger_type Type of log output (terminal or file)
     * @param[in] severity Log level
     *
     * \else
     *
     * @brief 设置日志等级
     * @brief 可通过设置日志等级过滤掉一些不必要的日志输出，默认等级为 ::OB2_LOG_SEVERITY_INFO
     *
     * @param[in] logger_type 日志输出类型（终端或者文件）
     * @param[in] severity 日志等级
     *
     * \endif
     */
    static void set_log_severity_threshold(ob2_logger_type_t logger_type, ob2_log_severity_t severity) {
        ob2_status_t status;
        ob2_set_log_severity_threshold(logger_type, severity, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

    /**
     * \if English
     *
     * @brief Set the directory for log output files
     * @brief The log file name is automatically generated by the SDK, and the output directory is ./Log by default, and you can modify the output directory
     * through this interface
     *
     * @param[in] directory The directory for the log output
     *
     * \else
     *
     * @brief 设置日志输出文件目录
     * @brief 日志文件名由 SDK 自动生成，输出目录默认为: ./Log，可通过本接口修改输出目录
     *
     * @param[in] directory 日志输出目录
     *
     * \endif
     */
    static void set_log_output_directory(const std::string &directory) {
        ob2_status_t status;
        ob2_set_log_output_directory(directory.c_str(), &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

public:
    /**
     * \if English
     *
     * @brief Get a list of installed device information
     *
     * @attention The installed device information only has some basic information (PID, SN, URL, etc.), and the detailed device information needs to be
     * obtained through the @ref device::get_info interface after opening the device
     *
     * @return std::vector<ob2_device_installation_info_t> Returns information about currently installed devices
     *
     * \else
     *
     * @brief 获取已安装的设备信息列表
     *
     * @attention 安装设备信息仅有一些基础信息（PID、SN、URL 等），详细的设备信息需要打开设备后通过 @ref device::get_info 接口获取
     *
     * @return std::vector<ob2_device_installation_info_t> 返回当前已安装的设备信息列表
     *
     * \endif
     */
    virtual std::vector<ob2_device_installation_info_t> get_installed_device_info_list() {
        ob2_status_t status;
        auto         count = ob2_context_get_installed_device_count(m_context_handle, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);

        std::vector<ob2_device_installation_info_t> device_info_list;
        for(uint32_t index = 0; index < count; index++) {
            auto device_info = ob2_context_get_installed_device_info(m_context_handle, index, &status);
            CHECK_OB2_STATUS_ERROR_THROW(status);
            device_info_list.push_back(device_info);
        }
        return device_info_list;
    }

    /**
     * \if English
     *
     * @brief Turn on the device by index number
     *
     * @attention The index number @index range is [0, count-1] (count is the length of the currently installed device information list), and the value passed
     * outside the range will throw an std::logic_error exception.
     * @attention It is not safe to open the device by the index number, and the installation of a new device or the disconnection of the device may cause the
     * device bound to the index number to change, and may even cause the @index to go out of range and report an error.
     * @ref context::open_device_by_serial_number and @ref context::open_device_by_url function are recommended.
     *
     * @param[in] index The index number of the device
     * @return std::shared_ptr<device> Returns a smart pointer to a device object
     *
     * \else
     *
     * @brief 通过索引号打开设备
     *
     * @attention 索引号 @index 范围为 [0, count-1] (count 为当前已安装的设备信息列表长度），传入范围外的数值将会抛出 std::logic_error 异常。
     * @attention 通过索引号打开设备是不安全的，新设备安装或设备掉线都可能会导致索引号绑定的设备发生改变，甚至可能会导致 @index 超出范围而报错。
     *  推荐使用 @ref context::open_device_by_serial_number 和 @ref context::open_device_by_url 接口。
     *
     * @param[in] index 设备索引号
     * @return std::shared_ptr<device> 返回设备对象智能指针
     *
     * \endif
     */
    virtual std::shared_ptr<device> open_device(uint32_t index) {
        ob2_status_t status;
        auto         device_handle = ob2_context_open_device(m_context_handle, index, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        return std::make_shared<device>(std::move(device_handle));
    }

    /**
     * \if English
     *
     * @brief Turn on the device by serial number
     *
     * @attention If no matching @serial_number is found among the installed devices, an std::runtime_error exception is thrown.
     *
     * @param[in] serial_number The serial number of the device, which can be obtained through the device installation information or through the serial number
     * pasted on the device body
     * @return std::shared_ptr<device> Returns a smart pointer to a device object
     *
     * \else
     *
     * @brief 通过序列号打开设备
     *
     * @attention 如果已安装的设备中未找到与 @serial_number 相匹配的设备将会抛出 std::runtime_error 异常。
     *
     * @param[in] serial_number 设备序列号，可通过设备安装信息获取或通过设备机身粘贴的序列号获取
     * @return std::shared_ptr<device> 返回设备对象智能指针
     *
     * \endif
     */
    virtual std::shared_ptr<device> open_device_by_serial_number(const std::string &serial_number) {
        ob2_status_t status;
        auto         device_handle = ob2_context_open_device_by_serial_number(m_context_handle, serial_number.c_str(), &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        return std::make_shared<device>(std::move(device_handle));
    }

    /**
     * \if English
     *
     * @brief Turn on the device by URL
     *
     * @attention The URL is the path assigned by the operating system after the device is connected to the host, and is the unique identification of the device
     * installed on the current host. But the same device is on different hosts or even the same one The URL may be different depending on the time and
     * interface access of the host.
     * @attention If no match for @url is found among the installed devices, an std::runtime_error exception is thrown.
     *
     * @param[in] url The path to the device installation
     * @return std::shared_ptr<device> Returns a smart pointer to a device object
     *
     * \else
     *
     * @brief 通过 URL 打开设备
     *
     * @attention URL 是设备接入主机后由操作系统分配的路径，是再当前主机上已安装的设备的唯一标识。但是同一台设备在不同主机甚至同一台
     *  主机不同时间和不同接口接入，URL 都可能会不一样。
     * @attention 如果已安装的设备中未找到与 @url 相匹配的设备将会抛出 std::runtime_error 异常。
     *
     * @param[in] url 设备安装路径
     * @return std::shared_ptr<device> 返回设备对象智能指针
     *
     * \endif
     */
    virtual std::shared_ptr<device> open_device_by_url(const std::string &url) {
        ob2_status_t status;
        auto         device_handle = ob2_context_open_device_by_url(m_context_handle, url.c_str(), &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        return std::make_shared<device>(std::move(device_handle));
    }

    /**
     * \if English
     *
     * @brief Turn on the network device
     *
     * @attention Network devices are not among the installed devices, and you cannot determine whether the network devices are online through the installed
     * device information, so users need to ensure that the device is online.
     * @attention If the incoming @address and @port fail to connect to the device, an std::runtime_error exception is thrown.
     *
     * @param[in] address The address of the network device, the IP address string of the IPv4 protocol, in the format: "192.168.1.10"
     * @param[in] port The port of the network device, the default port of the device is 8090
     * @return std::shared_ptr<device> Returns a smart pointer to a device object
     *
     * \else
     *
     * @brief 打开网络设备
     *
     * @attention 网络设备不在已安装设备之列，不能通过已安装设备信息确定网络设备是否在线，所以需要用户自行确保设备已上线。
     * @attention 如果传入的 @address 和 @port 未能连接到设备，将会将会抛出 std::runtime_error 异常。
     *
     * @param[in] address 网络设备地址，IPv4 协议 IP 地址字符串，格式如："192.168.1.10"
     * @param[in] port 网络设备端口，设备默认端口为 8090
     * @return std::shared_ptr<device> 返回设备对象智能指针
     *
     * \endif
     */
    virtual std::shared_ptr<device> open_net_device(const std::string &address, uint16_t port = 8090) {
        ob2_status_t status;
        auto         device_handle = ob2_context_open_net_device(m_context_handle, address.c_str(), port, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        return std::make_shared<device>(std::move(device_handle));
    }

    /**
     * \if English
     *
     * @brief Set the device's installation (go-live) callback
     * @brief After setting the callback, when a new device is admitted and the driver loading is completed, the set callback function will be called, and the
     * user can open the device through the callback information
     *
     * @param[in] cb Device installation callback function
     *
     * \else
     *
     * @brief 设置设备安装（上线）回调
     * @brief 设置回调后，当有新设备接入并完成驱动加载后，会调用设置的回调函数，此时用户可以通过回调的信息打开设备
     *
     * @param[in] cb 设备安装回调函数
     *
     * \endif
     */
    virtual void set_device_installed_callback(device_info_cb cb) {
        m_device_installed_callback = cb;

        ob2_status_t status;
        ob2_context_set_device_installed_callback(m_context_handle, &context::device_installed_callback, this, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

    /**
     * \if English
     *
     * @brief Set a callback for device removal (disconnection).
     * @brief After the callback is set, when a device is disconnected, the set callback function is immediately called, and the callback function sends back
     * the information of the disconnected device.
     *
     * @attention If the disconnected device is an open-ended device, access to the device should be stopped immediately and the device should be turned off.
     *
     * @param[in] cb Callback function for device removal
     *
     * \else
     *
     * @brief 设置设备移除（掉线）回调
     * @brief 设置回调后，当有设备出现掉线情况，会立即调用设置的回调函数，回调函数会传会掉线设备的信息。
     *
     * @attention 出现设备掉线后，如果掉线的设备是已打开的设备，应立即停止对该设备的访问，并关闭设备。
     *
     * @param[in] cb 设备移除回调函数
     *
     * \endif
     */
    virtual void set_device_removed_callback(device_info_cb cb) {
        m_device_removed_callback = cb;

        ob2_status_t status;
        ob2_context_set_device_removed_callback(m_context_handle, &context::device_removed_callback, this, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

protected:
    static void device_installed_callback(ob2_device_installation_info_t device_info, void *user_data) {
        auto ctx = (context *)user_data;
        if(ctx->m_device_installed_callback != nullptr) {
            ctx->m_device_installed_callback(device_info);
        }
    }

    static void device_removed_callback(ob2_device_installation_info_t device_info, void *user_data) {
        auto ctx = (context *)user_data;
        if(ctx->m_device_removed_callback != nullptr) {
            ctx->m_device_removed_callback(device_info);
        }
    }

protected:
    device_info_cb m_device_installed_callback;
    device_info_cb m_device_removed_callback;
    ob2_context_t  m_context_handle;
};

}  // namespace ob2