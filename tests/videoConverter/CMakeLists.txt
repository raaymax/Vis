
find_package(Qt4 REQUIRED COMPONENTS QtCore QtGui)

include(${QT_USE_FILE})


include_directories(
	${PROJECT_BINARY_DIR}/Include
	${QT_INCLUDE_DIR}
	${QT_QTGUI_INCLUDE_DIR}
)

set(video_srcs  video.cpp)

set(CMAKE_AUTOMOC TRUE)
add_executable(video ${video_srcs})
target_link_libraries(video 
libvis
video_converter 
${QT_LIBRARIES}
${QT_QTQUI_LIBRARIES}
)

