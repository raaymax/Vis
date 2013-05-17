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
set(test_srcs MainWindow.cpp main.cpp)

set(CMAKE_AUTOMOC TRUE)
add_executable(PlotterTest ${test_srcs})
target_link_libraries(PlotterTest 
	plotter 
	#    ${GTEST_LIBRARIES} 
	#    ${GTEST_MAIN_LIBRARY}
	${QT_LIBRARIES}
	${QT_QTQUI_LIBRARIES}
)

