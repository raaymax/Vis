find_package(CUDA REQUIRED)

set(matrix_srcs Matrix.cu)


cuda_add_library(libmatrix ${matrix_srcs})

