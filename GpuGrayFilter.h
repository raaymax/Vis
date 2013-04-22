#ifndef GPUGRAYFILTER_H
#define GPUGRAYFILTER_H
#include <IFilter.h>

class GpuGrayFilter : public IFilter
{

public:
    GpuGrayFilter();
	virtual void run(IImage &);
	
    virtual ~GpuGrayFilter();
};

#endif // GPUGRAYFILTER_H
