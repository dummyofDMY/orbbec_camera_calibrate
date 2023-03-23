#pragma once

#include "OB2Types.hpp"
#include "OB2Camera.hpp"
#include "OB2IMU.hpp"

extern "C" {
#include "h/ob2device.h"
#include "h/ob2command.h"
}

#include <vector>
#include <memory>

namespace ob2 {

/**
 * \if English
 *
 * @brief definition of device class,A device class represents a communication connection to a physical device through which it can be accessed and controlled.
 *
 * \else
 *
 * @brief 设备类定义，设备类代表着与物理设备的通信连接，可通过设备类访问和控制物理设备。
 *
 * \endif
 */
class device {
public:
    /**
     * \if English
     *
     * @brief Construct by passing in a device handle (primarily for implementations that open device function in context)
     *
     * @param device_handle A handle to the device
     *
     * \else
     *
     * @brief 通过传入设备句柄构造（主要用于 context 打开设备接口的实现）
     *
     * @param device_handle 设备句柄
     *
     * \endif
     */
    device(ob2_device_t &&device_handle) : m_device_handle(device_handle), m_capture_cb(nullptr), m_firmware_update_state_cb(nullptr) {
        VALIDATE_NOT_NULL(m_device_handle);
    }

    /**
     * \if English
     *
     * @brief Constructed through other device objects (move constructs, primarily for the implementation of derived classes)
     *
     * @attention When the constructor is called, the original object is no longer accessible
     *
     * @param dev Device object
     *
     * \else
     *
     * @brief 通过其他设备对象构造（移动构造，主要用于派生类的实现）
     *
     * @attention 调用该构造函数后，原对象将不再可以访问
     *
     * @param dev 设备对象
     *
     * \endif
     */
    device(device &&dev) : m_device_handle(dev.m_device_handle) {
        VALIDATE_NOT_NULL(m_device_handle);
        dev.m_device_handle = nullptr;
    }

    /**
     * \if English
     *
     * @brief Device destructor
     *
     * \else
     *
     * @brief 设备析构函数
     *
     * \endif
     */
    virtual ~device() noexcept {
        ob2_status_t status;
        if(m_device_handle != nullptr) {
            ob2_device_close(m_device_handle, &status);
        }
    }

