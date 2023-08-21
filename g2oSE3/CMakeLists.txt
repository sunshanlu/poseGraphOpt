include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)

set(targetName g2oSE3)

add_executable(
        ${targetName}
        src/main.cpp
        src/g2oSE3.cpp
)

target_link_libraries(
        ${targetName}
        PRIVATE compilerFlag
)