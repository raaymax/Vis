
set(INCLUDES ${PROJECT_BINARY_DIR}/Include)

function( move_to_includes )
    foreach(file ${ARGV})
        get_filename_component(fname ${file} NAME)
        configure_file(${file}  ${INCLUDES}/${fname} COPYONLY)
    endforeach(file)
endfunction( move_to_includes )


function (ADD_EXE)
    if(CUDA_FOUND)
        CUDA_ADD_EXECUTABLE(${CMAKE_PROJECT_NAME} ${Viss_UI_HDRS}  ${Viss_SRCS} ${Viss_CUDA_SRCS})
    else(CUDA_FOUND)
        ADD_EXECUTABLE(${CMAKE_PROJECT_NAME} ${Viss_UI_HDRS} ${Viss_SRCS})
    endif(CUDA_FOUND)
endfunction (ADD_EXE)
