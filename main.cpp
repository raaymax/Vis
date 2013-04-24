#include <QtGui/QApplication>
#include <QString>
#include "VImageWidget.h"
#include "ImageSource.h"
#include "CpuGrayFilter.h"
#include "GpuGrayFilter.h"
#include "FilterManager.h"
#include "exceptions/IException.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
	try{
		ImageSource * src;
		
		src = new ImageSource("test.jpg"); 

	
		Image img = src->getImage();
		Image img2 = src->getImage();

		FilterManager<CpuGrayFilter> filterCPU;
		filterCPU.process(img);
		std::cout<< "filter CPU time:" << filterCPU.getTime().total_microseconds() <<"us"<< std::endl;
		
		FilterManager<GpuGrayFilter> filterGPU;
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
	}catch(IException & ex){
		std::cout <<ex.getMessage().toStdString() << std::endl;
		return 1;
	}
    return app.exec();
}
