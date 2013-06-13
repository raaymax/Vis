#ifndef IEXCEPTION_H_
#define IEXCEPTION_H_

#include <string>

class IException{
public:
	virtual const QString getMessage()=0;
};

#endif // IEXCEPTION_H_
