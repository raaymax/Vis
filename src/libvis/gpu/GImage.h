#ifndef GIMAGE_H_
#define GIMAGE_H_

#include <IImage.h>

class GImage : public IImage{
public:
	GImage();
	GImage(uint w, uint h);
	GImage(const GImage& other);
	GImage(const IImage& other);
	
	virtual uint width()const;
	virtual uint height()const;
	virtual uint size() const;
	virtual float * data();
	virtual const float * data()const;
	virtual const uchar * constData() const;
	
	friend class GImageTransform;
private:
	float * data_;
	uchar * buf_;
	uint width_;
	uint height_;
	uint size_;
};


#endif // GIMAGE_H_
