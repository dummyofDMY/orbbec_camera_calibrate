#pragma once

#include "OB2Types.hpp"

extern "C" {
#include "h/ob2imu.h"
}

#include <functional>

namespace ob2 {
class device;

/**
 * \if English
 *
 * @brief imu_config, configuration for the working of each IMU Sensor in the device and for the working of IMU-related modules in the device and IMU-related
 * modules in the SDK.
 *
 * \else
 *
 * @brief IMU 配置，用于设备内各 IMU Sensor 的工作配置及设备内与 IMU 工作相关模块、SDK 内与 IMU 工作相关相关模块的工作配置。
 *
 * \endif
 */
class imu_config {
public:
    /**
     * \if English
     *
     * @brief Constructed from IMU imu_config handle (mainly used by @ref device::create_imu_config ).
     *
     * @param imu_config_handle handle of imu_config.
     *
     * \else
     *
     * @brief 通过 IMU 配置句柄构造（主要用于 @ref device::create_imu_config ）
     *
     * @param imu_config_handle imu_config 句柄
     *
     * \endif
     */
    imu_config(ob2_imu_config_t &&imu_config_handle) : m_imu_config_handle(imu_config_handle) {
        VALIDATE_NOT_NULL(m_imu_config_handle);
    }

    /**
     * \if English
     *
     * @brief Constructed via other imu_config object (mobile constructs, mainly used for derived class implementations).
     *
     * @attention After calling this constructor, the original object will no longer be accessible.
     *
     * @param config Another imu_config object
     *
     * \else
     *
     * @brief 通过其他 IMU 配置对象构造（移动构造，主要用于派生类的实现）
     *
     * @attention 调用该构造函数后，原对象将不再可以访问
     *
     * @param config 其他 IMU 配置对象
     *
     * \endif
     */
    imu_config(imu_config &&config) : m_imu_config_handle(config.m_imu_config_handle) {
        VALIDATE_NOT_NULL(m_imu_config_handle);
        config.m_imu_config_handle = nullptr;
    }

    /**
     * \if English
     *
     * @brief imu_config destructor
     *
     * \else
     *
     * @brief IMU 配置析构函数
     *
     * \endif
     */
    virtual ~imu_config() noexcept {
        ob2_status_t status;
        if(m_imu_config_handle != nullptr) {
            ob2_imu_config_release(m_imu_config_handle, &status);
        }
    }

