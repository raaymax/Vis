#include <ImageSource.h>
#include <QImage>
#include <Image.h>
#include "ImageFactory.h"
#include <cstring>
#include <QRgb>
#include <QStringList>
#include <exceptions/NoFileException.h>

ImageSource::ImageSource():
	multi(false),
	type(CPU),
	image(NULL)
{
    load();
}

ImageSource::ImageSource(const QString & filename):
	multi(false),
	type(CPU),
	image(NULL)
{
	files.append(filename);
	it = files.begin();
	load();
}

ImageSource::ImageSource(const QStringList & _files):
	files(_files),
	multi(true),
	image(NULL)
{
	it = files.begin();
}

const Image & ImageSource::getImage()
{	
	return *image;
}


void ImageSource::load(){
	if(!files.empty()){
		if( image != NULL){ delete image;image = NULL;}
		image = factory.fromFile(*it,type);
	}else{
		image = factory.black(512,512,type);
	}
}
void ImageSource::loadNext(){
	if(!files.empty()){
		if(++it == files.end()) it = files.begin();
		load();
	}else{
		load();
	}
}

ImageSource::~ImageSource()
{
	delete image;
}

void ImageSource::setType(MatrixType t){
	type = t;
	load();
}
