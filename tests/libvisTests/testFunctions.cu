#include "testFunctions.h"


__global__ void KrandF( float * f, int size){
	int id = blockDim.x * blockIdx.x + threadIdx.x;
	if(id < size) f[id] = id%256;
}

void randomize(float * gpu , int size){
	int threads = 1024;
	int blocks = (size+threads-1)/threads;
	KrandF<<<blocks,threads>>>(gpu,size);
}

void randomizeU(uchar * cpu , int size){
	for(int i = 0 ; i < size ; i ++){
		cpu[i] = i%256;
	}
}

void printU(const uchar * data , int size){
	for(int i = 0 ; i < size ; i ++){
		printf("%d ",data[i]);
	}
	printf("\n");
}

void printPix(const uchar *data , int width , int height){
	for(int y = 0 ; y < height ; y++){
		for(int x = 0 ; x < width*3 ; x+=3){
			for(int i = 0 ; i < 3 ; i++){
				printf("%2d ",data[y*width*3+x+i]);
			}
			printf(" ");
		}
		printf("\n");
	}
	printf("\n");
	
}
