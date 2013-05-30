project(Vis)
cmake_minimum_required(VERSION 2.8)

include(Make/Common.cmake)

option(USE_CUDA "Use CUDA computing" ON)

add_subdirectory(src/common)
add_subdirectory(src/video_converter)
add_subdirectory(src/plotter)
add_subdirectory(tests/plotterTest)


if(USE_CUDA)
    add_subdirectory(src/libvis)
    add_subdirectory(tests/libvisTests)
    add_subdirectory(tests/cudaPerformanceTest)
    add_subdirectory(tests/cudaDeviceQuery)
	add_subdirectory(tests/experimentalTests)
endif(USE_CUDA)
