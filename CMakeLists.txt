project(Vis)
cmake_minimum_required(VERSION 2.8)

include(Make/Common.cmake)

set(COMPILE_MAIN 0)
add_subdirectory(src)
add_subdirectory(tests/plotterTest)

#add_subdirectory(tests/libvisTests)
add_subdirectory(tests/cudaPerformanceTest)
add_subdirectory(tests/cudaDeviceQuery)

add_subdirectory(tests/experimentalTests)
