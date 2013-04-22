#ifndef FILTERMANAGER_H
#define FILTERMANAGER_H

#include <boost/date_time/posix_time/posix_time.hpp>
#include <IFilter.h>
template <class T>
class FilterManager: public IFilter
{
public:
	void process(IImage & image){
		boost::posix_time::ptime mst1 = boost::posix_time::microsec_clock::local_time();
		filter.process(image);
		boost::posix_time::ptime mst2 = boost::posix_time::microsec_clock::local_time();
		td = mst2 - mst1;
	}
	
	boost::posix_time::time_duration getTime(){return td;}
private:
	boost::posix_time::time_duration td;
	T filter;
	
};

#endif // FILTERMANAGER_H
