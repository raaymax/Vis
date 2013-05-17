#include "ImageWidget.h"
#include <QLayout>
#include <QHBoxLayout>

ImageWidget::ImageWidget(QWidget * parent ):
	QWidget(parent),
	scene()
{
	QLayout * layout = new QHBoxLayout(this);
	layout->addWidget(&scene);
	setMaximumSize(800,600);
	scene.setMaximumSize(800,600);
	scene.setScaledContents(true);
}

void ImageWidget::setImage(const IImage& img)
{
	QImage imag = img.toQImage();
	scene.setPixmap(QPixmap::fromImage(imag));
}


ImageWidget::~ImageWidget()
{

}

