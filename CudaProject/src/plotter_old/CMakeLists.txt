
FIND_PACKAGE(Qt4 COMPONENTS QtCore QtGui REQUIRED)
INCLUDE(${QT_USE_FILE})

set(CMAKE_AUTOMOC TRUE)
SET(LIBRARIES ${LIBRARIES} ${QT_LIBRARIES})


set(plotter_src Plot.cpp Plotter.cpp)
add_library(plotter_lib ${plotter_src} )
TARGET_LINK_LIBRARIES(plotter_lib ${LIBRARIES})
