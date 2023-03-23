#pragma once
#include "ob2types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \if English
 *
 * @brief Create an image converter
 * @brief The Image Converter completes the functions of depth image to point cloud and depth and RGB image to color point cloud
 *
 * @attention It is necessary to ensure that the image calibration parameters passed in to create the image converter are related to the image itself (the
 * cameras_config configuration used by the camera to start acquiring images and obtaining internal parameters is the same)
 * @attention After the image converter is successfully created, if the image converter is no longer used, you need to call @ref ob2_transformation_destroy to
 * destroy, otherwise the internal parameters will leak.
 *
 * @param[in] calibration Calibration parameters, image conversion depends on camera calibration parameters
 * @param[out] status Output function execution status
 * @return ob2_transformation_t Returns the handle to the image converter
 *
 * \else
 *
 * @brief 创建图像转换器
 * @brief 图像转换器可完成深度图像转点云图及深度和 RGB 图像转彩色点云图的功能
 *
 * @attention 需要保证传入创建图像转换器的图像标定参数，与图像本身是相关连的（相机启动获取图像和获取内参使用的 cameras_config 配置是一样的）
 * @attention 成功创建图像转换器后，不再使用该图像转换器的话，需要调用 @ref ob2_transformation_destroy 销毁，否则会导致内参泄漏。
 *
 * @param[in] calibration 标定参数，图像的转换依赖相机标定参数
 * @param[out] status 返回函数调用状态
 * @return ob2_transformation_t 返回图像转换器句柄
 *
 * \endif
 */
