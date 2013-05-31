#file(GLOB files "*/*.[cpp|cu]")
#file(GLOB hdrs "*/*.[cpp|cu]")

find_package(CUDA)
find_package(Qt4 REQUIRED)


include_directories(
	${PROJECT_BINARY_DIR}/Include 
	${QT_INCLUDES}
)

set(files
	GrayFilter_cpu/CpuGrayFilter.cpp
	GrayFilter_gpu/GpuGrayFilter.cu
)
set(hdrs
GrayFilter_cpu/CpuGrayFilter.h
GrayFilter_gpu/GpuGrayFilter.h
FilterManager.h
)

#move_to_includes(${hdrs})

CUDA_ADD_LIBRARY(filters ${files})
#target_link_libraries(filters)

