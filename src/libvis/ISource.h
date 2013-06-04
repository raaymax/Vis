#ifndef ISOURCE_H
#define ISOURCE_H

#include <Image.h>


class ISource
{
public:
	virtual const Image & getImage()=0;
};

#endif // ISOURCE_H
