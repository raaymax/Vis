#ifndef GIMAGETRANSFORM_H
#define GIMAGETRANSFORM_H
#include "GImage.h"

class GImageTransform
{

public:
	GImageTransform(GImage * img);
    virtual ~GImageTransform();
	
	void stretch(int val);
private:
	GImage * img_;
};

#endif // GIMAGETRANSFORM_H
