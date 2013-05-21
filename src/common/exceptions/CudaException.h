#ifndef CUDAEXCEPTION_H_
#define CUDAEXCEPTION_H_

#include <QString>
#include <exceptions/IException.h>

class CudaException : public IException{
public:
	typedef enum {NODEVICE} CudaReason;
	CudaException(CudaReason cr , QString msg = ""):msg_(msg),reason_(cr){
		
	}
	
	virtual const QString getMessage(){
		QString str;
		switch(reason_){
			case NODEVICE:
				str.append("Cuda device was not found. ");
				break;
		}
		str.append(msg_);
		return str;
	}
	CudaReason getReason(){return reason_;}
private:
	QString msg_;
	CudaReason reason_;
};

#endif // CUDAEXCEPTION_H_
