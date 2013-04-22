#ifndef IFILTER_H
#define IFILTER_H

#include <IImage.h>
#include <boost/date_time/posix_time/posix_time.hpp>

class IFilter
{
	
public:
	virtual void process(IImage & image){
		boost::posix_time::ptime mst1 = boost::posix_time::microsec_clock::local_time();
		run(image);
		boost::posix_time::ptime mst2 = boost::posix_time::microsec_clock::local_time();
		td = mst2 - mst1;
	}
	boost::posix_time::time_duration getTime(){return td;}
	virtual void run(IImage & image)=0;
private:
	boost::posix_time::time_duration td;
};

#endif // IFILTER_H
