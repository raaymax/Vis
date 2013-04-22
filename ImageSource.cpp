#include <ImageSource.h>
#include <QImage>
#include <Image.h>
#include "ImageFactory.h"
#include <cstring>
#include <QRgb>

ImageSource::ImageSource(const QString & filename)
{
	QImage qimage(filename);
//	if(qimage.isNull()) TODO: Exceptions
	image = ImageFactory::fromQImage(qimage);
}

const Image & ImageSource::getImage()
{
	return image;
}

ImageSource::~ImageSource()
{
	
}

