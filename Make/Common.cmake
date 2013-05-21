
set(INCLUDES 
	${CMAKE_CURRENT_SOURCE_DIR}
	${PROJECT_SOURCE_DIR}/src 
	${PROJECT_BINARY_DIR}/Include 
)


function( add_includes )
	include_directories(${ARGV} ${INCLUDES})
endfunction(add_includes)
