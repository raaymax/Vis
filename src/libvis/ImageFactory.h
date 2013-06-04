#ifndef IMAGEFACTORY_H
#define IMAGEFACTORY_H
#include <Image.h>


class ImageFactory
{
public:
	Image * fromFile(const QString &,MatrixType t);
	Image * black(uint width, uint height,MatrixType t);
};

#endif // IMAGEFACTORY_H
