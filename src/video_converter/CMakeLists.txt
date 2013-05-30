find_package(Qt4 REQUIRED COMPONENTS QtCore QtGui)
find_package(OpenCV REQUIRED)

include(${QT_USE_FILE})

set(CMAKE_AUTOMOC TRUE)

set(video_srcs VideoConverter.cpp)
set(video_hdrs VideoConverter.h)

foreach(head ${plotter_hdrs})
    configure_file(${head} ${PROJECT_BINARY_DIR}/Include/video/${head} COPYONLY)
endforeach(head)


INCLUDE_DIRECTORIES(${PROJECT_BINARY_DIR}/Include ${QT_INCLUDE_DIR} ${QT_QTGUI_INCLUDE_DIR} )


add_library(video_converter ${video_srcs})

TARGET_LINK_LIBRARIES( video_converter
   ${QT_LIBRARIES}
   ${QT_QTQUI_LIBRARIES}
   ${OpenCV_LIBS}
)
