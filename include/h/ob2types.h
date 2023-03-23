#pragma once

#ifdef __cplusplus
extern "C" {
#endif
#include <stdbool.h>
#include <stdint.h>

/**
 * \if English
 * @brief The context handle definition
 * @attention  After any interface returns the following handle parameters, the corresponding
 * release function needs to call when access is no longer needed. Otherwise, it may lead to a memory leak.
 * \else
 * @brief context 句柄定义
 * @attention 任何接口返回以下句柄参数后，不再需要访问时，都需要调用相应的释放函数，否则可能会导致内存泄漏。
 * \endif
 */
typedef struct OB2ContextImpl *ob2_context_t;

/**
 * \if English
 * @brief The device handle definition
 * @attention  After any interface returns the following handle parameters, the corresponding
 * release function needs to call when access is no longer needed. Otherwise, it may lead to a memory leak.
 * \else
 * @brief 设备句柄定义
 * @attention 任何接口返回以下句柄参数后，不再需要访问时，都需要调用相应的释放函数，否则可能会导致内存泄漏。
 * \endif
 */
typedef struct OB2DeviceImpl *ob2_device_t;

/**
 * \if English
 * @brief The camera Configuration Handle Definition
 * @attention After any interface returns the following handle parameters, the corresponding
 * release function needs to call when access is no longer needed. Otherwise, it may lead to a memory leak.
 * \else
 * @brief 相机配置句柄定义
 * @attention 任何接口返回以下句柄参数后，不再需要访问时，都需要调用相应的释放函数，否则可能会导致内存泄漏。
 * \endif
 */
typedef struct OB2CamerasConfigImpl *ob2_cameras_config_t;

/**
 * \if English
 * @brief The capture handle definition
 * @attention  After any interface returns the following handle parameters, the corresponding
 * release function needs to call when access is no longer needed. Otherwise, it may lead to a memory leak.
 * \else
 * @brief capture 句柄定义
 * @attention 任何接口返回以下句柄参数后，不再需要访问时，都需要调用相应的释放函数，否则可能会导致内存泄漏。
 * \endif
 */
typedef struct OB2CaptureImpl *ob2_capture_t;

/**
 * \if English
 * @brief The image handle definition
 * @attention  After any interface returns the following handle parameters, the corresponding
 * release function needs to call when access is no longer needed. Otherwise, it may lead to a memory leak.
 * \else
 * @brief 图像句柄定义
 * @attention 任何接口返回以下句柄参数后，不再需要访问时，都需要调用相应的释放函数，否则可能会导致内存泄漏。
 * \endif
 */
typedef struct OB2ImageImpl *ob2_image_t;

/**
 * \if English
 * @brief The IMU configuration handle definition
 * @attention  After any interface returns the following handle parameters, the corresponding
 * release function needs to call when access is no longer needed. Otherwise, it may lead to a memory leak.
 * \else
 * @brief IMU 配置句柄定义
 * @attention 任何接口返回以下句柄参数后，不再需要访问时，都需要调用相应的释放函数，否则可能会导致内存泄漏。
 * \endif
 */
typedef struct OB2ImuConfigImpl *ob2_imu_config_t;

/**
 * \if English
 * @brief The IMU sample data handle definition
 * @attention  After any interface returns the following handle parameters, the corresponding
 * release function needs to call when access is no longer needed. Otherwise, it may lead to a memory leak.
 * \else
 * @brief IMU 采样数据句柄定义
 * @attention 任何接口返回以下句柄参数后，不再需要访问时，都需要调用相应的释放函数，否则可能会导致内存泄漏。
 * \endif
 */
typedef struct OB2ImuSampleImpl *ob2_imu_sample_t;

/**
 * \if English
 * @brief The image converter handle definition
 * @attention  After any interface returns the following handle parameters, the corresponding
 * release function needs to call when access is no longer needed. Otherwise, it may lead to a memory leak.
 * \else
 * @brief 图像转换器句柄定义
 * @attention 任何接口返回以下句柄参数后，不再需要访问时，都需要调用相应的释放函数，否则可能会导致内存泄漏。
 * \endif
 */
typedef struct OB2TransformationImpl *ob2_transformation_t;

/**
 * \if English
 * @brief The image converter handle definition
 * @attention  After any interface returns the following handle parameters, the corresponding
 * release function needs to call when access is no longer needed. Otherwise, it may lead to a memory leak.
 * \else
 * @brief 图像格式转换器句柄定义
 * @attention 任何接口返回以下句柄参数后，不再需要访问时，都需要调用相应的释放函数，否则可能会导致内存泄漏。
 * \endif
 */
typedef struct OB2ImageFormatConverterImpl *ob2_image_format_converter_t;

/**
 * \if English
 * @brief The recorder handle definition
 * @attention  After any interface returns the following handle parameters, the corresponding
 * release function needs to call when access is no longer needed. Otherwise, it may lead to a memory leak.
 * \else
 * @brief 录制器句柄定义
 * @attention 任何接口返回以下句柄参数后，不再需要访问时，都需要调用相应的释放函数，否则可能会导致内存泄漏。
 * \endif
 */
typedef struct OB2RecordImpl *ob2_record_t;

/**
 * \if English
 * @brief The playback handle definition
 * @attention  After any interface returns the following handle parameters, the corresponding
 * release function needs to call when access is no longer needed. Otherwise, it may lead to a memory leak.
 * \else
 * @brief 回放器句柄定义
 * @attention 任何接口返回以下句柄参数后，不再需要访问时，都需要调用相应的释放函数，否则可能会导致内存泄漏。
 * \endif
 */
typedef struct OB2PlaybackImpl *ob2_playback_t;

/**
 * \if English
 * @brief The image data compressor handle definition
 * @attention  After any interface returns the following handle parameters, the corresponding
 * release function needs to call when access is no longer needed. Otherwise, it may lead to a memory leak.
 * \else
 * @brief 图像数据压缩器句柄定义
 * @attention 任何接口返回以下句柄参数后，不再需要访问时，都需要调用相应的释放函数，否则可能会导致内存泄漏。
 * \endif
 */
typedef struct OB2CompressionImpl *ob2_compression_t;

/**
 * \if English
 * @brief The image data decompressor handle definition
 * @attention  After any interface returns the following handle parameters, the corresponding
 * release function needs to call when access is no longer needed. Otherwise, it may lead to a memory leak.
 * \else
 * @brief 图像数据解压器句柄定义
 * @attention 任何接口返回以下句柄参数后，不再需要访问时，都需要调用相应的释放函数，否则可能会导致内存泄漏。
 * \endif
 */
typedef struct OB2DecompressionImpl *ob2_decompression_t;

#pragma pack(push, 1)  //!< struct 1-byte align

/**
 * \if English
 * @brief Default SDK configuration file path
 * \else
 * @brief 默认 SDK 配置文件路径
 * \endif
 */
#define OB2_DEFAULT_SDK_CONFIG_FILE_PATH ("")

/**
 * \if English
 * @brief Default Device Index
 * \else
 * @brief 默认设备索引
 * \endif
 */
#define OB2_DEFAULT_DEVICE (0)

/**
 * \if English
 * @brief The default Stream Configuration Index
 * \else
 * @brief 默认流配置索引
 * \endif
 */
#define OB2_DEFAULT_STREAM_PROFILE (0)

/**
 * \if English
 * @brief The default Camera Configuration
 * \else
 * @brief 默认相机配置
 * \endif
 */
#define OB2_DEFAULT_CAMERAS_CONFIG (nullptr)

/**
 * \if English
 * @brief The default IMU Configuration
 * \else
 * @brief 默认 IMU 配置
 * \endif
 */
#define OB2_DEFAULT_IMU_CONFIG (nullptr)

/**
 * \if English
 * @brief Used for fuzzy matching, indicating that it can be any width.
 * \else
 * @brief 用于模糊匹，标识可以任意宽度
 * \endif
 */
#define OB2_ANY_WIDTH (0)

/**
 * \if English
 * @brief Used for fuzzy matching, indicating that it can be any height.
 * \else
 * @brief 用于模糊匹，标识可以任意高度
 * \endif
 */
#define OB2_ANY_HEIGHT (0)

/**
 * \if English
 * @brief Used for fuzzy matching, indicating that it can be any frame rate.
 * \else
 * @brief 用于模糊匹，标识可以任意帧率
 * \endif
 */
#define OB2_ANY_FRAME_RATE (0)

/**
 * \if English
 * @brief Used for fuzzy matching, indicating that it can be any pixel format.
 * \else
 * @brief 用于模糊匹，标识可以任意图像格式
 * \endif
 */
#define OB2_ANY_IAMGE_FORMAT (OB2_FORMAT_ANY)

/**
 * \if English
 * @brief Used for waiting, indicating that it can always wait and will not time out.
 * \else
 * @brief 用于等待，标识可以一直等待，不会超时
 * \endif
 */
#define OB2_WAIT_INFINITE (-1)

/**
 * \if English
 * @brief
 * \else First sample data index
 * @brief 第一个采样数据索引
 *\endif
 */
#define OB2_FIRST_SAMPLE (0)

/**
 * \if English
 * @brief status code
 * \else
 * @brief 状态码
 * \endif
 */
typedef enum {
    /**\if English OK \else 正常 \endif*/
    OB2_STATUS_OK = 0,

    /** \if English
     * Logic errors (usually caused by wrong code calls, user code needs to be fixed or circumvented):
     * illegal parameters, parameters out of range, wrong length, wrong domain, etc.
     * \else 逻辑错误（通常是由于错误的代码调用引起，用户代码需要做修复或规避）：非法的参数、参数超范围、长度错误、域错误等
     * \endif
     */
    OB2_STATUS_LOGIC_ERROR = 1,

    /** \if English
     * Runtime errors (usually caused by equipment exceptions or current equipment and environment is not supported,
     * the user code needs to do a good prompt output): file does not exist, no access rights,
     * equipment does not support, equipment no corresponding, equipment abnormal corresponding, etc.
     * \else
     * 运行时错误（通常是由于设备异常或当前设备和环境不支持引起，用户代码需做好提示输出）：文件不存在、无访问权限、设备不支持、设备无相应、设备异常相应等
     * \endif
     */
    OB2_STATUS_RUNTIME_ERROR = 2,

    /**
     * \if English
     * unknown error
     * \else
     * 其他未知情况导致的程序运行异常
     * \endif
     */
    OB2_STATUS_UNKNOWN_ERROR = 255
} ob2_status_code_t;

/**
 * \if English
 * @brief This structure is used to represent the return status of a user function call.
 * \else
 * @brief 用户函数调用返回的状态结构体
 * \endif
 */
typedef struct {
    /** \if English Status code \else 状态码 \endif */
    ob2_status_code_t code;
    /**
     * \if English
     * Status information, when the status code is ::OB2_STATUS_OK, this item is
     * empty
     * \else
     * 状态信息，当状态码为 ::OB2_STATUS_OK 时，此项为空
     * \endif
     */
    char message[256];
    /**
     * \if English
     * Return the function called by this status, when the status code is ::OB2_STATUS_OK, this item is empty
     * \else
     * 返回此状态调用的函数，当状态码为 ::OB2_STATUS_OK 时，此项为空
     * \endif
     */
    char function[256];
    /**
     * \if English
     *  Return the parameters passed to this status call function,
     *  when the status code is ::OB2_STATUS_OK, this item is empty
     * \else
     *  返回此状态调用函数传入的参数，当状态码为 ::OB2_STATUS_OK 时，此项为空
     * \endif
     */
    char args[256];
} ob2_status_t;

/**
 * \if English
 * @brief version
 * \else
 * @brief 版本号
 * \endif
 */
typedef struct {
    /** \if English major version \else 主版本号 \endif */
    uint32_t major;

    /** \if English minor version \else 次版本号 \endif */
    uint32_t minor;

    /** \if English patch version \else 修订版本号 \endif */
    uint32_t patch;
} ob2_version_t;

/**
 * @brief
 *
 */
typedef enum {
    /** \if English debug \else 调试 \endif */
    OB2_LOG_SEVERITY_DEBUG = 0,

    /** \if English information \else 信息 \endif */
    OB2_LOG_SEVERITY_INFO = 1,

    /** \if English warning \else 警告 \endif */
    OB2_LOG_SEVERITY_WARN = 2,

    /** \if English error \else 错误 \endif */
    OB2_LOG_SEVERITY_ERROR = 3,

    /** \if English fatal error \else 致命错误 \endif */
    OB2_LOG_SEVERITY_FATAL = 4,

    /** \if English none (close LOG) \else 无 (关闭 LOG) \endif */
    OB2_LOG_SEVERITY_NONE = 5
} ob2_log_severity_t;

typedef enum {
    OB2_LOGGER_CONSOLE = 1,  //!< logger for logging to console
    OB2_LOGGER_FILE    = 2,  //!< logger for logging to file
    OB2_LOGGER_ALL     = 3,  //!< bitmap for both logging to console and file
} ob2_logger_type_t;

/**
 * \if English
 * @brief Device installation information, which can be used to open the device
 * \else
 * @brief 设备安装信息，可以用于打开设备
 * \endif
 */
typedef struct {
    /** \if English vendor ID \else 厂商 ID \endif */
    uint32_t vid;

    /** \if English product ID \else 产品 ID \endif */
    uint32_t pid;

    /** \if English device installation url \else 设备安装路径 \endif */
    char url[128];

    /** \if English device serial number url \else 设备序列号 \endif */
    char serial_number[16];

    /** \if English device connect type（usb2.0、usb3.0 ...） url \else 设备连接类型（usb2.0、usb3.0 ...） \endif */
    char connection_type[16];
} ob2_device_installation_info_t;

/**
 * \if English
 * @brief 3D (Depth) imaging technology type
 * \else
 * @brief 3D（Depth）成像技术类型
 * \endif
 */
typedef enum {
    OB2_3D_TECH_MONOCULAR_STRUCTURED_LIGHT = 0,  //!< \if English Monocular structured light \else 单目结构光 \endif
    OB2_3D_TECH_BINOCULAR_STRUCTURED_LIGHT = 1,  //!< \if English Binocular Structures \else  双目结构体 \endif
    OB2_3D_TECH_INDIRECT_TOF               = 2,  //!< iTOF
    OB2_3D_TECH_DIRECT_TOF                 = 3,  //!< dTOF
} ob2_3d_technology_type_t;

/**
 * \if English
 * @brief The device details you need to open the device first and then get the device details.
 * \else
 * @brief 设备详细信息，需要先打开设备后获取
 * \endif
 */
typedef struct {
    /** \if English vendor ID \else 厂商 ID \endif */
    uint32_t vid;

    /** \if English product ID \else 产品 ID \endif */
    uint32_t pid;

    /** \if English device installation url \else 设备安装路径 \endif */
    char url[128];

    /** \if English device serial number url \else 设备序列号 \endif */
    char serial_number[16];

    /** \if English device connect type（usb2.0、usb3.0 ...） url \else 设备连接类型（usb2.0、usb3.0 ...） \endif */
    char connection_type[16];

    /** \if English device name \else 设备名 \endif */
    char name[16];

    /** \if English device firmware version \else 设备固件版本号 \endif */
    char firmware_version[16];

    /** \if English device hardware version \else 设备硬件版本号 \endif */
    char hardware_version[16];

    /** \if English 3d technology type \else 3d 成像技术类型 \endif */
    ob2_3d_technology_type_t technology;
} ob2_device_info_t;

/**
 * \if English
 * @brief Camera Type
 * \else
 * @brief 相机类型
 * \endif
 */
typedef enum {
    OB2_CAMERA_UNKNOWN = 0,  //!< \if English Unknown Camera \else 未知相机 \endif
    OB2_CAMERA_COLOR   = 1,  //!< \if English Color Camera \else 彩色相机 \endif
    OB2_CAMERA_DEPTH   = 2,  //!< \if English Depth Camera \else 深度相机 \endif
    OB2_CAMERA_IR      = 3,  //!< \if English Infrared camera \else 红外相机 \endif
} ob2_camera_type_t;

/**
 * \if English
 * @brief Image format
 * \else
 * @brief 图像数据格式
 * \endif
 */
typedef enum {
    /** \if English YUYV format \else YUYV 格式 \endif */
    OB2_FORMAT_YUYV = 0,

    /** \if English YUY2 format (the actual format is the same as YUYV) \else YUY2 格式 (实际格式与 YUYV 相同) \endif */
    OB2_FORMAT_YUY2 = 1,

    /** \if English UYVY format \else UYVY 格式 \endif */
    OB2_FORMAT_UYVY = 2,

    /** \if English NV12 format \else NV12 格式 \endif */
    OB2_FORMAT_NV12 = 3,

    /** \if English NV21 format \else NV21 格式 \endif */
    OB2_FORMAT_NV21 = 4,

    /** \if English MJPG encoding format \else MJPG 编码格式 \endif */
    OB2_FORMAT_MJPG = 5,

    /** \if English H.264 encoding format \else H.264 编码格式 \endif */
    OB2_FORMAT_H264 = 6,

    /** \if English H.265 encoding format \else H.265 编码格式 \endif */
    OB2_FORMAT_H265 = 7,

    /** \if English Y16 format, single channel 16bit depth \else Y16 格式，单通道 16bit 深度 \endif */
    OB2_FORMAT_Y16 = 8,

    /** \if English Y8 format, single channel 8bit depth \else Y8 格式，单通道 8bit 深度 \endif */
    OB2_FORMAT_Y8 = 9,

    /** \if English Y10 format, single channel 10bit depth (SDK will unpack into Y16 by default) \else
                                Y10 格式，单通道 10bit 深度 (SDK 默认会解包成 Y16) \endif */
    OB2_FORMAT_Y10 = 10,

    /** \if English Y11 format, single channel 11bit depth (SDK will unpack into Y16 by default)\else
                               Y11 格式，单通道 11bit 深度 (SDK 默认会解包成 Y16) \endif */
    OB2_FORMAT_Y11 = 11,

    /** \if English Y12 format, single channel 12bit depth (SDK will unpack into Y16 by default) \else
                               Y12 格式，单通道 12bit 深度 (SDK 默认会解包成 Y16) \endif */
    OB2_FORMAT_Y12 = 12,

    /** \if English GRAY (the actual format is the same as YUYV) \else GRAY 灰度 (实际格式与 YUYV 相同) \endif */
    OB2_FORMAT_GRAY = 13,

    /** \if English HEVC encoding format (the actual format is the same as H265) \else HEVC 编码格式 (实际格式与 H265 相同) \endif */
    OB2_FORMAT_HEVC = 14,

    /** \if English I420 format \else I420 格式  \endif */
    OB2_FORMAT_I420 = 15,

    /** \if English xyz 3D coordinate point format \else 纯 x-y-z 三维坐标点格式  \endif */
    OB2_FORMAT_POINT = 19,

    /** \if English xyz 3D coordinate point format with RGB information \else 带 RGB 信息的 x-y-z 三维坐标点格式 \endif */
    OB2_FORMAT_COLORED_POINT = 20,

    /** \if English RLE pressure test format (SDK will be unpacked into Y16 by default) \else RLE 压测格式 (SDK 默认会解包成 Y16) \endif */
    OB2_FORMAT_RLE = 21,

    /** \if English RGB format \else RGB 格式  \endif */
    OB2_FORMAT_RGB = 22,

    /** \if English BGR format (actual BRG888) \else BGR 格式 (实际 BRG888) \endif */
    OB2_FORMAT_BGR = 23,

    /** \if English Y14 format, single channel 14bit depth (SDK will unpack into Y16 by default) \else
                               Y14 格式，单通道 14bit 深度 (SDK 默认会解包成 Y16) \endif */
    OB2_FORMAT_Y14 = 24,

    /** \if English BGRA format  \else BGRA 格式  \endif*/
    OB2_FORMAT_BGRA = 25,

    /** \if English compressed format \else 压缩格式  \endif*/
    OB2_FORMAT_COMPRESSED = 26,

    /** \if English any format for fuzzy matching \else 任意格式，用于模糊匹配 \endif*/
    OB2_FORMAT_ANY = 0xfe,

    /** \if English unknown format \else 未知格式 \endif */
    OB2_FORMAT_UNKNOWN = 0xff,
} ob2_image_format_t;

/**
 * \if English
 * @brief Point cloud type
 * \else
 * @brief 点云类型
 * \endif
 */
typedef enum {
    OB2_POINT_CLOUD         = 0,  //!< point cloud image format： ::OB2_FORMAT_POINT
    OB2_COLORED_POINT_CLOUD = 1,  //!< colored point cloud image format： ::OB2_FORMAT_COLORED_POINT
} ob2_point_cloud_type_t;

/**
 * \if English
 * @brief Three-dimensional point definition
 * \else
 * @brief 三维点定义
 *\endif
 */
typedef struct {
    float x;
    float y;
    float z;
} ob2_3d_point_t;

/**
 * \if English
 * @brief Three-dimensional point with colored definition
 * \else
 * @brief 带彩色信息的三维点定义
 * \endif
 */
typedef struct {
    float x;
    float y;
    float z;
    float r;
    float g;
    float b;
} ob2_colored_3d_point_t;

/**
 * \if English
 * @brief Camera stream configuration
 * \else
 * @brief 相机流配置
 * \endif
 */
typedef struct {
    /** \if English image width in pixels \else 图像像素宽度 \endif */
    uint16_t width_pixels;

    /** \if English image height in pixels \else 图像像素高度 \endif */
    uint16_t height_pixels;

    /** \if English frames per second \else 帧率，每秒帧数 \endif */
    uint16_t frame_rate;

    /** \if English frames format\else 图像数据格式 \endif */
    ob2_image_format_t format;
} ob2_camera_stream_profile_t;

/**
 * \if English
 * @brief Enable / disable definition
 * \else
 * @brief 使能 / 去使能定义
 * \endif
 */
typedef enum {
    OB2_DISABLE = 0,  //!< \if English Disable(turn of)  \else 去使能（关闭、禁用）\endif
    OB2_ENABLE  = 1,  //!< \if English Enable \else 使能 \endif
} ob2_enable_ctrl_t;

/**
 * \if English
 * @brief Image synchronization mode,
 * which controls how images from different
 * cameras are synchronized when generating a capture
 * \else
 * @brief 图像同步模式，用于控制生成 capture 时如何同步不同相机的图像
 * \endif
 */
typedef enum {
    /**
     * \if English
     * @brief The camera that receives the image first waits for the camera that receives the image later
     * \else
     * @brief 先接收到图像的相机等待后接收到的图像的相机
     * \endif
     */
    OB2_IMAGES_SYNC_MODE_WAIT_LATER_COMER = 0,

    /**
     * \if English
     * @brief Matching by timestamp, this mode eliminates desynchronisation due to inconsistent frame rates, inconsistent image processing and transmission
     * delays across cameras \else
     * @brief 通过时间戳进行匹配，该模式可消除由于帧率不一致、各相机图像处理和传输延时不一致导致的不同步问题
     * \endif
     */
    OB2_IMAGES_SYNC_MODE_DEVICE_TIMESTAMP_MATCH = 1,
} ob2_images_sync_mode_t;

/**
 * \if English
 * @brief capture generation policy
 * @brief capture 生成策略
 * \endif
 */
typedef enum {
    /**
     * \if English
     * Generate captures only after all camera images are synchronized,
     * and discard the current cache of images if it is no
     * longer possible to synchronize all enabled camera frames
     * \else
     * 仅所有相机图像同步后生成 capture，在已经无法同步所有已启用相机图像帧的情况下会丢弃当前缓存的图像
     * \endif
     */
    OB2_PRODUCE_CAPTURE_SYNC_IMAGES_ONLY = 0,

    /**
     * \if English
     * Ensures that color images are not discarded, in case it is already impossible to synchronize all enabled camera image
     * frames, it will ensure that color images are used to generate captures, while other camera images may be discarded,
     * for cases where color images are in H264 or H265 format, because H264 and H265 are inter-frame encoding formats and image
     * frames cannot be discarded without affecting the decoding results.
     * \else
     * 保证彩色图像不会被丢弃，在已经无法同步所有已启用相机图像帧的情况下，会保证彩色图像用于生成 capture，而其他相机图像可能会丢弃
     * 适用于彩色图像是 H264 或 H265 格式的情况，因为 H264 和 H265 是帧间编码格式，图像帧不能被丢弃，否则会影响解码结果。
     * \endif
     */
    OB2_PRODUCE_CAPTURE_KEEP_COLOR_IMAGE = 1,

    /**
     * \if English
     * Ensures that all images are not discarded and that only some camera frames are used to
     * generate captures when it is no longer possible to synchronize all enabled camera frames.
     * \else
     * 保证所有图像都不会被丢弃，在已经无法同步所有已启用相机图像帧的情况下，会仅用部分相机的图像帧生成 capture
     * \endif
     */
    OB2_PRODUCE_CAPTURE_KEEP_ALL_IMAGES = 2,
} ob2_produce_capture_policy_t;

/**
 * \if English
 * @brief Image alignment mode
 * \else
 * @brief 图像对齐模式
 * \endif
 */
typedef enum {
    /** \if English Turn off alignment mode \else 关闭对齐模式 \endif */
    OB2_IMAGES_ALIGN_MODE_DISABLE = 0,
    /**
     * \if English
     * Depth image to color camera by hardware,
     * The color camera can be left on, but the data stream format needs to be configured
     * \else
     * 硬件 D2C 对齐, color 相机可以不启用，但是需要配置数据流格式
     * \endif
     */
    OB2_IMAGES_ALIGN_MODE_D2C_HARDWARE = 1,
    /**
     * \if English
     * Depth image to color camera by software,
     * The color camera must be turned on, and the data stream format needs to be configured
     * \else
     * 软件 D2C 对齐, color 相机必须启用，且需要配置数据流格式
     * \endif
     */
    OB2_IMAGES_ALIGN_MODE_D2C_SOFTWARE = 2,
} ob2_images_align_mode_t;

/**
 * \if English
 * @brief IMU Sensor Type Definition
 * \else
 * @brief IMU Sensor 类型定义
 * \endif
 */
typedef enum {
    /** \if English unknown type sensor \else 未知类型传感器 \endif */
    OB2_IMU_SENSOR_UNKNOWN = 0,

    /** \if English Accel sensor \else 加速度计 \endif */
    OB2_IMU_SENSOR_ACCEL = 1,

    /** \if English Gyro sensor \else 陀螺仪 \endif */
    OB2_IMU_SENSOR_GYRO = 2,
} ob2_imu_sensor_type_t;

/**
 * \if English
 * @brief IMU sample rate values(gyroscope or accelerometer)
 * \else
 * @brief IMU 采样率值的枚举 (陀螺仪或加速度计)
 * \endif
 */
typedef enum {
    OB2_SAMPLE_RATE_1_5625_HZ = 1,   //!< 1.5625Hz
    OB2_SAMPLE_RATE_3_125_HZ  = 2,   //!< 3.125Hz
    OB2_SAMPLE_RATE_6_25_HZ   = 3,   //!< 6.25Hz
    OB2_SAMPLE_RATE_12_5_HZ   = 4,   //!< 12.5Hz
    OB2_SAMPLE_RATE_25_HZ     = 5,   //!< 25Hz
    OB2_SAMPLE_RATE_50_HZ     = 6,   //!< 50Hz
    OB2_SAMPLE_RATE_100_HZ    = 7,   //!< 100Hz
    OB2_SAMPLE_RATE_200_HZ    = 8,   //!< 200Hz
    OB2_SAMPLE_RATE_500_HZ    = 9,   //!< 500Hz
    OB2_SAMPLE_RATE_1_KHZ     = 10,  //!< 1KHz
    OB2_SAMPLE_RATE_2_KHZ     = 11,  //!< 2KHz
    OB2_SAMPLE_RATE_4_KHZ     = 12,  //!< 4KHz
    OB2_SAMPLE_RATE_8_KHZ     = 13,  //!< 8KHz
    OB2_SAMPLE_RATE_16_KHZ    = 14,  //!< 16KHz
    OB2_SAMPLE_RATE_32_KHZ    = 15,  //!< 32Hz
} ob2_gyro_sample_rate_t,
    ob2_accel_sample_rate_t;

/**
 * \if English
 * @brief Enumeration of gyroscope ranges
 * \else
 * @brief 陀螺仪量程的枚举
 * \endif
 */
typedef enum {
    /** \if English 16 degrees per second \else 16 度每秒 \endif */
    OB2_GYRO_FS_16_DPS = 1,

    /** \if English 31 degrees per second \else 31 度每秒 \endif */
    OB2_GYRO_FS_31_DPS = 2,

    /** \if English 62 degrees per second \else 62 度每秒 \endif */
    OB2_GYRO_FS_62_DPS = 3,

    /** \if English 125 degrees per second \else 125 度每秒 \endif */
    OB2_GYRO_FS_125_DPS = 4,

    /** \if English 245 degrees per second \else 245 度每秒 \endif */
    OB2_GYRO_FS_245_DPS = 5,

    /** \if English 250 degrees per second \else 250 度每秒 \endif */
    OB2_GYRO_FS_250_DPS = 6,

    /** \if English 500 degrees per second \else 500 度每秒 \endif */
    OB2_GYRO_FS_500_DPS = 7,

    /** \if English 1000 degrees per second \else 1000 度每秒 \endif */
    OB2_GYRO_FS_1000_DPS = 8,

    /** \if English 2000 degrees per second \else 2000 度每秒 \endif */
    OB2_GYRO_FS_2000_DPS = 9,
} ob2_gyro_full_scale_range_t;

/**
 * \if English
 * @brief Accelerometer range enumeration
 * \else
 * @brief 加速度计量程枚举
 * \endif
 */
typedef enum {
    /** \if English 1x the acceleration of gravity \else 1 倍重力加速度 \endif */
    OB2_ACCEL_FS_2_G = 1,

    /** \if English 4x the acceleration of gravity \else 4 倍重力加速度 \endif */
    OB2_ACCEL_FS_4_G = 2,

    /** \if English 8x the acceleration of gravity \else 8 倍重力加速度 \endif */
    OB2_ACCEL_FS_8_G = 3,

    /** \if English 16x the acceleration of gravity \else 16 倍重力加速度 \endif */
    OB2_ACCEL_FS_16_G = 4,
} ob2_accel_full_scale_range_t;

/**
 * \if English
 * @brief Gyroscope stream configuration
 * \else
 * @brief 陀螺仪流配置
 * \endif
 */
typedef struct {
    ob2_gyro_sample_rate_t      sample_rate;       //!< \if English Sampling rate \else 采样率 \endif
    ob2_gyro_full_scale_range_t full_scale_range;  //!< \if English full scale range \else 量程 \endif
} ob2_gyro_stream_profile_t;

/**
 * \if English
 * @brief Accelerometer stream configuration
 * \else
 * @brief 加速度计流配置
 * \endif
 */
typedef struct {
    ob2_accel_sample_rate_t      sample_rate;       //!< \if English Sampling rate \else 采样率 \endif
    ob2_accel_full_scale_range_t full_scale_range;  //!< \if English full scale range \else 量程 \endif
} ob2_accel_stream_profile_t;

/**
 * \if English
 * @brief Accelerometer/gyroscope sample data definition
 * \else
 * @brief 加速度计 / 陀螺仪采样数据定义
 * \endif
 */
typedef struct {
    uint64_t timestamp_usec;
    float    temperature;  //!< degrees celsius
    float    x;            //!< unit for accel sample: g; unit for gyro dgrees/sec (dps)
    float    y;
    float    z;
} ob2_accel_sample_t, ob2_gyro_sample_t;

/**
 * \if English
 * @brief Control Command ID
 * \else
 * @brief 控制命令 ID
 *\endif
 */
typedef enum {
    /** \if English LDP switch \else LDP 开关 \endif */
    OB2_PROP_LDP_BOOL = 2,

    /** \if English Laser switch \else 激光开关 \endif */
    OB2_PROP_LASER_BOOL = 3,

    /** \if English Read and write laser Time value (pulse width) \else 读写激光 Time 值（脉宽） \endif */
    OB2_PROP_LASER_PULSE_WIDTH_INT = 4,

    /** \if English Laser current \else 激光电流 \endif */
    OB2_PROP_LASER_CURRENT_FLOAT = 5,

    /** \if English IR flood switch \else 泛光灯开关 \endif */
    OB2_PROP_FLOOD_BOOL = 6,

    /** \if English IR flood level \else 泛光灯等级 \endif */
    OB2_PROP_FLOOD_LEVEL_INT = 7,

    /** \if English Depth mirror \else 深度镜像 \endif */
    OB2_PROP_DEPTH_MIRROR_BOOL = 14,

    /** \if English Depth flip \else  深度翻转 \endif */
    OB2_PROP_DEPTH_FLIP_BOOL = 15,

    /** \if English Depth Postfilter \else 深度 Postfilter \endif */
    OB2_PROP_DEPTH_POSTFILTER_BOOL = 16,

    /** \if English Depth Holefilter \else 深度 Holefilter \endif */
    OB2_PROP_DEPTH_HOLEFILTER_BOOL = 17,

    /** \if English IR mirror \else  IR 镜像 \endif */
    OB2_PROP_IR_MIRROR_BOOL = 18,

    /** \if English IR flip \else  IR 翻转 \endif */
    OB2_PROP_IR_FLIP_BOOL = 19,

    /** \if English Minimum depth threshold \else  最小深度阈值 \endif */
    OB2_PROP_MIN_DEPTH_INT = 22,

    /** \if English Maximum depth threshold \else  最大深度阈值 \endif */
    OB2_PROP_MAX_DEPTH_INT = 23,

    /** \if English Software filter switch \else  软件滤波开关 \endif */
    OB2_PROP_DEPTH_SOFT_FILTER_BOOL = 24,

    /** \if English LDP status \else  LDP 状态 \endif */
    OB2_PROP_LDP_STATUS_BOOL = 32,

    /** soft filter maxdiff param */
    OB2_PROP_DEPTH_MAX_DIFF_INT = 40,

    /** soft filter maxSpeckleSize */
    OB2_PROP_DEPTH_MAX_SPECKLE_SIZE_INT = 41,

    /** \if English Hardware d2c is on \else  硬件 d2c 开 \endif */
    OB2_PROP_DEPTH_ALIGN_HARDWARE_BOOL = 42,

    /** \if English Timestamp adjustment \else  时间戳调校 \endif */
    OB2_PROP_TIMESTAMP_OFFSET_INT = 43,

    /** \if English Hardware distortion switch Rectify \else  硬件去畸变开关 Rectify \endif */
    OB2_PROP_HARDWARE_DISTORTION_SWITCH_BOOL = 61,

    /** \if English Fan mode switch \else  风扇开关模式 \endif */
    OB2_PROP_FAN_WORK_MODE_INT = 62,

    /** \if English Multi-resolution D2C mode \else  多分辨率 D2C 模式 \endif */
    OB2_PROP_DEPTH_ALIGN_HARDWARE_MODE_INT = 63,

    /** \if English Anti_collusion activation status \else  防串货状态 \endif */
    OB2_PROP_ANTI_COLLUSION_ACTIVATION_STATUS_BOOL = 64,

    /** \if English
     * The depth precision level, which may change the depth frame data unit,
     *  needs to be confirmed through the ValueScale interface of DepthFrame
     * \else
     * 深度精度等级，可能会改变深度帧数据单位，需要通过 DepthFrame 的 ValueScale 接口确认
     * \endif
     */
    OB2_PROP_DEPTH_PRECISION_LEVEL_INT = 75,

    /** \if English tof filter range configuration \else  tof 滤波场景范围配置 \endif */
    OB2_PROP_TOF_FILTER_RANGE_INT = 76,

    /** \if English
     * laser mode, the firmware terminal currently only returns 1: IR Drive, 2: Torch
     * \else
     * 激光点亮模式，固件端目前只返回 1: IR Drive, 2: Torch
     * \endif
     */
    OB2_PROP_LASER_MODE_INT = 79,

    /** \if English
     * brt2r-rectify function switch (brt2r is a special module on mx6600), 0: Disable, 1: Rectify Enable
     * \else
     * brt2r-rectify 功能开关 (brt2r 是 mx6600 上的一个特殊模块)，0: 关闭, 1: 打开
     * \endif
     */
    OB2_PROP_RECTIFY2_BOOL = 80,

    /** \if English Color mirror \else  彩色镜像 \endif */
    OB2_PROP_COLOR_MIRROR_BOOL = 81,

    /** \if English Color flip \else  彩色翻转 \endif */
    OB2_PROP_COLOR_FLIP_BOOL = 82,

    /** \if English Indicator switch, 0: Disable, 1: Enable \else  指示灯开关，0: 关闭， 1: 打开 \endif */
    OB2_PROP_INDICATOR_LIGHT_BOOL = 83,

    /** \if English
     * Disparity to depth switch, 0: off, the depth stream outputs the disparity map; 1. On, the depth stream outputs the depth map.
     * \else
     * 视差转深度开关， 0：关闭，深度流输出视差图； 1. 打开，深度流输出深度图
     * \endif
     */
    OB2_PROP_DISPARITY_TO_DEPTH_BOOL = 85,

    /** \if English
     * BRT function switch (anti-background interference), 0: Disable, 1: Enable
     * \else
     * BRT 功能开关 (抗背景干扰)，0: 关闭， 1: 打开
     * \endif
     */
    OB2_PROP_BRT_BOOL = 86,

    /** \if English Watchdog function switch, 0: Disable, 1: Enable \else  看门狗功能开关，0: 关闭， 1: 打开 \endif */
    OB2_PROP_WATCHDOG_BOOL = 87,

    /** \if English
     * External signal trigger restart function switch, 0: Disable, 1: Enable
     * \else
     * 外部信号触发重启功能开关，0: 关闭， 1: 打开
     * \endif
     */
    OB2_PROP_EXTERNAL_SIGNAL_RESET_BOOL = 88,

    /** \if English Heartbeat monitoring function switch, 0: Disable, 1: Enable \else  心跳监测功能开关，0: 关闭， 1: 打开 \endif */
    OB2_PROP_HEARTBEAT_BOOL = 89,

    /** \if English Depth cropping mod  \else  深度裁剪模式 \endif */
    OB2_PROP_DEPTH_CROPPING_MODE_INT = 90,

    /** \if English D2C preprocessing switch (such as RGB cropping), 0: off, 1: on \else  D2C 前处理开关（如 RGB 裁剪），0: 关闭，1: 打开 \endif */
    OB2_PROP_D2C_PREPROCESS_BOOL = 91,

    /** \if English Custom RGB cropping switch, 0 is off, 1 is on custom cropping, and the ROI cropping area is issued
     * \else 自定义 RGB 裁剪开关，0 为关闭，1 为开启自定义裁剪，下发 ROI 裁剪区域
     * \endif
     */
    OB2_PROP_RGB_CUSTOM_CROP_BOOL = 94,

    /** \if English Device operating mode (power consumption) \else  设备工作模式（功耗） \endif */
    OB2_PROP_DEVICE_WORK_MODE_INT = 95,

    /** 设备通信方式 0: USB; 1: Ethernet(RTSP)*/
    OB2_PROP_DEVICE_COMMUNICATION_TYPE_INT = 97,

    /** 切换 IR 模式，0 为主动 IR 模式, 1 为被动 IR 模式 */
    OB2_PROP_SWITCH_IR_MODE_INT = 98,

    /** \if English Baseline calibration parameters \else  基线标定参数 \endif */
    OB2_STRUCT_BASELINE_CALIBRATION_PARAM = 1002,

    /** \if English Device temperature information \else  设备温度信息 \endif */
    OB2_STRUCT_DEVICE_TEMPERATURE = 1003,

    /** \if English TOF exposure threshold range \else  TOF 曝光阈值范围 \endif */
    OB2_STRUCT_TOF_EXPOSURE_THRESHOLD_CONTROL = 1024,

    /** \if English get/set serial number \else  获取 / 设置序列号 \endif */
    OB2_STRUCT_DEVICE_SERIAL_NUMBER = 1035,

    /** \if English get/set device time \else 获取 / 设置设备时间 \endif */
    OB2_STRUCT_DEVICE_TIME = 1037,

    /** \if English Multi-device synchronization mode and parameter configuration \else  多设备同步模式和参数配置 \endif */
    OB2_STRUCT_MULTI_DEVICE_SYNC_CONFIG = 1038,

    /** \if English RGB cropping ROI \else  RGB 裁剪 ROI \endif */
    OB2_STRUCT_RGB_CROP_ROI = 1040,

    /** \if English Device ip address configuration \else  设备 ip 地址配置 \endif */
    OB2_STRUCT_DEVICE_IP_ADDR_CONFIG = 1041,

    /** \if English Color camera auto exposure \else  彩色相机自动曝光 \endif */
    OB2_PROP_COLOR_AUTO_EXPOSURE_BOOL = 2000,

    /** \if English Color camera exposure adjustment \else  彩色相机曝光调节 \endif */
    OB2_PROP_COLOR_EXPOSURE_INT = 2001,

    /** \if English Color camera gain adjustment \else  彩色相机增益调节 \endif */
    OB2_PROP_COLOR_GAIN_INT = 2002,

    /** \if English Color camera automatic white balance \else  彩色相机自动白平衡 \endif */
    OB2_PROP_COLOR_AUTO_WHITE_BALANCE_BOOL = 2003,

    /** \if English Color camera white balance adjustment \else  彩色相机白平衡调节 \endif */
    OB2_PROP_COLOR_WHITE_BALANCE_INT = 2004,

    /** \if English Color camera brightness adjustment \else  彩色相机亮度调节 \endif */
    OB2_PROP_COLOR_BRIGHTNESS_INT = 2005,

    /** \if English Color camera sharpness adjustment \else  彩色相机锐度调节 \endif */
    OB2_PROP_COLOR_SHARPNESS_INT = 2006,

    /** \if English Color camera saturation adjustment \else  彩色相机饱和度调节 \endif */
    OB2_PROP_COLOR_SATURATION_INT = 2008,

    /** \if English Color camera contrast adjustment \else  彩色相机对比度调节 \endif */
    OB2_PROP_COLOR_CONTRAST_INT = 2009,

    /** \if English Color camera gamma adjustment \else  彩色相机伽马值调节 \endif */
    OB2_PROP_COLOR_GAMMA_INT = 2010,

    /** \if English Color camera image rotation\else  彩色相机图像旋转 \endif */
    OB2_PROP_COLOR_ROLL_INT = 2011,

    /** \if English Color camera auto exposure priority \else  彩色相机自动曝光优先 \endif */
    OB2_PROP_COLOR_AUTO_EXPOSURE_PRIORITY_INT = 2012,

    /** \if English Color camera brightness compensation \else  彩色相机亮度补偿 \endif */
    OB2_PROP_COLOR_BACKLIGHT_COMPENSATION_INT = 2013,

    /** \if English color camera color tint \else  彩色相机彩色色调 \endif */
    OB2_PROP_COLOR_HUE_INT = 2014,

    /** \if English Color Camera Power Line Frequency \else  彩色相机电力线路频率 \endif */
    OB2_PROP_COLOR_POWER_LINE_FREQUENCY_INT = 2015,

    /** \if English
     * Automatic exposure of depth camera (infrared camera will be set synchronously under some models of devices)
     * \else
     * 深度相机自动曝光（某些型号设备下会同步设置红外相机）
     * \endif
     */
    OB2_PROP_DEPTH_AUTO_EXPOSURE_BOOL = 2016,

    /** \if English
     * Depth camera exposure adjustment (infrared cameras will be set synchronously under some models of devices)
     * \else
     * 深度相机曝光调节（某些型号设备下会同步设置红外相机）
     * \endif
     */
    OB2_PROP_DEPTH_EXPOSURE_INT = 2017,

    /** \if English
     * Depth camera gain adjustment (infrared cameras will be set synchronously under some models of devices)
     * \else
     * 深度相机增益调节（某些型号设备下会同步设置红外相机）
     * \endif
     */
    OB2_PROP_DEPTH_GAIN_INT = 2018,

    /** \if English
     * Infrared camera auto exposure (depth camera will be set synchronously under some models of devices)
     * \else
     * 红外相机自动曝光（某些型号设备下会同步设置深度相机）
     * \endif
     */
    OB2_PROP_IR_AUTO_EXPOSURE_BOOL = 2025,

    /** \if English
     * Infrared camera exposure adjustment (some models of devices will set the depth camera synchronously)
     * \else
     * 红外相机曝光调节（某些型号设备下会同步设置深度相机）
     * \endif
     */
    OB2_PROP_IR_EXPOSURE_INT = 2026,

    /** \if English
     * Infrared camera gain adjustment (the depth camera will be set synchronously under some models of devices)
     * \else
     * 红外相机增益调节（某些型号设备下会同步设置深度相机）
     * \endif
     */
    OB2_PROP_IR_GAIN_INT = 2027,

    /**
     * \if English
     * Binocular infrared camera left and right IR switching
     * \else 双目红外相机左右 IR 切换
     * \endif
     */
    OB2_PROP_IR_SWITCH_INT = 2028,

    /** \if English Disparity to depth  \else 视差转深度 \endif*/
    OB2_PROP_SDK_DISPARITY_TO_DEPTH_BOOL = 3004,

    /**
     * \if English
     * Depth data unpacking function switch (will be turned on by default every time the stream is turned on, supports RLE/Y10/Y11/Y12/Y14 format)
     * \else
     * Depth 数据解包功能开关 (每次开流都会默认打开，支持 RLE/Y10/Y11/Y12/Y14 格式)
     * \endif
     */
    OB2_PROP_SDK_DEPTH_FRAME_UNPACK_BOOL = 3007,

    /**
     * \if English
     * IR data unpacking function switch (will be turned on by default every time the stream is turned on, supports RLE/Y10/Y11/Y12/Y14 format)
     * \else
     * IR 数据解包功能开关 (每次开流都会默认打开，支持 RLE/Y10/Y11/Y12/Y14 格式)
     * \endif
     */
    OB2_PROP_SDK_IR_FRAME_UNPACK_BOOL = 3008,

    /**
     * \if English
     * Calibration Json file read from the device side (Femto Mega, read only)
     * \else
     * 从设备端读取的标定 Json 文件 (Femto Mega, read only)
     * \endif
     */
    OB2_RAW_DATA_CAMERA_CALIB_JSON_FILE = 4029,

    /** \if English D2C initialization table file (Femto Mega) \else D2C 初始化表文件 (Femto Mega) \endif*/
    OB2_RAW_DATA_D2C_ROT_LUT_FILE = 4030,

    /** \if English LDP status \else  曝光时间读写 \endif */
    OB2_STRUCT_DEBUG_SENSOR_EXPOSURE_TIME = 5504,
} ob2_command_id_t;

/**
 * \if English
 * @brief Control command type
 * \else
 * @brief 控制命令类型
 * \endif
 */
typedef enum {
    OB2_UNKNOWN_COMMAND_TYPE = 0,  //!< \if English Unknown \else 未知 \endif
    OB2_BOOL_PROPERTY        = 1,  //!< \if English Boolean property command \else 布尔型属性命令 \endif
    OB2_INT_PROPERTY         = 2,  //!< \if English Integer property command \else 整型属性命令 \endif
    OB2_FLOAT_PROPERTY       = 3,  //!< \if English Float property command \else 浮点型属性命令 \endif
    OB2_ENUM_PROPERTY        = 4,  //!< \if English Enum Property Command \else 枚举型属性命令 \endif
    OB2_STRUCTURED_DATA      = 5,  //!< \if English Structure data command \else 结构体类似数据命令 \endif
    OB2_RAW_DATA             = 6,  //!< \if English raw data command \else 裸数据命令 \endif
} ob2_command_type_t;

/**
 * \if English
 * @brief Access privileges (primary user command)
 * \else
 * @brief 访问权限（主要用户命令）
 * \endif
 */
typedef enum {
    /** \if English no permission \else 无访问权限 \endif */
    OB2_PERMISSION_DENY = 0,

    /** \if English can read \else 可读 \endif */
    OB2_PERMISSION_READ = 1,

    /** \if English can write \else 可写 \endif */
    OB2_PERMISSION_WRITE = 2,

    /** \if English can read and write \else 可读写 \endif */
    OB2_PERMISSION_READ_WRITE = 3,
} ob2_access_permission_t;

/**
 * \if English
 * @brief Command Information
 * \else
 * @brief 命令信息
 *\endif
 */
typedef struct {
    ob2_command_id_t        id;          //!< \if English Command ID \else 命令 id \endif
    ob2_command_type_t      type;        //!< \if English Command type \else 命令类型 \endif
    uint32_t                version;     //!< \if English Command version \else 命令版本号 \endif
    char                    name[64];    //!< \if English Command name \else  命令名称 \endif
    ob2_access_permission_t permission;  //!< \if English Command permission \else 命令访问权限 \endif
} ob2_command_info_t;

/**
 * \if English
 * @brief Integer property command capability
 * \else
 * @brief 整型属性命令能力
 * \endif
 */
typedef struct {
    int max;   //!< \if English Maximum value \else 最大值 \endif
    int min;   //!< \if English Minimum value value \else 最小值 \endif
    int step;  //!< \if English step value \else 步进值 \endif
    int def;   //!< \if English default value \else 默认值 \endif
} ob2_int_property_capability_t;

/**
 * \if English
 * @brief Float property command capability
 * \else
 * @brief 浮点型属性命令能力
 * \endif
 */
typedef struct {
    float max;   //!< \if English Maximum value \else 最大值 \endif
    float min;   //!< \if English Minimum value value \else 最小值 \endif
    float step;  //!< \if English step value \else 步进值 \endif
    float def;   //!< \if English default value \else 默认值 \endif
} ob2_float_property_capability_t;

/**
 * \if English
 * @brief Enum property command capability
 * \else
 * @brief 枚举型属性命令能力
 * \endif
 */
typedef struct {
    uint32_t count;            //!< \if English Number of supported enumeration values \else 支持的枚举值个数 \endif
    int      value_list[254];  //!< \if English Support for enumerated value lists \else 支持枚举值列表 \endif
} ob2_enum_property_capability_t;

/**
 * \if English
 * @brief Bind data
 * \else
 * @brief 数据捆
 * \endif
 */
typedef struct {
    uint32_t item_count;         //!< \if English Number of data items \else 数据项个数 \endif
    uint32_t item_stride_bytes;  //!< \if English Data row span \else 数据行跨度 \endif
    uint32_t data_size;          //!< \if English Data size \else 数据长度 \endif
    uint8_t *data;               //!< \if English Data address pointer \else 数据地址指针 \endif
} ob2_data_bundle_t;

/**
 * \if English
 * @brief Device firmware upgrade status
 * \else
 * @brief 设备固件升级状态
 * \endif
 */
typedef enum {
    /** \if English file transfer \else 文件传输中 \endif */
    OB2_STAT_FILE_TRANSFER = 4,

    /** \if English update completed \else 升级完成 \endif */
    OB2_STAT_DONE = 3,

    /** \if English upgrade in process \else 升级中 \endif */
    OB2_STAT_IN_PROGRESS = 2,

    /** \if English start the upgrade \else 开始升级 \endif */
    OB2_STAT_START = 1,

    /** \if English Image file verification \else 镜像文件校验中 \endif */
    OB2_STAT_VERIFY_IMAGE = 0,

    /** \if English Verification failed \else 校验失败 \endif */
    OB2_ERR_VERIFY = -1,

    /** \if English Program execution failed \else 程序执行失败 \endif */
    OB2_ERR_PROGRAM = -2,

    /** \if English Flash parameter failed \else Flash 参数失败 \endif */
    OB2_ERR_ERASE = -3,

    /** \if English Flash type error \else Flash 类型错误 \endif */
    OB2_ERR_FLASH_TYPE = -4,

    /** \if English Image file size error \else 镜像文件大小错误 \endif */
    OB2_ERR_IMAGE_SIZE = -5,

    /** \if English other errors \else 其他错误 \endif */
    OB2_ERR_OTHER = -6,

    /** \if English DDR access error \else DDR 访问错误 \endif */
    OB2_ERR_DDR = -7,

    /** \if English timeout error \else 超时错误 \endif */
    OB2_ERR_TIMEOUT = -8
} ob2_update_state_t;

/**
 * \if English
 * @brief Camera internal parameters
 * \else
 * @brief 相机内参
 * \endif
 */
typedef struct {
    float   fx;      //!<  \if English focal length in x direction \else x 方向焦距 \endif
    float   fy;      //!<  \if English focal length in y direction \else y 方向焦距 \endif
    float   cx;      //!<  \if English Optical center abscissa \else 光心横坐标 \endif
    float   cy;      //!<  \if English Optical center ordinate \else 光心纵坐标 \endif
    int16_t width;   //!<  \if English image width \else 图像宽度 \endif
    int16_t height;  //!<  \if English image height \else 图像高度 \endif
} ob2_camera_intrinsic_t;

/**
 * \if English
 * @brief Distortion Parameters
 * \else
 * @brief 畸变参数
 * \endif
 */
typedef struct {
    float k1;  //!<  \if English Radial distortion factor 1 \else 径向畸变系数 1 \endif
    float k2;  //!<  \if English Radial distortion factor 2 \else 径向畸变系数 2 \endif
    float k3;  //!<  \if English Radial distortion factor 3 \else 径向畸变系数 3 \endif
    float k4;  //!<  \if English Radial distortion factor 4 \else 径向畸变系数 4 \endif
    float k5;  //!<  \if English Radial distortion factor 5 \else 径向畸变系数 5 \endif
    float k6;  //!<  \if English Radial distortion factor 6 \else 径向畸变系数 6 \endif
    float p1;  //!<  \if English Tangential distortion factor 1 \else 切向畸变系数 1 \endif
    float p2;  //!<  \if English Tangential distortion factor 2 \else 切向畸变系数 2 \endif
} ob2_camera_distortion_t;

/**
 * \if English
 * @brief Rotation/Transformation matrix
 * \else
 * @brief 旋转 / 变换矩阵
 * \endif
 */
typedef struct {
    float rot[9];    //!<  \if English Rotation matrix \else 旋转矩阵，行优先 \endif
    float trans[3];  //!<  \if English transformation matrix \else 变化矩阵 \endif
} ob2_d2c_transform_t;

/**
 * \if English
 * @brief Camera parameters
 * \else
 * @brief 相机参数
 * \endif
 */
typedef struct {
    ob2_camera_intrinsic_t  depth_intrinsic;   //!<  \if English Depth camera intrinsic parameters \else 深度相机内参 \endif
    ob2_camera_intrinsic_t  color_Intrinsic;   //!<  \if English Color camera intrinsic parameters \else 彩色相机内参 \endif
    ob2_camera_distortion_t depth_distortion;  //!<  \if English Depth camera distortion parameters \else 深度相机畸变参数 \endif
    ob2_camera_distortion_t color_distortion;  //!<  \if English Color camera distortion parameters 1 \else 彩色相机畸变参数 \endif
    ob2_d2c_transform_t     transform;         //!<  \if English rotation/transformation matrix \else 旋转 / 变换矩阵 \endif
} ob2_cameras_calibration_t;

/**
 * \if English
 * @brief Playback State
 * \else
 * @brief 回放状态
 *\endif
 */
typedef enum {
    /** \if English begin \else 开始 \endif */
    OB2_PLAYBACK_BEGIN = 0,

    /** \if English pause \else 暂停 \endif */
    OB2_PLAYBACK_PAUSE = 1,

    /** \if English resume \else 继续 \endif */
    OB2_PLAYBACK_RESUME = 2,

    /** \if English end \else 终止  \endif */
    OB2_PLAYBACK_END = 3,
} ob2_playback_state_t;

/**
 * \if English
 * @brief Camera synchronization mode
 * @attention Since the Depth and IR images actually come from the same Sensor,
 * the IR performance is the same as the Depth in different modes
 * \else
 * @brief 相机同步模式
 * @attention 由于 Depth 和 IR 图像实际上来自同一个 Sensor，所以不同模式中，IR 的表现和 Depth 是一致的
 * \endif
 */
typedef enum {
    /** \if English Close sync mode, Color is not associated with Depth  \else 关闭, Color 与 Depth 不相关联 \endif */
    OB2_CAMERA_SYNC_MODE_CLOSE = 0,
    /** \if English Color exposure first, Color exposure triggers Depth/IR exposure \else Color 优先曝光，Color 曝光触发 Depth/IR 曝光 \endif */
    OB2_CAMERA_SYNC_MODE_COLOR_EXPOSURE_FIRST = 1,
    /** \if English Depth/IR exposure first, Depth exposure triggers Color exposure \else Depth/IR 优先曝光，Depth 曝光触发 Color 曝光 \endif */
    OB2_CAMERA_SYNC_MODE_DEPTH_EXPOSURE_FIRST = 2,
} ob2_cameras_sync_mode_t;

/**
 * \if English
 * @brief Multi-camara synchronization mode
 * \else
 * @brief 多机线连接同步模式
 * \endif
 */
typedef enum {
    /**
     * \if English
     * Does not receive external trigger signals and does not output trigger signals to the outside
     * \else
     * 不接收外部触发信号，也不向外输出触发信号
     * \endif
     */
    OB2_WIRED_SYNC_MODE_STANDALONE = 0,
    /**
     * \if English
     * Main mode, does not receive external trigger signal, but will output trigger signal to the outside
     * \else
     * 主模式，不接收外部触发信号，但是会向外输出触发信号
     * \endif
     */
    OB2_WIRED_SYNC_MODE_PRIMARY = 1,
    /**
     * \if English
     * Slave mode, receives external trigger signal, does not output trigger signal to the outside
     * \else
     * 从模式，接收外部触发信号，不向外输出触发信号
     * \endif
     */
    OB2_WIRED_SYNC_MODE_SECONDARY = 2,
} ob2_wired_sync_mode_t;

/**
 * \if English
 * @brief Device information callback for device installation/removal monitoring
 * \else
 * @brief 设备信息回调，用于设备安装 / 移除监控
 * \endif
 */
typedef void (*ob2_device_info_cb_t)(ob2_device_installation_info_t device_info, void *user_data);

/**
 * \if English
 * @brief Firmware upgrade status callback
 * \else
 * @brief 固件升级状态回调
 * \endif
 */
typedef void (*ob2_firmware_update_state_cb_t)(ob2_update_state_t state, const char *message, uint8_t percent, void *user_data);

/**
 * \if English
 * @brief capture callback
 * @attention The captures returned by the callback need to be released by actively calling @ref ob2_capture_release, otherwise it will lead to memory leak.
 * \else
 * @attention 回调返回的 capture 需要主动调用 @ref ob2_capture_release 释放，否则会导致内存泄漏
 * \endif
 */
typedef void (*ob2_capture_cb_t)(ob2_capture_t capture_handle, void *user_data);

/**
 * \if English
 * @brief buffer release callback, used for reclaiming memory when user-defined buffer creation image is released
 * \else
 * @brief buffer 释放回调，用于用户自定义 buffer 创建 image 释放时回收内存
 * \endif
 */
typedef void (*ob2_buffer_release_cb_t)(uint8_t *buffer, void *user_data);

/**
 * \if English
 * @brief The IMU sample data callback
 * @attention The imu_sample returned by the callback needs to be released by actively calling @ref ob2_imu_sample_release, otherwise it will cause a memory
 * leak.
 * \else
 * @brief IMU 采样数据回调
 * @attention 回调返回的 imu_sample 需要主动调用 @ref ob2_imu_sample_release 释放，否则会导致内存泄漏
 * \endif
 */
typedef void (*ob2_imu_sample_cb_t)(ob2_imu_sample_t imu_sample_handle, void *user_data);

/**
 * \if English
 * @brief Playback state callback
 * \else
 * @brief 回放状态回调
 * \endif
 */
typedef void (*ob2_playback_state_cb_t)(ob2_playback_state_t state, void *user_data);

#pragma pack(pop)

#ifdef __cplusplus
}
#endif
