#include <cuda.h>
#include "GImage.h"
#include <cstdio>
#include "Common.h"

__global__ void Kzero(float * f, int size){
	int id = blockDim.x * blockIdx.x + threadIdx.x;
	if(id < size) f[id] = 0.0;
}

__global__ void KcopyFU(float * f, uchar * u , int size){
	int id = blockDim.x * blockIdx.x + threadIdx.x;
	if(id < size) u[id] = (uchar)f[id];
}
__global__ void KcopyUF( uchar * u, float * f, int size){
	int id = blockDim.x * blockIdx.x + threadIdx.x;
	if(id < size) f[id] = (float)u[id];
}



GImage::GImage():
	width_(0),
	height_(0),
	size_(0),
	data_(NULL)
{
	buf_ = NULL;
}

GImage::GImage(uint w, uint h):
	width_(w),
	height_(h),
	size_(w*h*3)
{
	int threads = MAX_THREADS;
	int blocks = (size_+threads-1)/threads;
	cudaMalloc(&data_,size_*sizeof(float));
	Kzero<<<blocks,threads>>>(data_,size_);
	
	buf_ = new uchar[size_]();
}
GImage::GImage(const GImage& other){
	width_ = other.width();
	height_ = other.height();
	size_ = other.size();
	cudaMalloc(&data_,size_*sizeof(float));
	cudaMemcpy(data_,other.data(),size_*sizeof(float),cudaMemcpyDeviceToDevice);
	buf_ = new uchar[size_]();
}

GImage::GImage(const IImage& other){
	width_ = other.width();
	height_ = other.height();
	size_ = other.size();
	buf_ = new uchar[size_]();
	cudaMalloc(&data_,size_*sizeof(float));
	
	uchar * buf;
	cudaMalloc(&buf,size_);
	cudaMemcpy(buf, other.constData() , size_ , cudaMemcpyHostToDevice);
	int threads = MAX_THREADS;
	int blocks = (size_+threads-1)/threads;
	KcopyUF<<<blocks,threads>>>(buf,data_,size_);
	cudaFree(buf);
}

uint GImage::width()const{
	return width_;
}
uint GImage::height()const{
	return height_;
}
uint GImage::size() const{
	return size_;
}
float * GImage::data(){
	return data_;
}
const float * GImage::data() const{
	return data_;
}
const uchar * GImage::constData() const{
	if(data_==NULL){
		return NULL;
	}else{
		int threads = MAX_THREADS;
		int blocks = (size_+threads-1)/threads;
		uchar * buf;
		cudaMalloc(&buf,size_);
		KcopyFU<<<blocks,threads>>>(data_,buf,size_);
		cudaMemcpy(buf_,buf,size_,cudaMemcpyDeviceToHost);
		cudaFree(buf);
		return buf_;
	}
}

