#include "ImageFactory.h"

Image ImageFactory::fromQImage(QImage & qimage){
//	if(qimage.isNull()) TODO: Exceptions
	qimage = qimage.rgbSwapped();
	QSize size = qimage.size();
	Image img(size.width(),size.height());
	unsigned char * c = img.data();
	for(int y = 0 ; y < size.height() ; y++)
		for(int x = 0 ; x < size.width() ; x++){
			c[y*size.width()*3 + x*3] = qRed(qimage.pixel(x,y));
			c[y*size.width()*3 + x*3+1] = qGreen(qimage.pixel(x,y));
			c[y*size.width()*3 + x*3+2] = qBlue(qimage.pixel(x,y));
		}
	return img;
}
