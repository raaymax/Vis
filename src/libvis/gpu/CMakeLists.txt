
find_package(CUDA)
find_package(Qt4 REQUIRED)


include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	${PROJECT_SOURCE_DIR}/src 
	${PROJECT_BINARY_DIR}/Include 
	${QT_INCLUDES}
)

set(srcs
GImage.cu
GImageTransform.cu
)

	
if(CUDA_FOUND)
	CUDA_ADD_library(libvis_gpu ${srcs})
else(CUDA_FOUND)
	add_library(libvis_gpu ${srcs})
endif(CUDA_FOUND)
