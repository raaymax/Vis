#ifndef RUNNER_H_
#define RUNNER_H_
#include <boost/function.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

template <class T>
class Runner{
public:
	Runner(boost::function<void(T &)> const & f_);
	void run(T & image);
	boost::posix_time::time_duration getTime();
private:
	boost::function<void(T &)> f;
	boost::posix_time::time_duration td;
};

#endif

template<class T>
Runner<T>::Runner(boost::function<void(T &)> const & f_):f(f_){}

template<class T>
void Runner<T>::run(T & image){
	boost::posix_time::ptime mst1 = boost::posix_time::microsec_clock::local_time();
	f(image);
	boost::posix_time::ptime mst2 = boost::posix_time::microsec_clock::local_time();
	td = mst2 - mst1;
}

template<class T>
boost::posix_time::time_duration Runner<T>::getTime(){return td;}
