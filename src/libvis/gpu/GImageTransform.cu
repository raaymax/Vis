#include "GImageTransform.h"
#include "Common.h"
#include <cuda_runtime.h>
#include <cstdio>
__global__ void copy(float * from ,float * to,int size,int width,int height, int offset,int color){
	int id = blockDim.x * blockIdx.x + threadIdx.x;
	int x = id%(width)-offset;
	if(x<0) x=2-(-x-1)%3;
	if(x>=(width-2*offset)) x = width-2*offset-3+(x%3);
	
	int y = id/width-offset/3;
	if(y<0) y=0;
	if(y>=height-2*offset/3)y=height-2*offset/3-1;
	if(id < size)to[id] = (float)from[y*(width-2*offset) +x];
}

void GImageTransform::stretch(int val){
	int newH = img_->height()+2*val;
	int newW = img_->width()+2*val;
	int newSize = newH*newW*3;
	float * newMatrix;
	cudaMalloc(&newMatrix,newSize*sizeof(float));

	int threadsPerBlock = MAX_THREADS;
	int blocksPerGrid = (newSize+threadsPerBlock-1) / threadsPerBlock;
	copy<<<blocksPerGrid,threadsPerBlock>>>(img_->data(),newMatrix,newSize,newW*3,newH,val*3,0);
	/*
	float *buf;
	buf = new float[newSize]();
	cudaMemcpy(buf,newMatrix,newSize*sizeof(float),cudaMemcpyDeviceToHost);
	for(int i = 0 ; i < newSize ; i++){
		if(i%(newW*3)==0)printf("\n");
		if(i%3==0)printf(" ");
		printf("%3.0f ",buf[i]);
	}
	printf("\n");
	printf("\n");
	
	cudaMemcpy(buf,img_->data_,img_->size_*sizeof(float),cudaMemcpyDeviceToHost);
	for(int i = 0 ; i < img_->size_ ; i++){
		if(i%(img_->width_*3)==0)printf("\n");
		if(i%3==0)printf(" ");
		printf("%3.0f ",buf[i]);
	}
	printf("\n");
	printf("\n");
	*/
	cudaFree(img_->data_);
	delete img_->buf_;
	img_->buf_ = new uchar[newSize]();//kocham Wiewiórka
	img_->data_ = newMatrix;
	img_->width_ = newW;
	img_->height_ = newH;
	img_->size_ = newSize;
	 
}

GImageTransform::GImageTransform(GImage * img):
	img_(img)
{
	
}

GImageTransform::~GImageTransform()
{
	
}
