#ifndef IIMAGE_H
#define IIMAGE_H
#include <QRgb>
#include <Matrix.h>
#include <assert.h>

class ImageFactory;

class Image
{
public:
	Image(const Image &);
	virtual ~Image();
	
	typedef enum{RED=0,GREEN=1,BLUE=2,ALL=3} channel_type;
	uint width()const;
	uint height()const;
	uint size() const;
	MatrixType getType()const;
	QRgb getPixel(uint x,uint y)const;

	Image copy(MatrixType type)const;
	void convolution(Matrix f,channel_type t = ALL);
	void divide(float val ,channel_type t = ALL);
	void normalize(channel_type t = ALL);
	void resize(uint width , uint height);
	
	friend class ImageFactory;

//TODO: ograniczenia dostępu
	Image(MatrixType type);
	Image(uint width,uint height,MatrixType type);
	
	Matrix channel[3];
private:
	MatrixType type;
	uint w;
	uint h;
	
};

#endif // IIMAGE_H
