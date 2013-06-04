#include "ImageFactory.h"
#include <QImage>
#include <exceptions/NoFileException.h>
#include <QString>
Image * ImageFactory::fromFile(const QString & filename, MatrixType t){
	QImage qimg(filename);
	if(qimg.isNull()) throw NoFileException(filename);
//	if(qimage.isNull()) TODO: Exceptions
	QImage qimage = qimg.rgbSwapped();
	QSize size = qimage.size();
	Image *img = new Image(size.width(),size.height(),CPU);
	
	for(int y = 0 ; y < size.height() ; y++)
		for(int x = 0 ; x < size.width() ; x++){
			img->channel[0].data[y*size.width() + x] = qRed(qimage.pixel(x,y));
			img->channel[1].data[y*size.width() + x] = qGreen(qimage.pixel(x,y));
			img->channel[2].data[y*size.width() + x] = qBlue(qimage.pixel(x,y));
		}
		
	debug((t==CPU)?"CPU":"GPU");
	if(t == GPU){
		Image *tmp = img;
		img = new Image(img->copy(GPU));
		delete tmp;
	}
	return img;
}

Image * ImageFactory::black(uint width, uint height,MatrixType t){
	return new Image(width,height,t);
}
