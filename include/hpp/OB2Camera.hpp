#pragma once

#include "OB2Types.hpp"

extern "C" {
#include "h/ob2camera.h"
}

#include <functional>
#include <memory>
#include <string>

namespace ob2 {

// 前置声明
class device;
class capture;
class image;

/**
 * \if English
 *
 * @brief cameras_config, for the working configuration of the camera within the device and the working configuration of the modules within the device
 * related to camera working and the modules within the SDK related to camera working.
 *
 * \else
 *
 * @brief 相机配置，用于设备内相机的工作配置及设备内与相机工作相关模块、SDK 内与相机工作相关相关模块的工作配置。
 *
 * \endif
 */
class cameras_config {
public:
    /**
     * \if English
     *
     * @brief Constructed by passing in a cameras_config handle (mainly used by the @ref device::create_cameras_config )
     *
     * @param cameras_config_handle Handle of cameras_config
     *
     * \else
     *
     * @brief 通过传入相机配置句柄构造（主要实现用于  @ref device::create_cameras_config ）
     *
     * @param cameras_config_handle 相机配置句柄
     *
     * \endif
     */
    cameras_config(ob2_cameras_config_t &&cameras_config_handle) : m_cameras_config_handle(cameras_config_handle) {
        VALIDATE_NOT_NULL(m_cameras_config_handle);
    }

    /**
     * \if English
     *
     * @brief Constructed via other cameras_config object (mobile constructs, mainly used in derived class implementations)
     *
     * @attention After calling this constructor, the original object will no longer be accessible
     *
     * @param config Another cameras_config object
     *
     * \else
     *
     * @brief 通过其他相机配置对象构造（移动构造，主要用于派生类的实现）
     *
     * @attention 调用该构造函数后，原对象将不再可以访问
     *
     * @param config 其他相机配置对象
     *
     * \endif
     */
    cameras_config(cameras_config &&config) : m_cameras_config_handle(config.m_cameras_config_handle) {
        VALIDATE_NOT_NULL(m_cameras_config_handle);
        config.m_cameras_config_handle = nullptr;
    }

    /**
     * \if English
     *
     * @brief Cameras_config destructor.
     *
     * \else
     *
     * @brief 相机配置析构函数
     *
     * \endif
     */
    virtual ~cameras_config() noexcept {
        ob2_status_t status;
        if(m_cameras_config_handle != nullptr) {
            ob2_cameras_config_release(m_cameras_config_handle, &status);
        }
    }

