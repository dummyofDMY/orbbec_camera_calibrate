cmake_minimum_required(VERSION 3.1.15)
project(test)

set(OrbbecSDK2_LIBRARY_DIRS ./lib)
set(OrbbecSDK2_LIBS OrbbecSDK2)
set(OrbbecSDK2_INCLUDE_DIR ./include)
include_directories(${OrbbecSDK2_INCLUDE_DIR})
link_directories(${OrbbecSDK2_LIBRARY_DIRS})

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(grasp CamerasStream.cpp)
target_link_libraries(grasp OrbbecSDK2 ${OrbbecSDK2_LIBS} ${OpenCV_LIBS})
target_include_directories(grasp PRIVATE ${OrbbecSDK_INCLUDE_DIR})

add_executable(calibrate Internal_cali.cpp)
target_link_libraries(calibrate ${OpenCV_LIBS})