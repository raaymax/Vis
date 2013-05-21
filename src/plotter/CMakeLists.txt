find_package(Qt4 REQUIRED COMPONENTS QtCore QtGui)

include(${QT_USE_FILE})

set(CMAKE_AUTOMOC TRUE)

set(plotter_srcs Points.cpp Plot.cpp Plotter.cpp)
set(plotter_hdrs Points.h Plot.h Plotter.h)

foreach(head ${plotter_hdrs})
    configure_file(${head} ${PROJECT_BINARY_DIR}/Include/plotter/${head} COPYONLY)
endforeach(head)


INCLUDE_DIRECTORIES(${PROJECT_BINARY_DIR}/Include ${QT_INCLUDE_DIR} ${QT_QTGUI_INCLUDE_DIR} )




#ADD_DEFINITIONS(${QT_DEFINITIONS})


add_library(plotter ${plotter_srcs})

TARGET_LINK_LIBRARIES( plotter
   ${QT_LIBRARIES}
   ${QT_QTQUI_LIBRARIES}
)
