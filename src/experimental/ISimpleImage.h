#ifndef ISIMPLEIMAGE_H
#define ISIMPLEIMAGE_H
typedef unsigned char uchar;
typedef unsigned int uint;

class ISimpleImage
{
public:
	virtual uint width()const=0;
	virtual uint height()const=0;
	virtual uint size() const=0;
	virtual const uchar * constData() const=0;	
};

#endif // ISIMPLEIMAGE_H
