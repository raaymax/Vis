find_package(CUDA)
find_package(Qt4 REQUIRED)


add_subdirectory(matrix)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	${PROJECT_SOURCE_DIR}/src 
	${PROJECT_BINARY_DIR}/Include 
	${QT_INCLUDES}
)

set(srcs
	Image.cpp
	ImageFactory.cpp
	ImageSource.cpp
	testFilter.cpp
)
set(cuda_srcs
	
)

file(GLOB_RECURSE files "*.h")
foreach(file ${files})
	get_filename_component(fname ${file} NAME)
	configure_file(${file} ${PROJECT_BINARY_DIR}/Include/${fname} COPYONLY)
endforeach(file)
	
if(CUDA_FOUND)
	CUDA_ADD_library(libvis ${srcs}  ${cuda_srcs})
else(CUDA_FOUND)
	add_library(libvis ${srcs})
endif(CUDA_FOUND)

target_link_libraries(libvis libmatrix)# libvis_gpu)


#add_subdirectory(gpu)

#add_subdirectory(cpu)



