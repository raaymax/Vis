#ifndef IMAGESOURCE_H
#define IMAGESOURCE_H

#include <ISource.h>
#include <QImage>
#include "Image.h"
#include <QStringList>
#include <string>
#include "ImageFactory.h"

class ImageSource : public ISource
{

public:
    ImageSource();
    ImageSource(const QString & filename);
	ImageSource(const QStringList & files);
	const Image & getImage();
	void setType(MatrixType t);
	void loadNext();
    virtual ~ImageSource();
private:
	MatrixType type;
	ImageFactory factory;
	QStringList files;

	void load();
	bool multi;
	QList<QString>::iterator it;
	Image * image;
};

#endif // IMAGESOURCE_H
