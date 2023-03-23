// Copyright(c) 2020 Orbbec Corporation. All Rights Reserved.
#pragma once
#include <opencv2/opencv.hpp>
#include <string>

extern "C" {
#include "hpp/OB2Camera.hpp"
}
#define ESC 27

// 快速取平方根的倒数
float Q_rsqrt(float number) {
    long        i;
    float       x2, y;
    const float threehalfs = 1.5F;

    x2 = number * 0.5F;
    y  = number;
    i  = *(long *)&y;
    i  = 0x5f3759df - (i >> 1);
    y  = *(float *)&i;
    y  = y * (threehalfs - (x2 * y * y));

    return y;
}

typedef enum {
    RENDER_SINGLE,      // Render only the first frame in the array
    RENDER_ONE_ROW,     // Render the frames in the array as a single line
    RENDER_ONE_COLUMN,  // Renders the frames in the array as a column
    RENDER_GRID,        // Render frames in an array as a grid
    RENDER_OVERLAY      // Render the frames in the array as an overlay
} RenderType;

class Window {
public:
    Window(std::string name, int width, int height) : _name(name), _width(width), _height(height), _windowClose(false), _key(-1) {}

    ~Window() {}

    void resize(int width, int height) {
        _width  = width;
        _height = height;
    }

    void render(std::vector<std::shared_ptr<ob2::image>> images, RenderType renderType) {
        _key = cv::waitKey(10);
        if(_key == ESC) {
            _windowClose = true;
        }
        if(_windowClose) {
            cv::destroyAllWindows();
            return;
        }

        auto mats = processImages(images);
        renderMats(mats, renderType);
    }

    void render(std::vector<std::shared_ptr<ob2::image>> images, float alpha) {
        _key = cv::waitKey(10);
        if(_key == ESC) {
            _windowClose = true;
        }
        if(_windowClose) {
            cv::destroyAllWindows();
            return;
        }

        auto mats = processImages(images);
        renderMats(mats, alpha);
    }

    inline int getKey() {
        return _key;
    }

    operator bool() {
        return !_windowClose;
    }

private:
    std::string _name;
    int         _width;
    int         _height;
    bool        _windowClose;
    int         _key;

