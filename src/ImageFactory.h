#ifndef IMAGEFACTORY_H
#define IMAGEFACTORY_H
#include <Image.h>
#include <QImage>
class ImageFactory
{
public:
	static Image fromQImage(QImage &);
};

#endif // IMAGEFACTORY_H
