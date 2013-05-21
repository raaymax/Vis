#include "ImageFactory.h"
#include <QImage>
#include <exceptions/NoFileException.h>
#include <QString>
Image * ImageFactory::fromFile(const QString & filename){
	QImage qimg(filename);
	if(qimg.isNull()) throw NoFileException(filename);
//	if(qimage.isNull()) TODO: Exceptions
	QImage qimage = qimg.rgbSwapped();
	QSize size = qimage.size();
	Image *img = new Image(size.width(),size.height());
	unsigned char * c = img->data();
	for(int y = 0 ; y < size.height() ; y++)
		for(int x = 0 ; x < size.width() ; x++){
			c[y*size.width()*3 + x*3] = qRed(qimage.pixel(x,y));
			c[y*size.width()*3 + x*3+1] = qGreen(qimage.pixel(x,y));
			c[y*size.width()*3 + x*3+2] = qBlue(qimage.pixel(x,y));
		}
	return img;
}
