#include <ImageSource.h>
#include <QImage>
#include <Image.h>
#include "ImageFactory.h"
#include <cstring>
#include <QRgb>
#include <QStringList>
#include <exceptions/NoFileException.h>

ImageSource::ImageSource():
	multi(false)
{
    image = Image(512,512);
}

ImageSource::ImageSource(const QString & filename):
	multi(false)
{
	load(filename);
}

ImageSource::ImageSource(const QStringList & _files):
	files(_files),
	multi(true)
{
	it = files.begin();
}

const Image & ImageSource::getImage()
{	
	if(multi) next();
	return image;
}
void ImageSource::next(){
	QString filename = *it;
	load(filename);
	if(++it == files.end()) it = files.begin();
}

void ImageSource::load(const QString & filename){
	QImage qimage(filename);
	if(qimage.isNull()) throw NoFileException(filename);
	image = ImageFactory::fromQImage(qimage);
}

ImageSource::~ImageSource()
{
	
}

