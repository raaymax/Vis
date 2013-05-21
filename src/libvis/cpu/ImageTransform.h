#ifndef IMAGETRANSFORM_H
#define IMAGETRANSFORM_H
#include "Image.h"

typedef struct {uchar r;uchar g;uchar b;} Pixel;

class ImageTransform
{
public:
	
	ImageTransform(Image * img);
	virtual ~ImageTransform();
	
	void stretch(int val);
private:
	Pixel & getPixel(int x, int y);
	Image * img_;
};

#endif // GIMAGETRANSFORM_H
