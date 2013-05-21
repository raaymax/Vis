#ifndef IFILTER_H
#define IFILTER_H

#include <Image.h>



class IFilter
{
public:
	virtual void process(Image & image)=0;
};

#endif // IFILTER_H
