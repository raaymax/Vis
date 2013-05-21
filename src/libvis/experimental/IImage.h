#ifndef IIMAGE_H_
#define IIMAGE_H_
#include "IMatrix.h"
#include "ISimpleImage.h"


template<class T>
class IImage{
public:
	typedef enum {BLACK=0,RED=1,GREEN=2,BLUE=3} color_t; 
	typedef enum {BLACK=1,COLOR=3} channel_t; 
	typedef enum {GPU=1,CPU=2} proc_t; 
	
	virtual T & getValue(color_t c, int x, int y);
	virtual const T & getValue(color_t c, int x, int y) const;
	virtual IMatrix<T> & getMatrix(color_t c); //TODO: throw brak koloru
	virtual const IMatrix<T> & getMatrix(color_t c) const; //TODO: throw brak koloru
	virtual const uint getWidth()const;
	virtual const uint getHeight()const;
	virtual void loadFromSimpleImage(const ISimpleImage &)=0;
	virtual ISimpleImage getSimpleImage()=0;
	virtual const ISimpleImage getSimpleImage() const;
	virtual proc_t getProc()=0;
private:
	uint width;
	uint height;
	channel_t channel;
	IMatrix<T> * M;
};
template<class T>
T & IImage::getValue(color_t c, int x, int y){
	return getMatrix(c).get(x,y);
}
template<class T>
const T & IImage::getValue(color_t c, int x, int y) const{
	return getValue(c,x,y);
}

template<class T>
IMatrix<T> & IImage::getMatrix(color_t c){ //TODO: throw brak koloru
	if(channel == BLACK){
		return M[0];
	}else if(channel == COLOR){
		switch(c){
			case RED:
				return M[0];
				break;
			case GREEN:
				return M[1];
				break;
			case BLUE:
				return M[2];
				break;
		}
	}
}

virtual const IMatrix<T> & getMatrix(color_t c) const{
	return getMatrix(c)
}
template<class T>
const uint IImage::getWidth()const{return width;}

template<class T>
const uint IImage::getHeight()const{return height;}

template<class T>
const ISimpleImage getSimpleImage() const{
	return getSimpleImage();
}

#endif
