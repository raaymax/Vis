#ifndef LIBVIS_GPU_COMMON_H_
#define LIBVIS_GPU_COMMON_H_

#include <cuda_runtime.h>
#include <cstdio>

static void HandleError( cudaError_t err, const char *file, int line ) {
	if (err != cudaSuccess) {
		printf( "%s in %s at line %d\n", cudaGetErrorString( err ), file, line);
		exit( EXIT_FAILURE );
	}
}
#define HANDLE_ERROR( err ) (HandleError( err, __FILE__, __LINE__ ))

#define MAX_THREADS 1024

#endif  // LIBVIS_GPU_COMMON_H_
