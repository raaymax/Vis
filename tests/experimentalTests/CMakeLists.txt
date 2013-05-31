#find_package(GTest REQUIRED)
find_package(Qt4 REQUIRED COMPONENTS QtCore QtGui)
find_package(CUDA)
include(${QT_USE_FILE})


include_directories(
	${PROJECT_BINARY_DIR}/Include
	#    ${GTEST_INCLUDE_DIR}
	${QT_INCLUDE_DIR}
	${QT_QTGUI_INCLUDE_DIR}
)

#file(GLOB_RECURSE test_srcs tests/*.cpp)
file(GLOB test_srcs Matrix.cu exp.cu)

set(CMAKE_AUTOMOC TRUE)
cuda_add_executable(expTest ${test_srcs})
target_link_libraries(expTest 
plotter 
#    ${GTEST_LIBRARIES} 
#    ${GTEST_MAIN_LIBRARY}
${QT_LIBRARIES}
${QT_QTQUI_LIBRARIES}
)
