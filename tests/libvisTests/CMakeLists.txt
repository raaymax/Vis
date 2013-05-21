find_package(GTest REQUIRED)
find_package(Qt4 REQUIRED COMPONENTS QtCore QtGui)
find_package(CUDA REQUIRED)

include(${QT_USE_FILE})


include_directories(
	${QT_INCLUDES}
	${CMAKE_CURRENT_SOURCE_DIR}
	${PROJECT_SOURCE_DIR}/src
	${PROJECT_BINARY_DIR}/Include 
	${GTEST_INCLUDE_DIR}
)

#file(GLOB_RECURSE test_srcs tests/*.cpp)
file(GLOB test_srcs "*.cpp")
list(APPEND test_srcs testFunctions.cu)
#set(CMAKE_AUTOMOC TRUE)
cuda_add_executable(libvisTests ${test_srcs})
target_link_libraries(libvisTests 
	libvis
    ${GTEST_LIBRARIES} 
    ${GTEST_MAIN_LIBRARY}
	${QT_LIBRARIES}
	${QT_QTQUI_LIBRARIES}
)

