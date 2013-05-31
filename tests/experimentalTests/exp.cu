#include <cuda_runtime.h>
#include <plotter/Plotter.h>
#include <QApplication>
#include "Matrix.h"
#include <boost/date_time/posix_time/posix_time.hpp>


__global__ 
void convolution(Matrix m , Matrix f, Matrix o){
	int idx = blockIdx.x*blockDim.x+threadIdx.x;
	int idy = blockIdx.y*blockDim.y+threadIdx.y;
	__shared__ float sm[5][5];
	if(idx < 5 && idy < 5) sm[idx][idy] = f.data[idy*5+idx];
	__syncthreads();
	for(int x = -2 ; x < 3 ; x++){
		for(int y = -2 ; y < 3 ; y++){
			if((y+idy) > 0 && (y+idy) < m.height && (x+idx) > 0 && (x+idx) < m.width)
				o.data[idy*m.width+idx] += m.data[(y+idy)*m.width+x+idx]*sm[2+y][2+x];
		}
	}
}

void function1(){
	Matrix i = create(32,32);
	randomize(i);
	printf("%s\n",cudaGetErrorString(cudaGetLastError()));
	
	Matrix o = create(32,32);
	Matrix f = create(5,5,CPU);
	f.data[2*f.width + 2] = 1;
	f.data[0*f.width + 2] = 0.5;
	f.data[4*f.width + 2] = 0.5;
	Matrix cf = copy(f,cudaMemcpyHostToDevice);
	convolution<<<dim3(8,8),dim3(32,32)>>>(i,cf,o);
	printf("%s\n",cudaGetErrorString(cudaGetLastError()));
	Matrix c = copy(o,cudaMemcpyDeviceToHost);
	printf("%s\n",cudaGetErrorString(cudaGetLastError()));
	for(int y = 0 ; y < c.height; y++){
		for(int x = 0 ; x < c.width ; x++){
			printf("%2.0f ",c.data[y*c.width + x]);
		}
		printf("\n");
	}
	printf("\n");
	
}

Matrix conv(const Matrix & A ,const Matrix &f){
	printf("%s",__FUNCTION__);
	Matrix n;
	if(A.type == CPU){
		printf("OK");
		if(f.type == GPU){
			printf("WTF2");
			throw;
		}
		n = create(A.width,A.height,CPU);
		for(int y = f.height/2 ; y < A.height-f.height/2 ;y++ ){
			for(int x = f.width/2 ; x < A.width-f.width/2 ;x++ ){
				for(int a = -(f.height/2) ; a < f.height/2 ;a++ ){
					for(int b = -(f.width/2) ; b < f.width/2 ;b++ ){
						if((y+a > 0) && (y+a < A.height) && (x+b > 0) && (x+b < A.width)){
							n.data[y*n.width+x] += A.data[(y+a)*A.width+(x+b)]*f.data[a*f.width+b];
						
							printf(".");
						}else{
							printf("%d %d",y+a,x+b);
						}
						printf("b");
					}
					printf("a");
				}
				printf("x");
			}
			printf("y");
		}
		
	}else{
		printf("WTF");
	}
	return n;
}

boost::posix_time::time_duration process(void (*func)()){
	boost::posix_time::ptime mst1 = boost::posix_time::microsec_clock::local_time();
	func();
	boost::posix_time::ptime mst2 = boost::posix_time::microsec_clock::local_time();
	return (mst2 - mst1);
}



int main(int argc , char ** argv){
//	QApplication app(argc,argv);
//	Plotter plotter;
//	Plot * p = plotter.createPlot(Qt::red);
//	plotter.show();
	for(int i = 0 ; i < 1 ; i++){
//		p->add(process(function1).total_milliseconds());
	}
	Matrix a = create(256,256,CPU);
	randomize(a);
	Matrix f = create(5,5,CPU);
	f.data[2*f.width+2]=1.0;
	Matrix c = conv(a,f);
//	print(c);

//	return app.exec();
}
