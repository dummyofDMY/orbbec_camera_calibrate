#pragma once

extern "C" {
#include "h/ob2types.h"
}

#include <stdexcept>
#include <functional>

namespace ob2 {
/**
 * \if English
 *
 * @brief Used to convert @ref ob2_status_t in the C API to an exception throw
 *
 * \else
 *
 * @brief 用于将 C API 中的 @ref ob2_status_t 转换成异常抛出
 *
 * \endif
 */
#define CHECK_OB2_STATUS_ERROR_THROW(status)      \
    switch(status.code) {                         \
    case OB2_STATUS_LOGIC_ERROR:                  \
        throw std::logic_error(status.message);   \
    case OB2_STATUS_RUNTIME_ERROR:                \
        throw std::runtime_error(status.message); \
    case OB2_STATUS_UNKNOWN_ERROR:                \
        throw status.message;                     \
    default:                                      \
        break;                                    \
    }

/**
 * \if English
 *
 * @brief User parameter non-empty check
 *
 * \else
 *
 * @brief 用户参数非空校验
 *
 * \endif
 */
#define VALIDATE_NOT_NULL(ARG)                                                   \
    if(!(ARG)) {                                                                 \
        throw std::logic_error("NULL pointer passed for argument \"" #ARG "\""); \
    }

/**
 * \if English
 *
 * @brief Device information callbacks (mainly for device installation and removal callbacks)
 *
 * \else
 *
 * @brief 设备信息回调（主要用于设备安装和移除回调）
 *
 * \endif
 */
typedef std::function<void(const ob2_device_installation_info_t &)> device_info_cb;

/**
 * \if English
 *
 * @brief Device upgrade status callback
 *
 * \else
 *
 * @brief 设备升级状态回调
 *
 * \endif
 */
typedef std::function<void(ob2_update_state_t state, std::string message, uint8_t percent)> firmware_update_state_cb;

/**
 * \if English
 *
 * @brief playback status callback
 *
 * \else
 *
 * @brief 回放器回放状态回调
 *
 * \endif
 */
typedef std::function<void(ob2_playback_state_t state)> playback_state_cb;

/**
 * \if English
 *
 * @brief buffer release callback
 *
 * \else
 *
 * @brief buffer 释放回调
 *
 * \endif
 */
typedef std::function<void(uint8_t *buffer)> buffer_release_cb;
}  // namespace ob2