#include "testFilter.h"
#include <QDebug>
#include <QColor>
TestFilter::TestFilter(MatrixType t):type(t){
	const int n = 3;
	Matrix buf = matrix_create(n,n,CPU);
	debug("init done");
	buf.data[0] = -0.5;
	buf.data[1] = -1.0;
	buf.data[2] = -0.5;
	
	buf.data[3] = -1.0;
	buf.data[4] = 6.0;
	buf.data[5] = -1.0;
	
	buf.data[6] = -0.5;
	buf.data[7] = -1.0;
	buf.data[8] = -0.5;

	
	sum = matrix_sum(buf);
	//if(sum <= 0) cor = 127; else cor=0;
	if(sum <= 0) sum = 1;
	debug("init done");
	test = matrix_copy(buf,t);
	matrix_destroy(buf);
	
}

void TestFilter::process(Image & img){
	debug(img.getType() == CPU?"in CPU":"in GPU");
	assert(img.getType() == type);
	img.resize(img.width()+2,img.height()+2);
	img.convolution(test);
	img.divide(sum);
	img.normalize();
	img.resize(img.width()-2,img.height()-2);
	debug("out");
}
