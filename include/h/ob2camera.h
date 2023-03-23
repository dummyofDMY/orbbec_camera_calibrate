#pragma once

#include "ob2types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \if English
 *
 * @brief Obtain the number of cameras supported by the device.
 * @brief In addition to having a Depth camera, a device may also include Color and IR cameras, depending on the model.
 *
 * @param[in] device_handle Handle of device.
 * @param[out] status Output function execution status.
 * @return uint32_t Returns the number of supported cameras.
 *
 * \else
 *
 * @brief 获取设备支持的相机个数
 * @brief 一个设备除了拥有一个 Depth 相机外，还可能会包含 Color、IR 相机，视具体型号而定。
 *
 * @param[in] device_handle 设备句柄
 * @param[out] status 返回函数调用状态
 * @return uint32_t 返回包含的相机个数
 *
 * \endif
 */
uint32_t ob2_device_get_supported_camera_count(ob2_device_t device_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Gets the camera type bound to the specified index number in the device.
 *
 * @attention The ranges of @index is from 0 to count-1（Count can be returned by @ref ob2_device_get_supported_camera_count ）.
 *  If an out-of-range value is passed, ::OB2_STATUS_LOGIC_ERROR will be outputted through the @status.
 *
 * @param[in] device_handle Handle of device.
 * @param[in] index Index number of target camera.
 * @param[out] status Output function execution status.
 * @return ob2_camera_type_t Return the camera type.
 *
 * \else
 *
 * @brief 获取设备内指定索引号绑定的相机类型
 *
 * @attention @index 的数值范围为 [0~count-1]（count 通过 @ref ob2_device_get_supported_camera_count 获取），若传入范围之外的值，将通过 @status 返回
 * ::OB2_STATUS_LOGIC_ERROR
 *
 * @param[in] device_handle 设备句柄
 * @param[in] index 相机索引号
 * @param[out] status 返回函数调用状态
 * @return ob2_camera_type_t 返回相机类型
 *
 * \endif
 */
ob2_camera_type_t ob2_device_get_supported_camera_type(ob2_device_t device_handle, uint32_t index, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Get the number of camera stream profile supported by the specified camera type.
 *
 * @attention The value for @camera_type needs to be the type of camera supported by the device，
 * otherwise ::OB2_STATUS_LOGIC_ERROR will be outputted through the @status.
 *
 * @param[in] device_handle Handle of device.
 * @param[in] camera_type  Type of camera.
 * @param[out] status Output function execution status.
 * @return uint32_t Return the number of camera stream profile.
 *
 * \else
 *
 * @brief 获取指定相机类型支持的数据流配置个数
 *
 * @attention @camera_type 传入的值需要是该设备支持的相机类型，否则将通过 @status 返回 ::OB2_STATUS_LOGIC_ERROR 。
 *
 * @param[in] device_handle 设备句柄
 * @param[in] camera_type 相机类型
 * @param[out] status 返回函数调用状态
 * @return uint32_t 返回支持的流配置个数
 *
 * \endif
 */
uint32_t ob2_device_get_camera_stream_profile_count(ob2_device_t device_handle, ob2_camera_type_t camera_type, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Get the camera stream profile for the specified camera type by index number.
 *
 * @attention The ranges of @index is from 0 to count-1（Count can be returned by @ref ob2_device_get_camera_stream_profile_count).
 *  If an out-of-range value is passed, ::OB2_STATUS_LOGIC_ERROR will be outputted through the @status.
 *
 * @param[in] device_handle Handle of device.
 * @param[in] camera_type Type of camera.
 * @param[in] index Index number of target camera stream profile.
 * @param[out] status Output function execution status.
 * @return ob2_camera_stream_profile_t Return camera stream profile.
 *
 * \else
 *
 * @brief 通过索引号获取指定相机类型的数据流配置
 *
 * @attention @index 的数值范围为 [0~count-1]（count 通过 @ref ob2_device_get_camera_stream_profile_count 获取），
 *  若传入范围之外的值，将通过 @status 返回 ::OB2_STATUS_LOGIC_ERROR 。
 *
 * @param[in] device_handle 设备句柄
 * @param[in] camera_type 相机类型
 * @param[in] index 索引号
 * @param[out] status 返回函数调用状态
 * @return ob2_camera_stream_profile_t 返回相机数据流配置
 *
 * \endif
 */
ob2_camera_stream_profile_t ob2_device_get_camera_stream_profile(ob2_device_t device_handle, ob2_camera_type_t camera_type, uint32_t index,
                                                                 ob2_status_t *status);

/**
 * \if English
 *
 * @brief Get the number of camera stream profile that support image alignment.
 * @brief When configuring the image alignment mode via @ref ob2_cameras_config_set_images_align_mode ，
 *  you can use this function to check whether the configured camera stream profile support the @image_align_mode.
 *
 * @attention @image_align_mode can not be ::OB2_IMAGES_ALIGN_MODE_DISABLE , otherwise ::OB2_STATUS_LOGIC_ERROR will output
 *  through the @status.
 *
 * @param[in] device_handle Handle of device.
 * @param[in] image_align_mode Image alignment mode.
 * @param[in] target_camera_stream_profile the target camera's steam profile（such as：::OB2_IMAGES_ALIGN_MODE_D2C_HARDWARE was passed，
 *  the target camera is color-camera）.
 * @param[out] status Output function execution status.
 * @return uint32_t return the number.
 *
 * \else
 *
 * @brief 获取支持对齐的相机数据流配置个数
 * @brief 在 cameras_config 中配置图像对齐模式时，可以先通过当前接口查询配置的不同相机数据流是否支持该对齐模式。
 *
 * @attention @image_align_mode 不能为 ::OB2_IMAGES_ALIGN_MODE_DISABLE ，否则将通过 @status 返回 ::OB2_STATUS_LOGIC_ERROR 。
 *
 * @param[in] device_handle 设备句柄
 * @param[in] image_align_mode 图像对齐模式
 * @param[in] target_camera_stream_profile 对齐的目标相机数据流配置（如：对齐模式为 ::OB2_IMAGES_ALIGN_MODE_D2C_HARDWARE ，则目标相机是 color 相机）
 * @param[out] status 返回函数调用状态
 * @return uint32_t 返回支持对齐的相机数据流配置个数
 *
 * \endif
 */
uint32_t ob2_device_get_alignable_camera_stream_profile_count(ob2_device_t device_handle, ob2_images_align_mode_t image_align_mode,
                                                              ob2_camera_stream_profile_t target_camera_stream_profile, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Get camera stream profile that support image alignment by index.
 * @brief When configuring the image alignment mode via @ref ob2_cameras_config_set_images_align_mode ，
 *  you can use this function to check whether the configured camera stream profile support the @image_align_mode.
 *
 * @attention @align_mode can not be ::OB2_IMAGES_ALIGN_MODE_DISABLE ，otherwise ::OB2_STATUS_LOGIC_ERROR will output
 *  through the @status.
 * @attention The ranges of @index is from 0 to count-1（Count can be returned by @ref ob2_device_get_alignable_camera_stream_profile_count).
 *  If an out-of-range value is passed, ::OB2_STATUS_LOGIC_ERROR will be outputted through the @status.
 *
 * @param[in] device_handle Handle of device.
 * @param[in] align_mode Image alignment mode.
 * @param[in] target_camera_stream_profile the target camera's steam profile（such as：::OB2_IMAGES_ALIGN_MODE_D2C_HARDWARE was passed，
 *  the target camera is color-camera）.
 * @param[in] index Index for camera stream profile.
 * @param[out] status Output function execution status.
 * @return ob2_camera_stream_profile_t return camera stream profile witch support for alignment.
 *
 * \else
 *
 * @brief 通过索引号获取支持对齐的相机数据流配置
 * @brief 在 cameras_config 中配置图像对齐模式时，可以先通过当前接口查询配置的不同相机数据流是否支持该对齐模式。
 *
 * @attention @align_mode 不能为 ::OB2_IMAGES_ALIGN_MODE_DISABLE ，否则将通过 @status 返回 ::OB2_STATUS_LOGIC_ERROR 。
 * @attention @index 的数值范围为 [0~count-1]（count 通过 @ref ob2_device_get_alignable_camera_stream_profile_count 获取），
 *  若传入范围之外的值，将通过 @status 返回 ::OB2_STATUS_LOGIC_ERROR 。
 *
 * @param[in] device_handle 设备句柄
 * @param[in] align_mode 图像对齐模式
 * @param[in] target_camera_stream_profile 对齐的目标相机数据流配置（如：对齐模式为 ::OB2_IMAGES_ALIGN_MODE_D2C_HARDWARE ，则目标相机是 color 相机）
 * @param[in] index 相机数据流配置索引号
 * @param[out] status 返回函数调用状态
 * @return ob2_camera_stream_profile_t 返回支持对齐的相机数据流配置
 *
 * \endif
 */
ob2_camera_stream_profile_t ob2_device_get_alignable_camera_stream_profile(ob2_device_t device_handle, ob2_images_align_mode_t align_mode,
                                                                           ob2_camera_stream_profile_t target_camera_stream_profile, uint32_t index,
                                                                           ob2_status_t *status);
/**
 * \if English
 *
 * @brief Create an cameras_config object.
 * @brief The cameras_config use to configures the working mode of each camera in the device and the processing mode of camera images within the
 * SDK.
 * @brief Once created, a default stream profile is configured for all supported cameras，but all cameras are disabled by default.
 *
 * @attention When the cameras_config is no longer used，callers must call @ref ob2_cameras_config_release  function to release it. Otherwise, memory leaks may
 * occur.
 * @attention After the @device_handle closed， except @ref ob2_cameras_config_release ，cameras_config will no longer be accessible by all
 * function. otherwise ::OB2_STATUS_LOGIC_ERROR will be outputted through the @status.
 *
 * @param[in] device_handle Handle of device.
 * @param[out] status Output function execution status.
 * @return ob2_cameras_config_t Out the cameras_config object handle.
 *
 * \else
 *
 * @brief 创建设备的相机配置
 * @brief 相机配置用于配置设备内各相机的工作方式以及 SDK 内部对相机图像的处理方式（具体支持的功能请查看 cameras_config 各接口说明）
 * @brief 相机配置创建后会为所有支持的相机配置一个默认的流配置，但是所有相机都是默认未使能的。
 *
 * @attention 不再使用相机配置时，需要调用 @ref ob2_cameras_config_release 接口释放相机配置句柄，否则会导致内存泄漏。
 * @attention 在 @device_handle 被释放后，除 @ref ob2_cameras_config_release 外，将不再可以通过相机配置句柄去访问相关配置接口，
 *  否则会通过 @status 返回 ::OB2_STATUS_RUNTIME_ERROR 。
 *
 * @param[in] device_handle 设备句柄, 传入句柄进行相机配置已实现在调用各配置接口时完成配置参数的合法性检查
 * @param[out] status 返回函数调用状态
 * @return ob2_cameras_config_t 返回相机配置句柄
 *
 * \endif
 */
ob2_cameras_config_t ob2_device_create_cameras_config(ob2_device_t device_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Release a cameras_config.
 *
 * @param[in] cameras_config_handle Cameras_config to release.
 * @param[out] status Output function execution status.
 *
 * \else
 *
 * @brief 释放相机配置句柄
 *
 * @param[in] cameras_config_handle 需要被释放的相机配置句柄
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_cameras_config_release(ob2_cameras_config_t cameras_config_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Set the camera's stream profile
 *
 * @attention @camera_type should be supported by the device, otherwise ::OB2_STATUS_LOGIC_ERROR will be outputted through the @status.
 * @attention @stream_profile should be supported by @camera_type camera, otherwise ::OB2_STATUS_LOGIC_ERROR will be outputted through the @status.
 *
 * @param[in] cameras_config_handle Handle of cameras_config
 * @param[in] camera_type  Type of camera
 * @param[in] stream_profile  camera stream profile
 * @param[out] status Output function execution status.
 *
 * \else
 *
 * @brief 设置相机数据流配置
 *
 * @attention @camera_type 需要是 @cameras_config_handle 所绑定的设备支持的相机类型，否则将会通过 @status 返回 ::OB2_STATUS_LOGIC_ERROR 。
 * @attention @stream_profile 需要是 @camera_type 指定类型相机支持的数据流配置，否则将会通过 @status 返回 ::OB2_STATUS_LOGIC_ERROR 。
 *
 * @param[in] cameras_config_handle 相机配置句柄
 * @param[in] camera_type  需要配置的相机类型
 * @param[in] stream_profile  需要配置的相机数据流配置
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_cameras_config_set_camera_stream_profile(ob2_cameras_config_t cameras_config_handle, ob2_camera_type_t camera_type,
                                                  const ob2_camera_stream_profile_t *stream_profile, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Enable camera
 * @brief When call @ref ob2_device_start_cameras function, the enabled camera in the cameras_config will be started.
 *
 * @attention @camera_type should be supported by the device, otherwise ::OB2_STATUS_LOGIC_ERROR will be outputted through the @status.
 *
 * @param[in] cameras_config_handle Handle of cameras_config.
 * @param[in] camera_type   Type of camera to be enabled.
 * @param[out] status Output function execution status.
 *
 * \else
 *
 * @brief 使能相机
 * @brief 启动相机时会将相机配置内已使能的相机依据设置的数据流配置开启数据流
 *
 * @attention @camera_type 需要是 @cameras_config_handle 所绑定的设备支持的相机类型，否则将会通过 @status 返回 ::OB2_STATUS_LOGIC_ERROR 。
 *
 * @param[in] cameras_config_handle 相机配置句柄
 * @param[in] camera_type   需要使能的相机类型
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_cameras_config_enable_camera_stream(ob2_cameras_config_t cameras_config_handle, ob2_camera_type_t camera_type, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Configure the camera's stream profile and enable the camera.
 * @brief When call @ref ob2_device_start_cameras function, the enabled camera in the cameras_config will be started.
 * @brief Parameters of stream profile support fuzzy matching. This means that if the parameter is a fuzzy value, the default value will be selected.
 *
 * @attention @camera_type should be supported by the device, otherwise ::OB2_STATUS_LOGIC_ERROR will be outputted through the @status.
 * @attention If the parameters failed to match，::OB2_STATUS_LOGIC_ERROR will be outputted through the @status.
 *
 * @param[in] cameras_config_handle Handle of cameras_config.
 * @param[in] camera_type Type of camera to be enabled and configured.
 * @param[in] width_pixels  Image width in pixels，::OB2_ANY_WIDTH as a fuzzy value.
 * @param[in] height_pixels Image height in pixels，::OB2_ANY_HEIGHT as a fuzzy value.
 * @param[in] frame_rate Frame rate in fps ::OB2_ANY_FRAME_RATE as a fuzzy value.
 * @param[in] format Image data format, ::OB2_ANY_FRAME_RATE as a fuzzy value.
 * @param[out] status Output function execution status.
 *
 * \else
 *
 * @brief 配置相机数据流并使能相机
 * @brief 启动相机时会将相机配置内已使能的相机依据设置的数据流配置开启数据流
 * @brief 相机数据流配置参数支持模糊匹配，即在进行匹配支持的相机数据流配置时，模糊匹配项不进行匹配，而是选用默认配置。
 *
 * @attention @camera_type 需要是 @cameras_config_handle 所绑定的设备支持的相机类型，否则将会通过 @status 返回 ::OB2_STATUS_LOGIC_ERROR 。
 * @attention 相机数据流配置参数匹配失败后，将会通过 @status 返回 ::OB2_STATUS_LOGIC_ERROR 。
 *
 * @param[in] cameras_config_handle 相机配置句柄
 * @param[in] camera_type 需要使能的相机类型
 * @param[in] width_pixels 配置的数据流图像宽度，单位：像素；可传入 ::OB2_ANY_WIDTH 进行模糊匹配。
 * @param[in] height_pixels 配置的数据流图高度，单位：像素；可传入 ::OB2_ANY_HEIGHT 进行模糊匹配。
 * @param[in] frame_rate 配置的数据流图像帧率，单位：fps；可传入 ::OB2_ANY_FRAME_RATE 进行模糊匹配。
 * @param[in] format 配置的数据流图像格式; 可传入 ::OB2_ANY_FRAME_RATE 进行模糊匹配。
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_cameras_config_set_and_enable_camera_stream(ob2_cameras_config_t cameras_config_handle, ob2_camera_type_t camera_type, uint32_t width_pixels,
                                                     uint32_t height_pixels, uint32_t frame_rate, ob2_image_format_t format, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Disable camera stream.
 *
 * @attention @camera_type should be supported by the device, otherwise ::OB2_STATUS_LOGIC_ERROR will be outputted through the @status.
 *
 * @param cameras_config_handle Handle of cameras_config.
 * @param[in] camera_type Types of cameras that need to be disable.
 * @param[out] status Output function execution status.
 *
 * \else
 *
 * @brief 关闭（去除使能）相机数据流
 *
 * @attention @camera_type 需要是 cameras_config_handle 所绑定的设备支持的相机类型，否则将会通过 @status 返回 ::OB2_STATUS_LOGIC_ERROR 。
 *
 * @param cameras_config_handle 相机配置句柄
 * @param[in] camera_type 需要关闭的相机类型
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_cameras_config_disable_camera_stream(ob2_cameras_config_t cameras_config_handle, ob2_camera_type_t camera_type, ob2_status_t *status);

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
 * @param[in] cameras_config_handle  Handle of cameras_config
 * @param[in] images_sync_mode  Image synchronisation mode, default mode is ::OB2_IMAGES_SYNC_MODE_WAIT_LATER_COMER
 * @param[out] status Output function execution status.
 *
 * \else
 *
 * @brief 设备内多相机图像同步模式配置
 * @brief SDK 内部会根据图像同步模式等待各相机的输出图像，然后将各相机的图像各取一帧用于生成 capture
 *
 * @attention 并非所有相机都支持配置为 ::OB2_IMAGES_SYNC_MODE_DEVICE_TIMESTAMP_MATCH ，
 *  并且在 Windows 系统平台，需要配置注册表后才能获取到设备时间戳用于同步（可通过管理员
 *  权限运行 OrbbecViewer 工具自动完成配置）
 *
 * @param[in] cameras_config_handle 相机配置句柄
 * @param[in] images_sync_mode  图像同步模式，默认模式为：::OB2_IMAGES_SYNC_MODE_WAIT_LATER_COMER
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_cameras_config_set_images_sync_mode(ob2_cameras_config_t cameras_config_handle, ob2_images_sync_mode_t images_sync_mode, ob2_status_t *status);

/**
 * \if English
 *
 * @brief The capture generates policy configuration
 * @brief When capture is generated, all images with the camera enabled are synchronized according to how the image synchronisation mode is
 * configured. However, due to inconsistent frame rate configurations between cameras, data transmission errors and frame loss, synchronisation is not
 * guaranteed in all cases. The capture generates policy is used to control when it is no longer possible to synchronize all enabled camera image
 * frames，how to process the current camera image (discard the image or generate an incomplete capture).
 *
 * @attention Except for the mode configured as ::OB2_PRODUCE_CAPTURE_SYNC_IMAGES_ONLY, the capture received by the user in other modes may be a non-complete
 * capture (meaning that the capture may not contain all enabled camera images)
 *
 * @param[in]  cameras_config_handle Handle of cameras_config
 * @param[in]  policy capture generate policy, the default policy is ::OB2_PRODUCE_CAPTURE_SYNC_IMAGES_ONLY
 * @param[out] status Output function execution status.
 *
 * \else
 *
 * @brief capture 生成策略配置
 * @brief capture 生成时，会根据图像同步模式配置的方式，同步所有已启用相机的图像。但是由于不同相机帧率配置不一致、数据传输错误丢帧等原因，并不能保证
 *  所有情况下都能够同步成功。capture 生成策略用于控制在已经无法同步所有已启用相机图像帧的情况下，如何处理当前相机图像（丢弃图像或者生成不完整 capture）。
 *
 * @attention 除配置为 ::OB2_PRODUCE_CAPTURE_SYNC_IMAGES_ONLY 模式外，其他模式用户接收到的 capture 可能为非完整 capture（者意味着 capture
 * 内不一定包含所有已启用的相机图像
 *
 * @param[in]  cameras_config_handle 相机配置句柄
 * @param[in]  policy capture 生成策略, 默认策略为：::OB2_PRODUCE_CAPTURE_SYNC_IMAGES_ONLY
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_cameras_config_set_produce_capture_policy(ob2_cameras_config_t cameras_config_handle, ob2_produce_capture_policy_t policy, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Image alignment mode configuration
 *
 * @attention Not all camera stream profile combinations support alignable, check with @ref ob2_device_get_alignable_camera_stream_profile_count function to
 * confirm how to configure.
 *
 * @param[in] cameras_config_handle Handle of cameras_config
 * @param[in] mode Image alignment mode, default mode is::OB2_IMAGES_ALIGN_MODE_DISABLE
 * @param[out] status Output function execution status.
 *
 * \else
 *
 * @brief 图像对齐模式配置
 *
 * @attention 并不是所有相机流配置组合都支持启用对齐，可通过 @ref ob2_device_get_alignable_camera_stream_profile_count 接口查询确认如何配置
 *
 * @param[in] cameras_config_handle 相机配置句柄
 * @param[in] mode 对齐模式，默认模式为：::OB2_IMAGES_ALIGN_MODE_DISABLE
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_cameras_config_set_images_align_mode(ob2_cameras_config_t cameras_config_handle, ob2_images_align_mode_t mode, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Multi-camera (within a single device) synchronization mode (simultaneous exposure)
 *
 * @attention ::OB2_CAMERA_SYNC_MODE_COLOR_EXPOSURE_FIRST and ::OB2_CAMERA_SYNC_MODE_DEPTH_EXPOSURE_FIRST modes: you need to ensure that the Color and Depth/IR
 * frame rates are the same
 *
 * @param[in] cameras_config_handle Handle of cameras_config
 * @param sync_mode Sync mode, default mode is ::OB2_CAMERA_SYNC_MODE_CLOSE.
 * @param status Output function execution status.
 *
 * \else
 *
 * @brief （单机内）多相机同步（同步曝光）模式配置
 *
 * @attention ::OB2_CAMERA_SYNC_MODE_COLOR_EXPOSURE_FIRST 及 ::OB2_CAMERA_SYNC_MODE_DEPTH_EXPOSURE_FIRST 模式： 需要保证 Color 与 Depth/IR 帧率配置一致
 *
 * @param[in] cameras_config_handle 相机配置句柄
 * @param sync_mode 同步模式，默认模式：::OB2_CAMERA_SYNC_MODE_CLOSE。
 * @param status 返回函数调用状态
 *
 * \endif
 */
void ob2_cameras_config_set_cameras_sync_mode(ob2_cameras_config_t cameras_config_handle, ob2_cameras_sync_mode_t sync_mode, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Multi-camera (within a single camera) synchronization delay configuration.
 *
 * @brief When the multi-camera sync mode is configured as ::OB2_CAMERA_SYNC_MODE_COLOR_EXPOSURE_FIRST, it indicates the delay time of the Depth/IR camera
 * relative to the Color camera
 * @brief When the multi-camera sync mode is configured as ::OB2_CAMERA_SYNC_MODE_DEPTH_EXPOSURE_FIRST, it indicates the delay time of the Color camera relative
 * to the Depth/IR camera
 * @brief This delay configuration has no effect when the multi-camera sync mode is configured as ::OB2_CAMERA_SYNC_MODE_CLOSE
 *
 * @param[in] cameras_config_handle Handle of cameras_config
 * @param[in] cameras_sync_delay_usec Camera sync delay in microseconds, default value is 0.
 * @param[out] status Output function execution status.
 *
 * \else
 *
 * @brief （单机内）多相机同步延时配置，用于控制从相机在主相机图像采集后延时多长时间开始图像采集
 *
 * @brief 当多相机同步模式配置为 ::OB2_CAMERA_SYNC_MODE_COLOR_EXPOSURE_FIRST 时表示 Depth/IR 相机相对 Color 相机的延时
 * @brief 当多相机同步模式配置为 ::OB2_CAMERA_SYNC_MODE_DEPTH_EXPOSURE_FIRST 时表示 Color 相机相对 Depth/IR 相机的延时
 * @brief 当多相机同步模式配置为 ::OB2_CAMERA_SYNC_MODE_CLOSE 时该延时配置无任何效果
 *
 * @param[in] cameras_config_handle 相机配置句柄
 * @param[in] cameras_sync_delay_usec 相机同步延时，单位为微秒, 默认值为 0
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_cameras_config_set_cameras_sync_delay_usec(ob2_cameras_config_t cameras_config_handle, uint32_t cameras_sync_delay_usec, ob2_status_t *status);

/**
 * \if English
 *
 * @brief External sync mode configuration (usually synchronization is done via sync signal line input/output sync signal, so named wired_sync_mode)
 * @brief This function is actually configuring the trigger signal source of the device camera and the trigger signal relay output. It is mainly used to realize
 * the multi-device synchronization function.
 *
 * @param[in] cameras_config_handle Handle of cameras_config
 * @param[in] wired_sync_mode External sync mode, default ::OB2_WIRED_SYNC_MODE_STANDALONE
 * @param[out] status Output function execution status.
 *
 * \else
 *
 * @brief 外部同步模式配置（通常是通过同步信号线输入 / 输出同步信号完成同步，所以命名为 wired_sync_mode）
 * @brief 该功能实际上是配置设备相机的触发信号来源，及触发信号中继输出。主要用于实现多机同步功能。
 *
 * @param[in] cameras_config_handle 相机配置句柄
 * @param[in] wired_sync_mode 外部同步模式，默认为 ::OB2_WIRED_SYNC_MODE_STANDALONE
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_cameras_config_set_wired_sync_mode(ob2_cameras_config_t cameras_config_handle, ob2_wired_sync_mode_t wired_sync_mode, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Secondary device delay configuration
 * @brief The device configured in ::OB2_WIRED_SYNC_MODE_SECONDARY mode delays the image acquisition for a period of time after receiving the trigger signal.
 *
 * @attention Effective only when the device is configured as ::OB2_WIRED_SYNC_MODE_SECONDARY
 * @attention This configuration does not affect the trigger signal output
 * @attention The delay time should be less than one image acquisition cycle
 *
 * @param[in] cameras_config_handle Handle of cameras_config
 * @param[in] secondary_delay_usec Secondary device delay, in microseconds, default value is 0.
 * @param[out] status Output function execution status.
 *
 * \else
 *
 * @brief 从设备延时配置
 * @brief 配置为 ::OB2_WIRED_SYNC_MODE_SECONDARY 模式的设备，在接收到触发信号后，延时一段时间后再执行图像采集。
 *
 * @attention 仅当设备配置为 ::OB2_WIRED_SYNC_MODE_SECONDARY 时生效
 * @attention 该配置不会影响触发信号输出
 * @attention 延时时间应当小于一个图像采集周期
 *
 * @param[in] cameras_config_handle 相机配置句柄
 * @param[in] secondary_delay_usec 从设备延时，单位：微秒，默认值为 0。
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_cameras_config_set_secondary_delay_off_primary_usec(ob2_cameras_config_t cameras_config_handle, uint32_t secondary_delay_usec, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Get the cameras calibration parameters under the current cameras_config
 *
 * @attention The calibration parameters obtained from different cameras configurations are not the same. So you need to make sure that you complete the
 * cameras_config first and then pass in the cameras_config to get the parameters.
 *
 * @param[in]  device_handle Handle of device
 * @param[in]  cameras_config_handle Handle of cameras_config
 * @param[out] status Output function execution status.
 * @return ob2_cameras_calibration_t Return cameras calibration parameters
 *
 * \else
 *
 * @brief 获取当前配置下的相机标定参数
 *
 * @attention 不同的相机配置获取得到的标定参数是不一样的。所以需要先确保先完成相机配置，然后传入相机配置获取参数。
 *
 * @param[in]  device_handle 设备句柄
 * @param[in]  cameras_config_handle 相机配置句柄
 * @param[out] status 返回函数调用状态
 * @return ob2_cameras_calibration_t 相机标定参数
 *
 * \endif
 */
ob2_cameras_calibration_t ob2_device_get_cameras_calibration(ob2_device_t device_handle, const ob2_cameras_config_t cameras_config_handle,
                                                             ob2_status_t *status);

/**
 * \if English
 *
 * @brief Start in-device cameras work (start stream)
 * @brief The @cameras_config_handle is used to enable the enabled camera stream, and to configure the device and the relevant work modules inside the SDK
 * according to the configuration.
 * @brief After starting the data stream, the SDK will internally generate capture for each camera output and cache the capture in the internal queue, users
 * need to get capture through @ref ob2_device_get_capture function, and then get each camera image data through capture.
 *
 * @attention After starting the cameras work in the device, you need to loop through @ref ob2_device_get_capture function to get capture in time, otherwise the
 * image data will be lost when the internal cache queue overflows.
 *
 * @param[in] device_handle  Handle of device
 * @param[in] cameras_config_handle Handle of cameras_config，You can release the handle immediately after calling this function.
 * You can pass ::OB2_DEFAULT_CAMERAS_CONFIG, so that the SDK will start all cameras with the default stream configuration of each camera.
 * @param[out] status Output function execution status.
 *
 * \else
 *
 * @brief 启动设备内相机工作（开流）
 * @brief 会根据 cameras_config_handle 开启已使能的相机数据流，同时也会根据配置内容完成设备、SDK 内部相关工作模块的配置。
 * @brief 开启数据流后，SDK 内部会将各相机输出的图像生成 capture，并将 capture 缓存在内部队列，用户需要通过 @ref ob2_device_get_capture 接口获取 capture，
 * 进而通过 capture 获取各相机图像数据。
 *
 * @attention 启动设备内相机工作后, 需要及时地通过 @ref ob2_device_get_capture 接口循环获取 capture，否则内部缓存队列溢出后会丢失图像数据。
 *
 * @param[in] device_handle 设备句柄
 * @param[in] cameras_config_handle 相机配置句柄，调用完本接口后可立即停释放相机配置句柄。可传入 ::OB2_DEFAULT_CAMERAS_CONFIG,
 * 这样 SDK 将通过各相机的默认流配置启动所有相机。
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_device_start_cameras(ob2_device_t device_handle, const ob2_cameras_config_t cameras_config_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Start in-device cameras work by returning capture via a callback (start stream)
 * @brief The @cameras_config_handle is used to enable the enabled camera stream, and to configure the device and the relevant work modules inside the SDK
 * according to the configuration.
 * @brief After starting the data stream, the SDK internally generates capture from the output of each camera and returns capture via the callback function @cb
 *
 * @attention The callback function @cb is a user-written function that needs to be executed in less than the capture generation period (determined by the image
 * output period of the stream with the highest frame rate of the enabled camera), otherwise it will cause the SDK internal cache queue to overflow and lose
 * image data, and the image data will have a cumulative delay resulting in poor image realtime. For some models of devices, this may even lead to stopped
 * streams.
 *
 * @param[in] device_handle Handle of device
 * @param[in] cameras_config_handle Handle of cameras_config，You can release the handle immediately after calling this function.
 * You can pass ::OB2_DEFAULT_CAMERAS_CONFIG, so that the SDK will start all cameras with the default stream configuration of each camera.
 * @param[in] cb capture callback function
 * @param[in] user_data User-defined data is returned as is via @cb, and the user can pass contextual data via user_data
 * @param[out] status Output function execution status.
 *
 * \else
 *
 * @brief 通过回调返回 capture 的方式启动设备内相机工作（开流）
 * @brief 会根据 cameras_config_handle 开启已使能的相机数据流，同时也会根据配置内容完成设备、SDK 内部相关工作模块的配置
 * @brief 开启数据流后，SDK 内部会将各相机输出的图像生成 capture，并通过回调函数 cb 返回 capture
 *
 * @attention 回调函数 @cb 是用户自行编写的函数，需要保证该函数的执行时间小于 capture 生成周期（由已使能的相机中数据流帧率最大的数据流图像输出周期决定），
 * 否则会导致 SDK 内部缓存队列溢出而丢失图像数据，并且图像数据会有累加延时导致图像实时性变差。对于某些型号的设备，甚至可能会导致停流。
 *
 * @param[in] device_handle 设备句柄
 * @param[in] cameras_config_handle 相机配置，调用完本接口后可立即停释放相机配置句柄。可传入 ::OB2_DEFAULT_CAMERAS_CONFIG,
 *  这样 SDK 将通过各相机的默认流配置启动所有相机
 * @param[in] cb capture 回调函数
 * @param[in] user_data 用户自定义数据，会通过 cb 原样返回，用户可通过 user_data 传递上下文数据
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_device_start_cameras_with_callback(ob2_device_t device_handle, const ob2_cameras_config_t cameras_config_handle, ob2_capture_cb_t cb, void *user_data,
                                            ob2_status_t *status);

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
 * @param[in] device_handle Handle of device
 * @param[in] cameras_config_handle Cameras_config for updates
 * @param[out] status Output function execution status.
 *
 * \else
 *
 * @brief 更新设备相机配置
 * @brief 可实现设备相机工作过程中的配置更新，比如在不停止相机工作的情况下打开或关闭某一类型相机的数据流
 *
 * @attention 需求先启动设备内相机工作，否则调用本接口将没有任何实际意义
 * @attention 当前不支持设备内多相机同步配置及外部同步配置更新
 *
 * @param[in] device_handle 设备句柄
 * @param[in] cameras_config_handle 用于更新的相机配置
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_device_update_cameras_config(ob2_device_t device_handle, const ob2_cameras_config_t cameras_config_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Stops cameras work in the device (stop stream)
 *
 * @param[in] device_handle  Handle of device
 * @param[out] status Output function execution status.
 *
 * \else
 *
 * @brief 停止设备内相机工作（关流）
 *
 * @param[in] device_handle  设备句柄
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_device_stop_cameras(ob2_device_t device_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Get capture
 * @brief Used in conjunction with the @ref ob2_device_start_cameras function, this function is used to obtain the capture generated by the received image after
 * starting the cameras in the device.
 * @brief When this function is called, if the SDK does not have a capture cache in its internal queue, it will wait blockingly until a capture is successfully
 * acquired or until the @timeout_msec has been exceeded.
 *
 * @attention Once you have started the cameras in the device, you need to cycle through this function to get capture in time, otherwise the image data will be
 * lost when the internal cache queue overflows.
 * @attention If the capture is not successfully generated after @timeout_msec has been set, it will return ::OB2_STATUS_RUNTIME_ERROR via @status and the
 * returned capture will be NULL
 * @attention If the capture is not in use after it has been successfully acquired, the @ref ob2_capture_release function needs to be called to release the
 * capture handle, otherwise a memory leak will result.
 *
 * @param[in] device_handle Handle of device
 * @param[in] timeout_msec Wait timeout, can be set to ::OB2_WAIT_INFINITE for unlimited waiting.
 * @param[out] status Output function execution status.
 * @return ob2_capture_t return the handle of capture
 *
 * \else
 *
 * @brief 获取 capture
 * @brief 配合 @ref ob2_device_start_cameras 接口使用，在启动设备内相机工作后，通过本接口获取接收到图像后生成的 capture。
 * @brief 调用本接口后，如果 SDK 内部未有 capture 缓存在队列中，会进行阻塞式等待，直到成功获取到 capture 或者等待超过了 @timeout_msec 设定的时间。
 *
 * @attention 启动设备内相机工作后，需要及时地通过本接口循环获取 capture，否则内部缓存队列溢出后会丢失图像数据。
 * @attention 如果 @timeout_msec 设置时间后还未成功生成 capture，将会通过 @status 返回 ::OB2_STATUS_RUNTIME_ERROR ，同时返回的 capture 也为 NULL
 * @attention 成功获取到 capture 后，若不在使用该 capture，需要调用 @ref ob2_capture_release 接口释放 capture 句柄，否则会导致内存泄漏。
 *
 * @param[in] device_handle 设备句柄
 * @param[in] timeout_msec 等待超时时间，可以设置为 ::OB2_WAIT_INFINITE 表示不限时等待。
 * @param[out] status 返回函数调用状态
 * @return ob2_capture_t 返回 capture 句柄
 *
 * \endif
 */
ob2_capture_t ob2_device_get_capture(ob2_device_t device_handle, int32_t timeout_msec, ob2_status_t *status);

/**
 * \if English
 *
 * @brief create capture
 * @brief After the capture has been created, it can be used for user-defined image staging (image staging is implemented via @ref
 * ob2_capture_set_image).
 *
 * @attention If you are not using the capture after it has been created, you need to call the @ref ob2_capture_release function to release the capture,
 * otherwise it will cause a memory leak.
 *
 * @param[out] status Output function execution status.
 * @return ob2_capture_t Returns the handle of newly created capture.
 *
 * \else
 *
 * @brief 创建 capture
 * @brief 创建 capture 后，可用于用户的自定义图像的暂存（通过 @ref ob2_capture_set_image 实现图像暂存）
 *
 * @attention 创建 capture 后，若不在使用该 capture，需要调用 @ref ob2_capture_release 接口释放 capture 句柄，否则会导致内存泄漏。
 *
 * @param[out] status 返回函数调用状态
 * @return ob2_capture_t 返回新创建的 capture 句柄
 *
 * \endif
 */
ob2_capture_t ob2_capture_create(ob2_status_t *status);

/**
 * \if English
 *
 * @brief Increasing the capture reference count
 * @brief Any capture acquired or created via any of the SDK's function has a reference count of 1. Calling this function adds 1 to the reference count, then
 * each call to @ref ob2_capture_release subtracts 1 from the reference count, and the memory bound to the capture handle is actually released when the
 * reference count is reduced to 0.
 *
 * @attention Calling this interface is risky and should only be used if you have a clear understanding of the capture reference counting mechanism and the
 * reference count values of the captures obtained by each function. It is also necessary to ensure that every time this function is called, the @ref
 * ob2_capture_release function is called in the future accordingly, otherwise a memory leak may occur.
 *
 * @param[in] capture_handle Handle of capture.
 * @param[out] status Output function execution status.
 *
 * \else
 *
 * @brief 增加 capture 引用计数
 * @brief 通过 SDK 的任何接口获取或创建的 capture 的引用计数都是 1，通过调用本接口可使引用计数加 1。然后每次调用 @ref ob2_capture_release 会使引用计数减 1，
 *  当引用计数减为 0 时，才会真正释放 capture 句柄所绑定的内存。
 *
 * @attention 调用本接口有较大风险，只有在清晰理解 capture 引用计数机制及各接口获取到的 capture 的引用计数值之后才可使用。
 *  并且需求确保每调用一次本接口，就要在未来相应地调用一次 @ref ob2_capture_release 接口，否则会导致内存泄漏。
 *
 * @param[in] capture_handle capture 句柄
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_capture_reference(ob2_capture_t capture_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief release capture
 * @brief Each call to @ref ob2_capture_release actually decrements the reference count of capture by 1, and the memory bound to the capture handle is not
 * actually released until the reference count is reduced to 0.
 *
 * @param[in] capture_handle Handle of capture.
 * @param[out] status Output function execution status.
 *
 * \else
 *
 * @brief 释放 capture
 * @brief 实际上每次调用 @ref ob2_capture_release 会将 capture 的引用计数减 1，当引用计数减为 0 时，才会真正释放 capture 句柄所绑定的内存。
 *
 * @param[in] capture_handle capture 句柄
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_capture_release(ob2_capture_t capture_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Get the image of the specified camera
 *
 * @attention If the current capture does not contain an image from the given camera, ::OB2_STATUS_LOGIC_ERROR will be returned via @status, with a NULL
 * image handle. Possible reasons for not including images from a specified camera are：
 *      1. The camera specified by @camera_type is not enabled when starting cameras operation
 *      2. The @produce_capture_policy default policy is modified when starting cameras operation
 * @attention After successfully acquiring an image, if the image is not in use, you need to call the @ref ob2_image_release function to release the image
 * handle, otherwise a memory leak will result.
 *
 * @param[in] capture_handle Handle of Capture
 * @param[in] camera_type Type of camera
 * @param[out] status Output function execution status.
 * @return ob2_image_t Return the handle of image
 *
 * \else
 *
 * @brief 获取指定相机的图像
 *
 * @attention 如果当前 capture 内不包含指定相机的图像，将会通过 @status 返回 ::OB2_STATUS_LOGIC_ERROR ，同时返回的图像句柄为 NULL。
 *  不包含指定相机的图像的原因可能为：
 *      1. 启动相机工作时 @camera_type 指定的相机未使能
 *      2. 启动相机工作时 @produce_capture_policy 默认策略被修改
 * @attention 成功获取到图像后，若不在使用该图像，需要调用 @ref ob2_image_release 接口释放图像句柄，否则会导致内存泄漏。
 *
 * @param[in] capture_handle capture 句柄
 * @param[in] camera_type 相机类型
 * @param[out] status 返回函数调用状态
 * @return ob2_image_t 图像句柄
 *
 * \endif
 */
ob2_image_t ob2_capture_get_image(ob2_capture_t capture_handle, ob2_camera_type_t camera_type, ob2_status_t *status);

/**
 * \if English
 *
 * @brief  Get an image of color camera
 *
 * @attention If the current capture does not contain an image from the color camera, ::OB2_STATUS_LOGIC_ERROR will be returned with @status and the image
 * handle returned will be NULL.
 * @attention After successfully acquiring an image, if the image is not in use, you need to call the @ref ob2_image_release interface to release the image
 * handle, otherwise a memory leak will result.
 *
 * @param[in] capture_handle Handle of Capture
 * @param[out] status Output function execution status.
 * @return ob2_image_t Return the handle of image
 *
 * \else
 *
 * @brief 获取 Color 相机图像
 *
 * @attention 如果当前 capture 内不包含 Color 相机的图像，将会通过 @status 返回 ::OB2_STATUS_LOGIC_ERROR ，同时返回的图像句柄为 NULL。
 * @attention 成功获取到图像后，若不在使用该图像，需要调用 @ref ob2_image_release 接口释放图像句柄，否则会导致内存泄漏。
 *
 * @param[in] capture_handle capture 句柄
 * @param[out] status 返回函数调用状态
 * @return ob2_image_t 图像句柄
 *
 * \endif
 */
ob2_image_t ob2_capture_get_color_image(ob2_capture_t capture_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief  Get an image of depth camera
 *
 * @attention If the current capture does not contain an image from the depth camera, ::OB2_STATUS_LOGIC_ERROR will be returned with @status and the image
 * handle returned will be NULL.
 * @attention After successfully acquiring an image, if the image is not in use, you need to call the @ref ob2_image_release interface to release the image
 * handle, otherwise a memory leak will result.
 *
 * @param[in] capture_handle Handle of Capture
 * @param[out] status Output function execution status.
 * @return ob2_image_t Return the handle of image
 *
 * \else
 *
 * @brief 获取 Depth 相机图像
 *
 * @attention 如果当前 capture 内不包含 Depth 相机的图像，将会通过 @status 返回 ::OB2_STATUS_LOGIC_ERROR ，同时返回的图像句柄为 NULL。
 * @attention 成功获取到图像后，若不在使用该图像，需要调用 @ref ob2_image_release 接口释放图像句柄，否则会导致内存泄漏。
 *
 * @param[in] capture_handle capture 句柄
 * @param[out] status 返回函数调用状态
 * @return ob2_image_t 图像句柄
 *
 * \endif
 */
ob2_image_t ob2_capture_get_depth_image(ob2_capture_t capture_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief  Get an image of infrared camera
 *
 * @attention If the current capture does not contain an image from the infrared camera, ::OB2_STATUS_LOGIC_ERROR will be returned with @status and the image
 * handle returned will be NULL.
 * @attention After successfully acquiring an image, if the image is not in use, you need to call the @ref ob2_image_release interface to release the image
 * handle, otherwise a memory leak will result.
 *
 * @param[in] capture_handle Handle of Capture
 * @param[out] status Output function execution status.
 * @return ob2_image_t Return the handle of image
 *
 * \else
 *
 * @brief 获取红外相机图像
 *
 * @attention 如果当前 capture 内不包含红外相机的图像，将会通过 @status 返回 ::OB2_STATUS_LOGIC_ERROR ，同时返回的图像句柄为 NULL。
 * @attention 成功获取到图像后，若不在使用该图像，需要调用 @ref ob2_image_release 接口释放图像句柄，否则会导致内存泄漏。
 *
 * @param[in] capture_handle capture 句柄
 * @param[out] status 返回函数调用状态
 * @return ob2_image_t 图像句柄
 *
 * \endif
 */
ob2_image_t ob2_capture_get_ir_image(ob2_capture_t capture_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Set the image for a given camera
 * @brief A copy (shallow copy) of the image is saved to capture. If the capture already contains an image from the specified camera, the original image is
 * released first.
 *
 * @attention After calling this interface, the image still needs to be released by the user by calling the @ref ob2_image_release function, otherwise it will
 * lead to a memory leak.
 *
 * @param[in] capture_handle Handle of Capture.
 * @param[in] camera_type Type of camera.
 * @param[in] image_handle The handle of iamge to be saved.
 * @param[out] status Output function execution status.
 *
 * \else
 *
 * @brief 设置指定相机的图像
 * @brief 会将图像拷贝（浅拷贝）保存一份到 capture 内，如果 capture 已包含指定相机的图像，则会先将原图像释放。
 *
 * @attention 调用本接口后，图像句柄还是需要用户调用 @ref ob2_image_release 接口释放，否则会导致内存泄漏。
 *
 * @param[in] capture_handle capture 句柄
 * @param[in] camera_type 相机类型
 * @param[in] image_handle 图像句柄
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_capture_set_image(ob2_capture_t capture_handle, ob2_camera_type_t camera_type, ob2_image_t image_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Set the image of color camera
 * @brief A copy (shallow copy) of the image is saved to capture. If the capture already contains an image of color camera, the original image is
 * released first.
 *
 * @attention After calling this interface, the image still needs to be released by the user by calling the @ref ob2_image_release function, otherwise it will
 * lead to a memory leak.
 *
 * @param[in] capture_handle Handle of Capture.
 * @param[in] image_handle The handle of iamge to be saved.
 * @param[out] status Output function execution status.
 *
 * \else
 *
 * @brief 设置 Color 相机的图像
 * @brief 会将图像拷贝（浅拷贝）保存一份到 capture 内，如果 capture 已包含 Color 相机的图像，则会先将原图像释放。
 *
 * @attention 调用本接口后，图像句柄还是需要用户调用 @ref ob2_image_release 接口释放，否则会导致内存泄漏。
 *
 * @param[in] capture_handle capture 句柄
 * @param[in] image_handle 图像句柄
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_capture_set_color_image(ob2_capture_t capture_handle, ob2_image_t image_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Set the image of depth camera
 * @brief A copy (shallow copy) of the image is saved to capture. If the capture already contains an image of depth camera, the original image is
 * released first.
 *
 * @attention After calling this interface, the image still needs to be released by the user by calling the @ref ob2_image_release function, otherwise it will
 * lead to a memory leak.
 *
 * @param[in] capture_handle Handle of Capture.
 * @param[in] image_handle The handle of iamge to be saved.
 * @param[out] status Output function execution status.
 *
 * \else
 *
 * @brief 设置 Depth 相机的图像
 * @brief 会将图像拷贝（浅拷贝）保存一份到 capture 内，如果 capture 已包含 Depth 相机的图像，则会先将原图像释放。
 *
 * @attention 调用本接口后，图像句柄还是需要用户调用 @ref ob2_image_release 接口释放，否则会导致内存泄漏。
 *
 * @param[in] capture_handle capture 句柄
 * @param[in] image_handle 图像句柄
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_capture_set_depth_image(ob2_capture_t capture_handle, ob2_image_t image_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Set the image of infrared camera
 * @brief A copy (shallow copy) of the image is saved to capture. If the capture already contains an image of infrared camera, the original image is
 * released first.
 *
 * @attention After calling this interface, the image still needs to be released by the user by calling the @ref ob2_image_release function, otherwise it will
 * lead to a memory leak.
 *
 * @param[in] capture_handle Handle of Capture.
 * @param[in] image_handle The handle of iamge to be saved.
 * @param[out] status Output function execution status.
 *
 * \else
 *
 * @brief 设置红外相机的图像
 * @brief 会将图像拷贝（浅拷贝）保存一份到 capture 内，如果 capture 已包含红外相机的图像，则会先将原图像释放。
 *
 * @attention 调用本接口后，图像句柄还是需要用户调用 @ref ob2_image_release 接口释放，否则会导致内存泄漏。
 *
 * @param[in] capture_handle capture 句柄
 * @param[in] image_handle 图像句柄
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_capture_set_ir_image(ob2_capture_t capture_handle, ob2_image_t image_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Create an image
 * @brief The SDK internally requests an appropriate size of memory based on the image format, width, height, row span, etc.
 *
 * @attention The @ref ob2_image_release function needs to be called to release the image handle when the created image is no longer in use, otherwise it will
 * cause a memory leak
 *
 * @param[in] source_camera_type Image original camera type (for image information tracking, can be filled with ::OB2_CAMERA_UNKNOWN)
 * @param[in] format Image formats
 * @param[in] width_pixels Image width in pixels
 * @param[in] height_pixels Image height in pixels
 * @param[in] stride_bytes Image stride (row span) in bytes
 * @param[out] status Output function execution status.
 * @return ob2_image_t Returns the handle of newly created image.
 *
 * \else
 *
 * @brief 创建图像
 * @brief SDK 内部会根据图像格式、宽、高、行跨都等信息在内部申请一块合适大小内存的内存
 *
 * @attention 当创建的图像不再使用时，需要调用 @ref ob2_image_release 接口释放图像句柄，否者将会导致内存泄漏
 *
 * @param[in] source_camera_type 图像原相机类型（用于图像信息追踪，可以填 ::OB2_CAMERA_UNKNOWN ）
 * @param[in] format 图像格式
 * @param[in] width_pixels 图像宽，单位：像素
 * @param[in] height_pixels 图像高，单位：像素
 * @param[in] stride_bytes 图像行跨度，单位：字节
 * @param[out] status 返回函数调用状态
 * @return ob2_image_t 返回新创建的图像句柄
 *
 * \endif
 */
ob2_image_t ob2_image_create(ob2_camera_type_t source_camera_type, ob2_image_format_t format, uint32_t width_pixels, uint32_t height_pixels,
                             uint32_t stride_bytes, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Create an image from buffer
 * @brief The buffer of the created image is the incoming buffer, the allocate and release of the buffer memory is done by the user code
 *
 * @attention The buffer memory needs to be allocated by the user in advance and the size of the memory needs to be matched to the image format, width, height,
 * row span etc.
 * @attention The @ref ob2_image_release interface needs to be called to release the image handle when the created image is no longer in use, otherwise it will
 * cause a memory leak
 *
 * @param[in] source_camera_type Image original camera type (for image information tracking, can be filled with ::OB2_CAMERA_UNKNOWN).
 * @param[in] format Image formats.
 * @param[in] width_pixels Image width in pixels.
 * @param[in] height_pixels Image height in pixels.
 * @param[in] stride_bytes Image stride (row span) in bytes.
 * @param[in] buffer  Pointer of buffer.
 * @param[in] buffer_size Buffer memory size in bytes.
 * @param[in] buffer_release_cb The buffer release callback function, which is called when the image is released, is the one that the user needs to ensure is
 * able to release the memory accurately.
 * @param[in] user_data User-defined data, which will be returned when buffer_release_cb is called, can be passed in by the user as contextual data.
 * @param[out] status Output function execution status.
 * @return ob2_image_t Returns the handle of newly created image.
 *
 * \else
 *
 * @brief 从指定 buffer 创建图像
 * @brief 创建好的图像的 buffer 即为传入的 buffer，buffer 内存的申请和释放都需要用户代码完成
 *
 * @attention buffer 内存需要由用户提前申请好，并且需要确保内存的大小与图像格式、宽、高、行跨都等条件匹配。
 * @attention 当创建的图像不再使用时，需要调用 @ref ob2_image_release 接口释放图像句柄，否者可能会导致内存泄漏。
 *
 * @param[in] source_camera_type 图像原相机类型（用于图像信息追踪，可以填 ::OB2_CAMERA_UNKNOWN ）
 * @param[in] format 图像格式
 * @param[in] width_pixels 图像宽，单位：像素
 * @param[in] height_pixels 图像高，单位：像素
 * @param[in] stride_bytes 图像行跨度，单位：字节
 * @param[in] buffer buffer 地址指针
 * @param[in] buffer_size buffer 内存大小，单位：字节
 * @param[in] buffer_release_cb buffer 释放回调函数，会在 image 释放时调用，用户需要确保该回调函数能够准确释放内存
 * @param[in] user_data 用户自定义数据，会在调用 buffer_release_cb 时返回，用户可以传入上下文数据
 * @param[out] status 返回函数调用状态
 * @return ob2_image_t 返回新创建的图像句柄
 *
 * \endif
 */
ob2_image_t ob2_image_create_from_buffer(ob2_camera_type_t source_camera_type, ob2_image_format_t format, uint32_t width_pixels, uint32_t height_pixels,
                                         uint32_t stride_bytes, uint8_t *buffer, uint32_t buffer_size, ob2_buffer_release_cb_t buffer_release_cb,
                                         void *user_data, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Increase image reference count
 * @brief Any image acquired or created through any of the SDK's function has a reference count of 1. Calling this interface adds 1 to the reference count,
 * then each call to @ref ob2_image_release decrements the reference count by 1, and the memory bound to the image handle is actually released when the
 * reference count is reduced to 0.
 *
 * @attention Calling this interface is risky and should only be used after a clear understanding of the image reference counting mechanism and the reference
 * count values of the images obtained by each interface. * It is also necessary to ensure that every call to this interface is followed by a future call to the
 *  @ref ob2_image_release function, otherwise a memory leak may result.
 *
 * @param[in] image_handle Handle of image
 * @param[out] status Output function execution status.
 *
 * \else
 *
 * @brief 增加图像引用计数
 * @brief 通过 SDK 的任何接口获取或创建的图像的引用计数都是 1，通过调用本接口可使引用计数加 1。然后每次调用 @ref ob2_image_release 会使引用计数减 1，
 *  当引用计数减为 0 时，才会真正释放 image 句柄所绑定的内存。
 *
 * @attention 调用本接口有较大风险，只有在清晰理解 image 引用计数机制及各接口获取到的 image 的引用计数值之后才可使用。
 *  并且需求确保每调用一次本接口，就要在未来相应地调用一次 @ref ob2_image_release 接口，否则会导致内存泄漏。
 *
 * @param[in] image_handle 图像句柄
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_image_reference(ob2_image_t image_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Release image
 * @brief In fact each call to @ref ob2_image_release decrements the reference count of the image by 1. When the reference count is reduced to 0, the memory
 * bound to the image handle is actually released.
 *
 * @param[in] image_handle Handle of image
 * @param[out] status Output function execution status.
 *
 * \else
 *
 * @brief 释放图像
 * @brief 实际上每次调用 @ref ob2_image_release 会将图像的引用计数减 1，当引用计数减为 0 时，才会真正释放 image 句柄所绑定的内存。
 *
 * @param[in] image_handle capture 句柄
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_image_release(ob2_image_t image_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Get image buffer
 * @brief The image buffer contains the data of the image, which can be read or modified directly by the user via the returned buffer pointer.
 *
 * @attention Do not access the buffer pointing memory after the image has been freed, otherwise unexpected problems may occur.
 *
 * @param[in] image_handle Handle of image
 * @param[out] status Output function execution status.
 *
 * @return uint8_t* Pointer of buffer.
 *
 * \else
 *
 * @brief 获取图像 buffer
 * @brief 图像 buffer 内放的即是图像的数据，用户可以通过返回的 buffer 指针直接读取或修改图像数据。
 *
 * @attention 在图像被释放后，不要再对 buffer 指向内存进行访问，否则会出现意想不到的问题。
 *
 * @param[in] image_handle 图像句柄
 * @param[out] status 返回函数调用状态
 * @return uint8_t* buffer 地址指针
 *
 * \endif
 */
uint8_t *ob2_image_get_buffer(ob2_image_t image_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Get image data size
 * @brief Normally the image data size will be the same as the buffer memory size, but for compressed or encoded format images, the image data size will be
 * smaller than the buffer size.
 *
 * @param[in] image_handle Handle of image
 * @param[out] status Output function execution status.
 * @return uint32_t Image data size in bytes
 *
 * \else
 *
 * @brief 获取图像数据大小
 * @brief 通常图像的数据大小会与 buffer 内存大小一致，但是对于压缩或者编码格式图像，图像数据数据大小会小于 buffer 大小。
 *  不过 buffer 大小对用户是没有啥实际意义的，所以可以不用理会
 *
 * @param[in] image_handle 图像句柄
 * @param[out] status 返回函数调用状态
 * @return uint32_t 图像数据大小，单位：字节
 *
 * \endif
 */
uint32_t ob2_image_get_size(ob2_image_t image_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Get image format
 * @brief The image format represents the arrangement of image pixels, compression, encoding and other characteristics. The user needs to decide how to use the
 * image data according to the image format
 *
 * @param[in] image_handle Handle of image
 * @param[out] status Output function execution status.
 * @return ob2_image_format_t Return the format of image.
 *
 * \else
 *
 * @brief 获取图像格式
 * @brief 图像格式代表着图像像素的排列方式、压缩、编码等特性。用户需要根据图像格式决定如何使用图像数据
 *
 * @param[in] image_handle 图像句柄
 * @param[out] status 返回函数调用状态
 * @return ob2_image_format_t 返回图像格式
 *
 * \endif
 */
ob2_image_format_t ob2_image_get_format(ob2_image_t image_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Get image width
 *
 * @param[in] image_handle Handle of image
 * @param[out] status Output function execution status.
 * @return uint32_t Returns the width of the image in pixels
 *
 * \else
 *
 * @brief 获取图像宽度
 *
 * @param[in] image_handle 图像句柄
 * @param[out] status 返回函数调用状态
 * @return uint32_t 返回图像宽度，单位：像素
 *
 * \endif
 */
uint32_t ob2_image_get_width_pixels(ob2_image_t image_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Get image height
 *
 * @param[in] image_handle Handle of image
 * @param[out] status Output function execution status.
 * @return uint32_t Returns the height of the image in pixels
 *
 * \else
 *
 * @brief 获取图像高度
 *
 * @param[in] image_handle 图像句柄
 * @param[out] status 返回函数调用状态
 * @return uint32_t 返回图像高度，单位：像素
 *
 * \endif
 */
uint32_t ob2_image_get_height_pixels(ob2_image_t image_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Get image stride (row span)
 * @brief The user can offset the buffer address pointer by the row span size to quickly fetch pixel data at the specified coordinates of the image.
 *
 * @attention stride_bytes and width_pixels are not necessarily multiples, as under certain conditions, some blank data may be padded at the end of each image
 * line to achieve memory alignment
 * @attention Images in non-planer formats (MJPG, H264, H265, RLE, COMPRESSED, etc.) do not have the stride_bytes concept and calls to this interface
 * return ::OB2_STATUS_RUNTIME_ERROR via @status
 *
 * @param[in] image_handle Handle of image
 * @param[out] status Output function execution status.
 * @return uint32_t Returns the image row span in bytes
 *
 * \else
 *
 * @brief 获取图像行跨度
 * @brief 用户可以通过行跨度大小，对 buffer 地址指针进行偏移，从而快速获取图像指定坐标下的像素数据
 *
 * @attention stride_bytes 与 width_pixels 不一定是倍数关系，因为某些条件下，可能会往图像每一行尾部数据填充一些空白数据以实现内存对齐
 * @attention 非像素平铺格式（MJPG、H264、H265、RLE、COMPRESSED 等）的图像没有 stride_bytes 概念，调用本接口会通过 @status 返回 ::OB2_STATUS_RUNTIME_ERROR
 *
 * @param[in] image_handle 图像句柄
 * @param[out] status 返回函数调用状态
 * @return uint32_t 返回图像行跨度，单位：字节
 *
 * \endif
 */
uint32_t ob2_image_get_stride_bytes(ob2_image_t image_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Get device timestamp
 * @brief The device timestamp is the time stamp on the device side of the image, which is closest to the time when the image was generated.
 *
 * @attention By default, this timestamp is the length of time that has passed since the device was started and is reset to zero and re-counted after the device
 * is rebooted. The device time counter is reset to zero and re-calculated after it overflows.
 * @attention Due to the precision of the device clock, although the device timestamp is in microseconds, the device precision of some devices is actually in
 * milliseconds, so the lower three digits of the value will be zero.
 * @attention Not all devices support device timestamp return, and due to Windows system limitations, some special system configuration is required to obtain
 * the timestamp (this can be done automatically by running the OrbbecViewer tool with administrator privileges).
 *
 * @param[in] image_handle Handle of image
 * @param[out] status Output function execution status.
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
 * @param[in] image_handle 图像句柄
 * @param[out] status 返回函数调用状态
 * @return uint64_t 返回设备时间戳，单位：微秒
 *
 * \endif
 */
uint64_t ob2_image_get_device_timestamp_usec(ob2_image_t image_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Get system timestamp
 * @brief The system timestamp is the timestamp punched when the image data is received by the SDK on the Host side (Host's localtime, timed from
 * 1970-01-01T00:00:00Z.)
 *
 * @param[in] image_handle Handle of image
 * @param[out] status Output function execution status.
 * @return uint64_t Return system timestamp in microseconds
 *
 * \else
 *
 * @brief 获取系统时间戳
 * @brief 系统时间戳是指 Host 端 SDK 接收到图像数据时打的时间戳（Host 的 localtime，是从 1970-01-01T00:00:00Z. 开始的计时）
 *
 * @param[in] image_handle 图像句柄
 * @param[out] status 返回函数调用状态
 * @return uint64_t 返回系统时间戳，单位：微秒
 *
 * \endif
 */
uint64_t ob2_image_get_system_timestamp_usec(ob2_image_t image_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Get image source camera type
 * @brief Images obtained through the SDK are filled in with the source camera type, which represents the source of the image data.
 *
 * @param[in] image_handle Handle of image
 * @param[out] status Output function execution status.
 * @return ob2_camera_type_t Return the source camera type of image.
 *
 * \else
 *
 * @brief 获取图像源相机类型
 * @brief 通过 SDK 获取得到的图像都会填写源相机类型，代表了图像数据来源
 *
 * @param[in] image_handle 图像句柄
 * @param[out] status 返回函数调用状态
 * @return ob2_camera_type_t 相机类型
 *
 * \endif
 */
ob2_camera_type_t ob2_image_get_source_camera_type(ob2_image_t image_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Get the number of valid bits of image pixels
 * @brief For Depth and IR images, usually only the low bits of the image pixels are valid and the high bits are fixed to zero. (For example, a camera depth
 * image in Y16 format has 16 bits for each pixel, but only the lower 14 bits are valid and the upper two bits are zero, so a call to this function will return
 * 14)
 *
 * @param[in] image_handle Handle of image
 * @param[out] status Output function execution status.
 * @return uint8_t Return the number of valid bits of image pixels
 *
 * \else
 *
 * @brief 获取图像像素有效位数
 * @brief 对于 Depth 和 IR 图像，通常其图像像素只有低位有效，高位固定为零。（比如某相机深度是 Y16 格式的图像，其像素位位数为 16，
 *  但是只有低 14 位有效，高两位为零，此时调用本接口将返回 14）
 *
 * @param[in] image_handle 图像句柄
 * @param[out] status 返回函数调用状态
 * @return uint8_t 返回图像像素有效位数
 *
 * \endif
 */
uint8_t ob2_image_get_available_bits_for_each_pixel(ob2_image_t image_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Get depth image pixel value scaling factor
 * @brief The depth image pixel value is the distance from the target object to the camera in millimeters, but the actual image value may be scaled due to
 * camera characteristics, algorithmic processing, etc. This function returns the scaling factor used to restore the image data to a value in millimeters, for
 * example, if scale=0.1 and the pixel value at a given coordinate is pixel_value=10000, then the depth distance value = pixel_Value*scale = 10000*0.1=1000mm.
 *
 * @attention Valid for depth images only, calls to this function for non-depth images will return ::OB2_STATUS_RUNTIME_ERROR via @status
 *
 * @param[in] image_handle Handle of image
 * @param[out] status Output function execution status.
 * @return uint8_t Return the depth image pixel value scaling factor
 *
 * \else
 *
 * @brief 获取深度图像数值缩放系数
 * @brief 深度图像像素值意义为目标物体到相机的距离，单位为 mm。但是，由于相机特性、算法处理等原因，实际图像的数值可能会被缩放。
 *  本接口返回用于将图像数据恢复为以毫米为单位的数值时所需要缩放的系数, 比如，scale=0.1 时, 某坐标下像素值为 pixel_value=10000，
 *  则表示深度距离 value = pixel_Value*scale = 10000*0.1=1000mm。
 *
 * @attention 仅深度图像有效，非深度图像调用本接口将会通过 @status 返回 ::OB2_STATUS_RUNTIME_ERROR
 *
 * @param[in] image_handle 图像句柄
 * @param[out] status 返回函数调用状态
 * @return uint8_t 返回深度图数值缩放系数
 *
 * \endif
 */
float ob2_depth_image_get_value_scale(ob2_image_t image_handle, ob2_status_t *status);

#ifdef __cplusplus
}
#endif