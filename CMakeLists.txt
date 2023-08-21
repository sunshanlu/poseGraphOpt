cmake_minimum_required(VERSION 3.15)
project(poseGraphOpt)

set(CMAKE_BUILD_TYPE Release)
add_subdirectory(
    g2oSE3/
)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
list(APPEND G2O_LIBS g2o_core g2o_stuff g2o_types_slam3d)
find_package(G2O REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(Sophus REQUIRED)


add_library(compilerFlag INTERFACE)
target_compile_features(
        compilerFlag INTERFACE cxx_std_14
)

message(STATUS G2O_FOUND: ${G2O_FOUND})
message(STATUS G2O_INCLUDE_DIR: ${EIGEN3_INCLUDE_DIR})

message(STATUS EIGEN3_FOUND: ${EIGEN3_FOUND})
message(STATUS Eigen3_INCLUDE_DIR: ${EIGEN3_INCLUDE_DIR})


target_link_libraries(
        compilerFlag
        INTERFACE ${G2O_LIBS}
        INTERFACE Sophus::Sophus
)

target_include_directories(
        compilerFlag
        INTERFACE ${EIGEN3_INCLUDE_DIR}
        INTERFACE ${G2O_INCLUDE_DIR}
        INTERFACE ${Sophus_INCLUDE_DIR}
)

enable_testing()

add_test(
        NAME Usage
        COMMAND g2oSE3
)

add_test(
        NAME g2oSE3
        COMMAND g2oSE3 ../../res/sphere.g2o 10 ../../result/result.g2o
)

set_tests_properties(
        g2oSE3 PROPERTIES
        PASS_REGULAR_EXPRESSION "saving .* ..."
)

set_tests_properties(
        Usage PROPERTIES
        PASS_REGULAR_EXPRESSION "Usage.*"
)