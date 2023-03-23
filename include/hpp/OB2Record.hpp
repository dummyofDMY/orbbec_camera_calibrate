#pragma once

#include "OB2Types.hpp"
#include "OB2Device.hpp"
#include <string>

extern "C" {
#include "h/ob2record.h"
}

namespace ob2 {

/**
 * \if English
 *
 * @brief record, for recording camera images, camera calibration parameters, IMU sampling, device information, etc.
 *
 * @attention The current IMU sampling data recording function is not available
 *
 * \else
 *
 * @brief 录制器，用于相机图像、相机标定参数、IMU 采样、设备信息等录制
 *
 * @attention 当前 IMU 采样数据录制功能未开放
 *
 * \endif
 */
class record {
public:
    /**
     * \if English
     *
     * @brief Record constructor
     * @brief Once the record is constructed, it can start receiving recorded data, and the recording is completed when the recorder is destructured.
     *
     * @attention The recording file will remain open during the recording process and will not be accessible through other programs until the recorder is
     * closed.
     *
     * @param file_path Recorded data output file
     *
     * \else
     *
     * @brief 录制器构造函数
     * @brief 录制器构造完后即可开始接收录制数据，录制器析构后即可完成录制。
     *
     * @attention 录制过程中会一直打开录制文件，此时通过其他程序将无法访问该文件，直到关闭录制器。
     *
     * @param file_path 录制数据输出文件
     *
     * \endif
     */
    record(const std::string file_path) {
        ob2_status_t status;
        m_record_handle = ob2_record_create(file_path.c_str(), &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

    /**
     * \if English
     *
     * @brief Constructed via other record object (mobile constructs, mainly used in derived class implementations)
     *
     * @attention After calling this constructor, the original object will no longer be accessible
     *
     * @param rc Another record object
     *
     * \else
     *
     * @brief 通过其他录制器对象构造（移动构造，主要用于派生类的实现）
     *
     * @attention 调用该构造函数后，原对象将不再可以访问
     *
     * @param rc 其他录制器对象
     *
     * \endif
     */
    record(record &&rc) : m_record_handle(rc.m_record_handle) {
        VALIDATE_NOT_NULL(m_record_handle);
        rc.m_record_handle = nullptr;
    }

    /**
     * \if English
     *
     * @brief Record destructor
     *
     * @attention The record destructor will immediately empty the internal cache of data, so to ensure that the recorded data is not lost, you need to call
     * the @ref record::flush interface to flush the data before closing
     *
     * \else
     *
     * @brief 录制器析构函数
     *
     * @attention 录制器析构析构时会立即清空内部缓存的数据，所以为了确保录制数据不丢失，关闭前需要调用 @ref record::flush 接口冲洗数据
     *
     * \endif
     */
    virtual ~record() noexcept {
        ob2_status_t status;
        if(m_record_handle != nullptr) {
            ob2_record_close(m_record_handle, &status);
        }
    }

    /**
     * \if English
     *
     * @brief Flush record cache data
     * @brief Write all the data currently cached inside the record to file.
     * @brief A call to this function will block until all the data in the record's internal cache has been written to the file, or until the wait time exceeds
     * @timeout_msec.
     *
     * @attention If the @timeout_msec is exceeded due to too much data being cached and the data being written to the file too slowly, will throw a
     * std::runtime_error exception.
     *
     * @param[in] timeout_msec Wait timeout, can be set to ::OB2_WAIT_INFINITE for unlimited waiting.
     *
     * \else
     *
     * @brief 冲洗录制器缓存数据
     * @brief 即将当前录制器内部缓存的数据全部写入文件
     * @brief 调用本接口将阻塞，直到录制器内部缓存的数据全部写入文件，或等待时长超过了 @timeout_msec。
     *
     * @attention 如果因为缓存数据过多，数据写入文件过慢，导致超过 @timeout_msec 时间还未冲洗完，则会抛出 std::runtime_error 异常
     *
     * @param[in] timeout_msec 等待超时时间，可以设置为 ::OB2_WAIT_INFINITE 表示不限时等待。
     *
     * \endif
     */
    virtual void flush(int32_t timeout_msec) {
        ob2_status_t status;
        ob2_record_flush(m_record_handle, timeout_msec, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

    /**
     * \if English
     *
     * @brief Write to cameras device information.
     *
     * @param[in] device_info device information
     *
     * \else
     *
     * @brief 写入设备信息
     *
     * @param[in] device_info 设备信息
     *
     * \endif
     */
    virtual void write_device_info(const ob2_device_info_t &device_info) {
        ob2_status_t status;
        ob2_record_write_device_info(m_record_handle, &device_info, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

    /**
     * \if English
     *
     * @brief Write to cameras calibration parameters
     *
     * @param[in] calibration cameras calibration parameters
     *
     * \else
     *
     * @brief 写入相机标定参数
     *
     * @param[in] calibration 相机标定参数
     *
     * \endif
     */
    virtual void write_cameras_calibration(const ob2_cameras_calibration_t &calibration) {
        ob2_status_t status;
        ob2_record_write_cameras_calibration(m_record_handle, &calibration, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

    /**
     * \if English
     *
     * @brief Write to capture
     *
     * @attention The time interval between writes to capture will directly determine the time interval between output captures on playback
     *
     * @param[in] capture A capture object
     *
     * \else
     *
     * @brief 写入 capture
     *
     * @attention 写入 capture 的时间间隔会直接决定回放时输出 capture 的时间间隔
     *
     * @param[in] capture capture 对象
     *
     * \endif
     */
    virtual void write_capture(const std::shared_ptr<capture> capture) {
        ob2_status_t status;
        ob2_record_write_capture(m_record_handle, capture->get_handle(), &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

    /**
     * \if English
     *
     * @brief (No open interface, please do not use)
     *
     * @param[in] imu_sample An imu_sample object.
     *
     * \else
     *
     * @brief (未开放接口，请不要使用）
     *
     * @param[in] imu_sample IMU 采样对象
     *
     * \endif
     */
    virtual void write_imu_sample(const std::shared_ptr<imu_sample> imu_sample) {
        ob2_status_t status;
        ob2_record_write_imu_sample(m_record_handle, imu_sample->get_handle(), &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

protected:
    ob2_record_t m_record_handle;
};
}  // namespace ob2