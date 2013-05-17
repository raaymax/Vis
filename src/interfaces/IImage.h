#ifndef IIMAGE_H
#define IIMAGE_H
#include <QImage>

typedef unsigned char uchar;
typedef unsigned int uint;

class IImage
{
public:
	virtual uint width()const=0;
	virtual uint height()const=0;
	virtual uint size() const=0;
	virtual uchar * data()=0;
	virtual const uchar * constData() const=0;
	virtual QImage toQImage() const{
		QImage img(constData(),width() , height(), QImage::Format_RGB888);
		return img.rgbSwapped();
	}
};

#endif // IIMAGE_H
