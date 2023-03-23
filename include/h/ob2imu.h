#pragma once

#include "ob2types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \if English
 *
 * @brief Get the number of IMU sensors supported by the device
 * @brief IMU (Inertial Measurement Unit) is a composite sensor, which is one or a combination of one or more of these sensors such as accelerometers,
 * gyroscopes, magnetometers, etc. This function is used for the interrogation of these individual sensors
 *
 * @param[in] device_handle Handle of device
 * @param[out] status Output function execution status.
 * @return uint32_t Return the number of sensors
 *
 * \else
 *
 * @brief 获取设备支持的 IMU 传感器个数
 * @brief IMU(惯性测量单元) 是一个复合传感器，是加速度计、陀螺仪、磁力计等这几个传感器中的一个或多个组合，
 * 本接口用于这些独立传感器的查询
 *
 * @param[in] device_handle 设备句柄
 * @param[out] status 返回函数调用状态
 * @return uint32_t 返回传感器个数
 *
 * \endif
 */
uint32_t ob2_device_get_supported_imu_sensor_count(ob2_device_t device_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Get the sensor type of the IMU supported by the device by index number.
 *
 * @attention Index number @index range is [0, count-1] (count is returned via @ref ob2_device_get_supported_imu_sensor_count), v passing in a value out of
 * range will result in a return of ::OB2_STATUS_LOGIC_ERROR via @status
 *
 * @param[in] device_handle Handle of device
 * @param[in] index Sensor index number
 * @param[out] status Output function execution status.
 * @return ob2_imu_sensor_type_t Return to sensor type.
 *
 * \else
 *
 * @brief 通过索引号获取设备支持的 IMU 的传感器类型
 *
 * @attention 索引号 index 范围为 [0, count-1] (count 通过 @ref ob2_device_get_supported_imu_sensor_count 返回），传入范围外的数值
 * 将通过 @status 返回 ::OB2_STATUS_LOGIC_ERROR
 *
 * @param[in] device_handle 设备句柄
 * @param[in] index 传感器索引号
 * @param[out] status 返回函数调用状态
 * @return ob2_imu_sensor_type_t 返回传感器类型
 *
 * \endif
 */
ob2_imu_sensor_type_t ob2_device_get_supported_imu_sensor_type(ob2_device_t device_handle, uint32_t index, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Get the number of accelerometer stream profiles
 * @brief The accelerometer stream profiles can be used to configure the sampling rate and range of the accelerometer
 *
 * @param[in] device_handle Handle of device
 * @param[out] status Output function execution status.
 * @return uint32_t Returns the number of accelerometer stream profiles
 *
 * \else
 *
 * @brief 获取加速度计流配置个数
 * @brief 加速度计流配置可用于配置加速度计的采样率和量程
 *
 * @param[in] device_handle 设备句柄
 * @param[out] status 返回函数调用状态
 * @return uint32_t 返回加速度计流配置个数
 *
 * \endif
 */
uint32_t ob2_device_get_accel_stream_profile_count(ob2_device_t device_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Get the accelerometer stream profiles by index number
 *
 * @attention Index number @index range is [0, count-1] (count is returned via @ref ob2_device_get_accel_stream_profile_count), passing in a value out of range
 * will result in a return of ::OB2_STATUS_LOGIC_ERROR via @status.
 *
 * @param[in] device_handle Handle of device.
 * @param[in] index Stream profile index number.
 * @param[out] status Output function execution status.
 * @return ob2_accel_stream_profile_t return accelerometer stream profile.
 *
 * \else
 *
 * @brief 通过索引号获取加速度计流配置
 *
 * @attention 索引号 index 范围为 [0, count-1] (count 通过 @ref ob2_device_get_accel_stream_profile_count 返回），传入范围外的数值
 * 将导致通过 @status 返回 ::OB2_STATUS_LOGIC_ERROR
 *
 * @param[in] device_handle 设备句柄
 * @param[in] index 流配置索引号
 * @param[out] status 返回函数调用状态
 * @return ob2_accel_stream_profile_t 返回加速度计流配置
 *
 * \endif
 */
ob2_accel_stream_profile_t ob2_device_get_accel_stream_profile(ob2_device_t device_handle, uint32_t index, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Get the number of gyroscope stream profiles
 * @brief Gyroscope stream profiles for configuring the sampling rate and range of the gyroscope
 *
 * @param[in] device_handle Handle of device.
 * @param[out] status Output function execution status.
 * @return uint32_t Returns the number of gyroscope stream profiles
 *
 * \else
 *
 * @brief 获取陀螺仪流配置个数
 * @brief 陀螺仪流配置可用于配置陀螺仪的采样率和量程
 *
 * @param[in] device_handle 设备句柄
 * @param[out] status 返回函数调用状态
 * @return uint32_t 返回陀螺仪流配置个数
 *
 * \endif
 */
uint32_t ob2_device_get_gyro_stream_profile_count(ob2_device_t device_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Get the gyroscope stream profiles by index number
 *
 * @attention Index number @index range is [0, count-1] (count is returned via @ref ob2_device_get_gyro_stream_profile_count), passing in a value out of range
 * will result in a return of ::OB2_STATUS_LOGIC_ERROR via @status.
 *
 * @param[in] device_handle Handle of device.
 * @param[in] index Stream profile index number.
 * @param[out] status Output function execution status.
 * @return ob2_gyro_stream_profile_t return gyroscope stream profile.
 *
 * \else
 *
 * @brief 通过索引号获取陀螺仪流配置
 *
 * @attention 索引号 @index 范围为 [0, count-1] (count 通过 @ref ob2_device_get_gyro_stream_profile_count 返回），传入范围外的数值
 * 将通过 @status 返回 ::OB2_STATUS_LOGIC_ERROR
 *
 * @param[in] device_handle 设备句柄
 * @param[in] index 流配置索引号
 * @param[out] status 返回函数调用状态
 * @return ob2_gyro_stream_profile_t 返回陀螺仪流配置
 *
 * \endif
 */
ob2_gyro_stream_profile_t ob2_device_get_gyro_stream_profile(ob2_device_t device_handle, uint32_t index, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Creating an imu_config
 * @brief The imu_config is created with a default stream profile for all supported sensors, but all sensors are unenabled by default.
 *
 * @attention When the imu_config is no longer used, the @ref ob2_imu_config_release function needs to be called to release the imu_config
 * handle, otherwise a memory leak will result.
 *
 * @param[in] device_handle Handle of device.
 * @param[out] status Output function execution status.
 * @return ob2_imu_config_t return handle of imu_config
 *
 * \else
 *
 * @brief 创建 IMU 配置
 * @brief IMU 配置创建后会为所有支持的 sensor 配置一个默认的流配置，但是所有 sensor 都是默认未使能的
 *
 * @attention 不再使用 IMU 配置时，需要调用 @ref ob2_imu_config_release 接口释放相机配置句柄，否则会导致内存泄漏。
 *
 * @param[in] device_handle 设备句柄
 * @param[out] status 返回函数调用状态
 * @return ob2_imu_config_t 返回 IMU 配置句柄
 *
 * \endif
 */
ob2_imu_config_t ob2_device_create_imu_config(ob2_device_t device_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Release imu_config
 *
 * @param[in] imu_config_handle Handle of imu_config
 * @param[out] status Output function execution status.
 *
 * \else
 *
 * @brief 释放 IMU 配置
 *
 * @param[in] imu_config_handle IMU 配置句柄
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_imu_config_release(ob2_imu_config_t imu_config_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Set the accelerometer stream profile
 *
 * @param[in] imu_config_handle Handle of imu_config
 * @param[in] stream_profile accelerometer stream profile
 * @param[out] status Output function execution status.
 *
 * \else
 *
 * @brief 设置加速度计流配置
 *
 * @param[in] imu_config_handle IMU 配置句柄
 * @param[in] stream_profile 加速度计流配置
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_imu_config_set_accel_stream_profile(ob2_imu_config_t imu_config_handle, const ob2_accel_stream_profile_t *stream_profile, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Enable the accelerometer stream
 *
 * @param[in] imu_config_handle Handle of imu_config
 * @param[out] status Output function execution status.
 *
 * \else
 *
 * @brief 使能加速度计流
 *
 * @param[in] imu_config_handle IMU 配置句柄
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_imu_config_enable_accel_stream(ob2_imu_config_t imu_config_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Disable the accelerometer stream
 *
 * @param[in] imu_config_handle Handle of imu_config
 * @param[out] status Output function execution status.
 *
 * \else
 *
 * @brief 关闭（去使能）加速度计流
 *
 * @param[in] imu_config_handle IMU 配置句柄
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_imu_config_disable_accel_stream(ob2_imu_config_t imu_config_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Set the gyroscope stream profile.
 *
 * @param[in] imu_config_handle Handle of imu_config
 * @param[in] stream_profile Gyroscope stream profile
 * @param[out] status Output function execution status.
 *
 * \else
 *
 * @brief 设置陀螺仪流配置
 *
 * @param[in] imu_config_handle IMU 配置句柄
 * @param[in] stream_profile 陀螺仪流配置
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_imu_config_set_gyro_stream_profile(ob2_imu_config_t imu_config_handle, const ob2_gyro_stream_profile_t *stream_profile, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Enable the gyroscope stream
 *
 * @param[in] imu_config_handle Handle of imu_config
 * @param[out] status Output function execution status.
 *
 * \else
 *
 * @brief 使能陀螺仪流
 *
 * @param[in] imu_config_handle IMU 配置句柄
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_imu_config_enable_gyro_stream(ob2_imu_config_t imu_config_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Enable the gyroscope stream
 *
 * @param[in] imu_config_handle Handle of imu_config
 * @param[out] status Output function execution status.
 *
 * \else
 *
 * @brief 关闭（去使能）陀螺仪流
 *
 * @param[in] imu_config_handle IMU 配置句柄
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_imu_config_disable_gyro_stream(ob2_imu_config_t imu_config_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Start IMU sensors work in the device (start stream)
 * @brief The sensor data stream will be enabled according to @imu_config_handle and the configuration of the device and other related work modules
 * within the SDK will also be completed according to the configuration
 * @brief Once the data stream is enabled, the SDK will internally generate imu_sample from the sensor output and cache the imu_sample in the internal queue.
 *
 * @attention After starting the IMU sensors work in the device, you need to loop through the @ref ob2_device_get_imu_sample function to get the imu_sample in
 * time, otherwise the internal cache queue will be overflowed and the data will be lost.
 *
 * @param[in] device_handle Handle of device
 * @param[in] imu_config_handle IMU configuration handle. You can pass ::OB2_DEFAULT_IMU_CONFIG, so that the SDK will start all IMU sensors with the default
 * stream configuration of each sensor.
 * @param[out] status Output function execution status.
 *
 * \else
 *
 * @brief 启动设备内 IMU 工作（开流）
 * @brief 会根据 @imu_config_handle 开启已使能的 Sensor 数据流，同时也会根据配置内容完成设备、SDK 内部其他相关工作模块的配置
 * @brief 开启数据流后，SDK 内部会将各 Sensor 输出的采用数据生成 imu_sample，并将 imu_sample 缓存在内部队列，用户需要通过
 * ob2_device_get_imu_sample 接口获取 imu_sample，进而通过 imu_sample 获取各 sensor 的采用数据
 *
 * @attention 启动设备内相机工作后, 需要及时地通过 @ref ob2_device_get_imu_sample 接口循环获取 imu_sample，否则内部缓存队列溢出后会丢失数据。
 *
 * @param[in] device_handle 设备句柄
 * @param[in] imu_config_handle IMU 配置句柄，调用完本接口后可立即停释放配置句柄。可传入 ::OB2_DEFAULT_IMU_CONFIG, 这样 SDK 将通过各 Sensor 的默认流配置启动所有
 * Sensor
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_device_start_imu(ob2_device_t device_handle, const ob2_imu_config_t imu_config_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Start IMU sensors work in the device by returning imu_sample as a callback
 * @brief The sensor data stream will be enabled according to @imu_config_handle and the configuration of the device and other related work modules
 * within the SDK will also be completed according to the configuration
 * @brief Once the data stream is turned on, the SDK internally generates imu_sample from the adopted data output by each Sensor and returns imu_sample via the
 * callback function @cb.
 *
 * @attention The callback function @cb is a user written function that needs to be executed in less than the imu_sample generation period (determined by the
 * data output period of the sensor with the highest sample rate enabled), otherwise the SDK internal cache queue will overflow and data will be lost and there
 * will be a cumulative delay in the data resulting in poor real time performance. For some device models, this may even lead to a stoppage of the stream.
 *
 * @param[in] device_handle Handle of device
 * @param[in] imu_config_handle IMU configuration handle. You can pass ::OB2_DEFAULT_IMU_CONFIG, so that the SDK will start all IMU sensors with the default
 * stream configuration of each sensor
 * @param[in] cb imu_sample callback function
 * @param[in] user_data User-defined data, which is returned as is via @cb, and contextual data that can be passed by the user via @user_data.
 * @param[out] status Output function execution status.
 *
 * \else
 *
 * @brief 通过回调返回 imu_sample 的方式启动设备 IMU 工作
 * @brief 会根据 @imu_config_handle 开启已使能的 Sensor 数据流，同时也会根据配置内容完成设备、SDK 内部其他相关工作模块的配置
 * @brief 开启数据流后，SDK 内部会将各 Sensor 输出的采用数据生成 imu_sample，并通过回调函数 cb 返回 imu_sample
 *
 * @attention 回调函数 @cb 是用户自行编写的函数，需要保证该函数的执行时间小于 imu_sample 生成周期（由已使能的 Sensor 中采样率最大的采用数据输出周期决定），
 * 否则会导致 SDK 内部缓存队列溢出而丢失数据，并且数据会有累加延时导致实时性变差。对于某些型号的设备，甚至可能会导致停流。
 *
 * @param[in] device_handle 设备句柄
 * @param[in] imu_config_handle IMU 配置句柄，调用完本接口后可立即停释放配置句柄。可传入 ::OB2_DEFAULT_IMU_CONFIG, 这样 SDK 将通过各 Sensor 的默认流配置启动所有
 * Sensor
 * @param[in] cb imu_sample 回调函数
 * @param[in] user_data 用户自定义数据，会通过 @cb 原样返回，用户可通过 @user_data 传递上下文数据
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_device_start_imu_with_callback(ob2_device_t device_handle, const ob2_imu_config_t imu_config_handle, ob2_imu_sample_cb_t cb, void *user_data,
                                        ob2_status_t *status);

/**
 * \if English
 *
 * @brief Update the device imu_config
 * @brief Configuration updates during the device IMU Sensors starting, such as turning the data stream of a Sensor on or off without stopping the all IMU
 * sensors.
 *
 * @attention The device IMU Sensors needs to be started first, otherwise there is no real point in calling this function.
 *
 * @param[in] device_handle Handle of device
 * @param[in] imu_config_handle IMU configuration handle. You can pass ::OB2_DEFAULT_IMU_CONFIG, so that the SDK will start all IMU sensors with the default
 * stream configuration of each sensor
 * @param[out] status Output function execution status.
 *
 * \else
 *
 * @brief 更新设备 IMU 配置
 * @brief 可实现设备 IMU 过程中的配置更新，比如在不停止 IMU 工作的情况下打开或关闭某一 Sensor 的数据流
 *
 * @attention 需要先启动设备 IMU 工作，否则调用本接口将没有任何实际意义
 *
 * @param[in] device_handle 设备句柄
 * @param[in] imu_config_handle 用于更新的 IMU 配置, 可传入 ::OB2_DEFAULT_IMU_CONFIG, 这样 SDK 将通过各 Sensor 的默认流配置启动所有 Sensor
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_device_update_imu_config(ob2_device_t device_handle, const ob2_imu_config_t imu_config_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Stop IMU Sensor work in device (stop stream)
 *
 * @param[in] device_handle Handle of device
 * @param[out] status Output function execution status.
 *
 * \else
 *
 * @brief 停止设备内 IMU 工作
 *
 * @param[in] device_handle 设备句柄
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_device_stop_imu(ob2_device_t device_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Get IMU sampling data
 * @brief imu_sample is a composite sample containing one sample of each enabled Sensor.
 * @brief Used in conjunction with the @ref ob2_device_start_imu function to obtain the imu_sample generated from each Sensor sample data received after the
 * IMU has been started in the device.
 * @brief When this function is called, if the SDK does not have an imu_sample cached internally in the queue, it will wait blockingly until the imu_sample is
 * successfully fetched or until the time set by @timeout_msec is exceeded.
 *
 * @attention After starting the IMU work within the device, you need to loop through this function to get the imu_sample in time, otherwise the data will be
 * lost when the internal cache queue overflows.
 * @attention If the imu_sample is not successfully fetched after the time set by @timeout_msec, it will return ::OB2_STATUS_RUNTIME_ERROR via @status and the
 * returned imu_sample will also be NULL.
 * @attention If you are not using the imu_sample after it has been successfully acquired, you need to call the @ref ob2_imu_sample_release function to release
 * the handle, otherwise a memory leak will result.
 *
 * @param[in] device_handle Handle of device
 * @param[in] timeout_msec Wait timeout, can be set to ::OB2_WAIT_INFINITE for unlimited waiting.
 * @param[out] status Output function execution status.
 * @return ob2_imu_sample_t Return imu_sample handle
 *
 * \else
 *
 * @brief 获取 IMU 采样数据
 * @brief imu_sample 是一个复合采样数据，包含每个已启用 Sensor 的一次采样数据
 * @brief 配合 @ref ob2_device_start_imu 接口使用，在启动设备内 IMU 工作后，通过本接口获取接收到各 Sensor 样数据后生成的 imu_sample。
 * @brief 调用本接口后，如果 SDK 内部未有 imu_sample 缓存在队列中，会进行阻塞式等待，直到成功获取到 imu_sample 或者等待超过了 @timeout_msec 设定的时间。
 *
 * @attention 启动设备内 IMU 工作后，需要及时地通过本接口循环获取 imu_sample，否则内部缓存队列溢出后会丢失数据。
 * @attention 超过 @timeout_msec 设置时间后还未成功获取到 imu_sample，将会通过 @status 返回 ::OB2_STATUS_RUNTIME_ERROR ，同时返回的 imu_sample 也为 NULL
 * @attention 成功获取到 imu_sample 后，若不在使用该 imu_sample，需要调用 @ref ob2_imu_sample_release 接口释放句柄，否则会导致内存泄漏。
 *
 * @param[in] device_handle 设备句柄
 * @param[in] timeout_msec 等待超时时间，可以设置为 ::OB2_WAIT_INFINITE 表示不限时等待。
 * @param[out] status 返回函数调用状态
 * @return ob2_imu_sample_t 返回 imu_sample 句柄
 *
 * \endif
 */
ob2_imu_sample_t ob2_device_get_imu_sample(ob2_device_t device_handle, int32_t timeout_msec, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Increase imu_sample reference count
 * @brief The reference count of an imu_sample obtained or created through any of the SDK's functions is 1. Calling this function adds 1 to the reference
 * count, then each call to @ref ob2_imu_sample_release subtracts 1 from the reference count, and the memory bound to the imu_sample handle is actually released
 * when the reference count is reduced to 0.
 *
 * @attention Calling this function is risky and should only be used after a clear understanding of the imu_sample reference counting mechanism and the
 * reference count values of the imu_sample obtained by each function. And make sure that every time this function is called, the @ref ob2_imu_sample_release
 * function is called in the future accordingly, otherwise a memory leak will result.
 *
 * @param[in] imu_sample_handle Handle of imu_sample
 * @param[out] status Output function execution status.
 *
 * \else
 *
 * @brief 增加 imu_sample 引用计数
 * @brief 通过 SDK 的任何接口获取或创建的 imu_sample 的引用计数都是 1，通过调用本接口可使引用计数加 1。然后每次调用 @ref ob2_imu_sample_release 会使引用计数减
 * 1， 当引用计数减为 0 时，才会真正释放 imu_sample 句柄所绑定的内存。
 *
 * @attention 调用本接口有较大风险，只有在清晰理解 imu_sample 引用计数机制及各接口获取到的 imu_sample 的引用计数值之后才可使用。
 * 并且需求确保每调用一次本接口，就要在未来相应地调用一次 @ref ob2_imu_sample_release 接口，否则会导致内存泄漏。
 *
 * @param[in] imu_sample_handle imu_sample 句柄
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_imu_sample_reference(ob2_imu_sample_t imu_sample_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Release imu_sample.
 * @brief In fact each call to this function decrements the reference count of imu_sample by 1. The memory bound to the imu_sample handle is not
 * actually released until the reference count is reduced to 0.
 *
 * @param[in] imu_sample_handle Handle of imu_sample
 * @param[out] status Output function execution status.
 *
 * \else
 *
 * @brief 释放 imu_sample
 * @brief 实际上每次调用本接口会将 imu_sample 的引用计数减 1，当引用计数减为 0 时，才会真正释放 imu_sample 句柄所绑定的内存。
 *
 * @param[in] imu_sample_handle imu_sample 句柄
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_imu_sample_release(ob2_imu_sample_t imu_sample_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Get the number of accelerometer samples in imu_sample
 * @brief When the accelerometer is switched on, an imu_sample is returned containing one or more accelerometer samples (the number may vary between device
 * models and sample frequency settings)
 *
 * @param[in] imu_sample_handle Handle of imu_sample.
 * @param[out] status Output function execution status.
 * @return uint32_t Returns the number of data sampled by the accelerometer.
 *
 * \else
 *
 * @brief 获取 imu_sample 中加速度计采样数据个数
 * @brief 开启加速度计后，返回的一个 imu_sample 会包含一个或多个加速度计采样数据 (不同型号设备和不同采样频率设置，个数可能会不同)
 *
 * @param[in] imu_sample_handle imu_sample 句柄
 * @param[out] status 返回函数调用状态
 * @return uint32_t 返回加速度计采样数据个数
 *
 * \endif
 */
uint32_t ob2_imu_sample_get_accel_sample_count(ob2_imu_sample_t imu_sample_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Acquisition of accelerometer sampling data
 *
 * @attention The range of index number index is [0~count-1] (count is obtained via @ref ob2_imu_sample_get_accel_sample_count function), If a value outside
 * the range is passed, it will be returned via @status ::OB2_STATUS_LOGIC_ERROR.
 *
 * @param[in] imu_sample_handle Handle of imu_sample
 * @param[in] index Sampled data index number, pass @ref ::OB2_FIRST_SAMPLE to get the first (index 0) data
 * @param[out] status 返 Output function execution status.
 * @return ob2_accel_sample_t Returns accelerometer sampling data (non-handle, no active release required)
 *
 * \else
 *
 * @brief 获取加速度计采样数据
 *
 * @attention 索引号 index 的范围为 [0~count-1](count 通过 @ref ob2_imu_sample_get_accel_sample_count 接口获取)，
 * 若传入范围之外的值，将通过 @status 返回 ::OB2_STATUS_LOGIC_ERROR 。
 *
 * @param[in] imu_sample_handle imu_sample 句柄
 * @param[in] index 采样数据索引号，可传入 @ref ::OB2_FIRST_SAMPLE 获取第一个（索引号为 0）数据
 * @param[out] status 返回函数调用状态
 * @return ob2_accel_sample_t 返回加速度计采样数据（非句柄，不需要主动释放）
 *
 * \endif
 */
ob2_accel_sample_t ob2_imu_sample_get_accel_sample(ob2_imu_sample_t imu_sample_handle, uint32_t index, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Get the number of gyroscope samples in imu_sample.
 * @brief When the gyroscope is switched on, an imu_sample is returned containing one or more gyroscope samples (the number may vary between device
 * models and sample frequency settings)
 *
 * @param[in] imu_sample_handle Handle of imu_sample.
 * @param[out] status Output function execution status.
 * @return uint32_t Returns the number of data sampled by the gyroscope.
 *
 * \else
 *
 * @brief 获取 imu_sample 陀螺仪采样数据个数
 * @brief 开启陀螺仪后，返回的一个 imu_sample 包含一个或多个陀螺仪采样数据 (不同型号设备和不同采样频率设置, 个数可能会不同)
 *
 * @param[in] imu_sample_handle imu_sample 句柄
 * @param[out] status 返回函数调用状态
 * @return uint32_t 返回陀螺仪采样数据个数
 *
 * \endif
 */
uint32_t ob2_imu_sample_get_gyro_sample_count(ob2_imu_sample_t imu_sample_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Acquisition of gyroscope sampling data
 *
 * @attention The range of index number index is [0~count-1] (count is obtained via @ref ob2_imu_sample_get_gyro_sample_count function), If a value outside
 * the range is passed, it will be returned via @status ::OB2_STATUS_LOGIC_ERROR.
 *
 * @param[in] imu_sample_handle Handle of imu_sample
 * @param[in] index Sampled data index number, pass @ref ::OB2_FIRST_SAMPLE to get the first (index 0) data
 * @param[out] status Output function execution status.
 * @return ob2_accel_sample_t Returns gyroscope sampling data (non-handle, no active release required)
 *
 * \else
 *
 * @brief 获取陀螺仪采样数据
 *
 * @attention 索引号 index 的范围为 [0~count-1](count 通过 @ref ob2_imu_sample_get_gyro_sample_count 接口获取)，
 * 若传入范围之外的值，将通过 @status 返回 ::OB2_STATUS_LOGIC_ERROR 。
 *
 * @param[in] imu_sample_handle imu_sample 句柄
 * @param[in] index 采样数据索引号，可传入 @ref ::OB2_FIRST_SAMPLE 获取第一个（索引号为 0）数据
 * @param[out] status 返回函数调用状态
 * @return ob2_gyro_sample_t 返回陀螺仪采样数据（非句柄，不需要主动释放）
 *
 * \endif
 */
ob2_gyro_sample_t ob2_imu_sample_get_gyro_sample(ob2_imu_sample_t imu_sample_handle, uint32_t index, ob2_status_t *status);

#ifdef __cplusplus
}
#endif