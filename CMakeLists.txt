project(Viss)
cmake_minimum_required(VERSION 2.6)
find_package(Boost REQUIRED)
find_package(Qt4 REQUIRED)
find_package(CUDA REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

set(Viss_SRCS Image.cpp ImageFactory.cpp CpuGrayFilter.cpp GpuGrayFilter.cu ImageSource.cpp VImageWidget.cpp main.cpp )
qt4_automoc(${Viss_SRCS})
CUDA_ADD_EXECUTABLE(Viss ${Viss_SRCS})
target_link_libraries(Viss ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
install(TARGETS Viss RUNTIME DESTINATION bin)
