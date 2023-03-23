#pragma once

#include "ob2types.h"

#ifdef __cplusplus
extern "C" {
#endif

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
ob2_version_t ob2_get_version(void);

/**
 * \if English
 *
 * @brief Gets the core version number of the SDK
 * @brief OrbbecSDK2 is actually an API encapsulation based on the core code of OrbbecSDK, and this interface is used to obtain the core version number of
 * OrbbecSDK
 *
 * @return ob2_version_t Returns the version number of the SDK
 *
 * \else
 *
 * @brief 获取 SDK 核心版本号
 * @brief OrbbecSDK2 其实是基于 OrbbecSDK 核心代码做的 API 封装，本接口用于获取 OrbbecSDK 核心版本号
 *
 * @return ob2_version_t 返回 SDK 版本号
 *
 * \endif
 */
ob2_version_t ob2_get_core_version(void);

/**
 * \if English
 *
 * @brief Set the level of the log
 * @brief You can filter out some unnecessary log output by setting the log level, and the default level is ::OB2_LOG_SEVERITY_INFO
 *
 * @param[in] logger_type Type of log output (terminal or file)
 * @param[in] severity Log level
 * @param[out] status Output function execution status
 *
 * \else
 *
 * @brief 设置日志等级
 * @brief 可通过设置日志等级过滤掉一些不必要的日志输出，默认等级为 ::OB2_LOG_SEVERITY_INFO
 *
 * @param[in] logger_type 日志输出类型（终端或者文件）
 * @param[in] severity 日志等级
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_set_log_severity_threshold(ob2_logger_type_t logger_type, ob2_log_severity_t severity, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Set the directory for log output files
 * @brief The log file name is automatically generated by the SDK, and the output directory is ./Log by default, and you can modify the output directory through
 * this interface
 *
 * @param[in] directory The directory for the log output
 * @param[out] status Output function execution status
 *
 * \else
 *
 * @brief 设置日志输出文件目录
 * @brief 日志文件名由 SDK 自动生成，输出目录默认为: ./Log，可通过本接口修改输出目录
 *
 * @param[in] directory 日志输出目录
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_set_log_output_directory(const char *directory, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Create a context
 * @brief context is used for the lifecycle management of the SDK, and the loading and initialization of all modules within the SDK and thread creation depend
 * on the creation of context.
 *
 * @attention When the SDK internal resources are no longer accessible, you need to call @ref ob2_release_context to free the context handle, otherwise it may
 * cause a memory leak.
 *
 * @param status Output function execution status
 * @return ob2_context_t Returns a handle to the context
 *
 * \else
 *
 * @brief 创建 context
 * @brief context 用于 SDK 的生命周期管理，SDK 内部所有模块的加载及初始化，线程创建都依赖 context 的创建。
 *
 * @attention 不再对 SDK 内部资源进行访问时，需要调用 @ref ob2_release_context 将 context 句柄释放，否则可能会导致内存泄漏。
 *
 * @param status 返回函数调用状态
 * @return ob2_context_t 返回 context 句柄
 *
 * \endif
 */
ob2_context_t ob2_create_context(ob2_status_t *status);

/**
 * \if English
 *
 * @brief Create a context by passing in a configuration file
 * @brief When the context is created, the configuration file will be loaded according to the configuration file path, and the internal module functions will be
 * initialized according to the configuration file content. The default configuration file path is: ./OrbbecSDKConfig_v1.0.xml
 *
 * @attention When the SDK internal resources are no longer accessible, you need to call @ref ob2_release_context to free the context handle, otherwise it may
 * cause a memory leak.
 *
 * @param[in] config_file_path Path of configuration file
 * @param[out] status Output function execution status
 * @return ob2_context_t Returns a handle to the context
 *
 * \else
 *
 * @brief 传入配置文件创建 context
 * @brief context 创建时会依据配置文件路径加载配置文件，并依据配置文件内容初始化内部各模块功能。默认配置文件路径为：./OrbbecSDKConfig_v1.0.xml
 *
 * @attention 不在对 SDK 内部资源进行访问时，需要调用 @ref ob2_release_context 将 context 句柄释放，否则可能会导致内存泄漏。
 *
 * @param[in] config_file_path 配置文件路径
 * @param[out] status 返回函数调用状态
 * @return ob2_context_t 返回 context 句柄
 *
 * \endif
 */
ob2_context_t ob2_create_context_with_config(const char *config_file_path, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Release the context
 * @brief context is used for the lifecycle management of the SDK, and the reset of modules and resource release within the SDK is completed when the context is
 * released.
 *
 * @param context_handle  context handle
 * @param status Output function execution status
 *
 * \else
 *
 * @brief 释放 context
 * @brief context 用于 SDK 的生命周期管理，在 context 释放时会完成 SDK 内部各模块复位和资源释放。
 *
 * @param context_handle  context 句柄
 * @param status 返回函数调用状态
 *
 * \endif
 */
void ob2_release_context(ob2_context_t context_handle, ob2_status_t *status);

#ifdef __cplusplus
}
#endif