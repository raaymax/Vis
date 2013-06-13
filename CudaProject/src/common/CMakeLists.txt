file(GLOB_RECURSE files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.h")

INCLUDE_DIRECTORIES(${PROJECT_BINARY_DIR}/Include)

foreach(file ${files})
	configure_file(${file} ${PROJECT_BINARY_DIR}/Include/${file} COPYONLY)
endforeach(file)
