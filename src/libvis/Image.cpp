#include <QColor>
#include "Image.h"
#include <QDebug>

Image::Image(const Image &i):
	w(i.w),
	h(i.h),
	type(i.type)
{
	for(int id = 0 ; id < 3 ; id++)
		channel[id] = matrix_copy(i.channel[id],type);
}

Image::Image(MatrixType type_):
type(type_)
{
}

Image::Image(uint width,uint height,MatrixType type_):
	w(width),
	h(height),
	type(type_)
{
	for(int i = 0 ; i < 3 ; i++){
		channel[i] = matrix_create(w,h,type_);
	}
}

Image::~Image(){
	for(int i = 0 ; i < 3 ; i++)
		matrix_destroy(channel[i]);
}

uint Image::width()const{
	return w;
}

uint Image::height()const{
	return h;
}

uint Image::size()const{
	return w*h;
}

MatrixType Image::getType()const{
	return type;
}

Image Image::copy(MatrixType type)const{
	Image i(type);
	i.w = w;
	i.h = h;
	for(int id = 0 ; id < 3 ; id++)
		i.channel[id] = matrix_copy(channel[id],type);
	return i;
}

void Image::convolution(Matrix f,channel_type t){
	assert(f.type != NONE);
	bool cpy = false;
	
	if(f.type != type){
		f = matrix_copy(f,type);
		cpy = true;
	}
	if(t==ALL){
		for(int i = 0 ; i < 3 ; i++){
			Matrix buf = matrix_convolution(channel[i],f);
			matrix_destroy(channel[i]);
			channel[i] = buf;
		}
	}else{
		Matrix buf = matrix_convolution(channel[(int)t],f);
		matrix_destroy(channel[(int)t]);
		channel[(int)t] = buf;
	}
	
	if(cpy)
		matrix_destroy(f);
	
}
void Image::divide(float val ,channel_type t ){
	if(t==ALL){
		for(int i = 0 ; i < 3 ; i++){
			matrix_divide(channel[i],val);
		}
	}else{
		matrix_divide(channel[(int)t],val);
	}
}
void Image::normalize(channel_type t ){
	if(t==ALL){
		for(int i = 0 ; i < 3 ; i++)
			matrix_normalize(channel[i]);
	}else{
		matrix_normalize(channel[(int)t]);
	}
}
void Image::resize(uint width , uint height){
	w = width;
	h = height;
	for(int i = 0 ; i < 3 ; i++){
		Matrix buf = matrix_resize(channel[i],width,height);
		matrix_destroy(channel[i]);
		channel[i] = buf;
	}
}
QRgb Image::getPixel(uint x,uint y)const{
	assert(type == CPU);
//	qDebug() << channel[0].data[y*width()+x] << channel[1].data[y*width()+x] << channel[2].data[y*width()+x];
	QColor c(channel[0].data[y*width()+x],channel[1].data[y*width()+x],channel[2].data[y*width()+x]);
	return c.rgb();
}

