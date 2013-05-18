file(GLOB files "*/*.[cpp|cu]")
file(GLOB hdrs "*/*.[cpp|cu]")
move_to_includes(${hdrs})

CUDA_ADD_LIBRARY(filters ${files})
#target_link_libraries(filters)

