#include "ImageWidget.h"
#include <FormatHelper.h>
#include <QLayout>
#include <QHBoxLayout>
#include <stdio.h>
#include <QDebug>


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

void ImageWidget::setImage(const Image& img)
{
	
	debug(img.getType()==CPU?"in CPU":"in GPU");
	QImage tmp = FormatHelper::ImageToQImage(img);
	scene.setPixmap(QPixmap::fromImage(tmp));
	debug("out");
}


ImageWidget::~ImageWidget()
{

}

