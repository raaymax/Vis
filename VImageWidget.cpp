#include "VImageWidget.h"
#include <QLayout>
#include <QHBoxLayout>

VImageWidget::VImageWidget(QWidget * parent ):
	QWidget(parent),
	scene()
{
	QLayout * layout = new QHBoxLayout(this);
	layout->addWidget(&scene);
	setMaximumSize(800,600);
	scene.setMaximumSize(800,600);
	scene.setScaledContents(true);
}

void VImageWidget::setImage(const IImage& img)
{
	QImage imag = img.toQImage();
	scene.setPixmap(QPixmap::fromImage(imag));
}


VImageWidget::~VImageWidget()
{

}

