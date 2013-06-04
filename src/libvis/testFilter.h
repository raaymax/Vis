#ifndef TESTFILTER_H_
#define TESTFILTER_H_

#include <Image.h>

class TestFilter{
public:
	TestFilter(MatrixType t);
	void process(Image & img);
private:
	MatrixType type;
	float sum;
	Matrix test;
};

#endif
