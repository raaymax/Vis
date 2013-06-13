#include <QApplication>
#include <video/VideoConverterWindow.h>
#include <video/QImageAdapter.h>
#include <testFilter.h>
#include <ImageFactory.h>
#include <FormatHelper.h>
#include <Runner.h>
#include <QDebug>

void filter(QImage & img, Plot * plot){
	TestFilter test(GPU);
	Image i = FormatHelper::QImageToImage(img,GPU);
	
	Runner<Image> filterCPU(bind(&TestFilter::process, &test, _1));
	filterCPU.run(i);
	plot->add(filterCPU.getTime().total_microseconds());
	
//	qDebug() << "processing...";
	test.process(i);
	img = FormatHelper::ImageToQImage(i);
}

int main(int argc , char ** argv){
    QApplication app(argc,argv);
    
	VideoConverter * conv = new VideoConverter();
	QImageAdapter adp(conv);
    VideoConverterWindow mainw(conv);
	
	adp.registerFilter(boost::bind(&filter,_1,mainw.getPlot()));
    mainw.show();
    
    return app.exec();
    
}
