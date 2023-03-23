#pragma once

#include "OB2Types.hpp"
#include "OB2Device.hpp"

extern "C" {
#include "h/ob2extension.h"
#include "h/ob2camera.h"
}

#include <memory>

namespace ob2 {

/**
 * \if English
 *
 * @brief Transformation for image transform
 * @brief Image converter for depth to point cloud and depth and RGB images to colored point cloud
 *
 * \else
 *
 * @brief 图像转换器
 * @brief 图像转换器可完成深度图像转点云图及深度和 RGB 图像转彩色点云图的功能
 *
 * \endif
 */

class transformation {
public:
    /**
     * \if English
     *
     * @brief Constructor of image transformation
     *
     * @attention Make sure that the cameras calibration parameters passed into the transformation are associated with the image itself (the cameras_config
     * configuration is the same as the cameras_config configuration used by the camera startup to get the image and to get the  cameras calibration
     * parameters).
     *
     * @param[in] calibration cameras calibration parameters, the transformation will use the cameras calibration parameters
     *
     * \else
     *
     * @brief 图像转换器构造函数
     *
     * @attention 需要保证传入创建图像转换器的图像标定参数，与图像本身是相关连的（相机启动获取图像和获取标定参数使用的 cameras_config 配置是一样的）
     *
     * @param[in] calibration 标定参数，图像的转换依赖相机标定参数
     *
     * \endif
     */

