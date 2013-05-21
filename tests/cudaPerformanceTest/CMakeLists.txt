find_package(Boost REQUIRED)
find_package(Qt4 REQUIRED)


find_package(CUDA)

INCLUDE(${QT_USE_FILE})

configure_file ( "${CMAKE_CURRENT_SOURCE_DIR}/config.h.in" "${CMAKE_CURRENT_BINARY_DIR}/config.h")

include_directories(
	${QT_INCLUDES}
	${CMAKE_CURRENT_BINARY_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}
	${PROJECT_BINARY_DIR}/Include
	${PROJECT_SOURCE_DIR}/src/libvis
)

set(Viss_SRCS    
    gui/ImageWidget.cpp 
    gui/MainWindow.cpp 
    main.cpp
    )

set(Viss_Uis
	gui/MainWindow.ui
    )

set(CMAKE_AUTOMOC TRUE)
QT4_WRAP_UI(Viss_UI_HDRS ${Viss_Uis})
#qt4_automoc(${Viss_SRCS})



ADD_EXECUTABLE(${CMAKE_PROJECT_NAME} ${Viss_UI_HDRS} ${Viss_SRCS})


target_link_libraries(${CMAKE_PROJECT_NAME} ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} plotter libvis filters)



