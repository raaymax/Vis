#include <CpuGrayFilter.h>

void CpuGrayFilter::process(IImage& inoutImage)
{
	uchar * data = inoutImage.data();
	for(int i = 0 ; i < inoutImage.size() ; i+=3){
		data[i]=data[i+1]=data[i+2]=(data[i]+data[i+1]+data[i+2])/3;
	}
}

CpuGrayFilter::CpuGrayFilter()
{

}

CpuGrayFilter::~CpuGrayFilter()
{

}

