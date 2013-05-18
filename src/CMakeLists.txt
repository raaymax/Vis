find_package(Boost REQUIRED)
find_package(Qt4 REQUIRED)


find_package(CUDA)

INCLUDE(${QT_USE_FILE})

configure_file ( "${CMAKE_CURRENT_SOURCE_DIR}/config.h.in" "${PROJECT_BINARY_DIR}/config.h")

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

set(Viss_SRCS    
    Image.cpp 
    ImageFactory.cpp 
    ImageSource.cpp 
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


if(CUDA_FOUND)
    CUDA_ADD_EXECUTABLE(${CMAKE_PROJECT_NAME} ${Viss_UI_HDRS}  ${Viss_SRCS} ${Viss_CUDA_SRCS})
else(CUDA_FOUND)
    ADD_EXECUTABLE(${CMAKE_PROJECT_NAME} ${Viss_UI_HDRS} ${Viss_SRCS})
endif(CUDA_FOUND)

target_link_libraries(${CMAKE_PROJECT_NAME} ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} plotter)


add_subdirectory(libs/plotter)
add_subdirectory(filters)
