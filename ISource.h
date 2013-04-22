#ifndef ISOURCE_H
#define ISOURCE_H

#include <IImage.h>


class ISource
{
public:
	virtual const IImage & getImage()=0;
};

#endif // ISOURCE_H
