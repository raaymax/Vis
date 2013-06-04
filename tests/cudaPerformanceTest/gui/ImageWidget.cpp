#include "ImageWidget.h"
#include <QLayout>
#include <QHBoxLayout>
#include <stdio.h>


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
	debug("in");
	Image cpu = img.copy(CPU);
	QImage tmp(QSize(cpu.width(),cpu.height()), QImage::Format_RGB888);
	for(int y = 0 ; y < cpu.height() ;y++ ){
		for(int x = 0 ; x < cpu.width() ;x++ ){
			tmp.setPixel(x,y,cpu.getPixel(x,y));
		}
	}
	
	scene.setPixmap(QPixmap::fromImage(tmp));
	debug("out");
}


ImageWidget::~ImageWidget()
{

}

