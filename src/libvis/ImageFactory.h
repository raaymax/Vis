#ifndef IMAGEFACTORY_H
#define IMAGEFACTORY_H
#include <Image.h>
#include <IImageFactory.h>

class ImageFactory : public IImageFactory
{
public:
	Image * fromFile(const QString &);
};

#endif // IMAGEFACTORY_H
