#include <cuda.h>
#include "GpuGrayFilter.h"
#include <exceptions/CudaException.h>

__global__ void process(uchar * data , int size){
	int i = blockDim.x * blockIdx.x + threadIdx.x;
	i*=3;
	data[i]=data[i+1]=data[i+2]=(data[i]+data[i+1]+data[i+2])/3;
}


// exported function, usable in the C++ part
extern "C" void runProcess(uchar* data , int size) {
	int nDevices;
	cudaGetDeviceCount(&nDevices);
	if(nDevices < 1) throw CudaException(CudaException::NODEVICE);
	
	int n = size/3;
	size_t size_ = size * sizeof(uchar);
	uchar* data_;
	

	cudaMalloc((void**)&data_, size_);
	cudaMemcpy(data_, data, size_, cudaMemcpyHostToDevice);

	int threadsPerBlock = 256;
	int blocksPerGrid = (n+threadsPerBlock-1) / threadsPerBlock;
	
	process<<<blocksPerGrid, threadsPerBlock>>>(data_, size_);

	cudaMemcpy(data, data_, size, cudaMemcpyDeviceToHost);
	
	cudaFree(data_);

}



GpuGrayFilter::GpuGrayFilter()
{

}

void GpuGrayFilter::process(Image & img){
	runProcess(img.data() , img.size());
}

GpuGrayFilter::~GpuGrayFilter()
{

}

