#ifndef IMAGE_H
#define IMAGE_H

#include <IImage.h>

#include <boost/scoped_array.hpp>

class Image : public IImage
{

public:
    virtual const uchar* constData() const;
    virtual uchar* data();
    virtual uint size() const;
    virtual uint height() const;
    virtual uint width() const;
	
    Image();
	Image(uint w, uint h);
    Image(const Image& other);
	
    virtual ~Image();
    virtual Image& operator=(const Image& other);
    virtual bool operator==(const Image& other) const;
	
	
private:
	boost::scoped_array<uchar> data_;
	uint size_;
	uint width_;
	uint height_;
};

#endif // IMAGE_H
