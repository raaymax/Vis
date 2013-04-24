#ifndef IMAGESOURCE_H
#define IMAGESOURCE_H

#include <ISource.h>
#include <QImage>
#include "Image.h"
#include <string>


class ImageSource : public ISource
{

public:
    ImageSource();
    ImageSource(const QString & filename);
	const Image & getImage();
    virtual ~ImageSource();
private:
	Image image;
};

#endif // IMAGESOURCE_H
