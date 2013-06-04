find_package(Qt4 REQUIRED COMPONENTS QtCore QtGui)
find_package(OpenCV REQUIRED)

include(${QT_USE_FILE})

set(CMAKE_AUTOMOC TRUE)

set(video_srcs VideoConverterWindow.cpp VideoConverter.cpp)
set(video_hdrs VideoConverterWindow.h VideoConverter.h)

set(video_ui VideoConverterWindow.ui)

set(CMAKE_AUTOMOC TRUE)
QT4_WRAP_UI(Video_UI_HDRS ${video_ui})


foreach(head ${video_hdrs})
    configure_file(${head} ${PROJECT_BINARY_DIR}/Include/video/${head} COPYONLY)
endforeach(head)


INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR} ${PROJECT_BINARY_DIR}/Include ${QT_INCLUDE_DIR} ${QT_QTGUI_INCLUDE_DIR} )


add_library(video_converter ${Video_UI_HDRS} ${video_srcs})

TARGET_LINK_LIBRARIES( video_converter
    plotter
   ${QT_LIBRARIES}
   ${QT_QTQUI_LIBRARIES}
   ${OpenCV_LIBS}
)