    /**
     * \if English
     *
     * @brief Set the camera's stream profile
     *
     * @attention @camera_type should be supported by the device, otherwise ::OB2_STATUS_LOGIC_ERROR will be outputted through the @status.
     * @attention @stream_profile should be supported by @camera_type camera, otherwise ::OB2_STATUS_LOGIC_ERROR will be outputted through the @status.
     *
     * @param[in] camera_type  Type of camera
     * @param[in] stream_profile  camera stream profile
     *
     * \else
     *
     * @brief 设置相机数据流配置
     *
     * @attention @camera_type 需要是设备支持的相机类型，否则将会抛出 std::logic_error 异常。
     * @attention @stream_profile 需要是 @camera_type 指定类型相机支持的数据流配置，否则将会抛出 std::logic_error 异常。
     *
     * @param[in] camera_type  需要配置的相机类型
     * @param[in] stream_profile  需要配置的相机数据流配置
     *
     * \endif
     */
    virtual void set_camera_stream_profile(ob2_camera_type_t camera_type, const ob2_camera_stream_profile_t &stream_profile) {
        ob2_status_t status;
        ob2_cameras_config_set_camera_stream_profile(m_cameras_config_handle, camera_type, &stream_profile, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

    /**
     * \if English
     *
     * @brief Enable camera
     * @brief When call @ref device::start_cameras function, the enabled camera in the cameras_config will be started.
     *
     * @attention \p camera_type should be supported by the device, otherwise ::OB2_STATUS_LOGIC_ERROR will be outputted through the @status.
     *
     * @param[in] camera_type Type of camera to be enabled.
     *
     * \else
     *
     * @brief 使能相机
     * @brief 启动相机时会将相机配置内已使能的相机依据设置的数据流配置开启数据流
     *
     * @attention @camera_type 需要是设备支持的相机类型，否则将会抛出 std::logic_error 异常。
     *
     * @param[in] camera_type 需要使能的相机类型
     *
     * \endif
     */
    virtual void enable_camera_stream(ob2_camera_type_t camera_type) {
        ob2_status_t status;
        ob2_cameras_config_enable_camera_stream(m_cameras_config_handle, camera_type, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

    /**
     * \if English
     *
     * @brief Configure the camera's stream profile and enable the camera.
     * @brief When call @ref device::start_cameras function, the enabled camera in the cameras_config will be started.
     * @brief Parameters of stream profile support fuzzy matching. This means that if the parameter is a fuzzy value, the default value will be selected.
     *
     * @attention @camera_type should be supported by the device, otherwise ::OB2_STATUS_LOGIC_ERROR will be outputted through the @status.
     * @attention If the parameters failed to match，::OB2_STATUS_LOGIC_ERROR will be outputted through the @status.
     *
     * @param[in] camera_type Type of camera to be enabled and configured.
     * @param[in] width_pixels  Image width in pixels，::OB2_ANY_WIDTH as a fuzzy value.
     * @param[in] height_pixels Image height in pixels，::OB2_ANY_HEIGHT as a fuzzy value.
     * @param[in] frame_rate Frame rate in fps ::OB2_ANY_FRAME_RATE as a fuzzy value.
     * @param[in] format Image data format, ::OB2_ANY_FRAME_RATE as a fuzzy value.
     *
     * \else
     *
     * @brief 配置相机数据流并使能相机
     * @brief 启动相机时会将相机配置内已使能的相机依据设置的数据流配置开启数据流
     * @brief 相机数据流配置参数支持模糊匹配，即在进行匹配支持的相机数据流配置时，模糊匹配项不进行匹配，而是选用默认配置。
     *
     * @attention @camera_type 需要是设备支持的相机类型，否则将会抛出 std::logic_error 异常。
     * @attention 相机数据流配置参数匹配失败后，将会抛出 std::logic_error 异常。
     *
     * @param[in] camera_type 需要使能的相机类型
     * @param[in] width_pixels 配置的数据流图像宽度，单位：像素；可传入 ::OB2_ANY_WIDTH 进行模糊匹配。
     * @param[in] height_pixels 配置的数据流图高度，单位：像素；可传入 ::OB2_ANY_HEIGHT 进行模糊匹配。
     * @param[in] frame_rate 配置的数据流图像帧率，单位：fps；可传入 ::OB2_ANY_FRAME_RATE 进行模糊匹配。
     * @param[in] format 配置的数据流图像格式; 可传入 ::OB2_ANY_FRAME_RATE 进行模糊匹配。
     *
     * \endif
     */
    virtual void enable_camera_stream(ob2_camera_type_t camera_type, uint32_t width_pixels, uint32_t height_pixels, uint32_t frame_rate,
                                      ob2_image_format_t format) {
        ob2_status_t status;
        ob2_cameras_config_set_and_enable_camera_stream(m_cameras_config_handle, camera_type, width_pixels, height_pixels, frame_rate, format, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

    /**
     * \if English
     *
     * @brief Disable camera stream.
     *
     * @attention @camera_type should be supported by the device, otherwise ::OB2_STATUS_LOGIC_ERROR will be outputted through the @status.
     *
     * @param[in] camera_type Types of cameras that need to be disable.
     *
     * \else
     *
     * @brief 关闭（去除使能）相机数据流
     *
     * @attention @camera_type 需要是设备支持的相机类型，否则将会抛出 std::logic_error 异常。
     *
     * @param[in] camera_type 需要关闭的相机类型
     *
     * \endif
     */
    virtual void set_disable_camera_stream(ob2_camera_type_t camera_type) {
        ob2_status_t status;
        ob2_cameras_config_disable_camera_stream(m_cameras_config_handle, camera_type, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

    /**
     * \if English
     *
     * @brief Multi-camera (in single device) image synchronisation mode configuration.
     * @brief The SDK internally waits for the output images from each camera according to the image synchronisation mode
     * and then takes one frame from each camera to generate the capture.
     *
     * @attention Not all device model support the configuration of ::OB2_IMAGES_SYNC_MODE_DEVICE_TIMESTAMP_MATCH.
     * @attention On Windows platforms, the registry needs to be configured to get the device timestamp for synchronisation
     *  (this can be done automatically by running the OrbbecViewer tool with administrator privileges).
     *
     * @param[in] images_sync_mode  Image synchronisation mode, default mode is ::OB2_IMAGES_SYNC_MODE_WAIT_LATER_COMER
     *
     * \else
     *
     * @brief 设备内多相机图像同步模式配置
     * @brief SDK 内部会根据图像同步模式等待各相机的输出图像，然后将各相机的图像各取一帧用于生成 capture
     *
     * @attention 并非所有相机都支持配置为 ::OB2_IMAGES_SYNC_MODE_DEVICE_TIMESTAMP_MATCH ，并且在 Windows
     * 系统平台，需要配置注册表后才能获取到设备时间戳用于同步（可通过管理员权限运行 OrbbecViewer 工具自动完成配置）
     *
     * @param[in] images_sync_mode  图像同步模式，默认模式为 ::OB2_IMAGES_SYNC_MODE_WAIT_LATER_COMER
     *
     * \endif
     */
    virtual void set_images_sync_mode(ob2_images_sync_mode_t images_sync_mode) {
        ob2_status_t status;
        ob2_cameras_config_set_images_sync_mode(m_cameras_config_handle, images_sync_mode, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

    /**
     * \if English
     *
     * @brief The capture generates policy configuration
     * @brief When capture is generated, all images with the camera enabled are synchronized according to how the image synchronisation mode is
     * configured. However, due to inconsistent frame rate configurations between cameras, data transmission errors and frame loss, synchronisation is not
     * guaranteed in all cases. The capture generates policy is used to control when it is no longer possible to synchronize all enabled camera image
     * frames，how to process the current camera image (discard the image or generate: an incomplete capture).
     *
     * @attention Except for the mode configured as ::OB2_PRODUCE_CAPTURE_SYNC_IMAGES_ONLY, the capture received by the user in other modes may be a
     * non-complete capture (meaning that the capture may not contain all enabled camera images)
     *
     * @param[in]  policy capture generate policy, the default policy is ::OB2_PRODUCE_CAPTURE_SYNC_IMAGES_ONLY
     *
     * \else
     *
     * @brief capture 生成策略配置
     * @brief capture 生成会根据图像同步模式配置的方式，同步所有已启用相机的图像。但是由于不同相机帧率配置不一致、数据传输错误丢帧等原因，并不能保证
     *  所有情况下都能够同步成功。capture 生成策略用于控制在已经无法同步所有已启用相机图像帧的情况下，如何处理当前相机图像（丢弃图像或者生成不完整 capture）。
     *
     * @attention 除配置为 ::OB2_PRODUCE_CAPTURE_SYNC_IMAGES_ONLY 模式外，其他模式用户接收到的 capture 可能为非完整 capture（者意味着 capture
     * 内不一定包含所有已启用的相机图像）
     *
     * @param[in]  policy capture 生成策略, 默认策略为 ::OB2_PRODUCE_CAPTURE_SYNC_IMAGES_ONLY
     *
     * \endif
     */
    virtual void set_produce_capture_policy(ob2_produce_capture_policy_t policy) {
        ob2_status_t status;
        ob2_cameras_config_set_produce_capture_policy(m_cameras_config_handle, policy, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

    /**
     * \if English
     *
     * @brief Image alignment mode configuration
     *
     * @attention Not all camera stream profile combinations support alignable, check with @ref device::get_alignable_camera_stream_profile_list function to
     * confirm how to configure.
     *
     * @param[in] images_align_mode Image alignment mode, default mode is::OB2_IMAGES_ALIGN_MODE_DISABLE
     *
     * \else
     *
     * @brief 图像对齐模式配置
     *
     * @attention 并不是所有相机流配置组合都支持启用对齐，可通过 @ref device::get_alignable_camera_stream_profile_list 接口查询确认如何配置
     *
     * @param[in] images_align_mode 对齐模式，默认模式为 ::OB2_IMAGES_ALIGN_MODE_DISABLE
     *
     * \endif
     */
    virtual void set_images_align_mode(ob2_images_align_mode_t images_align_mode) {
        ob2_status_t status;
        ob2_cameras_config_set_images_align_mode(m_cameras_config_handle, images_align_mode, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

    /**
     * \if English
     *
     * @brief Multi-camera (within a single device) synchronization mode (simultaneous exposure)
     *
     * @attention ::OB2_CAMERA_SYNC_MODE_COLOR_EXPOSURE_FIRST and ::OB2_CAMERA_SYNC_MODE_DEPTH_EXPOSURE_FIRST modes: you need to ensure that the Color and
     * Depth/IR frame rates are the same
     *
     * @param cameras_sync_mode Sync mode, default mode is ::OB2_CAMERA_SYNC_MODE_CLOSE.
     *
     * \else
     *
     * @brief （单机内）多相机同步（同步曝光）模式配置
     *
     * @attention ::OB2_CAMERA_SYNC_MODE_COLOR_EXPOSURE_FIRST 及 ::OB2_CAMERA_SYNC_MODE_DEPTH_EXPOSURE_FIRST 模式： 需要保证 Color 于 Depth/IR 帧率配置一致
     *
     * @param[in] cameras_sync_mode 同步模式，默认模式为 ::OB2_CAMERA_SYNC_MODE_CLOSE 。
     *
     * \endif
     */
    virtual void set_cameras_sync_mode(ob2_cameras_sync_mode_t cameras_sync_mode) {
        ob2_status_t status;
        ob2_cameras_config_set_cameras_sync_mode(m_cameras_config_handle, cameras_sync_mode, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

    /**
     * \if English
     *
     * @brief Multi-camera (within a single camera) synchronization delay configuration.
     *
     * @brief When the multi-camera sync mode is configured as ::OB2_CAMERA_SYNC_MODE_COLOR_EXPOSURE_FIRST, it indicates the delay time of the Depth/IR camera
     * relative to the Color camera
     * @brief When the multi-camera sync mode is configured as ::OB2_CAMERA_SYNC_MODE_DEPTH_EXPOSURE_FIRST, it indicates the delay time of the Color camera
     * relative to the Depth/IR camera
     * @brief This delay configuration has no effect when the multi-camera sync mode is configured as ::OB2_CAMERA_SYNC_MODE_CLOSE
     *
     * @param[in] delay_usec Camera sync delay in microseconds, default value is 0.
     *
     * \else
     *
     * @brief （单机内）多相机同步延时配置
     * @brief 用于控制从相机在主相机图像采集后延时多长时间开始图像采集
     * @brief 当多相机同步模式配置为 ::OB2_CAMERA_SYNC_MODE_COLOR_EXPOSURE_FIRST 时表示 Depth/IR 相机相对 Color 相机的延时
     * @brief 当多相机同步模式配置为 ::OB2_CAMERA_SYNC_MODE_DEPTH_EXPOSURE_FIRST 时表示 Color 相机相对 Depth/IR 相机的延时
     * @brief 当多相机同步模式配置为 ::OB2_CAMERA_SYNC_MODE_CLOSE 时该延时配置无任何效果
     *
     * @param[in] delay_usec 相机同步延时，单位为微秒, 默认值为 0
     *
     * \endif
     */
    virtual void set_cameras_sync_delay_usec(uint32_t delay_usec) {
        ob2_status_t status;
        ob2_cameras_config_set_cameras_sync_delay_usec(m_cameras_config_handle, delay_usec, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

    /**
     * \if English
     *
     * @brief External sync mode configuration (usually synchronization is done via sync signal line input/output sync signal, so named wired_sync_mode)
     * @brief This function is actually configuring the trigger signal source of the device camera and the trigger signal relay output. It is mainly used to
     * realize the multi-device synchronization function.
     *
     * @param[in] wired_sync_mode External sync mode, default ::OB2_WIRED_SYNC_MODE_STANDALONE
     *
     * \else
     *
     * @brief 外部同步模式配置（通常是通过同步信号线输入 / 输出同步信号完成同步，所以命名为 wired_sync_mode）
     * @brief 该功能实际上是配置设备相机的触发信号来源，及触发信号中继输出。主要用于实现多机同步功能。
     *
     * @param[in] wired_sync_mode 外部同步模式，默认为 ::OB2_WIRED_SYNC_MODE_STANDALONE
     *
     * \endif
     */
    virtual void set_wired_sync_mode(ob2_wired_sync_mode_t wired_sync_mode) {
        ob2_status_t status;
        ob2_cameras_config_set_wired_sync_mode(m_cameras_config_handle, wired_sync_mode, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

    /**
     * \if English
     *
     * @brief Secondary device delay configuration
     * @brief The device configured in ::OB2_WIRED_SYNC_MODE_SECONDARY mode delays the image acquisition for a period of time after receiving the trigger
     * signal.
     *
     * @attention Effective only when the device is configured as ::OB2_WIRED_SYNC_MODE_SECONDARY
     * @attention This configuration does not affect the trigger signal output
     * @attention The delay time should be less than one image acquisition cycle
     *
     * @param[in] delay_usec Secondary device delay, in microseconds, default value is 0.
     *
     * \else
     *
     * @brief 从设备延时配置（配置为 SECONDARY 模式的设备，在接收到触发信号后，延时一段时间后再执行图像采集）
     *
     * @attention 仅当设备配置为 SECONDARY 时生效
     * @attention 该配置不会影响触发信号输出
     * @attention 延时时间应当小于一个图像采集周期
     *
     * @param[in] delay_usec 从设备延时，单位：微秒，默认值为 0
     *
     * \endif
     */
    virtual void set_secondary_delay_off_primary_usec(uint32_t delay_usec) {
        ob2_status_t status;
        ob2_cameras_config_set_secondary_delay_off_primary_usec(m_cameras_config_handle, delay_usec, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

    /**
     * \if English
     *
     * @brief Get the cameras_config handle
     *
     * @attention Getting the handle does not increase the reference count of the cameras_config handle, its lifecycle is still managed by the cameras_config
     * object, i.e. the handle is released after the cameras_config is resolved
     *
     * @return ob2_cameras_config_t return handle of cameras_config
     *
     * \else
     *
     * @brief 获取相机配置句柄
     *
     * @attention 获取句柄不会增加相机配置句柄引用计数，其生命周期还是由 cameras_config 对象管理，即 cameras_config 析构后会释放句柄
     *
     * @return ob2_cameras_config_t 返回相机配置句柄
     *
     * \endif
     */
    virtual ob2_cameras_config_t get_handle() {
        return m_cameras_config_handle;
    }

protected:
    ob2_cameras_config_t m_cameras_config_handle;
};

/**
 * \if English
 *
 * @brief Camera image class, which is the carrier of camera image data
 *
 * \else
 *
 * @brief 相机图像类，是相机图像数据的载体
 *
 * \endif
 */
class image {
public:
    /**
     * \if English
     *
     * @brief Custom image construction
     * @brief The SDK internally requests an appropriate size of memory based on the image format, width, height, line span, etc.
     *
     * @param[in] source_camera_type Image original camera type (for image information tracking, can be filled with ::OB2_CAMERA_UNKNOWN)
     * @param[in] image_format Image formats
     * @param[in] width_pixels Image width in pixels
     * @param[in] height_pixels Image height in pixels
     * @param[in] stride_bytes Image stride (row span) in bytes
     *
     * \else
     *
     * @brief 自定义图像构造
     * @brief SDK 内部会根据图像格式、宽、高、行跨都等信息在内部申请一块合适大小内存的内存
     *
     * @param[in] source_camera_type 图像原相机类型（用于图像信息追踪，可以填 ::OB2_CAMERA_UNKNOWN ）
     * @param[in] image_format 图像格式
     * @param[in] width_pixels 图像宽，单位：像素
     * @param[in] height_pixels 图像高，单位：像素
     * @param[in] stride_bytes 图像行跨度，单位：字节
     *
     * \endif
     */
    image(ob2_camera_type_t source_camera_type, ob2_image_format_t image_format, uint32_t width_pixels, uint32_t height_pixels, uint32_t stride_bytes) {
        ob2_status_t status;
        m_image_handle = ob2_image_create(source_camera_type, image_format, width_pixels, height_pixels, stride_bytes, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

    /**
     * \if English
     *
     * @brief Constructed from a specified buffer
     * @brief The buffer of the created image is the incoming buffer, the allocate and release of the buffer memory is done by the user code
     *
     * @attention The buffer memory needs to be allocated by the user in advance and the size of the memory needs to be matched to the image format, width,
     * height, row span etc.
     *
     * @param[in] source_camera_type Image original camera type (for image information tracking, can be filled with ::OB2_CAMERA_UNKNOWN).
     * @param[in] image_format Image formats.
     * @param[in] width_pixels Image width in pixels.
     * @param[in] height_pixels Image height in pixels.
     * @param[in] stride_bytes Image stride (row span) in bytes.
     * @param[in] buffer  Pointer of buffer.
     * @param[in] buffer_size Buffer memory size in bytes.
     * @param[in] cb The buffer release callback function, which is called when the image is released, is the one that the user needs to ensure
     * is able to release the memory accurately.
     *
     * \else
     *
     * @brief 从指定 buffer 构造
     *
     * @attention buffer 内存需要有用户提前申请好，并且需要确保内存的大小与图像格式、宽、高、行跨都等条件匹配。
     *
     * @param[in] source_camera_type 图像原相机类型（用于图像信息追踪，可以填 ::OB2_CAMERA_UNKNOWN ）
     * @param[in] image_format 图像格式
     * @param[in] width_pixels 图像宽，单位：像素
     * @param[in] height_pixels 图像高，单位：像素
     * @param[in] stride_bytes 图像行跨度，单位：字节
     * @param[in] buffer buffer 地址指针
     * @param[in] buffer_size buffer 内存大小，单位：字节
     * @param[in] cb buffer 释放回调函数，会在 image 释放时调用，用户需要确保该回调函数能够准确释放内存
     *
     * \endif
     */
    image(ob2_camera_type_t source_camera_type, ob2_image_format_t image_format, uint32_t width_pixels, uint32_t height_pixels, uint32_t stride_bytes,
          uint8_t *buffer, uint32_t buffer_size, buffer_release_cb cb) {
        ob2_status_t status;
        m_buffer_release_cb = cb;
        m_image_handle      = ob2_image_create_from_buffer(source_camera_type, image_format, width_pixels, height_pixels,  //
                                                      stride_bytes, buffer, buffer_size, &image::buffer_release_callback, this, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

    /**
     * \if English
     *
     * @brief Constructed from image handles (mainly used by the @ref capture::get_image )
     *
     * @param image_handle Handle of image
     *
     * \else
     *
     * @brief 通过图像句柄构造（主要用于 @ref capture::get_image ）
     *
     * @param image_handle 图像句柄
     *
     * \endif
     */
    image(ob2_image_t &&image_handle) : m_image_handle(image_handle) {
        VALIDATE_NOT_NULL(image_handle);
    }

    /**
     * \if English
     *
     * @brief Constructed from other image object (mobile constructs, mainly used in derived class implementations)
     *
     * @attention After calling this constructor, the original image object will no longer be accessible
     *
     * @param img Another image object
     *
     * \else
     *
     * @brief 通过其他图像对象构造（移动构造，主要用于派生类的实现）
     *
     * @attention 调用该构造函数后，原图像对象将不再可以访问
     *
     * @param img 其他图像对象
     *
     * \endif
     */
    image(image &&img) : m_image_handle(img.m_image_handle) {
        VALIDATE_NOT_NULL(m_image_handle);
        img.m_image_handle = nullptr;
    }

    /**
     * \if English
     *
     * @brief Image destructor
     *
     * \else
     *
     * @brief 图像类析构函数
     *
     * \endif
     */
    virtual ~image() noexcept {
        ob2_status_t status;
        if(m_image_handle != nullptr) {
            ob2_image_release(m_image_handle, &status);
        }
    }

    /**
     * \if English
     *
     * @brief Get image buffer
     * @brief The image buffer contains the data of the image, which can be read or modified directly by the user via the returned buffer pointer.
     *
     * @attention Do not access the buffer pointing memory after the image object has been destructured, otherwise unexpected problems may occur.
     *
     * @return uint8_t* Pointer of buffer.
     *
     * \else
     *
     * @brief 获取图像 buffer
     * @brief 图像 buffer 内放的即是图像的数据，用户可以通过返回的 buffer 指针直接读取或修改图像数据
     *
     * @attention 在图像对象被析构后，不要再对 buffer 指向内存进行访问，否则会出现意想不到的问题
     *
     * @return uint8_t* buffer 地址指针
     *
     * \endif
     */
    virtual uint8_t *get_buffer() {
        ob2_status_t status;
        auto         buffer = ob2_image_get_buffer(m_image_handle, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        return buffer;
    }

    /**
     * \if English
     *
     * @brief Get image data size
     * @brief Normally the image data size will be the same as the buffer memory size, but for compressed or encoded format images, the image data size will be
     * smaller than the buffer size.
     *
     * @return uint32_t Image data size in bytes
     *
     * \else
     *
     * @brief 获取图像数据大小
     * @brief 通常图像的数据大小会与 buffer 内存大小一致，但是对于压缩或者编码格式图像，图像数据数据大小会小于 buffer 大小。
     *  不过 buffer 大小对用户是没有啥实际意义的，所以可以不用理会
     *
     * @return uint8_t* 图像数据大小，单位：字节
     *
     * \endif
     */
    virtual uint32_t get_size() {
        ob2_status_t status;
        auto         size = ob2_image_get_size(m_image_handle, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        return size;
    }

    /**
     * \if English
     *
     * @brief Get image format
     * @brief The image format represents the arrangement of image pixels, compression, encoding and other characteristics. The user needs to decide how to use
     * the image data according to the image format
     *
     * \else
     *
     * @brief 获取图像格式
     * @brief 图像格式代表着图像像素的排列方式、压缩、编码等特性，用户需要根据图像格式决定如何使用图像数据
     *
     * @return ob2_image_format_t 返回图像格式
     *
     * \endif
     */
    virtual ob2_image_format_t get_format() {
        ob2_status_t status;
        auto         format = ob2_image_get_format(m_image_handle, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        return format;
    }

    /**
     * \if English
     *
     * @brief Get image width
     *
     * @return uint32_t Return the width of the image in pixels
     *
     * \else
     *
     * @brief 获取图像宽度
     *
     * @return uint32_t 返回图像宽度，单位：像素
     *
     * \endif
     */
    virtual uint32_t get_width_pixels() {
        ob2_status_t status;
        auto         width = ob2_image_get_width_pixels(m_image_handle, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        return width;
    }

    /**
     * \if English
     *
     * @brief Get image height
     *
     * @return uint32_t Return the width of the image in pixels
     *
     * \else
     *
     * @brief 获取图像高度
     *
     * @return uint32_t 返回图像高度，单位：像素
     *
     * \endif
     */
    virtual uint32_t get_height_pixels() {
        ob2_status_t status;
        auto         height = ob2_image_get_height_pixels(m_image_handle, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        return height;
    }

    /**
     * \if English
     *
     * @brief Get image stride (row span)
     * @brief The user can offset the buffer address pointer by the row span size to quickly fetch pixel data at the specified coordinates of the image.
     *
     * @attention stride_bytes and width_pixels are not necessarily multiples, as under certain conditions, some blank data may be padded at the end of each
     * image line to achieve memory alignment.
     * @attention Images in non-planer formats (MJPG, H264, H265, RLE, COMPRESSED, etc.) do not have the stride_bytes concept and calling this function will
     * throw a std::runtime_error exception.
     *
     * @return uint32_t Return the image row span in bytes
     *
     * \else
     *
     * @brief 获取图像行跨度
     * @brief 用户可以通过行跨度大小，对 buffer 地址指针进行偏移，从而快速获取图像指定坐标下的像素数据
     *
     * @attention stride_bytes 与 width_pixels 不一定是倍数关系，因为某些条件下，可能会往图像每一行尾部数据填充一些已实现内存对齐
     * @attention 非像素平铺格式（MJPG、H264、H265、RLE、COMPRESSED 等）的图像没有 stride_bytes 概念，调用本接口会抛出 std::runtime_error 异常
     *
     * @return uint32_t 返回图像行跨度，单位：字节
     *
     * \endif
     */
    virtual uint32_t get_stride_bytes() {
        ob2_status_t status;
        auto         stride = ob2_image_get_stride_bytes(m_image_handle, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        return stride;
    }

    /**
     * \if English
     *
     * @brief Get device timestamp
     * @brief The device timestamp is the time stamp on the device side of the image, which is closest to the time when the image was generated.
     *
     * @attention By default, this timestamp is the length of time that has passed since the device was started and is reset to zero and re-counted after the
     * device is rebooted. The device time counter is reset to zero and re-calculated after it overflows.
     * @attention Due to the precision of the device clock, although the device timestamp is in microseconds, the device precision of some devices is actually
     * in milliseconds, so the lower three digits of the value will be zero.
     * @attention Not all devices support device timestamp return, and due to Windows system limitations, some special system configuration is required to
     * obtain the timestamp (this can be done automatically by running the OrbbecViewer tool with administrator privileges).
     *
     * @return uint64_t Return device timestamp in microseconds
     *
     * \else
     *
     * @brief 获取设备时间戳
     * @brief 设备实间戳是指图像在设备端打上的时间戳，这个时间戳最接近图像生成时的时间
     *
     * @attention 默认情况下，这个时间戳是指设备从启动开始过去的时间长度，设备重启后会归零重计。设备定时计数器溢出后会归零重计。
     * @attention 由于设备时钟精度关系，虽然设备时间戳单位为微秒，但是某些设备的设备精度其实是毫秒，所以在数值上低三位会为零。
     * @attention 并不是所有设备都支持设备时间戳返回，并且由于 Windows 系统限定，需要完成一些特殊系统配置获取到时间戳 (可通过管理员
     *  权限运行 OrbbecViewer 工具自动完成配置)。
     *
     * @return uint64_t 返回设备时间戳，单位：微秒
     *
     * \endif
     */
    virtual uint64_t get_device_timestamp_usec() {
        ob2_status_t status;
        auto         timestamp = ob2_image_get_device_timestamp_usec(m_image_handle, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        return timestamp;
    }

    /**
     * \if English
     *
     * @brief Get system timestamp
     * @brief The system timestamp is the timestamp punched when the image data is received by the SDK on the Host side (Host's localtime, timed from
     * 1970-01-01T00:00:00Z.)
     *
     * @return uint64_t Return system timestamp in microseconds
     *
     * \else
     *
     * @brief 获取系统时间戳
     * @brief 系统时间戳是指 Host 端 SDK 接收到图像数据时打的时间戳（Host 的 localtime，是从 1970-01-01T00:00:00Z. 开始的计时）
     *
     * @return uint64_t 返回系统时间戳，单位：微秒
     *
     * \endif
     */
    virtual uint64_t get_system_timestamp_usec() {
        ob2_status_t status;
        auto         timestamp = ob2_image_get_system_timestamp_usec(m_image_handle, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        return timestamp;
    }

    /**
     * \if English
     *
     * @brief Get image source camera type
     * @brief Images obtained through the SDK are filled in with the source camera type, which represents the source of the image data.
     *
     * @return ob2_camera_type_t Return the source camera type of image.
     *
     * \else
     *
     * @brief 获取图像源相机类型
     * @brief 通过 SDK 获取得到的图像都会填写源相机类型，代表了图像数据来源
     *
     * @return ob2_camera_type_t 相机类型
     *
     * \endif
     */
    virtual ob2_camera_type_t get_source_camera_type() {
        ob2_status_t status;
        auto         camera_type = ob2_image_get_source_camera_type(m_image_handle, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        return camera_type;
    }

    /**
     * \if English
     *
     * @brief Get the number of valid bits of image pixels
     * @brief For Depth and IR images, usually only the low bits of the image pixels are valid and the high bits are fixed to zero. (For example, a camera depth
     * image in Y16 format has 16 bits for each pixel, but only the lower 14 bits are valid and the upper two bits are zero, so a call to this function will
     * return 14)
     *
     * @return uint8_t Return the number of valid bits of image pixels
     *
     * \else
     *
     * @brief 获取图像像素有效位数
     * @brief 对于 Depth 和 IR 图像，通常其图像像素只有低位有效，高位固定为零。（比如某相机深度是 Y16 格式的图像，其像素位数为 16，
     *  但是只有低 14 位有效，高两位为零，此时调用本接口将返回 14）
     *
     * @return uint8_t 返回图像像素有效位数
     *
     * \endif
     */
    virtual uint8_t get_available_bits_for_each_pixel() {
        ob2_status_t status;
        auto         bits = ob2_image_get_available_bits_for_each_pixel(m_image_handle, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        return bits;
    }

    /**
     * \if English
     *
     * @brief Get depth image pixel value scaling factor
     * @brief The depth image pixel value is the distance from the target object to the camera in millimeters, but the actual image value may be scaled due to
     * camera characteristics, algorithmic processing, etc. This function Return the scaling factor used to restore the image data to a value in millimeters,
     * for example, if scale=0.1 and the pixel value at a given coordinate is pixel_value=10000, then the depth distance value = pixel_Value*scale =
     * 10000*0.1=1000mm.
     *
     * @attention Valid for depth images only, calls to this function from non-depth images will throw an std::runtime_error exception.
     *
     * @return uint8_t Return the depth image pixel value scaling factor
     *
     * \else
     *
     * @brief 获取深度图像数值缩放系数
     * @brief 深度图像像素值意义为目标物体到相机的距离，单位为 mm。但是，由于相机特性、算法处理等原因，实际图像的数值可能会被缩放。
     *  本接口返回用于将图像数据恢复为以毫米为单位的数值时所需要缩放的系数, 比如，scale=0.1 时, 某坐标下像素值为 pixel_value=10000，
     *     则表示深度距离 value = pixel_Value*scale = 10000*0.1=1000mm。
     *
     * @attention 仅深度图像有效，非深度图像调用本接口将会抛出 std::runtime_error 异常
     *
     * @return uint8_t 返回深度图数值缩放系数
     *
     * \endif
     */
    virtual float get_value_scale() {
        ob2_status_t status;
        auto         scale = ob2_depth_image_get_value_scale(m_image_handle, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        return scale;
    }

    /**
     * \if English
     *
     * @brief Get image handle
     *
     * @attention Getting a handle does not increase the handle reference count, its lifecycle is still managed by the image object, i.e. the handle is released
     * when the image is destructured
     *
     * @return ob2_image_t return image handle
     *
     * \else
     *
     * @brief 获取图像句柄
     *
     * @attention 获取句柄不会增加句柄引用计数，其生命周期还是由图像对象管理，即通图像析构后会释放句柄
     *
     * @return ob2_image_t 返回图像句柄
     *
     * \endif
     */
    virtual ob2_image_t get_handle() {
        return m_image_handle;
    }

protected:
    static void buffer_release_callback(uint8_t *buffer, void *user_data) {
        auto im = (image *)user_data;
        im->m_buffer_release_cb(buffer);
    }

protected:
    ob2_image_t       m_image_handle;
    buffer_release_cb m_buffer_release_cb;
};

/**
 * \if English
 *
 * @brief Camera capture, capture is the carrier of image object, a capture will usually contain one frame from one or more different types of cameras.
 *
 * \else
 *
 * @brief 相机 capture，capture 是图像对象的载体，一个 capture 通常会包含一个或多个不同类型相机的一帧图像
 *
 * \endif
 */
class capture {
public:
    /**
     * \if English
     *
     * @brief capture Custom Constructor
     *
     * \else
     *
     * @brief capture 自定义构造函数
     *
     * \endif
     */
    capture() {
        ob2_status_t status;
        m_capture_handle = ob2_capture_create(&status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

    /**
     * \if English
     *
     * @brief Constructed with a capture handle (mainly used by @ref device::get_capture )
     *
     * @param capture_handle handle of capture
     *
     * \else
     *
     * @brief 通过 capture 句柄构造（主要用于  @ref device::get_capture ）
     *
     * @param capture_handle capture 句柄
     *
     * \endif
     */
    capture(ob2_capture_t &&capture_handle) : m_capture_handle(capture_handle) {
        VALIDATE_NOT_NULL(capture_handle);
    }

    /**
     * \if English
     *
     * @brief Constructed from other capture object (mobile constructs, mainly used for derived class implementations).
     *
     * @attention After calling this constructor, the original object will no longer be accessible.
     *
     * @param cap Another capture object.
     *
     * \else
     *
     * @brief 通过其他 capture 对象构造（移动构造，主要用于派生类的实现）
     *
     * @attention 调用该构造函数后，原对象将不再可以访问
     *
     * @param cap 其他 capture 对象
     *
     * \endif
     */
    capture(capture &&cap) : m_capture_handle(cap.m_capture_handle) {
        VALIDATE_NOT_NULL(m_capture_handle);
        cap.m_capture_handle = nullptr;
    }

    /**
     * \if English
     *
     * @brief capture destructor
     *
     * \else
     *
     * @brief capture 析构函数
     *
     * \endif
     */
    virtual ~capture() noexcept {
        ob2_status_t status;
        if(nullptr != m_capture_handle) {
            ob2_capture_release(m_capture_handle, &status);
        }
    }

    /**
     * \if English
     *
     * @brief Get an image of the specified camera
     *
     * @attention If the current capture does not contain an image from the given camera,A std::logic_error exception will be thrown.
     * Possible reasons for not including images from a specified camera are：
     *      1. The camera specified by @camera_type is not enabled when starting cameras operation
     *      2. The @produce_capture_policy default policy is modified when starting cameras operation
     *
     * @param[in] camera_type Camera type
     * @return std::shared_ptr<image> Return a shared_ptr to the image object
     *
     * \else
     *
     * @brief 获取指定相机图像
     *
     * @attention 如果当前 capture 内不包含指定相机的图像，将会抛出 std::logic_error 异常。
     *  不包含指定相机的图像的原因可能为：
     *      1. camera_type 指定的相机未使能
     *      2. produce_capture_policy 默认策略被修改
     *
     * @param[in] camera_type 相机类型
     * @return std::shared_ptr<image> 返回图像对象智能指针
     *
     * \endif
     */
    virtual std::shared_ptr<image> get_image(ob2_camera_type_t camera_type) {
        ob2_status_t status;
        auto         image_handle = ob2_capture_get_image(m_capture_handle, camera_type, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        if(nullptr != image_handle) {
            return std::make_shared<image>(std::move(image_handle));
        }
        return nullptr;
    }

    /**
     * \if English
     *
     * @brief Get an image of color camera
     *
     * @attention If the current capture does not contain an image of color camera, a std::logic_error exception will be thrown.
     *
     * @return std::shared_ptr<image> Return a shared_ptr to the image object
     *
     * \else
     *
     * @brief 获取 Color 相机图像
     *
     * @attention 如果当前 capture 内不包含 Color 相机的图像，将会抛出 std::logic_error 异常。
     *  不包含 Color 相机的图像的原因可能为：
     *      1. 启动相机工作时 Color 相机未使能
     *      2. 启动相机工作时 produce_capture_policy 默认策略被修改
     *
     * @return std::shared_ptr<image> 返回图像对象智能指针
     *
     * \endif
     */
    virtual std::shared_ptr<image> get_color_image() {
        ob2_status_t status;
        auto         image_handle = ob2_capture_get_color_image(m_capture_handle, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        if(nullptr != image_handle) {
            return std::make_shared<image>(std::move(image_handle));
        }
        return nullptr;
    }

    /**
     * \if English
     *
     * @brief Get an image of depth camera
     *
     * @attention If the current capture does not contain an image of depth camera, a std::logic_error exception will be thrown.
     *
     * @return std::shared_ptr<image> Return a shared_ptr to the image object
     *
     * \else
     *
     * @brief 获取 Depth 相机图像
     *
     * @attention 如果当前 capture 内不包含 Depth 相机的图像，将会抛出 std::logic_error 异常。
     *  不包含 Depth 相机的图像的原因可能为：
     *      1. 启动相机工作时 Depth 相机未使能
     *      2. 启动相机工作时 produce_capture_policy 默认策略被修改
     *
     * @return std::shared_ptr<image> 返回图像对象智能指针
     *
     * \endif
     */
    virtual std::shared_ptr<image> get_depth_image() {
        ob2_status_t status;
        auto         image_handle = ob2_capture_get_depth_image(m_capture_handle, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        if(nullptr != image_handle) {
            return std::make_shared<image>(std::move(image_handle));
        }
        return nullptr;
    }

    /**
     * \if English
     *
     * @brief Get an image of infrared cameras
     *
     * @attention If the current capture does not contain an image of infrared camera, a std::logic_error exception will be thrown.
     *
     * @return std::shared_ptr<image> Return a shared_ptr to the image object
     *
     * \else
     *
     * @brief 获取 红外 相机图像
     *
     * @attention 如果当前 capture 内不包含红外相机的图像，将会抛出 std::logic_error 异常。
     *  不包含红外相机的图像的原因可能为：
     *      1. 启动相机工作时红外相机未使能
     *      2. 启动相机工作时 produce_capture_policy 默认策略被修改
     *
     * @return std::shared_ptr<image> 返回图像对象智能指针
     *
     * \endif
     */
    virtual std::shared_ptr<image> get_ir_image() {
        ob2_status_t status;
        auto         image_handle = ob2_capture_get_ir_image(m_capture_handle, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        if(nullptr != image_handle) {
            return std::make_shared<image>(std::move(image_handle));
        }
        return nullptr;
    }

    /**
     * \if English
     *
     * @brief Set the image for a given camera
     * @brief A copy (shallow copy) of the image is saved to capture. If the capture already contains an image of color camera, the original image is
     * released first.
     *
     * @param[in] camera_type Camera type
     * @param[in] im Camera image object to be set
     *
     * \else
     *
     * @brief 设置指定相机图像
     * @brief 会将图像拷贝（浅拷贝）保存一份到 capture 内，如果 capture 已包含指定相机的图像，则会先将原图像释放。
     *
     * @param[in] camera_type 相机类型
     * @param[in] im 需要设置的相机图像
     *
     * \endif
     */
    virtual void set_image(ob2_camera_type_t camera_type, std::shared_ptr<image> im) {
        ob2_status_t status;
        ob2_capture_set_image(m_capture_handle, camera_type, im->get_handle(), &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

    /**
     * \if English
     *
     * @brief Set the image for color camera
     * @brief A copy (shallow copy) of the image is saved to capture. If the capture already contains an image of color camera, the original image is
     * released first.
     *
     * @param[in] im Camera image object to be set
     *
     * \else
     *
     * @brief 设置 Color 相机图像
     * @brief 会将图像拷贝（浅拷贝）保存一份到 capture 内，如果 capture 已包含 Color 相机的图像，则会先将原图像释放。
     *
     * @param[in] im 需要设置的相机图像
     *
     * \endif
     */
    virtual void set_color_image(std::shared_ptr<image> im) {
        ob2_status_t status;
        ob2_capture_set_color_image(m_capture_handle, im->get_handle(), &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

    /**
     * \if English
     *
     * @brief Set the image for depth camera
     * @brief A copy (shallow copy) of the image is saved to capture. If the capture already contains an image of depth camera, the original image is
     * released first.
     *
     * @param[in] im Camera image object to be set
     *
     * \else
     *
     * @brief 设置 Depth 相机图像
     * @brief 会将图像拷贝（浅拷贝）保存一份到 capture 内，如果 capture 已包含 Depth 相机的图像，则会先将原图像释放。
     *
     * @param[in] im 需要设置的相机图像
     *
     * \endif
     */
    virtual void set_depth_image(std::shared_ptr<image> im) {
        ob2_status_t status;
        ob2_capture_set_depth_image(m_capture_handle, im->get_handle(), &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

    /**
     * \if English
     *
     * @brief Set the image for infrared camera
     * @brief A copy (shallow copy) of the image is saved to capture. If the capture already contains an image of infrared camera, the original image is
     * released first.
     *
     * @param[in] im Camera image object to be set
     *
     * \else
     *
     * @brief 设红外相机图像
     * @brief 会将图像拷贝（浅拷贝）保存一份到 capture 内，如果 capture 已包含红外相机的图像，则会先将原图像释放。
     *
     * @param[in] im 需要设置的相机图像
     *
     * \endif
     */
    virtual void set_ir_image(std::shared_ptr<image> im) {
        ob2_status_t status;
        ob2_capture_set_ir_image(m_capture_handle, im->get_handle(), &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

    /**
     * \if English
     *
     * @brief Get capture handle
     *
     * @attention Getting a handle does not increase the handle reference count, its lifecycle is still managed by the capture object, i.e. the handle is
     * released when the capture is destructured
     *
     * @return ob2_capture_t return capture handle
     *
     * \else
     *
     * @brief 获取 capture 句柄
     *
     * @attention 获取句柄不会增加句柄引用计数，其生命周期还是由 capture 对象管理，即 capture 析构后会释放句柄
     *
     * @return ob2_capture_t 返回 capture 句柄
     *
     * \endif
     */
    virtual ob2_capture_t get_handle() {
        return m_capture_handle;
    }

protected:
    ob2_capture_t m_capture_handle;
};

/**
 * \if English
 *
 * \else
 *
 * @brief capture 回调函数
 *
 *
 * \endif
 */
typedef std::function<void(std::shared_ptr<capture>)> capture_cb;
}  // namespace ob2