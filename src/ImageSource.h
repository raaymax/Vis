#ifndef IMAGESOURCE_H
#define IMAGESOURCE_H

#include <ISource.h>
#include <QImage>
#include "Image.h"
#include <QStringList>
#include <string>


class ImageSource : public ISource
{

public:
    ImageSource();
    ImageSource(const QString & filename);
	ImageSource(const QStringList & files);
	const Image & getImage();
    virtual ~ImageSource();
private:
	QStringList files;
	void next();
	void load(const QString & filename);
	bool multi;
	QList<QString>::iterator it;
	Image image;
};

#endif // IMAGESOURCE_H
