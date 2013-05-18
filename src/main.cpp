#include <QtGui/QApplication>
#include <QString>
#include "config.h"
#include "gui/ImageWidget.h"
#include "ImageSource.h"
#include <CpuGrayFilter.h>

#ifdef USE_CUDA
#include <GpuGrayFilter.h>
#endif

#include <FilterManager.h>
#include "exceptions/IException.h"
#include "gui/MainWindow.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    MainWindow mw;
    mw.show();
#if 0
	try{
		ImageSource * src;
		
		src = new ImageSource("test.jpg"); 

	
		Image img = src->getImage();
		FilterManager<CpuGrayFilter> filterCPU;
		filterCPU.process(img);
		std::cout<< "filter CPU time:" << filterCPU.getTime().total_microseconds() <<"us"<< std::endl;
        ImageWidget foo;
        foo.setImage(img);
        foo.setWindowTitle("Vis - CPU");
        foo.show();
        
#ifdef USE_CUDA
        Image img2 = src->getImage();
		FilterManager<GpuGrayFilter> filterGPU;
		filterGPU.process(img2);
		std::cout<< "filter GPU time:" << filterGPU.getTime().total_microseconds()<<"us" << std::endl;
        ImageWidget foo2;
        foo2.setImage(img2);
        foo2.setWindowTitle("Vis - GPU");
        foo2.show();
#endif

	}catch(IException & ex){
		std::cout <<ex.getMessage().toStdString() << std::endl;
		return 1;
	}
#endif
    return app.exec();
}
