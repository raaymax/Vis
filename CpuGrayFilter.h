#ifndef CPUGRAYFILTER_H
#define CPUGRAYFILTER_H

#include <IFilter.h>
#include <IImage.h>

class CpuGrayFilter : public IFilter
{

public:
    virtual void process(IImage& inoutImage);
    CpuGrayFilter();
    virtual ~CpuGrayFilter();
};

#endif // CPUGRAYFILTER_H
