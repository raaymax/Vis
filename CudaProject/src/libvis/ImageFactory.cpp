#include "ImageFactory.h"

#include <QImage>
#include <exceptions/NoFileException.h>
#include <QString>
#include <common/FormatHelper.h>
Image * ImageFactory::fromFile(const QString & filename, MatrixType t){
	debug("in");
	QImage qimage(filename);
	if(qimage.isNull()) throw NoFileException(filename);
	return fromQImage(qimage,t);
}

Image * ImageFactory::fromQImage(const QImage & qimage, MatrixType t){
	debug("in");
	return new Image(FormatHelper::QImageToImage(qimage,t));
}

Image * ImageFactory::black(uint width, uint height,MatrixType t){
	debug("in");
	return new Image(width,height,t);
}
