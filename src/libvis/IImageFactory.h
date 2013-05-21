#ifndef IIMAGEFACTORY_H
#define IIMAGEFACTORY_H
#include "IImage.h"
#include <QString>

class IImageFactory
{
public:
	virtual	IImage * fromFile(const QString &)=0;
};

#endif // IIMAGEFACTORY_H
