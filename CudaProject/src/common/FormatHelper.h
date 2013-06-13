#ifndef FORMATHELPER_H_
#define FORMATHELPER_H_
#include <Image.h>
#include <QImage>
#include <QColor>
#include <QSize>
#include <QDebug>

class FormatHelper{
public:
	static QImage ImageToQImage(const Image & img){
		debug("in");
		Image cpu = img.copy(CPU);
		QImage tmp(QSize(cpu.width(),cpu.height()), QImage::Format_RGB888);
		for(int y = 0 ; y < cpu.height() ;y++ ){
			for(int x = 0 ; x < cpu.width() ;x++ ){
				tmp.setPixel(x,y,cpu.getPixel(x,y));
			}
		}
		debug("out");
		return tmp;
	}
	
	static Image QImageToImage(const QImage & qimage,MatrixType t){
		debug("in");
		QSize size = qimage.size();
		Image img(size.width(),size.height(),CPU);
		
		for(int y = 0 ; y < size.height() ; y++)
			for(int x = 0 ; x < size.width() ; x++){
				img.channel[0].data[y*size.width() + x] = qRed(qimage.pixel(x,y));
				img.channel[1].data[y*size.width() + x] = qGreen(qimage.pixel(x,y));
				img.channel[2].data[y*size.width() + x] = qBlue(qimage.pixel(x,y));
			}	
		debug("out");
		return img.copy(t);;
	}
};

#endif
