#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "Matrix.h"
#include <cuda_runtime_api.h>
#define DEBUG

#ifdef DEBUG
#define debug() printf("%s:%d %s#%s\n",__FILE__,__LINE__,__FUNCTION__,cudaGetErrorString(cudaGetLastError()))
#else
#define debug() 
#endif

__global__ void cuda_randomize(Matrix x){
	int idx = blockDim.x*blockIdx.x + threadIdx.x;
	int idy = blockDim.y*blockIdx.y + threadIdx.y;
	int id = idy * x.width + idx;
	if(id < x.count)
		x.data[id] = id%256;
}

Matrix matrix_create(uint w, uint h , MatrixType type){
	Matrix m;
	m.width = w;
	m.height = h;
	m.type = type;
	m.size = w*h*sizeof(float);
	m.count = w*h;
	if(type == CPU){
		m.data = (float*)malloc(m.size);
		memset(m.data,0,m.size);
	}else{
		cudaMalloc(&m.data,m.size);
		debug();
		cudaMemset(m.data,0,m.size );
		debug();
	}

	return m;
}

void matrix_destroy(Matrix & A){
	if(A.type == CPU){
		free(A.data);
	}else{
		cudaFree(A.data);
		debug();
	}
	
	A.data = NULL;
	A.size = 0;
	A.data = 0;
	A.type = NONE;
}

void matrix_randomize(Matrix & m){
	assert(m.type != NONE);
	if(m.type == GPU){
		int dx=32,dy=32;
		while(m.height < dy) dy/=2;
		while(m.width < dx) dx/=2;
		dim3 t(dx,dy);
		dim3 b(m.width/32 , m.height/32);
		cuda_randomize<<<b,t>>>(m);
		debug();
	}else{
		for(int i = 0 ; i < m.width* m.height ; i++){
			m.data[i] = i%256;
		}
	}
}

Matrix matrix_copy(const Matrix & m, cudaMCKind kind){
	assert(m.type != NONE);
	Matrix nm;
	if(((int)kind)%2==1)
		nm = matrix_create(m.width,m.height,GPU);
	else
		nm = matrix_create(m.width,m.height,CPU);
	
	cudaMemcpy(nm.data,m.data,m.size, static_cast<cudaMemcpyKind>(kind));
	debug();
	return nm;
}

Matrix matrix_copy(const Matrix & m, MatrixType type){
	if(m.type == type){
		if(type==CPU){
			return matrix_copy(m,H2H);
		}else{
			return matrix_copy(m,D2D);
		}
	}else{
		if(type==CPU){
			return matrix_copy(m,D2H);
		}else{
			return matrix_copy(m,H2D);
		}
	}
}


void matrix_print(const Matrix &c){
	assert(c.type == CPU);
	for(int y = 0 ; y < c.height; y++){
		for(int x = 0 ; x < c.width ; x++){
			printf("%2.0f ",c.data[y*c.width + x]);
		}
		printf("\n");
	}
	printf("\n");
	debug();
}

__global__ 
void cuda_convolution(Matrix m , Matrix f, Matrix o){
	int idx = blockIdx.x*blockDim.x+threadIdx.x;
	int idy = blockIdx.y*blockDim.y+threadIdx.y;
	extern __shared__ float sm[];
	if(threadIdx.x < f.width && threadIdx.y < f.height) sm[threadIdx.y*f.width+threadIdx.x ] = f.data[threadIdx.y*f.width+threadIdx.x ];
	__syncthreads();
	int my = (f.height/2);
	int mx = (f.width/2);
	if(idy < m.height && idx < m.width){
		float r = 0.0;
		for(int y = -my ; y <= my ; y++){
			for(int x = -mx ; x <= mx; x++){
				if((y+idy) >= 0 && (y+idy) < m.height && (x+idx) >= 0 && (x+idx) < m.width)
					 r += m.data[(y+idy)*m.width+ x+idx]*sm[ (y+my)*f.width+x+mx ];
				
			}
		}
		o.data[idy*o.width+idx] = r;
	}
	
}

__global__
void cuda_normalize(Matrix m){
	int idx = blockIdx.x*blockDim.x+threadIdx.x;
	int idy = blockIdx.y*blockDim.y+threadIdx.y;
	if(idx < m.width && idy < m.height){
		m.data[idy*m.width+idx] = round(m.data[idy*m.width+idx]);
		if(m.data[idy*m.width+idx] < 0)
			m.data[idy*m.width+idx] = 0;
		else if(m.data[idy*m.width+idx] > 255)
			m.data[idy*m.width+idx] = 255;
	}
}



float matrix_convolution(int x, int y,const Matrix & A ,const Matrix &f){
	assert(A.type == CPU && f.type == CPU);
	float r = 0.0;
	for(int a = -(f.height/2) ; a <= (int)(f.height/2) ;a++ ){
		for(int b = -(f.width/2) ; b <= (int)(f.width/2) ;b++ ){
			if((y+a >= 0) && (y+a < A.height) && (x+b >= 0) && (x+b < A.width)){
				r += A.data[(y+a)*A.width+(x+b)]*f.data[(a+(f.height/2))*f.width+(b+(f.width/2))];
			}
		}
	}
	return r;
}


