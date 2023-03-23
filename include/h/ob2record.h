#pragma once

#include "ob2types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \if English
 *
 * @brief Creating a record
 * @brief Once the record has been created it will start to receive the data to be recorded and the record will close to complete the recording.
 *
 * @attention After successfully creating a record, you need to call @ref ob2_record_close to close the record when you no longer need to record data,
 * otherwise it will cause a memory leak.
 * @attention The recording file will remain open during the recording process and will not be accessible through other programs until the record is closed
 *
 * @param[in] file_path Recorded output file path
 * @param[out] status Output function execution status.
 * @return ob2_record_t Return the handle of record.
 *
 * \else
 *
 * @brief 创建录制器
 * @brief 录制器创建完后就会开始接收录制数据，录制器关闭后即可完成录制
 *
 * @attention 成功创建录制器后，不再需要录制数据时，需要调用 @ref ob2_record_close 关闭录制器，否则会导致内存泄漏。
 * @attention 录制过程中会一直打开录制文件，此时通过其他程序将无法访问该文件，直到关闭录制器
 *
 * @param[in] file_path 录制输出文件路径
 * @param[out] status 返回函数调用状态
 * @return ob2_record_t 录制器句柄
 *
 * \endif
 */
ob2_record_t ob2_record_create(const char *file_path, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Flush record cache data
 * @brief Write all the data currently cached inside the record to file.
 * @brief A call to this function will block until all the data in the record's internal cache has been written to the file, or until the wait time exceeds
 * @timeout_msec.
 *
 * @attention If the @timeout_msec is exceeded due to too much data being cached and the data being written to the file too slowly, ::OB2_STATUS_RUNTIME_ERROR
 * will be returned via status
 *
 * @param[in] recording_handle Handle of record.
 * @param[in] timeout_msec Wait timeout, can be set to ::OB2_WAIT_INFINITE for unlimited waiting.
 * @param[out] status Output function execution status.
 *
 * \else
 *
 * @brief 冲洗录制器缓存数据
 * @brief 即将当前录制器内部缓存的数据全部写入文件
 * @brief 调用本接口将阻塞，直到录制器内部缓存的数据全部写入文件，或等待时长超过了 @timeout_msec
 *
 * @attention 如果因为缓存数据过多，数据写入文件过慢，导致超过 @timeout_msec 时间还未冲洗完，则会通过 @status 返回 ::OB2_STATUS_RUNTIME_ERROR
 *
 * @param[in] recording_handle 录制器句柄
 * @param[in] timeout_msec 等待超时时间，可以设置为 ::OB2_WAIT_INFINITE 表示不限时等待。
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_record_flush(ob2_record_t recording_handle, int32_t timeout_msec, ob2_status_t *status);

/**
 * \if English
 *
 * @brief close record
 *
 * @attention Closing the record will immediately empty the internal cache of data, so to ensure that no recorded data is lost, the @ref ob2_record_flush
 *  function needs to be called before closing
 *
 * @param[in] recording_handle Handle of record.
 * @param[out] status Output function execution status.
 *
 * \else
 *
 * @brief 关闭录制器
 *
 * @attention 关闭录制器会立即清空内部缓存的数据，所以为了确保录制数据不丢失，关闭前需要调用 @ref ob2_record_flush 接口冲洗数据
 *
 * @param[in] recording_handle 录制器句柄
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_record_close(ob2_record_t recording_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Write to device information
 *
 * @param[in] recording_handle Handle of record.
 * @param[in] device_info device information
 * @param[out] status Output function execution status.
 *
 * \else
 *
 * @brief 写入设备信息
 *
 * @param[in] recording_handle 录制器句柄
 * @param[in] device_info 设备信息
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_record_write_device_info(ob2_record_t recording_handle, const ob2_device_info_t *device_info, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Write to cameras calibration parameters
 *
 * @param[in] recording_handle Handle of record.
 * @param[in] calibration cameras calibration parameters
 * @param[out] status Output function execution status.
 *
 * \else
 *
 * @brief 写入相机标定参数
 *
 * @param[in] recording_handle 录制器句柄
 * @param[in] calibration 相机标定参数
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_record_write_cameras_calibration(ob2_record_t recording_handle, const ob2_cameras_calibration_t *calibration, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Write to capture
 *
 * @attention The time interval between writes to capture will directly determine the time interval between output captures on playback
 *
 * @param[in] recording_handle Handle of record.
 * @param[in] capture_handle Handle of capture
 * @param[out] status Output function execution status.
 *
 * \else
 *
 * @brief 写入 capture
 *
 * @attention 写入 capture 的时间间隔会直接决定回放时输出 capture 的时间间隔
 *
 * @param[in] recording_handle 录制器句柄
 * @param[in] capture_handle capture 句柄
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_record_write_capture(ob2_record_t recording_handle, const ob2_capture_t capture_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief (No open interface, please do not use)
 *
 * @param[in] recording_handle Handle of record.
 * @param[in] imu_sample_handle Handle imu_sample.
 * @param[out] status Output function execution status.
 *
 * \else
 *
 * @brief (未开放接口，请不要使用）
 *
 * @param[in] recording_handle 录制器句柄
 * @param[in] imu_sample_handle IMU 采样数据
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_record_write_imu_sample(ob2_record_t recording_handle, const ob2_imu_sample_t imu_sample_handle, ob2_status_t *status);

#ifdef __cplusplus
}
#endif