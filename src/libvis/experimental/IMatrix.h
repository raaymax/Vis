#ifndef IMATRIX_H_
#define IMATRIX_H_
#include "ISimpleImage.h"

template <class T>
class IMatrix{
	virtual const uint getWidth()const;
	virtual const uint getHeight()const;
	
	virtual void set(int x , int y, T value)=0;
	virtual T & get(int x , int y)=0;
	virtual const T & get(int x , int y) const=0;
	virtual IMatrix<T> operator*(const IMatrix<T> &)=0;
	virtual IMatrix<T> & operator*=(const IMatrix<T> &)=0;
	virtual IMatrix<T> operator+(const IMatrix<T> &)=0;
	virtual IMatrix<T> & operator+=(const IMatrix<T> &)=0;
	virtual IMatrix<T> & operator=(const IMatrix<T> &)=0;
	virtual IMatrix<T> operator/(const T &)=0;
	virtual IMatrix<T> & operator/=(const T &)=0;
	virtual IMatrix<T> operator-(const T &)=0;
	virtual IMatrix<T> & operator-=(const T &)=0;
	
private:
	uint width;
	uint height;
	
	T * matrix;
};

const uint IMatrix::getWidth()const{return width;}
const uint IMatrix::getHeight()const{return height;}

#endif