Matrix matrix_convolution(const Matrix & A ,const Matrix &f){
	assert(A.type != NONE && f.type != NONE);
	Matrix n;
	if(A.type == CPU){
		assert(f.type != GPU);
		
		float sum = 0;
		for(int i = 0 ; i < f.size/4 ; i++){
			sum += f.data[i];
		}
		n = matrix_create(A.width,A.height,CPU);
		for(int y = 0 ; y < A.height ;y++ ){
			for(int x = 0 ; x < A.width ;x++ ){
				n.data[y*n.width+x]= matrix_convolution(x, y,A ,f);
	/*			n.data[y*n.width+x] = round(n.data[y*n.width+x]);
				if(A.data[y*A.width+x] < 0)
					A.data[y*A.width+x]= 0;
				else if(A.data[y*A.width+x] > 255)
					A.data[y*A.width+x] = 255;
	*/
			}
		}
		
		
	}else{
		assert(f.type != CPU);
		n = matrix_create(A.width,A.height,GPU);
		//	convolution<<<dim3(8,8),dim3(32,32)>>>(A,f,n);
		int dx=32,dy=32;
		while(A.height < dy) dy/=2;
		while(A.width < dx) dx/=2;
		dim3 t(dx,dy);
		dim3 b((A.width+dx)/dx , (A.height+dy)/dy);
	//	printf("%d %d %d %d\n",dx,dy,(A.width+dx)/dx,(A.height+dy)/dy);
		cuda_convolution<<<b,t,f.size>>>(A,f,n);
	//	normalize<<<dim3(8,8),dim3(32,32)>>>(n);
		debug();
	}
	return n;
}

__global__ 
void cuda_divide(Matrix A , float val){
	int idx = blockIdx.x*blockDim.x+threadIdx.x;
	int idy = blockIdx.y*blockDim.y+threadIdx.y;
	if(idx < A.width && idy < A.height)
	A.data[idy*A.width+idx] /= val;
}

void matrix_divide(Matrix & A , float val){
	assert(A.type != NONE);
	if(A.type == CPU){
		for(int y = 0 ; y < A.height ;y++ ){
			for(int x = 0 ; x < A.width ;x++ ){
				A.data[y*A.width+x] /= val; 
			}
		}
	}else{
		int dx=32,dy=32;
		while(A.height < dy) dy/=2;
		while(A.width < dx) dx/=2;
		dim3 t(dx,dy);
		dim3 b((A.width+dx)/dx , (A.height+dy)/dy);
		cuda_divide<<<b,t>>>(A,val);
		debug();
	}
}

void matrix_normalize(Matrix & A){
	assert(A.type != NONE);
	if(A.type == CPU){
		for(int y = 0 ; y < A.height ;y++ ){
			for(int x = 0 ; x < A.width ;x++ ){
				A.data[y*A.width+x] = round(A.data[y*A.width+x]);
				if(A.data[y*A.width+x] < 0)
					A.data[y*A.width+x]= 0;
				else if(A.data[y*A.width+x] > 255)
					A.data[y*A.width+x] = 255;
			}
		}
	}else{
		int dx=32,dy=32;
		while(A.height < dy) dy/=2;
		while(A.width < dx) dx/=2;
		dim3 t(dx,dy);
		dim3 b(A.width/dx , A.height/dy);
		cuda_normalize<<<b,t>>>(A);
		debug();
	}
}

float matrix_sum(const Matrix &A){
	assert(A.type != NONE);
	float sum_=0.0;
	if(A.type == CPU){
		for(int i = 0 ; i< A.count ;i++ ){
			sum_ += A.data[i];
		}
	}else{
		//TODO: sumowanie elementow macierzy
	}
	return sum_;
}

__host__ __device__ 
float get(const Matrix & A , int x , int y){
	if(x < 0 )x = 0;
	if(y < 0 ) y=0;
	if(x >= A.width) x = A.width-1;
	if(y >= A.height) y = A.height-1;
	return A.data[y*A.width+x];
}
__global__
void cuda_resize(Matrix A , Matrix o){
	int idx = blockIdx.x*blockDim.x+threadIdx.x;
	int idy = blockIdx.y*blockDim.y+threadIdx.y;
	int nx = ((int)A.width - (int)o.width)/2;
	int ny = ((int)A.height - (int)o.height)/2;
	if(idx < o.width && idy < o.height)
	o.data[idy*o.width+idx] = get(A,idx+nx,idy+ny);
}

Matrix matrix_resize(const Matrix &A , uint width , uint height){
	assert(A.type != NONE);
	Matrix n;
	if(A.type == CPU){
		int nx = ((int)A.width - (int)width)/2;
		int ny = ((int)A.height - (int)height)/2;
		
		n = matrix_create(width,height,CPU);
		for(int y = 0 ; y < height ; y++){
			for(int x = 0 ; x < width ; x++){
			//	printf("%d %d\n",x+nx,y+ny);
				n.data[y*width+x] = get(A,x+nx,y+ny);
			}
		}
		
	}else{
		n = matrix_create(width,height,GPU);
		int dx=32,dy=32;
		while(n.height < dy) dy/=2;
		while(n.width < dx) dx/=2;
		dim3 t(dx,dy);
		dim3 b((n.width+dx)/dx , (n.height+dy)/dy);
		cuda_resize<<<b,t>>>(A,n);
		debug();
	}
	return n;
}

bool matrix_compare(const Matrix &A ,const Matrix &B){
	assert(A.type == CPU && A.type == B.type);
	if(A.width != B.width) return false; 
	if(A.height != B.height) return false; 
	if(A.size != B.size) return false; 
	if(memcmp(A.data,B.data,A.size)!=0)return false;
	return true;
}




