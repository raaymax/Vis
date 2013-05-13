
project(Test)
cmake_minimum_required(VERSION 2.8)

add_subdirectory(src/libs/plotter)


#find_package(GTest REQUIRED)
find_package(Qt4 REQUIRED COMPONENTS QtCore QtGui)

include(${QT_USE_FILE})


include_directories(
    ${PROJECT_BINARY_DIR}/Include
#    ${GTEST_INCLUDE_DIR}
    ${QT_INCLUDE_DIR}
    ${QT_QTGUI_INCLUDE_DIR}
    )

#file(GLOB_RECURSE test_srcs tests/*.cpp)
set(test_srcs src/main.cpp)


add_executable(Test ${test_srcs})
target_link_libraries(Test 
    plotter 
#    ${GTEST_LIBRARIES} 
#    ${GTEST_MAIN_LIBRARY}
    ${QT_LIBRARIES}
    ${QT_QTQUI_LIBRARIES}
    )