ob2_transformation_t ob2_transformation_create(const ob2_cameras_calibration_t *calibration, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Destroy the image converter
 *
 * @param[in] transformation_handle Image converter handle
 * @param[out] status Output function execution status
 *
 * \else
 *
 * @brief 销毁图像转换器
 *
 * @param[in] transformation_handle 图像转换器句柄
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_transformation_destroy(ob2_transformation_t transformation_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Depth image to point cloud image
 *
 * @attention After the point cloud image is successfully converted and generated, if the point cloud image or the original depth image is no longer needed, you
 * need to call @ref ob2_image_release release, otherwise the internal parameters will leak.
 *
 * @param[in] transformation_handle A handle to the image converter
 * @param[in] depth_image_handle A handle to the depth image
 * @param[in] position_scale The coefficient of coordinate scaling, when not scaling, can be filled in 1.0f
 * @param[out] status Output function execution status
 * @return ob2_image_t Returns a handle to the point cloud
 *
 * \else
 *
 * @brief 深度图转点云图
 *
 * @attention 成功转换生成点云图后，无论点云图还是原始深度图，如果不再需要使用，需要调用 @ref ob2_image_release 释放，否则会导致内参泄漏。
 *
 * @param[in] transformation_handle 图像转换器句柄
 * @param[in] depth_image_handle 深度图句柄
 * @param[in] position_scale 坐标缩放系数，不缩放可填 1.0f
 * @param[out] status 返回函数调用状态
 * @return ob2_image_t 返回点云图句柄
 *
 * \endif
 */
ob2_image_t ob2_transformation_depth_image_to_point_cloud(ob2_transformation_t transformation_handle, const ob2_image_t depth_image_handle,
                                                          float position_scale, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Depth image to point cloud image
 *
 * @attention After the point cloud image is successfully converted to generate it, whether it is a point cloud image, the original depth image or the original
 * color image, if it is no longer needed, you need to call @ref ob2_image_release release, otherwise the internal parameters will leak.
 *
 * @param[in] transformation_handle A handle to the image converter
 * @param[in] depth_image_handle A handle to the depth image
 * @param[in] color_image_handle A handle to the color image
 * @param[in] position_scale The coefficient of coordinate scaling, when not scaling, can be filled in 1.0f
 * @param[in] color_normalization Color normalization, the default output color point cloud RGB each channel value is 0~255, after enabling the normalization
 * function, the value normalized to 0.0f~1.0f
 * @param[out] status Output function execution status
 * @return ob2_image_t Returns a handle to a colored point cloud
 *
 * \else
 *
 * @brief 深度图转点云图
 *
 * @attention 成功转换生成点云图后，无论点云图还是原始深度图和原始彩色图，如果不再需要使用，需要调用 @ref ob2_image_release 释放，否则会导致内参泄漏。
 *
 * @param[in] transformation_handle 图像转换器句柄
 * @param[in] depth_image_handle 深度图句柄
 * @param[in] color_image_handle 彩色图句柄
 * @param[in] position_scale 坐标缩放系数，不缩放可填 1.0f
 * @param[in] color_normalization 彩色归一化，默认输出的彩色点云 RGB 各通道数值是 0~255，使能归一化功能以后，数值归一化为 0.0f~1.0f
 * @param[out] status 返回函数调用状态
 * @return ob2_image_t 返回彩色点云图句柄
 *
 * \endif
 */
ob2_image_t ob2_transformation_depth_image_to_colored_point_cloud(ob2_transformation_t transformation_handle, const ob2_image_t depth_image_handle,
                                                                  const ob2_image_t color_image_handle, float position_scale,
                                                                  ob2_enable_ctrl_t color_normalization, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Create a converter for image formats
 *
 * @attention After the image format converter is successfully created, if the image format converter is no longer used, you need to call @ref
 * ob2_image_format_converter_destroy to destroy, otherwise the internal parameters will leak.
 *
 * @param[out] status Output function execution status
 * @return ob2_image_format_converter_t Returns a handle to the image format converter
 *
 * \else
 *
 * @brief 创建图像格式转换器
 *
 * @attention 成功创建图像格式转换器后，不再使用该图像格式转换器的话，需要调用 @ref ob2_image_format_converter_destroy 销毁，否则会导致内参泄漏。
 *
 * @param[out] status 返回函数调用状态
 * @return ob2_image_format_converter_t 返回图像格式转换器句柄
 *
 * \endif
 */
ob2_image_format_converter_t ob2_image_format_converter_create(ob2_status_t *status);

/**
 * \if English
 *
 * @brief Destroys the converter for image formats
 *
 * @param[in] converter_handle A handle to the image format converter
 * @param[out] status Output function execution status
 *
 * \else
 *
 * @brief 销毁图像格式转换器
 *
 * @param[in] converter_handle 图像格式转换器句柄
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_image_format_converter_destroy(ob2_image_format_converter_t converter_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief YUYV to RGB
 *
 * @attention After the format conversion is successfully completed, if the output image or the original image is no longer needed, you need to call @ref
 * ob2_image_release release, otherwise it will cause the internal parameter leakage.
 *
 * @param[in] converter_handle A handle to the image format converter
 * @param[in] source_image_handle A handle to the original image
 * @param[out] status Output function execution status
 * @return ob2_image_t A handle to the output image after format conversion
 *
 * \else
 *
 * @brief YUYV 转 RGB
 *
 * @attention 成功完成格式转换后，无论输出图像还是原始图像，如果不再需要使用，需要调用 @ref ob2_image_release 释放，否则会导致内参泄漏。
 *
 * @param[in] converter_handle 图像格式转换器句柄
 * @param[in] source_image_handle 原始图像句柄
 * @param[out] status 返回函数调用状态
 * @return ob2_image_t 格式转换后输出的图像句柄
 *
 * \endif
 */
ob2_image_t ob2_image_format_converter_yuyv_to_rgb(ob2_image_format_converter_t converter_handle, const ob2_image_t source_image_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief UYVY to RGB
 *
 * @attention After the format conversion is successfully completed, if the output image or the original image is no longer needed, you need to call @ref
 * ob2_image_release release, otherwise it will cause the internal parameter leakage.
 *
 * @param[in] converter_handle A handle to the image format converter
 * @param[in] source_image_handle A handle to the original image
 * @param[out] status Output function execution status
 * @return ob2_image_t A handle to the output image after format conversion
 *
 * \else
 *
 * @brief UYVY 转 RGB
 *
 * @attention 成功完成格式转换后，无论输出图像还是原始图像，如果不再需要使用，需要调用 @ref ob2_image_release 释放，否则会导致内参泄漏。
 *
 * @param[in] converter_handle 图像格式转换器句柄
 * @param[in] source_image_handle 原始图像句柄
 * @param[out] status 返回函数调用状态
 * @return ob2_image_t 格式转换后输出的图像句柄
 *
 * \endif
 */
ob2_image_t ob2_image_format_converter_uyvy_to_rgb(ob2_image_format_converter_t converter_handle, const ob2_image_t source_image_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief I420 to RGB
 *
 * @attention After the format conversion is successfully completed, if the output image or the original image is no longer needed, you need to call @ref
 * ob2_image_release release, otherwise it will cause the internal parameter leakage.
 *
 * @param[in] converter_handle A handle to the image format converter
 * @param[in] source_image_handle A handle to the original image
 * @param[out] status Output function execution status
 * @return ob2_image_t A handle to the output image after format conversion
 *
 * \else
 *
 * @brief I420 转 RGB
 *
 * @attention 成功完成格式转换后，无论输出图像还是原始图像，如果不再需要使用，需要调用 @ref ob2_image_release 释放，否则会导致内参泄漏。
 *
 * @param[in] converter_handle 图像格式转换器句柄
 * @param[in] source_image_handle 原始图像句柄
 * @param[out] status 返回函数调用状态
 * @return ob2_image_t 格式转换后输出的图像句柄
 *
 * \endif
 */
ob2_image_t ob2_image_format_converter_i420_to_rgb(ob2_image_format_converter_t converter_handle, const ob2_image_t source_image_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief NV21 to RGB
 *
 * @attention After the format conversion is successfully completed, if the output image or the original image is no longer needed, you need to call @ref
 * ob2_image_release release, otherwise it will cause the internal parameter leakage.
 *
 * @param[in] converter_handle A handle to the image format converter
 * @param[in] source_image_handle A handle to the original image
 * @param[out] status Output function execution status
 * @return ob2_image_t A handle to the output image after format conversion
 *
 * \else
 *
 * @brief NV21 转 RGB
 *
 * @attention 成功完成格式转换后，无论输出图像还是原始图像，如果不再需要使用，需要调用 @ref ob2_image_release 释放，否则会导致内参泄漏。
 *
 * @param[in] converter_handle 图像格式转换器句柄
 * @param[in] source_image_handle 原始图像句柄
 * @param[out] status 返回函数调用状态
 * @return ob2_image_t 格式转换后输出的图像句柄
 *
 * \endif
 */
ob2_image_t ob2_image_format_converter_nv21_to_rgb(ob2_image_format_converter_t converter_handle, const ob2_image_t source_image_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief NV12 to RGB
 *
 * @attention After the format conversion is successfully completed, if the output image or the original image is no longer needed, you need to call @ref
 * ob2_image_release release, otherwise it will cause the internal parameter leakage.
 *
 * @param[in] converter_handle A handle to the image format converter
 * @param[in] source_image_handle A handle to the original image
 * @param[out] status Output function execution status
 * @return ob2_image_t A handle to the output image after format conversion
 *
 * \else
 *
 * @brief NV12 转 RGB
 *
 * @attention 成功完成格式转换后，无论输出图像还是原始图像，如果不再需要使用，需要调用 @ref ob2_image_release 释放，否则会导致内参泄漏。
 *
 * @param[in] converter_handle 图像格式转换器句柄
 * @param[in] source_image_handle 原始图像句柄
 * @param[out] status 返回函数调用状态
 * @return ob2_image_t 格式转换后输出的图像句柄
 *
 * \endif
 */
ob2_image_t ob2_image_format_converter_nv12_to_rgb(ob2_image_format_converter_t converter_handle, const ob2_image_t source_image_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief RGB to BGR
 *
 * @attention After the format conversion is successfully completed, if the output image or the original image is no longer needed, you need to call @ref
 * ob2_image_release release, otherwise it will cause the internal parameter leakage.
 *
 * @param[in] converter_handle A handle to the image format converter
 * @param[in] source_image_handle A handle to the original image
 * @param[out] status Output function execution status
 * @return ob2_image_t A handle to the output image after format conversion
 *
 * \else
 *
 * @brief RGB 转 BGR
 *
 * @attention 成功完成格式转换后，无论输出图像还是原始图像，如果不再需要使用，需要调用 @ref ob2_image_release 释放，否则会导致内参泄漏。
 *
 * @param[in] converter_handle 图像格式转换器句柄
 * @param[in] source_image_handle 原始图像句柄
 * @param[out] status 返回函数调用状态
 * @return ob2_image_t 格式转换后输出的图像句柄
 *
 * \endif
 */
ob2_image_t ob2_image_format_converter_rgb_to_bgr(ob2_image_format_converter_t converter_handle, const ob2_image_t source_image_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief MJPG to I420
 *
 * @attention After the format conversion is successfully completed, if the output image or the original image is no longer needed, you need to call @ref
 * ob2_image_release release, otherwise it will cause the internal parameter leakage.
 *
 * @param[in] converter_handle A handle to the image format converter
 * @param[in] source_image_handle A handle to the original image
 * @param[out] status Output function execution status
 * @return ob2_image_t A handle to the output image after format conversion
 *
 * \else
 *
 * @brief MJPG 转 I420
 *
 * @attention 成功完成格式转换后，无论输出图像还是原始图像，如果不再需要使用，需要调用 @ref ob2_image_release 释放，否则会导致内参泄漏。
 *
 * @param[in] converter_handle 图像格式转换器句柄
 * @param[in] source_image_handle 原始图像句柄
 * @param[out] status 返回函数调用状态
 * @return ob2_image_t 格式转换后输出的图像句柄
 *
 * \endif
 */
ob2_image_t ob2_image_format_converter_mjpg_to_i420(ob2_image_format_converter_t converter_handle, const ob2_image_t source_image_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief MJPG to NV21
 *
 * @attention After the format conversion is successfully completed, if the output image or the original image is no longer needed, you need to call @ref
 * ob2_image_release release, otherwise it will cause the internal parameter leakage.
 *
 * @param[in] converter_handle A handle to the image format converter
 * @param[in] source_image_handle A handle to the original image
 * @param[out] status Output function execution status
 * @return ob2_image_t A handle to the output image after format conversion
 *
 * \else
 *
 * @brief MJPG 转 NV21
 *
 * @attention 成功完成格式转换后，无论输出图像还是原始图像，如果不再需要使用，需要调用 @ref ob2_image_release 释放，否则会导致内参泄漏。
 *
 * @param[in] converter_handle 图像格式转换器句柄
 * @param[in] source_image_handle 原始图像句柄
 * @param[out] status 返回函数调用状态
 * @return ob2_image_t 格式转换后输出的图像句柄
 *
 * \endif
 */
ob2_image_t ob2_image_format_converter_mjpg_to_nv21(ob2_image_format_converter_t converter_handle, const ob2_image_t source_image_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief MJPG to RGB
 *
 * @attention After the format conversion is successfully completed, if the output image or the original image is no longer needed, you need to call @ref
 * ob2_image_release release, otherwise it will cause the internal parameter leakage.
 *
 * @param[in] converter_handle A handle to the image format converter
 * @param[in] source_image_handle A handle to the original image
 * @param[out] status Output function execution status
 * @return ob2_image_t A handle to the output image after format conversion
 *
 * \else
 *
 * @brief MJPG 转 RGB
 *
 * @attention 成功完成格式转换后，无论输出图像还是原始图像，如果不再需要使用，需要调用 @ref ob2_image_release 释放，否则会导致内参泄漏。
 *
 * @param[in] converter_handle 图像格式转换器句柄
 * @param[in] source_image_handle 原始图像句柄
 * @param[out] status 返回函数调用状态
 * @return ob2_image_t 格式转换后输出的图像句柄
 *
 * \endif
 */
ob2_image_t ob2_image_format_converter_mjpg_to_rgb(ob2_image_format_converter_t converter_handle, const ob2_image_t source_image_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief MJPG to BGR
 *
 * @attention After the format conversion is successfully completed, if the output image or the original image is no longer needed, you need to call @ref
 * ob2_image_release release, otherwise it will cause the internal parameter leakage.
 *
 * @param[in] converter_handle A handle to the image format converter
 * @param[in] source_image_handle A handle to the original image
 * @param[out] status Output function execution status
 * @return ob2_image_t A handle to the output image after format conversion
 *
 * \else
 *
 * @brief MJPG 转 BGR
 *
 * @attention 成功完成格式转换后，无论输出图像还是原始图像，如果不再需要使用，需要调用 @ref ob2_image_release 释放，否则会导致内参泄漏。
 *
 * @param[in] converter_handle 图像格式转换器句柄
 * @param[in] source_image_handle 原始图像句柄
 * @param[out] status 返回函数调用状态
 * @return ob2_image_t 格式转换后输出的图像句柄
 *
 * \endif
 */
ob2_image_t ob2_image_format_converter_mjpg_to_bgr(ob2_image_format_converter_t converter_handle, const ob2_image_t source_image_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief MJPG to BGRA
 *
 * @attention After the format conversion is successfully completed, if the output image or the original image is no longer needed, you need to call @ref
 * ob2_image_release release, otherwise it will cause the internal parameter leakage.
 *
 * @param[in] converter_handle A handle to the image format converter
 * @param[in] source_image_handle A handle to the original image
 * @param[out] status Output function execution status
 * @return ob2_image_t A handle to the output image after format conversion
 *
 * \else
 *
 * @brief MJPG 转 BGRA
 *
 * @attention 成功完成格式转换后，无论输出图像还是原始图像，如果不再需要使用，需要调用 @ref ob2_image_release 释放，否则会导致内参泄漏。
 *
 * @param[in] converter_handle 图像格式转换器句柄
 * @param[in] source_image_handle 原始图像句柄
 * @param[out] status 返回函数调用状态
 * @return ob2_image_t 格式转换后输出的图像句柄
 *
 * \endif
 */
ob2_image_t ob2_image_format_converter_mjpg_to_bgra(ob2_image_format_converter_t converter_handle, const ob2_image_t source_image_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Create an image data compressor
 * @brief Supports lossy and lossless compression of images, regardless of the compression method, can be decompressed by the decompressor decompressor
 *
 * @attention The current image data compressor only supports Y16 format compression for depth and IR images
 * @attention After the image data compressor is successfully created, if the image data compressor is no longer used, you need to call @ref
 * ob2_image_compressor_destroy to destroy, otherwise the internal parameters will leak.
 *
 * @param[out] status Output function execution status
 * @return ob2_compression_t Returns a handle to the image data compressor
 *
 * \else
 *
 * @brief 创建图像数据压缩器
 * @brief 支持图像有损压缩和无损压缩，无论哪种压缩方式，都可以通过 decompressor 解压缩器进行解压
 *
 * @attention 当前图像数据压缩器仅支持深度和 IR 图像的 Y16 格式压缩
 * @attention 成功创建图像数据压缩器后，不再使用该图像数据压缩器的话，需要调用 @ref ob2_image_compressor_destroy 销毁，否则会导致内参泄漏。
 *
 * @param[out] status 返回函数调用状态
 * @return ob2_compression_t 返回图像数据压缩器句柄
 *
 * \endif
 */
ob2_compression_t ob2_image_compressor_create(ob2_status_t *status);

/**
 * \if English
 *
 * @brief Destroy the image data compressor
 *
 * @param[in] compression_handle A handle to the image data compressor
 * @param[out] status Output function execution status
 *
 * \else
 *
 * @brief 销毁图像数据压缩器
 *
 * @param[in] compression_handle 图像数据压缩器句柄
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_image_compressor_destroy(ob2_compression_t compression_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Lossless compression of image data
 *
 * @attention After the image compression is successfully completed, if the output image or the original image is no longer needed, you need to call @ref
 * ob2_image_release release, otherwise it will cause internal parameter leakage.
 *
 * @param[in] compression_handle A handle to the image data compressor
 * @param[in] source_image_handle A handle to the original image
 * @param[out] status Output function execution status
 * @return ob2_image_t Image handle to the output after image compression
 *
 * \else
 *
 * @brief 图像数据无损压缩
 *
 * @attention 成功完成图像压缩后，无论输出图像还是原始图像，如果不再需要使用，需要调用 @ref ob2_image_release 释放，否则会导致内参泄漏。
 *
 * @param[in] compression_handle 图像数据压缩器句柄
 * @param[in] source_image_handle 原始图像句柄
 * @param[out] status 返回函数调用状态
 * @return ob2_image_t 图像压缩后输出的图像句柄
 *
 * \endif
 */
ob2_image_t ob2_image_compress_lossless(ob2_compression_t compression_handle, const ob2_image_t source_image_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Lossy compression of image data
 *
 * @attention After the image compression is successfully completed, if the output image or the original image is no longer needed, you need to call @ref
 * ob2_image_release release, otherwise it will cause internal parameter leakage.
 * @attention The higher the image compression threshold, the higher the compression ratio, but the greater the loss of image information, so users need to
 * confirm the most appropriate threshold through testing based on their own usage scenarios.
 *
 * @param[in] compression_handle A handle to the image data compressor
 * @param[in] source_image_handle A handle to the original image
 * @param[in] threshold Lossy compression threshold, range [0~255], recommended value is 9, the higher the threshold, the higher the compression ratio.
 * @param[out] status Output function execution status
 * @return ob2_image_t Image handle to the output after image compression
 *
 * \else
 *
 * @brief 图像数据有损压缩
 *
 * @attention 成功完成图像压缩后，无论输出图像还是原始图像，如果不再需要使用，需要调用 @ref ob2_image_release 释放，否则会导致内参泄漏。
 * @attention 图像压缩阈值越高压缩率越高, 但是图像信息损失越大，所以用户需要结合自身使用场景，通过测试确认最合适的阈值。
 *
 * @param[in] compression_handle 图像数据压缩器句柄
 * @param[in] source_image_handle 原始图像句柄
 * @param[in] threshold 有损压缩阈值，范围 [0~255]，推荐值为 9，阈值越高压缩率越高。
 * @param[out] status 返回函数调用状态
 * @return ob2_image_t 图像压缩后输出的图像句柄
 *
 * \endif
 */
ob2_image_t ob2_image_compress_lossy(ob2_compression_t compression_handle, const ob2_image_t source_image_handle, uint8_t threshold, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Create an image data decompressor
 * @brief Whether it is lossy or lossless compression, it can be decompressed by the decompressor
 *
 * @attention After the image data decompressor is successfully created, if the image data decompressor is no longer used, you need to call @ref
 * ob2_image_compressor_destroy to destroy, otherwise the internal parameters will leak.
 *
 * @param[out] status Output function execution status
 * @return ob2_compression_t Returns a handle to the image data decompressor
 *
 * \else
 *
 * @brief 创建图像数据解压器
 * @brief 图像使用 compressor 经过有损压缩或无损压缩，都可以通过 decompressor 解解压器进行解压
 *
 * @attention 成功创建图像数据解压器后，不再使用该图像数据解压器的话，需要调用 @ref ob2_image_compressor_destroy 销毁，否则会导致内参泄漏。
 *
 * @param[out] status 返回函数调用状态
 * @return ob2_compression_t 返回图像数据解压器句柄
 *
 * \endif
 */
ob2_decompression_t ob2_image_decompressor_create(ob2_status_t *status);

/**
 * \if English
 *
 * @brief Destroy the image data decompressor
 *
 * @param[in] decompression_handle A handle to the image data decompressor
 * @param[out] status Output function execution status
 *
 * \else
 *
 * @brief 销毁图像数据解压器
 *
 * @param[in] decompression_handle 图像数据解压器句柄
 * @param[out] status 返回函数调用状态
 *
 * \endif
 */
void ob2_image_decompressor_destroy(ob2_decompression_t decompression_handle, ob2_status_t *status);

/**
 * \if English
 *
 * @brief Decompress the image data
 *
 * @attention After the image decompression is successfully completed, if the output image or the original image is no longer needed, you need to call @ref
 * ob2_image_release release, otherwise the internal parameters will leak.
 *
 * @param[in] decompression_handle A handle to the image data decompressor
 * @param[in] source_image_handle A handle to the original image
 * @param[out] status Output function execution status
 * @return ob2_image_t A handle to the output image after the image is extracted
 *
 * \else
 *
 * @brief 图像数据解压
 *
 * @attention 成功完成图像解压后，无论输出图像还是原始图像，如果不再需要使用，需要调用 @ref ob2_image_release 释放，否则会导致内参泄漏。
 *
 * @param[in] decompression_handle 图像数据解压器句柄
 * @param[in] source_image_handle 原始图像句柄
 * @param[out] status 返回函数调用状态
 * @return ob2_image_t 图像解压后输出的图像句柄
 *
 * \endif
 */
ob2_image_t ob2_image_decompress(ob2_decompression_t decompression_handle, const ob2_image_t source_image_handle, ob2_status_t *status);

#ifdef __cplusplus
}
#endif