    transformation(const ob2_cameras_calibration_t &calibration) {
        ob2_status_t status;
        m_transformation_handle = ob2_transformation_create(&calibration, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

    /**
     * \if English
     *
     * @brief Constructed via other transformation object (mobile constructs, mainly for derived class implementations)
     *
     * @attention After calling this constructor, the original object will no longer be accessible
     *
     * @param trans Another transformation object
     *
     * \else
     *
     * @brief 通过其他转换器对象构造（移动构造，主要用于派生类的实现）
     *
     * @attention 调用该构造函数后，原对象将不再可以访问
     *
     * @param trans 其他转换器对象
     *
     * \endif
     */

    transformation(transformation &&trans) : m_transformation_handle(trans.m_transformation_handle) {
        VALIDATE_NOT_NULL(m_transformation_handle);
        trans.m_transformation_handle = nullptr;
    }

    /**
     * \if English
     *
     * @brief Image converter destructor
     *
     * \else
     *
     * @brief 图像转换器析构函数
     *
     * \endif
     */

    virtual ~transformation() noexcept {
        ob2_status_t status;
        if(m_transformation_handle != nullptr) {
            ob2_transformation_destroy(m_transformation_handle, &status);
        }
    }

    /**
     * \if English
     *
     * @brief Depth transform to point cloud map
     *
     * @param[in] depth_image Depth image object
     * @param[in] position_scale The coefficient of coordinate scaling, when not scaling, can be filled in 1.0f
     * @return std::shared_ptr<image> Return smart pointer of point cloud iamge
     *
     * \else
     *
     * @brief 深度图转点云图
     *
     * @param[in] depth_image 深度图
     * @param[in] position_scale 坐标缩放系数，不缩放可填 1.0f
     * @return std::shared_ptr<image> 返回点云图对象智能指针
     *
     * \endif
     */

    virtual std::shared_ptr<image> depth_image_to_point_cloud(std::shared_ptr<image> depth_image, float position_scale) {
        ob2_status_t status;
        auto         depth_image_handle  = depth_image->get_handle();
        auto         result_image_handle = ob2_transformation_depth_image_to_point_cloud(m_transformation_handle, depth_image_handle, position_scale, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        return std::make_shared<image>(std::move(result_image_handle));
    }

    /**
     * \if English
     *
     * @brief Depth image to colored point cloud image
     *
     * @param[in] depth_image Depth image
     * @param[in] color_image Color image
     * @param[in] position_scale The coefficient of coordinate scaling, when not scaling, can be filled in 1.0f
     * @param[in] color_normalization Color normalization, the default output color point cloud RGB each channel value is 0~255, after enabling the
     * normalization function, the value normalized to 0.0f~1.0f
     * @return std::shared_ptr<image> Returns a colored point cloud image
     *
     * \else
     *
     * @brief 深度图转彩色点云图
     *
     * @param[in] depth_image 深度图
     * @param[in] color_image 彩色图
     * @param[in] position_scale 坐标缩放系数，不缩放可填 1.0f
     * @param[in] color_normalization 彩色归一化，默认输出的彩色点云 RGB 各通道数值是 0~255，使能归一化功能以后，数值归一化为 0.0f~1.0f
     * @return std::shared_ptr<image> 返回点云图对象智能指针
     *
     * \endif
     */

    virtual std::shared_ptr<image> depth_image_to_colored_point_cloud(std::shared_ptr<image> depth_image, std::shared_ptr<image> color_image,
                                                                      float position_scale, ob2_enable_ctrl_t color_normalization) {
        ob2_status_t status;
        auto         depth_image_handle = depth_image->get_handle();
        auto         color_image_handle = color_image->get_handle();
        auto result_image_handle        = ob2_transformation_depth_image_to_colored_point_cloud(m_transformation_handle, depth_image_handle, color_image_handle,
                                                                                         position_scale, color_normalization, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        return std::make_shared<image>(std::move(result_image_handle));
    }

private:
    ob2_transformation_t m_transformation_handle;
};

/**
 * \if English
 *
 * @brief Image data compressor
 *
 * @attention The current image data compressor only supports Y16 format compression for depth and Infrared images
 *
 * \else
 *
 * @brief 图像数据压缩器
 *
 * @attention 当前图像数据压缩器仅支持深度和红外图像的 Y16 格式压缩
 *
 * \endif
 */

class image_compressor {
public:
    /**
     * \if English
     *
     * @brief Constructor of compressor.
     *
     * \else
     *
     * @brief 图像数据压缩器构造函数
     *
     * \endif
     */

    image_compressor() {
        ob2_status_t status;
        m_compressor_handle = ob2_image_compressor_create(&status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

    /**
     * \if English
     *
     * @brief Constructed via other compressor object (mobile constructs, mainly used in derived class implementations)
     *
     * @attention After calling this constructor, the original object will no longer be accessible
     *
     * @param converter Another compressor object
     *
     * \else
     *
     * @brief 通过其他压缩器对象构造（移动构造，主要用于派生类的实现）
     *
     * @attention 调用该构造函数后，原对象将不再可以访问
     *
     * @param converter 其他压缩器对象
     *
     * \endif
     */

    image_compressor(image_compressor &&converter) : m_compressor_handle(converter.m_compressor_handle) {
        VALIDATE_NOT_NULL(m_compressor_handle);
        converter.m_compressor_handle = nullptr;
    }

    /**
     * \if English
     *
     * @brief Destructor of compressor
     *
     * \else
     *
     * @brief 图像数据压缩器析构函数
     *
     * \endif
     */

    virtual ~image_compressor() noexcept {
        ob2_status_t status;
        if(m_compressor_handle != nullptr) {
            ob2_image_compressor_destroy(m_compressor_handle, &status);
        }
    }

    /**
     * \if English
     *
     * @brief Lossless compression of image data
     *
     * @param[in] source_image Source image
     * @return std::shared_ptr<image> Output image
     *
     * \else
     *
     * @brief 图像数据无损压缩
     *
     * @param[in] source_image 原始图像
     * @return std::shared_ptr<image> 输出图像
     *
     * \endif
     */

    virtual std::shared_ptr<image> compress_lossless(const std::shared_ptr<image> source_image) {
        ob2_status_t status;
        auto         source_image_handle = source_image->get_handle();
        auto         result_image_handle = ob2_image_compress_lossless(m_compressor_handle, source_image_handle, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        return std::make_shared<image>(std::move(result_image_handle));
    }

    /**
     * \if English
     *
     * @brief Lossy compression of image data
     *
     * @attention The higher the image compression @threshold, the higher the compression rate, but the greater the loss of image information, so users need to
     * confirm the most appropriate @threshold through testing, taking into account their own usage scenarios.
     *
     * @param[in] source_image Source image
     * @param[in] threshold Lossy compression threshold, range [0~255], recommended value is 9, the higher the threshold the higher the compression rate.
     * @return std::shared_ptr<image> Output image
     *
     * \else
     *
     * @brief 图像数据有损压缩
     *
     * @attention 图像压缩阈值越高压缩率越高, 但是图像信息损失越大，所以用户需要结合自身使用场景，通过测试确认最合适的阈值。
     *
     * @param[in] source_image 原始图像
     * @param[in] threshold 有损压缩阈值，范围 [0~255]，推荐值为 9，阈值越高压缩率越高。
     * @return std::shared_ptr<image> 输出图像
     *
     * \endif
     */

    virtual std::shared_ptr<image> compress_lossy(const std::shared_ptr<image> source_image, uint8_t threshold) {
        ob2_status_t status;
        auto         source_image_handle = source_image->get_handle();
        auto         result_image_handle = ob2_image_compress_lossy(m_compressor_handle, source_image_handle, threshold, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        return std::make_shared<image>(std::move(result_image_handle));
    }

private:
    ob2_compression_t m_compressor_handle;
};

/**
 * \if English
 *
 * @brief Image data decompressor
 * @brief Images are compressed using @ref image_compressor, either lossy or lossless, and can be decompressed using the @ref image_decompressor
 *
 * \else
 *
 * @brief 图像数据解压器
 * @brief 图像使用 @ref image_compressor 经过有损压缩或无损压缩，都可以通过 @ref image_decompressor 进行解压
 *
 * \endif
 */

class image_decompressor {
public:
    /**
     * \if English
     *
     * @brief Constructor of Image data decompressor
     *
     * \else
     *
     * @brief 图像数据解压器构造函数
     *
     * \endif
     */

    image_decompressor() {
        ob2_status_t status;
        m_decompressor_handle = ob2_image_decompressor_create(&status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

    /**
     * \if English
     *
     * @brief Constructed via other decompressor object (mobile constructs, mainly used in derived class implementations)
     *
     * @attention After calling this constructor, the original object will no longer be accessible
     *
     * @param converter Another decompressor object
     *
     * \else
     *
     * @brief 通过其他解压器对象构造（移动构造，主要用于派生类的实现）
     *
     * @attention 调用该构造函数后，原对象将不再可以访问
     *
     * @param converter 其他解压器对象
     *
     * \endif
     */

    image_decompressor(image_decompressor &&converter) : m_decompressor_handle(converter.m_decompressor_handle) {
        VALIDATE_NOT_NULL(m_decompressor_handle);
        converter.m_decompressor_handle = nullptr;
    }

    /**
     * \if English
     *
     * @brief Destructor of image data decompressor
     *
     * \else
     *
     * @brief 图像数据解压器析构函数
     *
     * \endif
     */

    virtual ~image_decompressor() noexcept {
        ob2_status_t status;
        if(m_decompressor_handle != nullptr) {
            ob2_image_decompressor_destroy(m_decompressor_handle, &status);
        }
    }

    /**
     * \if English
     *
     * @brief Image data decompression
     *
     * @param[in] source_image Source image
     * @return std::shared_ptr<image> output image
     *
     * \else
     *
     * @brief 图像数据解压
     *
     * @param[in] source_image 原始图像
     * @return std::shared_ptr<image> 图像解压后输出的图像对象智能指针
     *
     * \endif
     */

    virtual std::shared_ptr<image> decompress(const std::shared_ptr<image> source_image) {
        ob2_status_t status;
        auto         source_image_handle = source_image->get_handle();
        auto         result_image_handle = ob2_image_decompress(m_decompressor_handle, source_image_handle, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        return std::make_shared<image>(std::move(result_image_handle));
    }

private:
    ob2_decompression_t m_decompressor_handle;
};

/**
 * \if English
 *
 * @brief Image format converter
 *
 * \else
 *
 * @brief 图像格式转换器
 *
 * \endif
 */

class image_format_converter {
public:
    /**
     * \if English
     *
     * @brief Constructor of image format converter.
     *
     * \else
     *
     * @brief 图像格式转换器构造函数
     *
     * \endif
     */

    image_format_converter() {
        ob2_status_t status;
        m_converter_handle = ob2_image_format_converter_create(&status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
    }

    /**
     * \if English
     *
     * @brief Constructed via other converter object (mobile constructs, mainly for derived class implementations)
     *
     * @attention After calling this constructor, the original object will no longer be accessible
     *
     * @param converter Another converter object
     *
     * \else
     *
     * @brief 通过其他转换器对象构造（移动构造，主要用于派生类的实现）
     *
     * @attention 调用该构造函数后，原对象将不再可以访问
     *
     * @param converter 其转换器对象
     *
     * \endif
     */

    image_format_converter(image_format_converter &&converter) : m_converter_handle(converter.m_converter_handle) {
        VALIDATE_NOT_NULL(m_converter_handle);
        converter.m_converter_handle = nullptr;
    }

    /**
     * \if English
     *
     * @brief Destructor of Image format converter
     *
     * \else
     *
     * @brief 图像格式转换器析构函数
     *
     *\endif
     */

    virtual ~image_format_converter() noexcept {
        ob2_status_t status;
        if(m_converter_handle != nullptr) {
            ob2_image_format_converter_destroy(m_converter_handle, &status);
        }
    }

    /**
     * \if English
     *
     * @brief YUYV convert to RGB
     *
     * @param[in] source_image source image
     * @return std::shared_ptr<image> output image
     *
     * \else
     *
     * @brief YUYV 转 RGB
     *
     * @param[in] source_image 原始图像
     * @return std::shared_ptr<image> 格式转换后输出的图像对象智能指针
     *
     * \endif
     */

    virtual std::shared_ptr<image> yuyv_to_rgb(const std::shared_ptr<image> source_image) {
        ob2_status_t status;
        auto         source_image_handle = source_image->get_handle();
        auto         result_image_handle = ob2_image_format_converter_yuyv_to_rgb(m_converter_handle, source_image_handle, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        return std::make_shared<image>(std::move(result_image_handle));
    }

    /**
     * \if English
     *
     * @brief UYVY convert to RGB
     *
     * @param[in] source_image source image
     * @return std::shared_ptr<image> output image
     *
     * \else
     *
     * @brief UYVY 转 RGB
     *
     * @param[in] source_image 原始图像
     * @return std::shared_ptr<image> 格式转换后输出的图像对象智能指针
     *
     * \endif
     */

    virtual std::shared_ptr<image> uyvy_to_rgb(const std::shared_ptr<image> source_image) {
        ob2_status_t status;
        auto         source_image_handle = source_image->get_handle();
        auto         result_image_handle = ob2_image_format_converter_uyvy_to_rgb(m_converter_handle, source_image_handle, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        return std::make_shared<image>(std::move(result_image_handle));
    }

    /**
     * \if English
     *
     * @brief I420 convert to RGB
     *
     * @param[in] source_image source image
     * @return std::shared_ptr<image> output image
     *
     * \else
     *
     * @brief I420 转 RGB
     *
     * @param[in] source_image 原始图像
     * @return std::shared_ptr<image> 格式转换后输出的图像对象智能指针
     *
     * \endif
     */

    virtual std::shared_ptr<image> i420_to_rgb(const std::shared_ptr<image> source_image) {
        ob2_status_t status;
        auto         source_image_handle = source_image->get_handle();
        auto         result_image_handle = ob2_image_format_converter_uyvy_to_rgb(m_converter_handle, source_image_handle, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        return std::make_shared<image>(std::move(result_image_handle));
    }

    /**
     * \if English
     *
     * @brief NV21 convert to RGB
     *
     * @param[in] source_image source image
     * @return std::shared_ptr<image> output image
     *
     * \else
     *
     * @brief NV21 转 RGB
     *
     * @param[in] source_image 原始图像
     * @return std::shared_ptr<image> 格式转换后输出的图像对象智能指针
     *
     * \endif
     */

    virtual std::shared_ptr<image> nv21_to_rgb(const std::shared_ptr<image> source_image) {
        ob2_status_t status;
        auto         source_image_handle = source_image->get_handle();
        auto         result_image_handle = ob2_image_format_converter_uyvy_to_rgb(m_converter_handle, source_image_handle, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        return std::make_shared<image>(std::move(result_image_handle));
    }

    /**
     * \if English
     *
     * @brief NV12 convert to RGB
     *
     * @param[in] source_image source image
     * @return std::shared_ptr<image> output image
     *
     * \else
     *
     * @brief NV12 转 RGB
     *
     * @param[in] source_image 原始图像
     * @return std::shared_ptr<image> 格式转换后输出的图像对象智能指针
     *
     * \endif
     */

    virtual std::shared_ptr<image> nv12_to_rgb(const std::shared_ptr<image> source_image) {
        ob2_status_t status;
        auto         source_image_handle = source_image->get_handle();
        auto         result_image_handle = ob2_image_format_converter_nv12_to_rgb(m_converter_handle, source_image_handle, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        return std::make_shared<image>(std::move(result_image_handle));
    }

    /**
     * \if English
     *
     * @brief RGB convert to BGR
     *
     * @param[in] source_image source image
     * @return std::shared_ptr<image> output image
     *
     * \else
     *
     * @brief RGB 转 BGR
     *
     * @param[in] source_image 原始图像
     * @return std::shared_ptr<image> 格式转换后输出的图像对象智能指针
     *
     * \endif
     */

    virtual std::shared_ptr<image> rgb_to_bgr(const std::shared_ptr<image> source_image) {
        ob2_status_t status;
        auto         source_image_handle = source_image->get_handle();
        auto         result_image_handle = ob2_image_format_converter_rgb_to_bgr(m_converter_handle, source_image_handle, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        return std::make_shared<image>(std::move(result_image_handle));
    }

    /**
     * \if English
     *
     * @brief MJPG convert to I420
     *
     * @param[in] source_image source image
     * @return std::shared_ptr<image> output image
     *
     * \else
     *
     * @brief MJPG 转 I420
     *
     * @param[in] source_image 原始图像
     * @return std::shared_ptr<image> 格式转换后输出的图像对象智能指针
     *
     * \endif
     */

    virtual std::shared_ptr<image> mjpg_to_i420(const std::shared_ptr<image> source_image) {
        ob2_status_t status;
        auto         source_image_handle = source_image->get_handle();
        auto         result_image_handle = ob2_image_format_converter_mjpg_to_i420(m_converter_handle, source_image_handle, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        return std::make_shared<image>(std::move(result_image_handle));
    }

    /**
     * \if English
     *
     * @brief MJPG convert to NV21
     *
     * @param[in] source_image source image
     * @return std::shared_ptr<image> output image
     *
     * \else
     *
     * @brief MJPG 转 NV21
     *
     * @param[in] source_image 原始图像
     * @return std::shared_ptr<image> 格式转换后输出的图像对象智能指针
     *
     * \endif
     */

    virtual std::shared_ptr<image> mjpg_to_nv21(const std::shared_ptr<image> source_image) {
        ob2_status_t status;
        auto         source_image_handle = source_image->get_handle();
        auto         result_image_handle = ob2_image_format_converter_mjpg_to_nv21(m_converter_handle, source_image_handle, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        return std::make_shared<image>(std::move(result_image_handle));
    }

    /**
     * \if English
     *
     * @brief MJPG convert to RGB
     *
     * @param[in] source_image source image
     * @return std::shared_ptr<image> output image
     *
     * \else
     *
     * @brief MJPG 转 RGB
     *
     * @param[in] source_image 原始图像
     * @return std::shared_ptr<image> 格式转换后输出的图像对象智能指针
     *
     * \endif
     */

    virtual std::shared_ptr<image> mjpg_to_rgb(const std::shared_ptr<image> source_image) {
        ob2_status_t status;
        auto         source_image_handle = source_image->get_handle();
        auto         result_image_handle = ob2_image_format_converter_mjpg_to_rgb(m_converter_handle, source_image_handle, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        return std::make_shared<image>(std::move(result_image_handle));
    }

    /**
     * \if English
     *
     * @brief MJPG convert to BGR
     *
     * @param[in] source_image source image
     * @return std::shared_ptr<image> output image
     *
     * \else
     *
     * @brief MJPG 转 BGR
     *
     * @param[in] source_image 原始图像
     * @return std::shared_ptr<image> 格式转换后输出的图像对象智能指针
     *
     * \endif
     */

    virtual std::shared_ptr<image> mjpg_to_bgr(const std::shared_ptr<image> source_image) {
        ob2_status_t status;
        auto         source_image_handle = source_image->get_handle();
        auto         result_image_handle = ob2_image_format_converter_mjpg_to_bgr(m_converter_handle, source_image_handle, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        return std::make_shared<image>(std::move(result_image_handle));
    }

    /**
     * \if English
     *
     * @brief MJPG convert to BGRA
     *
     * @param[in] source_image source image
     * @return std::shared_ptr<image> output image
     *
     * \else
     *
     * @brief MJPG 转 BGRA
     *
     * @param[in] source_image 原始图像
     * @return std::shared_ptr<image> 格式转换后输出的图像对象智能指针
     *
     * \endif
     */

    virtual std::shared_ptr<image> mjpg_to_bgra(const std::shared_ptr<image> source_image) {
        ob2_status_t status;
        auto         source_image_handle = source_image->get_handle();
        auto         result_image_handle = ob2_image_format_converter_mjpg_to_bgra(m_converter_handle, source_image_handle, &status);
        CHECK_OB2_STATUS_ERROR_THROW(status);
        return std::make_shared<image>(std::move(result_image_handle));
    }

private:
    ob2_image_format_converter_t m_converter_handle;
};

}  // namespace ob2