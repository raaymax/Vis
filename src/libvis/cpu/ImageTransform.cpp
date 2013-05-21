#include "ImageTransform.h"
#include <cstdio>

ImageTransform::ImageTransform(Image * img):
	img_(img)
{

}

ImageTransform::~ImageTransform()
{

}


void ImageTransform::stretch(int val){
	int newW = img_->width()+2*val;
	int newH = img_->height()+2*val;
	int newS = newW*newH*3;
	uchar * data = new uchar[newS]();
	for(int y = 0;  y<newH ; y++){
		for(int x = 0; x < newW ; x++){
			*((Pixel*)&data[y*newW*3+x*3]) = getPixel(x-val,y-val);
		}
	}
/*	for(int y = -val;  y<newH ; y++){
		for(int x = -val*3; x < newW*3 ; x+=3){
			data[y*newW+x] = getPixel(x,y);
			data[y*newW+x+1] = getPixel(x+1,y);
			data[y*newW+x+2] = getPixel(x+2,y);
		}
	}*/
	img_->width_ = newW;
	img_->height_=newH;
	img_->size_= newS;
	img_->data_.reset(data);
}

Pixel & ImageTransform::getPixel(int x, int y){
	if(x >=((int)img_->width())) x = img_->width()-1;
	if(x < 0) x = 0;
	if(y >=(int)img_->height()) y = img_->height()-1;
	if(y < 0) y = 0;
	return *((Pixel *)&img_->data()[y*img_->width()*3+x*3]);
}