    /**
     * \if English
     *
     * @brief Get information about the device
     * @brief Compared with the device installation information, this interface can obtain more detailed information (firmware version number, device name,
     * device technology type, etc.) through the opened device
     *
     * @return ob2_device_info_t Returns information for the device
     *
     * \else
     *
     * @brief 获取设备信息
     * @brief 相对于设备安装信息，本接口能够通过已打开的设备获取到更详细的信息（固件版本号、设备名称、设备技术类型等）
     *
     * @return ob2_device_info_t 返回设备信息
     *
     * \endif
     */
    virtual ob2_device_info_t get_info() {
        ob2_status_t status;
        auto         device_info = ob2_device_get_info(m_device_handle, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        return device_info;
    }

    /**
     * \if English
     *
     * @brief Gets a handle to the device
     *
     * @attention Acquiring a handle does not increase the reference count of the handle, and its lifecycle is managed by the device object, that is, the handle
     * is released after the device is destroyed
     *
     * @return ob2_device_t Returns a handle to the device
     *
     * \else
     *
     * @brief 获取设备句柄
     *
     * @attention 获取句柄不会增加句柄引用计数，其生命周期还是由设备对象管理，即设备析构后会释放句柄
     *
     * @return ob2_device_t 返回设备句柄
     *
     * \endif
     */
    virtual ob2_device_t get_handle() {
        return m_device_handle;
    }

public:
    /**
     * \if English
     *
     * @brief Gets a list of supported camera types
     * @brief In addition to having a Depth camera, a device may also include Color and IR cameras, depending on the model.
     *
     * @return std::vector<ob2_camera_type_t> Returns a list of supported camera types
     *
     * \else
     *
     * @brief 获取支持的相机类型列表
     * @brief 一个设备除了拥有一个 Depth 相机外，还可能会包含 Color、IR 相机，视具体型号而定。
     *
     * @return std::vector<ob2_camera_type_t> 返回支持的相机类型列表
     *
     * \endif
     */
    virtual std::vector<ob2_camera_type_t> get_supported_camera_type_list() {
        ob2_status_t status;
        auto         count = ob2_device_get_supported_camera_count(m_device_handle, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);

        std::vector<ob2_camera_type_t> camera_list;
        for(uint32_t index = 0; index < count; index++) {
            auto camera_type = ob2_device_get_supported_camera_type(m_device_handle, index, &status);
            CHECK_OB2_STATUS_ERROR_THROW(status);
            camera_list.emplace_back(camera_type);
        }
        return camera_list;
    }

    /**
     * \if English
     *
     * @brief Get the list of camera stream profile supported by the specified camera type.
     *
     * @attention The value for @camera_type needs to be the type of camera supported by the device，
     * otherwise，an std::logic_error exception will be thrown.
     *
     * @param camera_type Type of camera.
     * @return std::vector<ob2_camera_stream_profile_t> Return the list of camera stream profile.
     *
     * \else
     *
     * @brief 获取指定相机类型支持的流配置列表
     *
     * @attention @camera_type 传入的值需要是该设备支持的相机类型，否则将会抛出 std::logic_error 异常。
     *
     * @param camera_type 相机类型
     * @return std::vector<ob2_camera_stream_profile_t> 返回流配置列表
     *
     * \endif
     */
    virtual std::vector<ob2_camera_stream_profile_t> get_camera_stream_profile_list(ob2_camera_type_t camera_type) {
        ob2_status_t status;
        auto         count = ob2_device_get_camera_stream_profile_count(m_device_handle, camera_type, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);

        std::vector<ob2_camera_stream_profile_t> profile_list;
        for(uint32_t index = 0; index < count; index++) {
            auto profile = ob2_device_get_camera_stream_profile(m_device_handle, camera_type, index, &status);
            CHECK_OB2_STATUS_ERROR_THROW(status);
            profile_list.emplace_back(std::move(profile));
        }
        return profile_list;
    }

    /**
     * \if English
     *
     * @brief Get the list of camera default stream profile supported by the specified camera type.
     *
     * @attention The value for @camera_type needs to be the type of camera supported by the device，
     * otherwise，an std::logic_error exception will be thrown.
     *
     * @param camera_type Type of camera
     * @return ob2_camera_stream_profile_t Returns the default stream profile
     *
     * \else
     *
     * @brief 获取指定相机类型的默认流配置列表
     *
     * @attention @camera_type 传入的值需要是该设备支持的相机类型，否则将会抛出 std::logic_error 异常。
     *
     * @param camera_type 相机类型
     * @return ob2_camera_stream_profile_t 返回默认流配置
     *
     * \endif
     */
    virtual ob2_camera_stream_profile_t get_default_camera_stream_profile(ob2_camera_type_t camera_type) {
        ob2_status_t status;
        auto         profile = ob2_device_get_camera_stream_profile(m_device_handle, camera_type, OB2_DEFAULT_STREAM_PROFILE, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        return profile;
    }

    /**
     * \if English
     *
     * @brief Get the list of camera stream profile that support image alignment.
     * @brief When configuring the image alignment mode ，you can use this function to check whether the configured camera stream profile support the
     * @image_align_mode.
     *
     * @attention @image_align_mode can not be ::OB2_IMAGES_ALIGN_MODE_DISABLE ，otherwise，an std::logic_error exception will be thrown.
     *
     * @param align_mode Image alignment mode
     * @param[in] target_camera_stream_profile target_camera_stream_profile the target camera's steam profile（such as：::OB2_IMAGES_ALIGN_MODE_D2C_HARDWARE was
     * passed， the target camera is color-camera）.
     * @return uint32_t Returns a list of camera data stream profile that support alignment
     *
     * \else
     *
     * @brief 获取支持对齐的相机数据流配置列表
     * @brief 在 cameras_config 中配置图像对齐模式时，可以先通过当前接口查询配置的不同相机数据流是否支持该对齐模式。
     *
     * @attention @image_align_mode 不能为 ::OB2_IMAGES_ALIGN_MODE_DISABLE ，否则将会抛出 std::logic_error 异常。
     *
     * @param align_mode 对齐模式
     * @param[in] target_camera_stream_profile 对齐的目标相机数据流配置（如：对齐模式为 ::OB2_IMAGES_ALIGN_MODE_D2C_HARDWARE ，则目标相机是 Color 相机）
     * @return uint32_t 返回支持对齐的相机数据流配置列表
     *
     * \endif
     */
    virtual std::vector<ob2_camera_stream_profile_t> get_alignable_camera_stream_profile_list(ob2_images_align_mode_t            align_mode,
                                                                                              const ob2_camera_stream_profile_t &target_camera_stream_profile) {
        ob2_status_t status;

        auto count = ob2_device_get_alignable_camera_stream_profile_count(m_device_handle, align_mode, target_camera_stream_profile, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);

        std::vector<ob2_camera_stream_profile_t> profile_list;
        for(uint32_t index = 0; index < count; index++) {
            auto profile = ob2_device_get_alignable_camera_stream_profile(m_device_handle, align_mode, target_camera_stream_profile, index, &status);
            CHECK_OB2_STATUS_ERROR_THROW(status);
            profile_list.emplace_back(std::move(profile));
        }
        return profile_list;
    }

    /**
     * \if English
     *
     * @brief Create an cameras_config object.
     * @brief The cameras_config use to configures the working mode of each camera in the device and the processing mode of camera images within the
     * SDK.
     * @brief Once created, a default stream profile is configured for all supported cameras，but all cameras are disabled by default.
     *
     * @attention After @device destruction, the relevant configuration interface will no longer be accessible through the camera configuration object,
     * otherwise std::runtime_error will be thrown.
     *
     * @return std::shared_ptr<cameras_config> Returns the smart pointer of the camera configuration object
     *
     * \else
     *
     * @brief 创建设备的相机配置
     * @brief 相机配置用于配置设备内各相机的工作方式以及 SDK 内部对相机图像的处理方式（具体支持的功能请查看 cameras_config 各接口说明）
     * @brief 相机配置创建后会为所有支持的相机配置一个默认的流配置，但是所有相机都是默认未使能的。
     *
     * @attention 在 @device 析构后，将不再可以通过相机配置对象去访问相关配置接口，否则将会抛出 std::runtime_ERROR 。
     *
     * @return std::shared_ptr<cameras_config> 返回相机配置对象智能指针
     *
     * \endif
     */
    virtual std::shared_ptr<cameras_config> create_cameras_config() {
        ob2_status_t status;
        auto         cameras_config_handle = ob2_device_create_cameras_config(m_device_handle, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        return std::make_shared<cameras_config>(std::move(cameras_config_handle));
    }

    /**
     * \if English
     *
     * @brief Start in-device cameras work (start stream)
     * @brief The @cameras_config is used to enable the enabled camera stream, and to configure the device and the relevant work modules inside the SDK
     * according to the configuration.
     * @brief After starting the data stream, the SDK will internally generate capture for each camera output and cache the capture in the internal queue, users
     * need to get capture through @ref device::get_capture function, and then get each camera image data through capture.
     *
     * @attention After starting the cameras work in the device, you need to loop through @ref device::get_capture function to get capture in time, otherwise
     * the image data will be lost when the internal cache queue overflows.
     *
     * @param[in] cam_config Camera configuration; You can pass in ::OB2_DEFAULT_CAMERAS_CONFIG so that the SDK will start all cameras through each camera's
     * default stream profile.
     *
     * \else
     *
     * @brief 启动设备内相机工作（开流）
     * @brief 会根据 @cameras_config 开启已使能的相机数据流，同时也会根据配置内容完成设备、SDK 内部相关工作模块的配置。
     * @brief 开启数据流后，SDK 内部会将各相机输出的图像生成 capture，并将 capture 缓存在内部队列，用户需要通过 @ref device::get_capture 接口获取 capture，
     * 进而通过 capture 获取各相机图像数据。
     *
     * @attention 启动设备内相机工作后, 需要及时地通过 @ref device::get_capture 接口循环获取 capture，否则内部缓存队列溢出后会丢失图像数据。
     *
     * @param[in] cam_config 相机配置；可传入 ::OB2_DEFAULT_CAMERAS_CONFIG, 这样 SDK 将通过各相机的默认流配置启动所有相机。
     *
     * \endif
     */
    virtual void start_cameras(std::shared_ptr<cameras_config> cam_config) {
        ob2_status_t         status;
        ob2_cameras_config_t cameras_config_handle = OB2_DEFAULT_CAMERAS_CONFIG;
        if(cam_config) {
            cameras_config_handle = cam_config->get_handle();
        }
        ob2_device_start_cameras(m_device_handle, cameras_config_handle, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

    /**
     * \if English
     *
     * @brief Start in-device cameras work by returning capture via a callback (start stream)
     * @brief The @cameras_config_handle is used to enable the enabled camera stream, and to configure the device and the relevant work modules inside the SDK
     * according to the configuration.
     * @brief After starting the data stream, the SDK internally generates capture from the output of each camera and returns capture via the callback function
     * @cb
     *
     * @attention The callback function @cb is a user-written function that needs to be executed in less than the capture generation period (determined by the
     * image output period of the stream with the highest frame rate of the enabled camera), otherwise it will cause the SDK internal cache queue to overflow
     * and lose image data, and the image data will have a cumulative delay resulting in poor image realtime. For some models of devices, this may even lead to
     * stopped streams.
     *
     * @param[in] cam_config Camera configuration; You can pass in ::OB2_DEFAULT_CAMERAS_CONFIG so that the SDK will start all cameras through each camera's
     * default stream profile.
     * @param[in] cb capture callback function
     *
     * \else
     *
     * @brief 通过回调返回 capture 的方式启动设备内相机工作（开流）
     * @brief 会根据 cameras_config 开启已使能的相机数据流，同时也会根据配置内容完成设备、SDK 内部相关工作模块的配置
     * @brief 开启数据流后，SDK 内部会将各相机输出的图像生成 capture，并通过回调函数 cb 返回 capture
     *
     * @attention 回调函数 @cb 是用户自行编写的函数，需要保证该函数的执行时间小于 capture 生成周期（由已使能的相机中数据流帧率最大的数据流图像输出周期决定），
     * 否则会导致 SDK 内部缓存队列溢出而丢失图像数据，并且图像数据会有累加延时导致图像实时性变差。对于某些型号的设备，甚至可能会导致停流。
     *
     * @param[in] cam_config 相机配置，可可传入 ::OB2_DEFAULT_CAMERAS_CONFIG, 这样 SDK 将通过各相机的默认流配置启动所有相机。
     * @param[in] cb capture 回调函数
     *
     * \endif
     */
    virtual void start_cameras_with_callback(std::shared_ptr<cameras_config> cam_config, capture_cb cb) {
        ob2_status_t         status;
        ob2_cameras_config_t cameras_config_handle = OB2_DEFAULT_CAMERAS_CONFIG;
        if(cam_config) {
            cameras_config_handle = cam_config->get_handle();
        }

        m_capture_cb = cb;

        ob2_device_start_cameras_with_callback(m_device_handle, cameras_config_handle, &device::capture_callback, this, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

    /**
     * \if English
     *
     * @brief Update device cameras_config
     * @brief Enables configuration updates during device camera operation, such as turning on or off the data stream for a particular type of camera without
     * stopping the camera
     *
     * @attention You need to start the cameras in the device first, otherwise there will be no practical meaning to call this function
     * @attention Multi-camera sync configuration and external sync configuration update within the device are not currently supported
     *
     * @param[in] cam_config Cameras_config for updates
     *
     * \else
     *
     * @brief 更新设备相机配置
     * @brief 可实现设备相机工作过程中的配置更新，比如在不停止相机工作的情况下打开或关闭某一类型相机的数据流
     *
     * @attention 需求先启动设备内相机工作，否则调用本接口将没有任何实际意义
     * @attention 当前不支持设备内多相机同步配置及外部同步配置更新
     *
     * @param[in] cam_config 用于更新的相机配置
     *
     * \endif
     */
    virtual void update_cameras_config(std::shared_ptr<cameras_config> cam_config) {
        ob2_status_t status;
        ob2_device_update_cameras_config(m_device_handle, cam_config->get_handle(), &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

    /**
     * \if English
     *
     * @brief Stops cameras work in the device (stop stream)
     *
     * \else
     *
     * @brief 停止设备内相机工作（关流）
     *
     * \endif
     */
    virtual void stop_cameras() {
        ob2_status_t status;
        ob2_device_stop_cameras(m_device_handle, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

    /**
     * \if English
     *
     * @brief Get the cameras calibration parameters under the current cameras_config
     *
     * @attention The calibration parameters obtained from different cameras configurations are not the same. So you need to make sure that you complete the
     * cameras_config first and then pass in the cameras_config to get the parameters.
     *
     * @param[in] cam_config Cameras_config for updates
     * @return ob2_cameras_calibration_t Return cameras calibration parameters
     *
     * \else
     *
     * @brief 获取当前配置下的相机标定参数
     *
     * @attention 不同的相机配置获取得到的标定参数是不一样的。所以需要先确保先完成相机配置，然后传入相机配置获取参数。
     *
     * @param[in] cam_config 用于更新的相机配置
     * @return ob2_cameras_calibration_t 相机标定参数
     *
     * \endif
     */
    virtual ob2_cameras_calibration_t get_cameras_calibration(std::shared_ptr<cameras_config> cam_config) {
        ob2_status_t status;
        auto         calibration = ob2_device_get_cameras_calibration(m_device_handle, cam_config->get_handle(), &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        return calibration;
    }

    /**
     * \if English
     *
     * @brief Get capture
     * @brief Used in conjunction with the @ref device::start_cameras function, this function is used to obtain the capture generated by the received image
     * after starting the cameras in the device.
     * @brief When this function is called, if the SDK does not have a capture cache in its internal queue, it will wait blockingly until a capture is
     * successfully acquired or until the @timeout_msec has been exceeded.
     *
     * @attention Once you have started the cameras in the device, you need to cycle through this function to get capture in time, otherwise the image data will
     * be lost when the internal cache queue overflows.
     * @attention If the capture is not successfully obtained after the @timeout_msec set time, an std::runtime_error exception will be thrown
     *
     * @param[in] timeout_msec timeout_msec Wait timeout, can be set to ::OB2_WAIT_INFINITE for unlimited waiting.
     * @return std::shared_ptr<capture Returns a smart pointer to the capture object
     *
     * \else
     *
     * @brief 获取 capture
     * @brief 配合 @ref device::start_cameras 接口使用，在启动设备内相机工作后，通过本接口获取接收到图像后生成的 capture。
     * @brief 调用本接口后，如果 SDK 内部未有 capture 缓存在队列中，会进行阻塞式等待，直到成功获取到 capture 或者等待超过了 timeout_msec 设定的时间。
     *
     * @attention 启动设备内相机工作，需要及时地通过本接口循环获取 capture，否则内部缓存队列溢出后会丢失图像数据。
     * @attention 超过 @timeout_msec 设置时间后还未成功获取到 capture，将会抛出 std::runtime_error 异常
     *
     * @param[in] timeout_msec 等待超时时间，可以设置为 ::OB2_WAIT_INFINITE 表示不限时等待。
     * @return std::shared_ptr<capture 返回 capture 对象智能指针
     *s
     * \endif
     */
    virtual std::shared_ptr<capture> get_capture(int32_t timeout_msec) {
        ob2_status_t status;
        auto         capture_handle = ob2_device_get_capture(m_device_handle, timeout_msec, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        if(nullptr != capture_handle) {
            return std::make_shared<capture>(std::move(capture_handle));
        }
        return nullptr;
    }

public:
    /**
     * \if English
     *
     * @brief Get the list of IMU sensors supported by the device
     * @brief IMU (Inertial Measurement Unit) is a composite sensor, which is one or a combination of one or more of these sensors such as accelerometers,
     * gyroscopes, magnetometers, etc. This function is used for the interrogation of these individual sensors
     *
     * @return std::vector<ob2_imu_sensor_type_t> Returns the list of IMU sensors
     *
     * \else
     * @brief 获取设备支持的 IMU 传感器列表
     * @brief IMU(惯性测量单元) 是一个复合传感器，是加速度计、陀螺仪、磁力计这几个传感器中的一个或多个组合，
     *  本接口用于这些独立传感器的查询
     *
     * @return std::vector<ob2_imu_sensor_type_t> 返回 IMU 传感器列表
     *
     * \endif
     */
    virtual std::vector<ob2_imu_sensor_type_t> get_supported_imu_sensor_type_list() {
        ob2_status_t status;
        auto         count = ob2_device_get_supported_imu_sensor_count(m_device_handle, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);

        std::vector<ob2_imu_sensor_type_t> imu_sensor_list;
        for(uint32_t index = 0; index < count; index++) {
            auto sensor_type = ob2_device_get_supported_imu_sensor_type(m_device_handle, index, &status);
            imu_sensor_list.push_back(sensor_type);
        }
        return imu_sensor_list;
    }

    /**
     * \if English
     *
     * @brief Get the list of accelerometer stream profiles
     * @brief The accelerometer stream profiles can be used to configure the sampling rate and range of the accelerometer
     *
     * @return std::vector<ob2_accel_stream_profile_t> Returns the list of accelerometer stream profiles
     *
     * \else
     *
     * @brief 获取加速度计流配置列表
     * @brief 加速度计流配置可用于配置加速度计的采样率和量程
     *
     * @return std::vector<ob2_accel_stream_profile_t> 返回加速度计流配置列表
     *
     * \endif
     */
    virtual std::vector<ob2_accel_stream_profile_t> get_accel_stream_profile_list() {
        ob2_status_t status;
        auto         count = ob2_device_get_accel_stream_profile_count(m_device_handle, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);

        std::vector<ob2_accel_stream_profile_t> profile_list;
        for(uint32_t index = 0; index < count; index++) {
            auto profile = ob2_device_get_accel_stream_profile(m_device_handle, index, &status);
            CHECK_OB2_STATUS_ERROR_THROW(status);
            profile_list.emplace_back(std::move(profile));
        }
        return profile_list;
    }

    /**
     * \if English
     *
     * @brief Get the list of gyroscope stream profiles
     * @brief Gyroscope stream profiles for configuring the sampling rate and range of the gyroscope
     *
     * @return std::vector<ob2_gyro_stream_profile_t> Returns the list of gyroscope stream profiles
     *
     * \else
     *
     * @brief 获取陀螺仪流配置列表
     * @brief 陀螺仪流配置可用于配置陀螺仪的采样率和量程
     *
     * @return std::vector<ob2_gyro_stream_profile_t> 返回陀螺仪流配置列表
     *
     * \endif
     */
    virtual std::vector<ob2_gyro_stream_profile_t> get_gyro_stream_profile_list() {
        ob2_status_t status;
        auto         count = ob2_device_get_gyro_stream_profile_count(m_device_handle, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);

        std::vector<ob2_gyro_stream_profile_t> profile_list;
        for(uint32_t index = 0; index < count; index++) {
            auto profile = ob2_device_get_gyro_stream_profile(m_device_handle, index, &status);
            CHECK_OB2_STATUS_ERROR_THROW(status);
            profile_list.emplace_back(std::move(profile));
        }
        return profile_list;
    }

    /**
     * \if English
     *
     * @brief Creating an imu_config
     * @brief The imu_config is created with a default stream profile for all supported sensors, but all sensors are unenabled by default.
     *
     * @return std::shared_ptr<imu_config Returns a smart pointer to the IMU configuration object
     *
     * \else
     *
     * @brief 创建 IMU 配置
     * @brief IMU 配置创建后会为所有支持的 sensor 配置一个默认的流配置，但是所有 sensor 都是默认未使能的
     *
     * @return std::shared_ptr<imu_config 返回 IMU 配置对象智能指针
     *
     * \endif
     */
    virtual std::shared_ptr<imu_config> create_imu_config() {
        ob2_status_t status;
        auto         imu_config_handle = ob2_device_create_imu_config(m_device_handle, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        return std::make_shared<imu_config>(std::move(imu_config_handle));
    }

    /**
     * \if English
     *
     * @brief Start IMU sensors work in the device (start stream)
     * @brief The sensor data stream will be enabled according to @imu_config and the configuration of the device and other related work modules
     * within the SDK will also be completed according to the configuration
     * @brief After the data stream is enabled, the SDK will generate a imu_sample of the adoption data output by each Sensor and cache the imu_sample in an
     * internal queue, which users need to pass
     * @ref device::get_imu_sample interface to obtain imu_sample, and then obtain the adoption data of each sensor through the imu_sample
     *
     * @attention After starting the IMU sensors work in the device, you need to loop through the @ref device::get_imu_sample function to get the imu_sample in
     * time, otherwise the internal cache queue will be overflowed and the data will be lost.
     *
     * @param[in] imu_config IMU configuration. You can pass ::OB2_DEFAULT_IMU_CONFIG, so that the SDK will start all IMU sensors with the default
     * stream configuration of each sensor.
     *
     * \else
     *
     * @brief 启动设备内 IMU 工作（开流）
     * @brief 会根据 imu_config 开启已使能的 Sensor 数据流，同时也会根据配置内容完成设备、SDK 内部其他相关工作模块的配置
     * @brief 开启数据流后，SDK 内部会将各 Sensor 输出的采用数据生成 imu_sample，并将 imu_sample 缓存在内部队列，用户需要通过
     *  @ref device::get_imu_sample 接口获取 imu_sample，进而通过 imu_sample 获取各 sensor 的采用数据
     *
     * @attention 启动设备内相机工作后, 需要及时地通过 @ref device::get_imu_sample 接口循环获取 imu_sample，否则内部缓存队列溢出后会丢失数据。
     *
     * @param[in] imu_config IMU 配置，调用完本接口后可立即停释放配置句柄。可传入 ::OB2_DEFAULT_IMU_CONFIG, 这样 SDK 将通过各 Sensor 的默认流配置启动所有 Sensor
     *
     * \endif
     */
    virtual void start_imu(std::shared_ptr<imu_config> imu_config) {
        ob2_status_t     status;
        ob2_imu_config_t imu_config_handle = OB2_DEFAULT_IMU_CONFIG;
        if(imu_config) {
            imu_config_handle = imu_config->get_handle();
        }

        ob2_device_start_imu(m_device_handle, imu_config_handle, &status);

        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

    /**
     * \if English
     *
     * @brief Start IMU sensors work in the device by returning imu_sample as a callback
     * @brief The sensor data stream will be enabled according to @imu_config_handle and the configuration of the device and other related work modules
     * within the SDK will also be completed according to the configuration
     * @brief Once the data stream is turned on, the SDK internally generates imu_sample from the adopted data output by each Sensor and returns imu_sample via
     * the callback function @cb.
     *
     * @attention The callback function @cb is a user written function that needs to be executed in less than the imu_sample generation period (determined by
     * the data output period of the sensor with the highest sample rate enabled), otherwise the SDK internal cache queue will overflow and data will be lost
     * and there will be a cumulative delay in the data resulting in poor real time performance. For some device models, this may even lead to a stoppage of the
     * stream.
     *
     * @param[in] imu_config IMU configuration handle. You can pass ::OB2_DEFAULT_IMU_CONFIG, so that the SDK will start all IMU sensors with the default
     * stream configuration of each sensor
     * @param[in] cb imu_sample callback function
     *
     * \else
     *
     * @brief 通过回调返回 imu_sample 的方式启动设备 IMU 工作（开流）
     * @brief 会根据 imu_config 开启已使能的 Sensor 数据流，同时也会根据配置内容完成设备、SDK 内部其他相关工作模块的配置
     * @brief 开启数据流后，SDK 内部会将各 Sensor 输出的采用数据生成 imu_sample，并通过回调函数 cb 返回 imu_sample
     *
     * @attention 回调函数 cb 是用户自行编写的函数，需要保证该函数的执行时间小于 imu_sample 生成周期（由已使能的 Sensor 中采样率最大的采用数据输出周期决定），
     * 否则会导致 SDK 内部缓存队列溢出而丢失数据，并且数据会有累加延时导致实时性变差。对于某些型号的设备，甚至可能会导致停流。
     *
     * @param[in] imu_config IMU 配置句柄，调用完本接口后可立即停释放配置句柄。可传入 ::OB2_DEFAULT_IMU_CONFIG, 这样 SDK 将通过各 Sensor 的默认流配置启动所有
     * Sensor
     * @param[in] cb imu_sample 回调函数
     *
     * \endif
     */
    virtual void start_imu_with_callback(std::shared_ptr<imu_config> imu_config, imu_sample_cb cb) {
        ob2_status_t     status;
        ob2_imu_config_t imu_config_handle = OB2_DEFAULT_IMU_CONFIG;
        if(imu_config) {
            imu_config_handle = imu_config->get_handle();
        }

        m_imu_sample_cb = cb;

        ob2_device_start_imu_with_callback(m_device_handle, imu_config_handle, &device::imu_sample_callback, this, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

    /**
     * \if English
     *
     * @brief Stop IMU Sensor work in device (stop stream)
     *
     * \else
     *
     * @brief 停止设备内 IMU 工作（关流）
     *
     * \endif
     */
    virtual void stop_imu() {
        ob2_status_t status;
        ob2_device_stop_imu(m_device_handle, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

    /**
     * \if English
     *
     * @brief Get IMU sampling data
     * @brief imu_sample is a composite sample containing one sample of each enabled Sensor.
     * @brief Used in conjunction with the @ref device::start_imu function to obtain the imu_sample generated from each Sensor sample data received after the
     * IMU has been started in the device.
     * @brief When this function is called, if the SDK does not have an imu_sample cached internally in the queue, it will wait blockingly until the imu_sample
     * is successfully fetched or until the time set by @timeout_msec is exceeded.
     *
     * @attention After starting the IMU work within the device, you need to loop through this function to get the imu_sample in time, otherwise the data will
     * be lost when the internal cache queue overflows.
     * @attention If the imu_sample is not successfully fetched after the time set by @timeout_msec, an std::runtime_error exception will be thrown.
     *
     * @param[in] timeout_msec Wait timeout, can be set to ::OB2_WAIT_INFINITE for unlimited waiting.
     * @return std::shared_ptr<imu_sample> Returns a smart pointer to an imu_sample object
     *
     * \else
     *
     * @brief 获取 IMU 采样数据
     * @brief imu_sample 是一个复合采样数据，包含每个已启用 Sensor 的一次采样数据
     * @brief 配合 @ref device::start_imu 接口使用，在启动设备内 IMU 工作后，通过本接口获取接收到各 Sensor 样数据后生成的 imu_sample。
     * @brief 调用本接口后，如果 SDK 内部未有 imu_sample 缓存在队列中，会进行阻塞式等待，直到成功获取到 imu_sample 或者等待超过了 @timeout_msec 设定的时间。
     *
     * @attention 启动设备内 IMU 工作后，需要及时地通过本接口循环获取 imu_sample，否则内部缓存队列溢出后会丢失数据。
     * @attention 超过 timeout_msec 设置时间后还未成功获取到 imu_sample，将会抛出 std::runtime_error 异常
     *
     * @param[in] timeout_msec 等待超时时间，可以设置为 ::OB2_WAIT_INFINITE 表示不限时等待。
     * @return std::shared_ptr<imu_sample> 返回 imu_sample 对象智能指针
     *
     * \endif
     */
    std::shared_ptr<imu_sample> get_imu_sample(int32_t timeout_msec) {
        ob2_status_t status;
        auto         imu_sample_handle = ob2_device_get_imu_sample(m_device_handle, timeout_msec, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        return std::make_shared<imu_sample>(std::move(imu_sample_handle));
    }

    /**
     * \if English
     *
     * @brief Update the device imu_config
     * @brief Configuration updates during the device IMU Sensors starting, such as turning the data stream of a Sensor on or off without stopping the all IMU
     * sensors.
     *
     * @attention The device IMU Sensors needs to be started first, otherwise there is no real point in calling this function.
     *
     * @param[in] config IMU configuration for updates
     *
     * \else
     *
     * @brief 更新设备 IMU 配置
     * @brief 可实现设备 IMU 过程中的配置更新，比如在不停止 IMU 工作的情况下打开或关闭某一 Sensor 的数据流
     *
     * @attention 需要先启动设备 IMU 工作，否则调用本接口将没有任何实际意义
     *
     * @param[in] config 用于更新的 IMU 配置
     *
     * \endif
     */
    void update_imu_config(std::shared_ptr<imu_config> config) {
        ob2_status_t status;
        ob2_device_update_imu_config(m_device_handle, config->get_handle(), &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

public:
    /**
     * \if English
     *
     * @brief Upgrade the device firmware
     *
     * @attention After the firmware is upgraded, you need to restart the device (some devices will restart automatically)
     *
     * @param[in] firmware_file_path The firmware address of the device
     * @param[in] callback Upgrade status callback
     * @param[in] enable_async_mode Asynchronous mode enabled (true: the call to this interface will return immediately, and a new thread will be opened in the
     * SDK to continue to complete the upgrade task; false: This interface will block execution until the upgrade task is completed or fails to exit)
     *
     * \else
     *
     * @brief 升级设备固件
     *
     * @attention 固件升级完后需要重启设备（部分设备会自动重启）
     *
     * @param[in] firmware_file_path 设备固件地址
     * @param[in] callback 升级状态回调
     * @param[in] enable_async_mode 异步模式使能（true：本接口调用会立即返回，SDK 内部会新开线程继续完成升级任务；
     *  false：本接口会阻塞式执行，直到升级任务完成或失败退出）
     *
     * \endif
     */
    virtual void update_firmware(const char *firmware_file_path, firmware_update_state_cb callback, ob2_enable_ctrl_t enable_async_mode) {
        ob2_status_t status;
        ob2_device_update_firmware(m_device_handle, firmware_file_path, &device::firmware_update_state_callback, this, enable_async_mode, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

    /**
     * \if English
     *
     * @brief The device restarts
     * @brief Triggering a device restart will cause the device to be abnormal and then reinstalled
     *
     * @attention When this interface is called, the device is removed, so do not access the original device handle anymore, but shut down the device
     * immediately. After the device restarts successfully, reinstall successfully, and then reopen the device to obtain a new device handle.
     *
     * \else
     *
     * @brief 设备重启
     * @brief 触发设备重启，会导致设备异常然后重新安装
     *
     * @attention 调用本接口后，设备会被移除，所以不要再对原设备句柄进行访问，而是立即关闭设备。
     *  待设备重启完成后重新安装成功，再重新打开设备获取新的设备句柄。
     *
     * \endif
     */
    virtual void reboot() {
        ob2_status_t status;
        ob2_device_reboot(m_device_handle, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

    /**
     * \if English
     *
     * @brief Synchronize the device clock
     * @brief After the device boots, the device clock starts clocking from zero. Through this interface, the device can be assigned the time to synchronize the
     * device clock with the host clock
     *
     * @attention Due to the problem of device clock accuracy, the clock synchronization error between the host and the device may increase after a certain
     * period of time after clock synchronization, so it is recommended that according to the application scenario. This interface can be called regularly to
     * synchronize the device clock.
     *
     * \else
     *
     * @brief 同步设备时钟
     * @brief 设备启动后，设备时钟会从零开始计时。通过本接口，可实现向设备授时，使设备时钟与主机时钟同步
     *
     * @attention 由于设备时钟精度问题，时钟同步后经过一定时间主机与设备的时钟同步误差可能会加大，所以建议依据应用场景，
     *  可定时调用本接口同步设备时钟。
     *
     * \endif
     */
    virtual void sync_clock_with_host() {
        ob2_status_t status;
        ob2_device_sync_clock_with_host(m_device_handle, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

public:
    /**
     * \if English
     *
     * @brief Gets the list of commands supported by the device
     *
     * @return std::vector<ob2_command_info_t> Returns the list of commands supported by the device
     *
     * \else
     *
     * @brief 获取设备支持的命令信息列表
     *
     * @return std::vector<ob2_command_info_t> 返回设备支持的命令信息列表
     *
     * \endif
     */
    virtual std::vector<ob2_command_info_t> get_supported_command_info_list() {
        ob2_status_t status;
        auto         count = ob2_device_get_supported_command_count(m_device_handle, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);

        std::vector<ob2_command_info_t> command_info_list;
        for(uint32_t index = 0; index < count; index++) {
            auto command_info = ob2_device_get_supported_command_info(m_device_handle, index, &status);
            CHECK_OB2_STATUS_ERROR_THROW(status);
            command_info_list.emplace_back(std::move(command_info));
        }

        return command_info_list;
    }

    /**
     * \if English
     *
     * @brief Use the command ID to obtain the command information supported by the device
     *
     * @attention @command_id needs to be an ID supported by the device, if not, An std::logic_error exception will be thrown.
     *
     * @param[in] command_id Command ID
     * @return ob2_command_info_t Returns command information
     *
     * \else
     *
     * @brief 通过命令 id 获取设备支持的命令信息
     *
     * @attention @command_id 需要是设备支持的 id，如果是不支持的，将会抛出 std::logic_error 异常。
     *
     * @param[in] command_id 命令 id
     * @return ob2_command_info_t 返回命令信息
     *
     * \endif
     */
    virtual ob2_command_info_t get_supported_command_info_by_id(ob2_command_id_t command_id) {
        ob2_status_t status;
        auto         command_info = ob2_device_get_supported_command_info_by_id(m_device_handle, command_id, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        return command_info;
    }

    /**
     * \if English
     *
     * @brief Check the access permissions of the device command
     *
     * @param[in] command_id Command ID
     * @param[in] permission Permission type
     * @return true The device supports access permission
     * @return false The device does not support access permission
     *
     * \else
     *
     * @brief 检查设备命令访问权限
     *
     * @param[in] command_id 命令 id
     * @param[in] permission 权限类型
     * @return true 该设备支持该访问权限
     * @return false 该设备不支持该访问权限
     *
     * \endif
     */
    virtual bool check_command_access_permission(ob2_command_id_t command_id, ob2_access_permission_t permission) {
        ob2_status_t status;
        auto         command_info = ob2_device_check_command_access_permission(m_device_handle, command_id, permission, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        return command_info;
    }

    /**
     * \if English
     *
     * @brief Gets the device property value of Boolean type
     * @brief Boolean type properties are a type of device command
     *
     * @attention If the device does not support the read permission of the command specified by @command_id, an std::logic_error exception is thrown.
     *
     * @param[in] command_id Device command ID
     * @return bool Returns the value of the property
     *
     * \else
     *
     * @brief 获取设备布尔类型属性值
     * @brief 布尔类型属性是设备命令的一种
     *
     * @attention 如果该设备不支持 @command_id 指定命令的读取权限，将会抛出 std::logic_error 异常。
     *
     * @param[in] command_id 设备命令 id
     * @return bool 返回属性值
     *
     * \endif
     */
    virtual bool get_bool_property_value(ob2_command_id_t command_id) {
        ob2_status_t status;
        bool         value = ob2_device_get_bool_property_value(m_device_handle, command_id, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        return value;
    }

    /**
     * \if English
     *
     * @brief Set the device property value of Boolean type
     *
     * @attention If the device does not support write permission for @command_id specified command, an std::logic_error exception will be thrown.
     *
     * @param[in] value The value that needs to be set
     * @param[in] command_id Device command ID
     *
     * \else
     *
     * @brief 设置设备布尔类型属性值
     *
     * @attention 如果该设备不支持 @command_id 指定命令的写权限，将会抛出 std::logic_error 异常。
     *
     * @param[in] value 需要设置的值
     * @param[in] command_id 设备命令 id
     *
     * \endif
     */
    virtual void set_bool_property_value(ob2_command_id_t command_id, bool value) {
        ob2_status_t status;
        ob2_device_set_bool_property_value(m_device_handle, command_id, value, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

    /**
     * \if English
     *
     * @brief Sets the default value for a property of the Boolean type of the device
     *
     * @attention If the device does not support the write and read permission of the command specified by @command_id, an std::logic_error exception will be
     * thrown.
     *
     * @param[in] command_id Device command ID
     * @return bool Returns the default value of the property
     *
     * \else
     *
     * @brief 设置设备布尔类型属性默认值
     *
     * @attention 如果该设备不支持 @command_id 指定命令的写读权限，将会抛出 std::logic_error 异常。
     *
     * @param[in] command_id 设备命令 id
     * @return bool 返回属性默认值
     *
     * \endif
     */
    virtual bool get_bool_property_default_value(ob2_command_id_t command_id) {
        ob2_status_t status;
        bool         def = ob2_device_get_bool_property_default_value(m_device_handle, command_id, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        return def;
    }

    /**
     * \if English
     *
     * @brief Gets the device property value of the integer type
     * @brief The integer type property is a type of device command
     *
     * @attention If the device does not support the write and read permission of the command specified by @command_id, an std::logic_error exception will be
     * thrown.
     *
     * @param[in] command_id Device command ID
     * @return int Returns the value of the property
     *
     * \else
     *
     * @brief 获取设备整型类型属性值
     * @brief 整型类型属性是设备命令的一种
     *
     * @attention 如果该设备不支持 @command_id 指定命令的读取权限，将会抛出 std::logic_error 异常。
     *
     * @param[in] command_id 设备命令 id
     * @return int 返回属性值
     *
     * \endif
     */
    virtual int get_int_property_value(ob2_command_id_t command_id) {
        ob2_status_t status;
        int          value = ob2_device_get_int_property_value(m_device_handle, command_id, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        return value;
    }

    /**
     * \if English
     *
     * @brief Sets the value for a property of the integer type of the device
     *
     * @attention If the device does not support write permission for the @command_id specified command, an std::logic_error exception is thrown.
     *
     * @param[in] value The value that needs to be set
     * @param[in] command_id Device command ID
     *
     * \else
     *
     * @brief 设置设备整型类型属性值
     *
     * @attention 如果该设备不支持 @command_id 指定命令的写权限，将会抛出 std::logic_error 异常。
     *
     * @param[in] value 需要设置的值
     * @param[in] command_id 设备命令 id
     *
     * \endif
     */
    virtual void set_int_property_value(ob2_command_id_t command_id, int value) {
        ob2_status_t status;
        ob2_device_set_int_property_value(m_device_handle, command_id, value, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

    /**
     * \if English
     *
     * @brief Gets the property capabilities of the device integer type
     * @brief Property capabilities include their maximum, minimum, step, and default values
     *
     * @attention If the device does not support the read permission of the command specified by @command_id, an std::logic_error exception is thrown.
     *
     * @param[in] command_id Device command ID
     * @return ob2_int_property_capability_t Returns property capabilities
     *
     * \else
     *
     * @brief 获取设备整型类型属性能力
     * @brief 属性能力包括其最大值、最小值、步进值、默认值
     *
     * @attention 如果该设备不支持 @command_id 指定命令的读取权限，将会抛出 std::logic_error 异常。
     *
     * @param[in] command_id 设备命令 id
     * @return ob2_int_property_capability_t 返回属性能力
     *
     * \endif
     */
    virtual ob2_int_property_capability_t get_int_property_capability(ob2_command_id_t command_id) {
        ob2_status_t                  status;
        ob2_int_property_capability_t capability = ob2_device_get_int_property_capability(m_device_handle, command_id, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        return capability;
    }

    /**
     * \if English
     *
     * @brief Gets the device property value of the float type
     * @brief The floating type property is a type of device command
     *
     * @attention If the device does not support the read permission of the command specified by @command_id, an std::logic_error exception is thrown.
     *
     * @param[in] command_id Device command ID
     * @return float Returns the value of the property
     *
     * \else
     *
     * @brief 获取设备浮点类型属性值
     * @brief 浮点类型属性是设备命令的一种
     *
     * @attention 如果该设备不支持 @command_id 指定命令的读取权限，将会抛出 std::logic_error 异常。
     *
     * @param[in] command_id 设备命令 id
     * @return float 返回属性值
     *
     * \endif
     */
    virtual float get_float_property_value(ob2_command_id_t command_id) {
        ob2_status_t status;
        float        value = ob2_device_get_float_property_value(m_device_handle, command_id, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        return value;
    }

    /**
     * \if English
     *
     * @brief Sets the device property value of the floating type
     *
     * @attention If the device does not support write permission for the @command_id specified command, an std::logic_error exception is thrown.
     *
     * @param[in] value The value that needs to be set
     * @param[in] command_id Device command ID
     *
     * \else
     *
     * @brief 设置设备浮点类型属性值
     *
     * @attention 如果该设备不支持 @command_id 指定命令的写权限，将会抛出 std::logic_error 异常。
     *
     * @param[in] value 需要设置的值
     * @param[in] command_id 设备命令 id
     *
     * \endif
     */
    virtual void set_float_property_value(ob2_command_id_t command_id, float value) {
        ob2_status_t status;
        ob2_device_set_float_property_value(m_device_handle, command_id, value, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

    /**
     * \if English
     *
     * @brief The capability to get the properties of a device's floating type
     * @brief Property capabilities include their maximum, minimum, step, and default values
     *
     * @attention If the device does not support the read permission of the command specified by @command_id, an std::logic_error exception is thrown.
     *
     * @param[in] command_id Device command ID
     * @return ob2_float_property_capability_t Returns property capabilities
     *
     * \else
     *
     * @brief 获取设备浮点类型属性能力
     * @brief 属性能力包括其最大值、最小值、步进值、默认值
     *
     * @attention 如果该设备不支持 @command_id 指定命令的读取权限，将会抛出 std::logic_error 异常。
     *
     * @param[in] command_id 设备命令 id
     * @return ob2_float_property_capability_t 返回属性能力
     *
     * \endif
     */
    virtual ob2_float_property_capability_t get_float_property_capability(ob2_command_id_t command_id) {
        ob2_status_t                    status;
        ob2_float_property_capability_t capability = ob2_device_get_float_property_capability(m_device_handle, command_id, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        return capability;
    }

    /**
     * \if English
     *
     * @brief Gets the data for the struct type
     * @brief The struct type data command is one of the device commands
     *
     * @attention If the device does not support the read permission of the command specified by @command_id, an std::logic_error exception is thrown.
     * @attention If the returned data is no longer needed, you need to call the @ref device::release_data_bundle interface to release it, otherwise it will
     * cause a memory leak.
     *
     * @param[in] command_id Device command ID
     * @return ob2_data_bundle_t* Returns a bundle of struct-type data (sets of data containing similar data for that struct)
     *
     * \else
     *
     * @brief 获取结构体类型数据
     * @brief 结构体类型数据命令是设备命令中的一种
     *
     * @attention 如果该设备不支持 @command_id 指定命令的读取权限，将会抛出 std::logic_error 异常。
     * @attention 如果返回的数据捆不在需要使用，需要调用 @ref device::release_data_bundle 接口释放，否则会导致内存泄漏。
     *
     * @param[in] command_id 设备命令 id
     * @return ob2_data_bundle_t* 返回结构体类型数据捆（包含该结构体类似数据的多组数据）
     *
     * \endif
     */
    virtual ob2_data_bundle_t *get_structured_data(ob2_command_id_t command_id) {
        ob2_status_t       status;
        ob2_data_bundle_t *data_bundle = ob2_device_get_structured_data(m_device_handle, command_id, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        return data_bundle;
    }

    /**
     * \if English
     *
     * @brief Set the data for the struct type
     * @brief The struct type data command is one of the device commands
     *
     * @param[in] command_id Device command ID
     * @param[in] data_bundle The data that needs to be set
     *
     * \else
     *
     * @brief 设置结构体类型数据
     * @brief 结构体类型数据命令是设备命令中的一种
     *
     * @param[in] command_id 设备命令 id
     * @param[in] data_bundle 需要设置的数据
     *
     * \endif
     */
    virtual void update_structured_data(ob2_command_id_t command_id, ob2_data_bundle_t *data_bundle) {
        ob2_status_t status;
        ob2_device_update_structured_data(m_device_handle, command_id, data_bundle, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

    /**
     * \if English
     *
     * @brief Release the bundle of data
     *
     * @param[in] data_bundle The bundle of data that needs to be released
     *
     * \else
     *
     * @brief 释放数据捆
     *
     * @param[in] data_bundle 需要释放的数据捆
     *
     * \endif
     */
    static void release_data_bundle(ob2_data_bundle_t *data_bundle) {
        ob2_status_t status;
        ob2_data_bundle_release(data_bundle, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

protected:
    static void firmware_update_state_callback(ob2_update_state_t state, const char *message, uint8_t percent, void *user_data) {
        auto dev = (device *)user_data;
        if(dev->m_firmware_update_state_cb != nullptr) {
            dev->m_firmware_update_state_cb(state, std::string(message), percent);
        }
    }

    static void capture_callback(ob2_capture_t capture_handle, void *user_data) {
        auto dev = (device *)user_data;
        if(dev->m_capture_cb != nullptr) {
            dev->m_capture_cb(std::make_shared<capture>(std::move(capture_handle)));
        }
    }

    static void imu_sample_callback(ob2_imu_sample_t imu_sample_handle, void *user_data) {
        auto dev = (device *)user_data;
        if(dev->m_imu_sample_cb != nullptr) {
            dev->m_imu_sample_cb(std::make_shared<imu_sample>(std::move(imu_sample_handle)));
        }
    }

protected:
    firmware_update_state_cb m_firmware_update_state_cb;
    capture_cb               m_capture_cb;
    imu_sample_cb            m_imu_sample_cb;

    ob2_device_t m_device_handle;
};

}  // namespace ob2