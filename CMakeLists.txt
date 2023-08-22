# 1.子目录可以使用父目录的变量名，反过来则不行
# 2.启用测试以及测试内容要写在根目录下的CMakeLists.txt中

cmake_minimum_required(VERSION 3.15)
project(poseGraphOpt)

set(CMAKE_BUILD_TYPE Release)
set(COMPILE_FEATURES_LIB compilerFlag)
set(G2O_SLAM_TARGET g2oSE3)
set(G2O_MYSELF_TARGET g2oMyself)
option(USE_MYSELF "use myself define or not" ON)

add_subdirectory(
        g2oSE3/
)
add_subdirectory(
        g2oMyself/
)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
list(APPEND G2O_LIBS g2o_core g2o_stuff g2o_types_slam3d)
find_package(G2O REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(Sophus REQUIRED)


add_library(${COMPILE_FEATURES_LIB} INTERFACE)
target_compile_features(
        ${COMPILE_FEATURES_LIB} INTERFACE cxx_std_14
)

message(STATUS G2O_FOUND: ${G2O_FOUND})
message(STATUS G2O_INCLUDE_DIR: ${EIGEN3_INCLUDE_DIR})

message(STATUS EIGEN3_FOUND: ${EIGEN3_FOUND})
message(STATUS Eigen3_INCLUDE_DIR: ${EIGEN3_INCLUDE_DIR})


target_link_libraries(
        ${COMPILE_FEATURES_LIB}
        INTERFACE ${G2O_LIBS}
        INTERFACE Sophus::Sophus
)

target_include_directories(
        ${COMPILE_FEATURES_LIB}
        INTERFACE ${EIGEN3_INCLUDE_DIR}
        INTERFACE ${G2O_INCLUDE_DIR}
        INTERFACE ${Sophus_INCLUDE_DIR}
)

add_executable(
        ${PROJECT_NAME}
        main.cpp
)

target_link_libraries(
        ${PROJECT_NAME}
        PRIVATE g2oSE3
        PRIVATE ${COMPILE_FEATURES_LIB}
)

target_include_directories(
        ${PROJECT_NAME}
        PRIVATE g2oSE3/include
)

if (${USE_MYSELF})
    target_compile_definitions(
            ${G2O_SLAM_TARGET}
            PRIVATE USE_MYSELF
    )
endif ()


#enable_testing()

#add_test(
#        NAME Usage
#        COMMAND g2oSE3
#)
#
#add_test(
#        NAME g2oSE3
#        COMMAND g2oSE3 ../../res/sphere.g2o 10 ../../result/result.g2o
#)
#
#set_tests_properties(
#        g2oSE3 PROPERTIES
#        PASS_REGULAR_EXPRESSION "saving .* ..."
#)
#
#set_tests_properties(
#        Usage PROPERTIES
#        PASS_REGULAR_EXPRESSION "Usage.*"
#)