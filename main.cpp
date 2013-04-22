#include <QtGui/QApplication>
#include "VImageWidget.h"
#include "ImageSource.h"
#include "CpuGrayFilter.h"
#include "GpuGrayFilter.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
	ImageSource * src = new ImageSource("test.jpg"); 
	Image img = src->getImage();
	CpuGrayFilter filterCPU;
	filterCPU.process(img);
	std::cout<< "filter CPU time:" << filterCPU.getTime().total_microseconds() <<"us"<< std::endl;
	Image img2 = src->getImage();
	GpuGrayFilter filterGPU;
	filterGPU.process(img2);
	std::cout<< "filter GPU time:" << filterGPU.getTime().total_microseconds()<<"us" << std::endl;
//	Image img(800,600);
	VImageWidget foo;
	foo.setImage(img);
	foo.setWindowTitle("Vis - CPU");
    foo.show();
	
	VImageWidget foo2;
	foo2.setImage(img2);
	foo2.setWindowTitle("Vis - GPU");
    foo2.show();

    return app.exec();
}
