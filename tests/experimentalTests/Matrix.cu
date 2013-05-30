#include <stdio.h>
#include "Matrix.h"


__global__ void rand(Matrix x){
	int idx = blockDim.x*blockIdx.x + threadIdx.x;
	int idy = blockDim.y*blockIdx.y + threadIdx.y;
	int id = idy * x.width + idx;
	x.data[id] = id%256;
}

Matrix create(uint w, uint h , MatrixType type){
	Matrix m;
	m.width = w;
	m.height = h;
	m.type = type;
	m.size = w*h*sizeof(float);
	if(type == CPU){
		m.data = (float*)malloc(m.size);
		memset(m.data,0,m.size);
	}else{
		cudaMalloc(&m.data,m.size);
		cudaMemset(m.data,0,m.size );
	}
	return m;
}

void randomize(Matrix & m){
	if(m.type == GPU){
		int dx=32,dy=32;
		while(m.height < dy) dy/=2;
		while(m.width < dx) dx/=2;
		dim3 t(dx,dy);
		dim3 b(m.width/32 , m.height/32);
		rand<<<b,t>>>(m);
	}else{
		for(int i = 0 ; i < m.width* m.height ; i++){
			m.data[i] = i%256;
		}
	}
}

Matrix copy(const Matrix & m, cudaMemcpyKind kind){
	Matrix nm;
	if(kind == cudaMemcpyDeviceToHost || kind == cudaMemcpyHostToHost)
		nm = create(m.width,m.height,CPU);
	else
		nm = create(m.width,m.height,GPU);
	
	cudaMemcpy(nm.data,m.data,m.size, kind);
	return nm;
}


void print(const Matrix &c){
	for(int y = 0 ; y < c.height; y++){
		for(int x = 0 ; x < c.width ; x++){
			printf("%2.0f ",c.data[y*c.width + x]);
		}
		printf("\n");
	}
	printf("\n");
}
