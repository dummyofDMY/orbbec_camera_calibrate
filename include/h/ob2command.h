#pragma once

#include "ob2types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \if English
 *
 * @brief Gets the number of commands supported by the device
 *
 * @param[in] device_handle device handle
 * @param[out] status Output function execution status
 * @return uint32_t Returns the number of commands supported by the device
 *
 * \else
 *
 * @brief 获取设备支持的命令个数
 *
 * @param[in] device_handle 设备句柄
 * @param[out] status 返回函数调用状态
 * @return uint32_t 返回设备支持的命令个数
 *
 * \endif
 */
uint32_t ob2_device_get_supported_command_count(ob2_device_t device_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Get the command information supported by the device by the index number
 *
 * @attention The control commands supported by the device refer to the commands that the device supports for either read and write access
 * @attention The @index number is in the range [0, count-1] (count is returned by @ref ob2_device_get_supported_command_count ), passing in a numeric value
 * outside the range The ::OB2_STATUS_LOGIC_ERROR will be returned by status
 *
 * @param[in] device_handle Device handle
 * @param[in] index Number of the command index
 * @param[out] status Output function execution status
 * @return ob2_command_info_t Returns command information
 *
 * \else
 *
 * @brief 通过索引号获取设备支持的命令信息
 *
 * @attention 设备支持的控制命令指该设备支持读和写任一访问权限的命令
 * @attention 索引号 @index 范围为 [0, count-1] (count 通过 @ref ob2_device_get_supported_command_count 返回），传入范围外的数值
 *  将通过 @status 返回::OB2_STATUS_LOGIC_ERROR
 *
 * @param[in] device_handle 设备句柄
 * @param[in] index 命令索引号
 * @param[out] status 返回函数调用状态
 * @return ob2_command_info_t 返回命令信息
 *
 * \endif
 */
ob2_command_info_t ob2_device_get_supported_command_info(ob2_device_t device_handle, uint32_t index, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Use the command ID to obtain the command information supported by the device
 *
 * @attention @command_id needs to be an ID supported by the device, if not, the ::OB2_STATUS_LOGIC_ERROR will be returned via @status
 *
 * @param[in] device_handle Device handle
 * @param[in] command_id Command ID
 * @param[out] status Output function execution status
 * @return ob2_command_info_t Returns command information
 *
 * \else
 *
 * @brief 通过命令 id 获取设备支持的命令信息
 *
 * @attention @command_id 需要是设备支持的 id，如果是不支持的，将通过 @status 返回::OB2_STATUS_LOGIC_ERROR 。
 *
 * @param[in] device_handle 设备句柄
 * @param[in] command_id 命令 id
 * @param[out] status 返回函数调用状态
 * @return ob2_command_info_t 返回命令信息
 *
 * \endif
 */
ob2_command_info_t ob2_device_get_supported_command_info_by_id(ob2_device_t device_handle, ob2_command_id_t command_id, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Check the access permissions of the device command
 *
 * @param[in] device_handle Device handle
 * @param[in] command_id Command ID
 * @param[in] permission Permission type
 * @param[out] status Output function execution status
 * @return true The device supports access permission
 * @return false The device does not support access permission
 *
 * \else
 *
 * @brief 检查设备命令访问权限
 *
 * @param[in] device_handle 设备句柄
 * @param[in] command_id 命令 id
 * @param[in] permission 权限类型
 * @param[out] status 返回函数调用状态
 * @return true 该设备支持该访问权限
 * @return false 该设备不支持该访问权限
 *
 *\endif
 */
bool ob2_device_check_command_access_permission(ob2_device_t device_handle, ob2_command_id_t command_id, ob2_access_permission_t permission,
                                                ob2_status_t *status);
/**
 * \if English
 *
 * @brief Gets the device property value of Boolean type
 * @brief Boolean type properties are a type of device command
 *
 * @attention If the device does not support read permission @command_id the specified command, the ::OB2_STATUS_LOGIC_ERROR will be returned via @status
 *
 * @param[in] device_handle Device handle
 * @param[in] command_id Device command ID
 * @param[out] status Output function execution status
 * @return bool Returns the value of the property
 *
 * \else
 *
 * @brief 获取设备布尔类型属性值
 * @brief 布尔类型属性是设备命令的一种
 *
 * @attention 如果该设备不支持 @command_id 指定命令的读取权限，将通过 @status 返回::OB2_STATUS_LOGIC_ERROR 。
 *
 * @param[in] device_handle 设备句柄
 * @param[in] command_id 设备命令 id
 * @param[out] status 返回函数调用状态
 * @return bool 返回属性值
 *
 * \endif
 */
bool ob2_device_get_bool_property_value(ob2_device_t device_handle, ob2_command_id_t command_id, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Set the device property value of Boolean type
 *
 * @attention If the device does not support write permission for @command_id specified command, the ::OB2_STATUS_LOGIC_ERROR will be returned via @status。
 *
 * @param[in] device_handle Device handle
 * @param[in] value The value that needs to be set
 * @param[in] command_id Device command ID
 * @param[out] status Output function execution status
 *
 * \else
 *
 * @brief 设置设备布尔类型属性值
 *
 * @attention 如果该设备不支持 @command_id 指定命令的写权限，将通过 @status 返回::OB2_STATUS_LOGIC_ERROR 。
 *
 * @param[in] device_handle 设备句柄
 * @param[in] value 需要设置的值
 * @param[in] command_id 设备命令 id
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_device_set_bool_property_value(ob2_device_t device_handle, ob2_command_id_t command_id, bool value, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Sets the default value for a property of the Boolean type of the device
 *
 * @attention If the device does not support write and read permissions of the specified command of the @command_id, the ::OB2_STATUS_LOGIC_ERROR will be
 * returned through @status.
 *
 * @param[in] device_handle Device handle
 * @param[in] command_id Device command ID
 * @param[out] status Output function execution status
 * @return bool Returns the default value of the property
 *
 * \else
 *
 * @brief 设置设备布尔类型属性默认值
 *
 * @attention 如果该设备不支持 @command_id 指定命令的写读权限，将通过 @status 返回::OB2_STATUS_LOGIC_ERROR 。
 *
 * @param[in] device_handle 设备句柄
 * @param[in] command_id 设备命令 id
 * @param[out] status 返回函数调用状态
 * @return bool 返回属性默认值
 *
 * \endif
 */
bool ob2_device_get_bool_property_default_value(ob2_device_t device_handle, ob2_command_id_t command_id, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Gets the device property value of the integer type
 * @brief The integer type property is a type of device command
 *
 * @attention If the device does not support write and read permissions of the specified command of the @command_id, the ::OB2_STATUS_LOGIC_ERROR will be
 * returned through @status.
 *
 * @param[in] device_handle Device handle
 * @param[in] command_id Device command ID
 * @param[out] status Output function execution status
 * @return int Returns the value of the property
 *
 * \else
 *
 * @brief 获取设备整型类型属性值
 * @brief 整型类型属性是设备命令的一种
 *
 * @attention 如果该设备不支持 @command_id 指定命令的读取权限，将通过 @status 返回::OB2_STATUS_LOGIC_ERROR 。
 *
 * @param[in] device_handle 设备句柄
 * @param[in] command_id 设备命令 id
 * @param[out] status 返回函数调用状态
 * @return int 返回属性值
 *
 * \endif
 */
int ob2_device_get_int_property_value(ob2_device_t device_handle, ob2_command_id_t command_id, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Sets the value for a property of the integer type of the device
 *
 * @attention If the device does not support write and read permissions of the specified command of the @command_id, the ::OB2_STATUS_LOGIC_ERROR will be
 * returned through @status.
 *
 * @param[in] device_handle Device handle
 * @param[in] value The value that needs to be set
 * @param[in] command_id Device command ID
 * @param[out] status Output function execution status
 *
 * \else
 *
 * @brief 设置设备整型类型属性值
 *
 * @attention 如果该设备不支持 @command_id 指定命令的写权限，将通过 @status 返回::OB2_STATUS_LOGIC_ERROR 。
 *
 * @param[in] device_handle 设备句柄
 * @param[in] value 需要设置的值
 * @param[in] command_id 设备命令 id
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_device_set_int_property_value(ob2_device_t device_handle, ob2_command_id_t command_id, int value, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Gets the property capabilities of the device integer type
 * @brief Property capabilities include their maximum, minimum, step, and default values
 *
 * @attention If the device does not support write and read permissions of the specified command of the @command_id, the ::OB2_STATUS_LOGIC_ERROR will be
 * returned through @status.
 *
 * @param[in] device_handle Device handle
 * @param[in] command_id Device command ID
 * @param[out] status Output function execution status
 * @return ob2_int_property_capability_t Returns property capabilities
 *
 * \else
 *
 * @brief 获取设备整型类型属性能力
 * @brief 属性能力包括其最大值、最小值、步进值、默认值
 *
 * @attention 如果该设备不支持 @command_id 指定命令的读取权限，将通过 @status 返回::OB2_STATUS_LOGIC_ERROR 。
 *
 * @param[in] device_handle 设备句柄
 * @param[in] command_id 设备命令 id
 * @param[out] status 返回函数调用状态
 * @return ob2_int_property_capability_t 返回属性能力
 *
 * \endif
 */
ob2_int_property_capability_t ob2_device_get_int_property_capability(ob2_device_t device_handle, ob2_command_id_t command_id, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Gets the device property value of the float type
 * @brief The float type property is a type of device command
 *
 * @attention If the device does not support write and read permissions of the specified command of the @command_id, the ::OB2_STATUS_LOGIC_ERROR will be
 * returned through @status.
 *
 * @param[in] device_handle Device handle
 * @param[in] command_id Device command ID
 * @param[out] status Output function execution status
 * @return float Returns the value of the property
 *
 * \else
 *
 * @brief 获取设备浮点类型属性值
 * @brief 浮点类型属性是设备命令的一种
 *
 * @attention 如果该设备不支持 @command_id 指定命令的读取权限，将通过 @status 返回::OB2_STATUS_LOGIC_ERROR 。
 *
 * @param[in] device_handle 设备句柄
 * @param[in] command_id 设备命令 id
 * @param[out] status 返回函数调用状态
 * @return float 返回属性值
 *
 * \endif
 */
float ob2_device_get_float_property_value(ob2_device_t device_handle, ob2_command_id_t command_id, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Sets the device property value of the float type
 *
 * @attention If the device does not support write and read permissions of the specified command of the @command_id, the ::OB2_STATUS_LOGIC_ERROR will be
 * returned through @status.
 *
 * @param[in] device_handle Device handle
 * @param[in] value The value that needs to be set
 * @param[in] command_id Device command ID
 * @param[out] status Output function execution status
 *
 * \else
 *
 * @brief 设置设备浮点类型属性值
 *
 * @attention 如果该设备不支持 @command_id 指定命令的写权限，将通过 @status 返回::OB2_STATUS_LOGIC_ERROR 。
 *
 * @param[in] device_handle 设备句柄
 * @param[in] value 需要设置的值
 * @param[in] command_id 设备命令 id
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_device_set_float_property_value(ob2_device_t device_handle, ob2_command_id_t command_id, float value, ob2_status_t *status);

/**
 * \if English
 *
 * @brief The capability to get the properties of a device's float type
 * @brief Property capabilities include their maximum, minimum, step, and default values
 *
 * @attention If the device does not support write and read permissions of the specified command of the @command_id, the ::OB2_STATUS_LOGIC_ERROR will be
 * returned through @status.
 *
 * @param[in] device_handle Device handle
 * @param[in] command_id Device command ID
 * @param[out] status Output function execution status
 * @return ob2_float_property_capability_t Returns property capabilities
 *
 * \else
 *
 * @brief 获取设备浮点类型属性能力
 * @brief 属性能力包括其最大值、最小值、步进值、默认值
 *
 * @attention 如果该设备不支持 @command_id 指定命令的读取权限，将通过 @status 返回::OB2_STATUS_LOGIC_ERROR 。
 *
 * @param[in] device_handle 设备句柄
 * @param[in] command_id 设备命令 id
 * @param[out] status 返回函数调用状态
 * @return ob2_float_property_capability_t 返回属性能力
 *
 * \endif
 */
ob2_float_property_capability_t ob2_device_get_float_property_capability(ob2_device_t device_handle, ob2_command_id_t command_id, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Gets the data for the struct type
 * @brief The struct type data command is one of the device commands
 *
 * @attention If the device does not support write and read permissions of the specified command of the @command_id, the ::OB2_STATUS_LOGIC_ERROR will be
 * returned through @status.
 * @attention If the returned data is no longer needed, you need to call the @ref ob2_data_bundle_release interface to release it, otherwise it will cause a
 * memory leak.
 *
 * @param[in] device_handle Device handle
 * @param[in] command_id Device command ID
 * @param[out] status Output function execution status
 * @return ob2_data_bundle_t* Returns a bundle of struct-type data (sets of data containing similar data for that struct)
 *
 * \else
 *
 * @brief 获取结构体类型数据
 * @brief 结构体类型数据命令是设备命令中的一种
 *
 * @attention 如果该设备不支持 @command_id 指定命令的读取权限，将通过 @status 返回::OB2_STATUS_LOGIC_ERROR 。
 * @attention 如果返回的数据捆不在需要使用，需要调用 @ref ob2_data_bundle_release 接口释放，否则会导致内存泄漏。
 *
 * @param[in] device_handle 设备句柄
 * @param[in] command_id 设备命令 id
 * @param[out] status 返回函数调用状态
 * @return ob2_data_bundle_t* 返回结构体类型数据捆（包含该结构体类似数据的多组数据）
 *
 * \endif
 */
ob2_data_bundle_t *ob2_device_get_structured_data(ob2_device_t device_handle, ob2_command_id_t command_id, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Set the data for the struct type
 * @brief The struct type data command is one of the device commands
 *
 * @param[in] device_handle Device handle
 * @param[in] command_id Device command ID
 * @param[in] data_bundle The data that needs to be set
 * @param[out] status Output function execution status
 *
 * \else
 *
 * @brief 设置结构体类型数据
 * @brief 结构体类型数据命令是设备命令中的一种
 *
 * @param[in] device_handle 设备句柄
 * @param[in] command_id 设备命令 id
 * @param[in] data_bundle 需要设置的数据
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_device_update_structured_data(ob2_device_t device_handle, ob2_command_id_t command_id, ob2_data_bundle_t *data_bundle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Release the bundle of data
 *
 * @param[in] data_bundle The bundle of data that needs to be released
 * @param[out] status Output function execution status
 * \else
 *
 * @brief 释放数据捆
 *
 * @param[in] data_bundle 需要释放的数据捆
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_data_bundle_release(ob2_data_bundle_t *data_bundle, ob2_status_t *status);

#ifdef __cplusplus
}
#endif