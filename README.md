# 相机标定程序

## 简介
    本程序针对奥比中光的Astra Pro深度相机的RGB相机进行标定，以获取相机内参矩阵以及五个畸变系数。本程序采用C++语言，涉及的非标准库主要有奥比中光的官方相机驱动库（已包含在文件中并配置好CMake），以及OpenCV4.7.0（在本人的计算机上已配置好库和CMake，使用时CMake的OpenCV部分可能要有些改动）。

## 使用方法
### 编译程序
    - 拉取之后如工作目录没有名为imgs的文件夹的话要先创建，配置好环境后在build文件夹中打开终端，执行以下指令
    ```
        cmake ..
        make
    ```
### 图像采集
    - 首先执行图像采集在build下的终端里执行
    ```
        ./grasp
    ```
    移动相机或标定板使标定板完整地出现在视野中，光标聚焦于OpenCV窗口后，按下's'（注意得是小写）后将把当前捕获的图像存至imgs文件夹中，图像左上角的数字是已捕获的照片数（这个数字不会出现在捕获的图像中，不会影响标定板的识别），不断改变标定板在视野中的姿态，通过按下's'来拍摄图片，收集至少20张，收集完后按下'q'以正常关闭相机并退出程序。
### 相机内参计算
    - 在Internal_cali.cpp文件中根据使用的标定板修改参数，参数含义代码内有注释。
    - 同样在build文件夹下的终端里运行可执行文件：
    ```
        ./calibrate
    ```
    执行该指令后计算机将自动运行标定代码。 ** 注意：可能有一些相片识别不出所有棋盘格，这样的图片不会被纳入计算，每张有效的图片都会在窗口依次展示，展示时程序会暂停，按下任意键继续 ** 执行完毕后会在终端依次输出相机内参、畸变系数、内参偏差估计值、畸变系数偏差估计值、每张图片的重投影误差及平均重投影误差，同时这些内容也会输出在工作目录下的result.txt中

## clean工具
    如需要清理imgs内的图片，可以运行clear.sh脚本。在工作目录打开终端，输入以下指令：
    ```
        sh clear.sh
    ```
    要执行sh文件不同的电脑可能会有不同的问题，如不幸遭遇，可上网搜索解决方案