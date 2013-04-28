project(Vis)
cmake_minimum_required(VERSION 2.6)

find_package(Boost REQUIRED)
find_package(Qt4 REQUIRED)


find_package(CUDA)

INCLUDE(${QT_USE_FILE})
configure_file ( "${PROJECT_SOURCE_DIR}/config.h.in" "${PROJECT_BINARY_DIR}/config.h")


set(Viss_SRCS    
    Image.cpp 
    ImageFactory.cpp 
    CpuGrayFilter.cpp  
    ImageSource.cpp 
    ImageWidget.cpp 
    MainWindow.cpp 
    main.cpp
    )
    
set(Viss_CUDA_SRCS
    GpuGrayFilter.cu
    )
set(Viss_Uis
    MainWindow.ui
    )
set(CMAKE_AUTOMOC TRUE)
QT4_WRAP_UI(Viss_UI_HDRS ${Viss_Uis})
#qt4_automoc(${Viss_SRCS})

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

if(CUDA_FOUND)
    CUDA_ADD_EXECUTABLE(${CMAKE_PROJECT_NAME} ${Viss_UI_HDRS}  ${Viss_SRCS} ${Viss_CUDA_SRCS})
else(CUDA_FOUND)
    ADD_EXECUTABLE(${CMAKE_PROJECT_NAME} ${Viss_UI_HDRS} ${Viss_SRCS})
endif(CUDA_FOUND)

target_link_libraries(${CMAKE_PROJECT_NAME} ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} plotter_lib)
install(TARGETS ${CMAKE_PROJECT_NAME} RUNTIME DESTINATION bin)


add_subdirectory(plotter)