    std::vector<cv::Mat> processImages(std::vector<std::shared_ptr<ob2::image>> images) {
        std::vector<cv::Mat> mats;
        void *               data;
        uint32_t             dataSize;
        ob2_camera_type_t    cameraType;
        ob2_image_format_t   format;
        uint32_t             width;
        uint32_t             height;

        for(auto im: images) {
            if(im == nullptr || im->get_size() < 1024) {
                break;
            }

            data       = im->get_buffer();
            dataSize   = im->get_size();
            cameraType = im->get_source_camera_type();
            format     = im->get_format();
            width      = im->get_width_pixels();
            height     = im->get_height_pixels();

            cv::Mat rstMat;
            switch(cameraType) {
            case OB2_CAMERA_COLOR:
                switch(format) {
                case OB2_FORMAT_MJPG:
                    rstMat = cv::Mat(1, dataSize, CV_8UC1, data).clone();
                    rstMat = cv::imdecode(rstMat, 1);
                    break;
                case OB2_FORMAT_YUYV:
                    rstMat = cv::Mat(height, width, CV_8UC2, data).clone();
                    cv::cvtColor(rstMat, rstMat, cv::COLOR_YUV2BGR_YUYV);
                    break;
                case OB2_FORMAT_NV12:
                    rstMat = cv::Mat(height, width, CV_8UC3, data).clone();
                    cv::cvtColor(rstMat, rstMat, cv::COLOR_YUV2BGR_NV12);
                    break;
                case OB2_FORMAT_RGB:
                    rstMat = cv::Mat(height, width, CV_8UC3, data).clone();
                    cv::cvtColor(rstMat, rstMat, cv::COLOR_RGB2BGR);
                    break;
                default:
                    break;
                }
                break;
            case OB2_CAMERA_DEPTH:
                switch(format) {
                case OB2_FORMAT_Y16: {
                    float scale = im->get_value_scale();
                    rstMat      = cv::Mat(height, width, CV_16UC1, data).clone();
                    // cv::threshold(rstMat, rstMat, 6000 / scale, 0, cv::THRESH_TRUNC);

                    // Scaling of depth values from 0 to 6000mm to 0 to 255
                    rstMat = rstMat * 255 / (6000 / scale);

                    // CV_16UC1 to CV_8UC1, which includes the cv::threshold operation, i.e. any value greater than 255 becomes 255
                    rstMat.convertTo(rstMat, CV_8UC1);

                    cv::applyColorMap(rstMat, rstMat, cv::COLORMAP_JET);
                } break;
                default:
                    break;
                }
                break;
            case OB2_CAMERA_IR:
                switch(format) {
                case OB2_FORMAT_Y16:
                    rstMat = cv::Mat(height, width, CV_16UC1, data).clone();
                    // cv::threshold(rstMat, rstMat, 4096, 0, cv::THRESH_TRUNC);

                    // Most of the value of ir pixels are between 0 and 20102448, scaling them to 0 to 255
                    rstMat = rstMat * 255 / 1024;

                    // CV_16UC1 to CV_8UC1, which includes the cv::threshold operation, i.e. any value greater than 255 becomes 255
                    rstMat.convertTo(rstMat, CV_8UC1);

                    cv::cvtColor(rstMat, rstMat, cv::COLOR_GRAY2BGR);
                    break;
                case OB2_FORMAT_Y8:
                    rstMat = cv::Mat(height, width, CV_8UC1, data).clone();
                    cv::cvtColor(rstMat, rstMat, cv::COLOR_GRAY2BGR);
                    break;
                case OB2_FORMAT_MJPG:
                    rstMat = cv::Mat(1, dataSize, CV_8UC1, data).clone();
                    rstMat = cv::imdecode(rstMat, 1);
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }

            if(!rstMat.empty()) {
                mats.push_back(rstMat);
            }
        }
        return mats;
    }

    void renderMats(std::vector<cv::Mat> mats, RenderType renderType) {
        if(mats.size() == 0) {
            return;
        }
        try {
            if(renderType == RENDER_SINGLE) {
                cv::Mat outMat;
                cv::resize(mats[0], outMat, cv::Size(_width, _height));
                cv::imshow(_name, outMat);
            }
            else if(renderType == RENDER_ONE_ROW) {
                cv::Mat outMat;
                for(auto mat: mats) {
                    cv::Mat resizeMat;
                    cv::resize(mat, resizeMat, cv::Size(_width / mats.size(), _height));
                    if(outMat.dims > 0) {
                        cv::hconcat(outMat, resizeMat, outMat);
                    }
                    else {
                        outMat = resizeMat;
                    }
                }
                cv::imshow(_name, outMat);
            }
            else if(renderType == RENDER_ONE_COLUMN) {
                cv::Mat outMat;
                for(auto mat: mats) {
                    cv::Mat resizeMat;
                    cv::resize(mat, resizeMat, cv::Size(_width, _height / mats.size()));
                    if(outMat.dims > 0) {
                        cv::vconcat(outMat, resizeMat, outMat);
                    }
                    else {
                        outMat = resizeMat;
                    }
                }
                cv::imshow(_name, outMat);
            }
            else if(renderType == RENDER_GRID) {
                int     count = mats.size();
                float   sq    = 1.0f / Q_rsqrt((float)count);
                int     isq   = (int)sq;
                int     cols  = (sq - isq < 0.01f) ? isq : isq + 1;
                float   div   = (float)count / (float)cols;
                int     idiv  = (int)div;
                int     rows  = (div - idiv < 0.01f) ? idiv : idiv + 1;
                cv::Mat outMat;
                for(int i = 0; i < rows; i++) {
                    cv::Mat lineMat;
                    for(int j = 0; j < cols; j++) {
                        cv::Mat mat;
                        cv::Mat resizeMat;
                        int     index = i * cols + j;
                        if(index < count) {
                            mat = mats[index];
                        }
                        else {
                            mat = cv::Mat(_width / cols, _height / rows, CV_8UC3);
                        }
                        cv::resize(mat, resizeMat, cv::Size(_width / cols, _height / rows));

                        if(lineMat.dims > 0) {
                            cv::hconcat(lineMat, resizeMat, lineMat);
                        }
                        else {
                            lineMat = resizeMat;
                        }
                    }
                    if(outMat.dims > 0) {
                        cv::vconcat(outMat, lineMat, outMat);
                    }
                    else {
                        outMat = lineMat;
                    }
                }
                cv::imshow(_name, outMat);
            }
            else if(renderType == RENDER_OVERLAY) {
                cv::Mat outMat, resizeMat;
                cv::resize(mats[0], outMat, cv::Size(_width, _height));
                for(int i = 1; i < mats.size(); i++) {
                    cv::resize(mats[i], resizeMat, cv::Size(_width, _height));
                    cv::bitwise_or(outMat, resizeMat, outMat);
                }
                cv::imshow(_name, outMat);
            }
        }
        catch(std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }

    void renderMats(std::vector<cv::Mat> mats, float alpha) {
        int size = mats.size();
        if(size != 2) {
            std::cout << "only support the satuation with two mats!" << std::endl;
            return;
        }
        try {
            cv::Mat outMat, resizeMat;
            cv::resize(mats[0], outMat, cv::Size(_width, _height));
            cv::resize(mats[1], resizeMat, cv::Size(_width, _height));

            for(int i = 0; i < outMat.rows; i++) {
                for(int j = 0; j < outMat.cols; j++) {
                    cv::Vec3b &outRgb    = outMat.at<cv::Vec3b>(i, j);
                    cv::Vec3b &resizeRgb = resizeMat.at<cv::Vec3b>(i, j);

                    outRgb[0] = (uint8_t)(outRgb[0] * (1 - alpha) + resizeRgb[0] * alpha);
                    outRgb[1] = (uint8_t)(outRgb[1] * (1 - alpha) + resizeRgb[1] * alpha);
                    outRgb[2] = (uint8_t)(outRgb[2] * (1 - alpha) + resizeRgb[2] * alpha);
                }
            }
            cv::imshow(_name, outMat);
        }
        catch(std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }
};
