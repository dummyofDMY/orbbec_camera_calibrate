#include<opencv2/opencv.hpp>
#include<iostream>
#include<sstream>
#include<vector>
#include<fstream>

#define BOARD_COL 11 //棋盘格列数
#define BOARD_ROW 8 //棋盘格行数
#define SIDE_LENGTH 0.025 //格子边长，单位：m

int main()
{
    int count = 0;
    std::vector<std::vector<cv::Point2f> > im_points;
    std::vector<std::vector<cv::Point3f> > obj_points;
    cv::Size im_size;
    while (1) {
        std::stringstream buffer;
        buffer << "../imgs/" << count << ".jpg";
        cv::Mat im = cv::imread(buffer.str());
        ++count;
        if (im.empty()) {
            // std::cout << "Success in loading " << count << "picture" << std::endl;
            break;
        }
        // std::cout << "Success in loading im" << count << std::endl;
        im_size = im.size();
        std::vector<cv::Point2f> corners;
        if (!cv::findChessboardCornersSB(im, cv::Size(BOARD_COL, BOARD_ROW), corners, cv::CALIB_CB_EXHAUSTIVE | cv::CALIB_CB_ACCURACY)) {
            // std::cout << "This image is invalid" << std::endl;
            continue;
        }
        // std::cout << "Success in finding chessboard corners in im" << count << std::endl;
        im_points.push_back(corners);
        std::vector<cv::Point3f> obj_pt;
        for (int i = 0; i < BOARD_ROW; ++i) {
            for (int j = 0; j < BOARD_COL; ++j) {
                obj_pt.push_back(cv::Point3f(i * SIDE_LENGTH, j * SIDE_LENGTH, 0));
            }
        }
        obj_points.push_back(obj_pt);
        drawChessboardCorners(im, cv::Size(BOARD_COL, BOARD_ROW), corners, true);
        cv::namedWindow("out", cv::WINDOW_NORMAL);
        cv::imshow("out", im);
        cv::waitKey(0);
    }
    cv::Mat cam_mat, dist;
    std::vector<cv::Mat> rvecs, tvecs, rmat;
    cv::Mat cam_deviation, dist_deviation;
    std::vector<double> error;
    cv::calibrateCamera(obj_points, im_points, im_size, cam_mat, dist, rvecs, tvecs, cam_deviation, dist_deviation, error, 0, cv::TermCriteria(cv::TermCriteria::Type::COUNT + cv::TermCriteria::Type::EPS, 50, 1e-12));
    std::stringstream buffer;
    buffer << "Camera Matrix =\n";
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            buffer << cam_mat.at<double>(i, j) << " ";
        }
        buffer << "\n";
    }
    buffer << "Dist Coeffs =\n";
    for (int i = 0; i < 5; ++i) {
        buffer << dist.at<double>(0, i) << " ";
    }
    buffer << "\n";
    buffer << "Camera Matrix Deviation =\n";
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            buffer << cam_deviation.at<double>(i, j) << " ";
        }
        buffer << "\n";
    }
    buffer << "Dist Coeffs Deviation =\n";
    for (int i = 0; i < 5; ++i) {
        buffer << dist_deviation.at<double>(0, i) << " ";
    }
    buffer << "\n";
    buffer << "Re-projection Error:\n";
    double total_err = 0;
    int err_count = 0;
    for (auto tem_error : error) {
        buffer << tem_error << " ";
        total_err += tem_error;
        ++err_count;
    }
    buffer << "\n";
    buffer << "Average Error = " << total_err / err_count;
    std::cout << buffer.str() << std::endl;
    std::ofstream out("../result.txt");
    if (!out.is_open()) {
        std::cout << "Fail to open result.txt" << std::endl;
    }
    out << buffer.str() << std::endl;
    return 0;
}