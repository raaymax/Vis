#ifndef IMATRIX_H_
#define IMATRIX_H_
#include <iostream>
#include "ISimpleImage.h"

template <class T>
class IMatrix{
public:
	IMatrix();
	IMatrix(uint x, uint y);
	typedef T MType;
	virtual const uint getWidth()const;
	virtual const uint getHeight()const;
	
	virtual void set(int x , int y, T value)=0;
	virtual T & get(int x , int y)=0;

	uint getCount();
	uint getSize();
protected:
	
	void normalizeXY(int & x,int & y);

	uint width;
	uint height;
	
	T * matrix;
};
template <class T>
IMatrix<T>::IMatrix():width(0),height(0),matrix(NULL){}

template <class T>
IMatrix<T>::IMatrix(uint x, uint y):width(x),height(y),matrix(new MType[x*y]()){}

template <class T>
const uint IMatrix<T>::getWidth()const{return width;}

template <class T>
const uint IMatrix<T>::getHeight()const{return height;}

template <class T>
void IMatrix<T>::normalizeXY(int & x,int & y){
	if(x<0)x=0;
	if(x>=width)x=width-1;
	if(y<0)y=0;
	if(y>=height)y=height-1;
}

template <class T>
uint IMatrix<T>::getCount(){
	return getWidth()*getHeight();
}

template <class T>
uint IMatrix<T>::getSize(){
	return getCount()*sizeof(MType);
}

#endif
