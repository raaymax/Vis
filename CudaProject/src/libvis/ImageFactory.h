#ifndef IMAGEFACTORY_H
#define IMAGEFACTORY_H
#include <Image.h>
#include <QImage>
//TODO: static methods
class ImageFactory
{
public:
	Image * fromFile(const QString &,MatrixType t);
	Image * fromQImage(const QImage & qimage, MatrixType t);
	Image * black(uint width, uint height,MatrixType t);
};

#endif // IMAGEFACTORY_H
