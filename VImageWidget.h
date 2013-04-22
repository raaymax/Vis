#ifndef VIMAGEWIDGET_H
#define VIMAGEWIDGET_H

#include <QWidget>
#include <QLabel>
#include "IImage.h"


class VImageWidget : public QWidget
{

public:
    VImageWidget( QWidget * parent = 0);
	virtual void setImage(const IImage & img);
    virtual ~VImageWidget();
	
private:
	QLabel scene;
};

#endif // VIMAGEWIDGET_H
