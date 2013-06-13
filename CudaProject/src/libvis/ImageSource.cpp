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
	debug("none");
    load();
}

ImageSource::ImageSource(const QString & filename):
	multi(false),
	type(CPU),
	image(NULL)
{
	debug("one");
	files.append(filename);
	it = files.begin();
	load();
}

ImageSource::ImageSource(const QStringList & _files):
	files(_files),
	multi(true),
	image(NULL)
{
	debug("manny");
	it = files.begin();
}

const Image & ImageSource::getImage()
{	
	debug("get");
	return *image;
}


void ImageSource::load(){
	debug("in");
	if(!files.empty()){
		if( image != NULL){ delete image;image = NULL;}
		image = factory.fromFile(*it,type);
	}else{
		image = factory.black(512,512,type);
	}
	debug("out");
}
void ImageSource::loadNext(){
	debug("in");
	if(!files.empty()){
		if(++it == files.end()) it = files.begin();
		load();
	}else{
		load();
	}
	debug("out");
}

ImageSource::~ImageSource()
{
	debug("in");
	delete image;
	debug("out");
}

void ImageSource::setType(MatrixType t){
	debug("in");
	type = t;
	load();
	debug("out");
}
