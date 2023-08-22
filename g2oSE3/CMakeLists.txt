include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(
        ${G2O_SLAM_TARGET}
        src/g2oSE3.cpp
)

target_link_libraries(
        ${G2O_SLAM_TARGET}
        PUBLIC ${G2O_MYSELF_TARGET}
        PUBLIC ${COMPILE_FEATURES_LIB}
)

target_include_directories(
        ${G2O_SLAM_TARGET}
        PUBLIC include/
        PUBLIC ${PROJECT_SOURCE_DIR}/g2oMyself/include
)