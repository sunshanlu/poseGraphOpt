add_library(
        ${G2O_MYSELF_TARGET} SHARED
        src/EdgeSE3.cpp
        src/VertexSE3.cpp
)

target_link_libraries(
        ${G2O_MYSELF_TARGET}
        PUBLIC ${COMPILE_FEATURES_LIB}
)

target_include_directories(
        ${G2O_MYSELF_TARGET}
        PUBLIC include
)