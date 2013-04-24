#include <ImageSource.h>
#include <QImage>
#include <Image.h>
#include "ImageFactory.h"
#include <cstring>
#include <QRgb>
#include <exceptions/NoFileException.h>

ImageSource::ImageSource()
{
    image = Image(512,512);
}

ImageSource::ImageSource(const QString & filename)
{
	QImage qimage(filename);
	if(qimage.isNull()) throw NoFileException(filename);
	image = ImageFactory::fromQImage(qimage);
}

const Image & ImageSource::getImage()
{
	return image;
}

ImageSource::~ImageSource()
{
	
}

