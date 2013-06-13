#ifndef NOFILEEXCEPTION_H_
#define NOFILEEXCEPTION_H_

#include <QString>
#include "IException.h"

class NoFileException: public IException{
public:
	NoFileException(const QString file):msg_(file){msg_.append(" was not found.");};
	const QString getMessage(){return msg_;};
private:
	QString msg_;
};

#endif // NOFILEEXCEPTION_H_
