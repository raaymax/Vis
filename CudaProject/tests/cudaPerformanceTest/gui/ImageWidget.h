#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <Image.h>


class ImageWidget : public QWidget
{

public:
    ImageWidget( QWidget * parent = 0);
	virtual void setImage(const Image & img);
    virtual ~ImageWidget();
	
private:
	QLabel scene;
};

#endif // IMAGEWIDGET_H
