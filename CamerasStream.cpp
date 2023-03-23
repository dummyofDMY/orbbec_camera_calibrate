#include "hpp/OB2Context.hpp"
#include "hpp/preheader.hpp"
#include "hpp/window.hpp"
#include <iostream>
#include <sstream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

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

int main(int argc, char **argv) TRY_EXECUTE {
    // Create context
    auto ctx = std::make_shared<ob2::context>();

    // Open default device
    auto dev = ctx->open_device(OB2_DEFAULT_DEVICE);

    // Open camera (use default configuration, the default configuration will open Color, Depth, Ir camera data stream)
    dev->start_cameras(OB2_DEFAULT_CAMERAS_CONFIG);

    // Create a window for rendering and set the resolution of the window
    //Window win("DefaultViewer", 1470, 360);

    std::cerr << "Into loop" << std::endl;
    char key = 0;
    int count = 0;
    do {
        // Get capture
        std::shared_ptr<ob2::capture> capture = nullptr;
        try {
            // Timeout is set to 100ms
            capture = dev->get_capture(100);
        }
        catch(const std::runtime_error &e) {
            // Maybe timeout
            std::cerr << "Get capture failed! msg=" << e.what() << std::endl;
            continue;
        }

        // Get color_image
        std::shared_ptr<ob2::image> color_image = capture->get_color_image();

        // Get depth_image
        //std::shared_ptr<ob2::image> depth_image = capture->get_depth_image();

        // Get ir_image
        //std::shared_ptr<ob2::image> ir_image = capture->get_ir_image();

        // Render image
        //win.render({ color_image, depth_image, ir_image }, RENDER_ONE_ROW);

        auto mats = processImages({color_image});
        cv::namedWindow("show", cv::WINDOW_NORMAL);
        for (auto im : mats) {
            cv::Mat tem;
            im.copyTo(tem);
            std::stringstream count_str;
            count_str << count;
            cv::putText(tem, count_str.str(), cv::Point(100, 200), cv::FONT_HERSHEY_SIMPLEX, 5, cv::Scalar(255, 0, 0), 5);
            cv::imshow("show", tem);
            key = cv::waitKey(22);
            // std::cout << key << std::endl;
            if ('q' == key) {
                break;
            }
            else if ('s' == key) {
                std::ostringstream buff;
                buff << "../imgs/" << count << ".jpg";
                if (!cv::imwrite(buff.str(), im, std::vector<int>({cv::IMWRITE_JPEG_QUALITY, 100}))) {
                    std::cout << "\nFail to write the file" << std::endl;
                }
                else {
                    ++count;
                }
            }
        }
    } while (!('q' == key || 'Q'== key));

    // Stop camera
    dev->stop_cameras();

    return 0;
}
CATCH_EXCEPTIONS()
