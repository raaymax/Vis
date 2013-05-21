find_package(Qt4 REQUIRED)


include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	${PROJECT_SOURCE_DIR}/src 
	${PROJECT_BINARY_DIR}/Include 
	${QT_INCLUDES}
)

set(srcs
Image.cpp
ImageTransform.cpp
)


add_library(libvis_cpu ${srcs})

		
