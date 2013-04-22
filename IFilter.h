#ifndef IFILTER_H
#define IFILTER_H

#include <IImage.h>



class IFilter
{
public:
	virtual void process(IImage & image)=0;
};

#endif // IFILTER_H
