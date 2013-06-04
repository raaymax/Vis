#include "testFilter.h"

TestFilter::TestFilter(MatrixType t):type(t){
	const int n = 3;
	Matrix buf = matrix_create(n,n,CPU);
	debug("init done");
	buf.data[0] = 0.5;
	buf.data[2] = 0.5;
	buf.data[4] = 1.0;
	buf.data[6] = 0.5;
	buf.data[8] = 0.5;


	sum = matrix_sum(buf);
	debug("init done");
	test = matrix_copy(buf,t);
	matrix_destroy(buf);
	
}

void TestFilter::process(Image & img){
	debug("in");
	assert(img.getType() == type);
	img.resize(img.width()+2,img.height()+2);
	img.convolution(test);
	img.divide(sum);
	img.normalize();
	img.resize(img.width()-2,img.height()-2);
	debug("out");
}