    /**
     * \if English
     *
     * @brief Set the accelerometer stream profile
     *
     * @param[in] stream_profile accelerometer stream profile
     *
     * \else
     *
     * @brief 设置加速度计流配置
     *
     * @param[in] stream_profile 加速度计流配置
     *
     * \endif
     */
    virtual void set_accel_stream_profile(const ob2_accel_stream_profile_t &stream_profile) {
        ob2_status_t status;
        ob2_imu_config_set_accel_stream_profile(m_imu_config_handle, &stream_profile, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

    /**
     * \if English
     *
     * @brief Enable the accelerometer stream
     *
     * \else
     *
     * @brief 使能加速度计流
     *
     * \endif
     */
    virtual void enable_accel_stream() {
        ob2_status_t status;
        ob2_imu_config_enable_accel_stream(m_imu_config_handle, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

    /**
     * \if English
     *
     * @brief Disable the accelerometer stream
     *
     * \else
     *
     * @brief 关闭（去使能）加速度计流
     *
     * \endif
     */
    virtual void disable_accel_stream() {
        ob2_status_t status;
        ob2_imu_config_disable_accel_stream(m_imu_config_handle, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

    /**
     * \if English
     *
     * @brief Set the gyroscope stream profile.
     *
     * \else
     *
     * @brief 设置陀螺仪流配置
     *
     * @param[in] stream_profile 陀螺仪流配置
     *
     * \endif
     */
    virtual void set_gyro_stream_profile(const ob2_gyro_stream_profile_t &stream_profile) {
        ob2_status_t status;
        ob2_imu_config_set_gyro_stream_profile(m_imu_config_handle, &stream_profile, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

    /**
     * \if English
     *
     * @brief Enable the gyroscope stream
     *
     * \else
     *
     * @brief 使能陀螺仪流
     *
     * \endif
     */
    virtual void enable_gyro_stream(ob2_enable_ctrl_t enable) {
        ob2_status_t status;
        ob2_imu_config_enable_gyro_stream(m_imu_config_handle, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

    /**
     * \if English
     *
     * @brief Enable the gyroscope stream
     *
     * \else
     *
     * @brief 关闭（去使能）陀螺仪流
     *
     * \endif
     */
    virtual void disable_gyro_stream(ob2_enable_ctrl_t enable) {
        ob2_status_t status;
        ob2_imu_config_disable_gyro_stream(m_imu_config_handle, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

    /**
     * \if English
     *
     * @brief get imu_config handle
     *
     * @attention Getting a handle does not increase the imu_config handle reference count, its lifecycle is still managed by the imu_config object, i.e.
     * imu_config will release the handle when it is destructured
     *
     * @return ob2_imu_config_t Return the imu_config handle
     *
     * \else
     *
     * @brief 获取 IMU 配置句柄
     *
     * @attention 获取句柄不会增加 IMU 配置句柄引用计数，其生命周期还是由 imu_config 对象管理，即 imu_config 析构后会释放句柄
     *
     * @return ob2_imu_config_t 返回 IMU 配置句柄
     *
     * \endif
     */
    virtual ob2_imu_config_t get_handle() {
        return m_imu_config_handle;
    }

protected:
    ob2_imu_config_t m_imu_config_handle;
};

/**
 * \if English
 *
 * @brief imu_sample, a composite sampling data carrier containing one packet of sampling data for each enabled Sensor
 *
 * \else
 *
 * @brief IMU 采样, 是一个复合采样数据载体，包含每个已启用 Sensor 的一包采样数据
 *
 * \endif
 */
class imu_sample {
public:
    /**
     * \if English
     *
     * @brief Constructed from imu_sample handle (mainly used by @ref device::get_imu_sample()).
     *
     * @param imu_sample_handle  handle of imu_sample
     *
     * \else
     *
     * @brief 通过 IMU 采样句柄构造（主要用于 @ref device::get_imu_sample()）
     *
     * @param imu_sample_handle imu_sample jub
     *
     * \endif
     */
    imu_sample(ob2_imu_sample_t &&imu_sample_handle) : m_imu_sample_handle(imu_sample_handle) {
        VALIDATE_NOT_NULL(m_imu_sample_handle);
    }

    /**
     * \if English
     *
     * @brief Constructed from other imu_sample object (mobile constructs, mainly used in derived class implementations)
     *
     * @attention After calling this constructor, the original object will no longer be accessible
     *
     * @param[in] sample Another imu_sample object
     *
     * \else
     *
     * @brief 通过其他 IMU 采样对象构造（移动构造，主要用于派生类的实现）
     *
     * @attention 调用该构造函数后，原对象将不再可以访问
     *
     * @param[in] sample 其他 IMU 采样对象
     *
     * \endif
     */
    imu_sample(imu_sample &&sample) : m_imu_sample_handle(sample.m_imu_sample_handle) {
        VALIDATE_NOT_NULL(m_imu_sample_handle);
        sample.m_imu_sample_handle = nullptr;
    }

    /**
     * \if English
     *
     * @brief imu_sample destructor
     *
     * \else
     *
     * @brief IMU 采样析构函数
     *
     * \endif
     */
    virtual ~imu_sample() noexcept {
        ob2_status_t status;
        if(m_imu_sample_handle != nullptr) {
            ob2_imu_sample_release(m_imu_sample_handle, &status);
        }
    }

    /**
     * \if English
     *
     * @brief Get the number of accelerometer samples in imu_sample
     * @brief When the accelerometer is switched on, an imu_sample is returned containing one or more accelerometer samples (the number may vary between device
     * models and sample frequency settings)
     *
     * @return uint32_t Returns the number of data sampled by the accelerometer.
     *
     * \else
     *
     * @brief 获取 imu_sample 中加速度计采样数据个数
     * @brief 开启加速度计后，返回的一个 imu_sample 会包含一个或多个加速度计采样数据 (不同型号设备和不同采样频率设置，个数可能会不同)
     *
     * @return uint32_t 返回加速度计采样数据个数
     *
     * \endif
     */
    virtual uint32_t get_accel_sample_count() {
        ob2_status_t status;
        auto         count = ob2_imu_sample_get_accel_sample_count(m_imu_sample_handle, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        return count;
    }

    /**
     * \if English
     *
     * @brief get accelerometer sampling data
     *
     * @attention The range of index number index is [0~count-1] (count is obtained via @ref imu_sample::get_accel_sample_count function), If a value outside
     * the range is passed, it will be returned via @status ::OB2_STATUS_LOGIC_ERROR.
     *
     * @param[in] index Sampled data index number, pass ::OB2_FIRST_SAMPLE to get the first (index 0) data
     * @return ob2_accel_sample_t Returns accelerometer sampling data
     *
     * \else
     *
     * @brief 获取加速度计采样数据
     *
     * @attention 索引号 index 的范围为 [0~count-1](count 通过 @ref imu_sample::get_accel_sample_count 接口获取)，
     *  若传入范围之外的值，将会抛出 std::runtime_ERROR 。
     *
     * @param[in] index 采样数据索引号，可传入 ::OB2_FIRST_SAMPLE 获取第一个（索引号为 0）数据
     * @return ob2_accel_sample_t 返回加速度计采样数据
     *
     * \endif
     */
    virtual ob2_accel_sample_t get_accel_sample(uint32_t index) {
        ob2_status_t status;
        auto         sample = ob2_imu_sample_get_accel_sample(m_imu_sample_handle, index, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        return sample;
    }

    /**
     * \if English
     *
     * @brief Get the number of gyroscope samples in imu_sample
     * @brief When the accelerometer is switched on, an imu_sample is returned containing one or more gyroscope samples (the number may vary between device
     * models and sample frequency settings)
     *
     * @return uint32_t Returns the number of data sampled by the gyroscope.
     *
     * \else
     *
     * @brief 获取 imu_sample 陀螺仪采样数据个数
     * @brief 开启陀螺仪后，返回的一个 imu_sample 包含一个或多个陀螺仪采样数据 (不同型号设备和不同采样频率设置, 个数可能会不同)
     *
     * @return uint32_t 返回陀螺仪采样数据个数
     *
     * \endif
     */
    virtual uint32_t get_gyro_sample_count() {
        ob2_status_t status;
        auto         count = ob2_imu_sample_get_gyro_sample_count(m_imu_sample_handle, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        return count;
    }

    /**
     * \if English
     *
     * @brief get gyroscope sampling data
     *
     * @attention The range of index number index is [0~count-1] (count is obtained via @ref imu_sample::get_gyro_sample_count function), If a value outside
     * the range is passed, it will be returned via @status ::OB2_STATUS_LOGIC_ERROR.
     *
     * @param[in] index Sampled data index number, pass @ref ::OB2_FIRST_SAMPLE to get the first (index 0) data
     * @return ob2_gyro_sample_t Returns gyroscope sampling data
     *
     * \else
     *
     * @brief 获取陀螺仪采样数据
     *
     * @attention 索引号 index 的范围为 [0~count-1](count 通过 @ref imu_sample::get_gyro_sample_count 接口获取)，
     *  若传入范围之外的值，将会抛出 std::runtime_ERROR 。
     *
     * @param[in] index 采样数据索引号，可传入 ::OB2_FIRST_SAMPLE 获取第一个（索引号为 0）数据
     * @return ob2_gyro_sample_t 返回陀螺仪采样数据
     *
     * \endif
     */
    virtual ob2_gyro_sample_t get_gyro_sample(uint32_t index) {
        ob2_status_t status;
        auto         sample = ob2_imu_sample_get_gyro_sample(m_imu_sample_handle, index, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        return sample;
    }

    /**
     * \if English
     *
     * @brief get imu_sample handle
     *
     * @attention Getting a handle does not increase the imu_sample handle reference count, its lifecycle is still managed by the imu_sample object, i.e.
     * imu_sample will release the handle when it is destructured
     *
     * @return ob2_imu_sample_t Return the imu_sample handle
     *
     * \else
     *
     * @brief 获取 IMU 配置句柄
     *
     * @attention 获取句柄不会增加 IMU 配置句柄引用计数，其生命周期还是由 imu_sample 对象管理，即 imu_sample 析构后会释放句柄
     *
     * @return ob2_imu_sample_t 返回 IMU 配置句柄
     *
     * \endif
     */
    virtual ob2_imu_sample_t get_handle() {
        return m_imu_sample_handle;
    }

protected:
    ob2_imu_sample_t m_imu_sample_handle;
};

/**
 * \if English
 *
 * @brief imu_sample callback
 *
 * \else
 *
 * @brief IMU 采样回调
 *
 * \endif
 */
typedef std::function<void(std::shared_ptr<imu_sample>)> imu_sample_cb;

}  // namespace ob2