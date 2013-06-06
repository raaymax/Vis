#include <QApplication>
#include <video/VideoConverterWindow.h>
#include <video/QImageAdapter.h>
#include <testFilter.h>
#include <ImageFactory.h>
#include <FormatHelper.h>

void filter(QImage & img){
	TestFilter test(GPU);
	Image i = FormatHelper::QImageToImage(img,GPU);
	test.process(i);
	img = FormatHelper::ImageToQImage(i);
}

int main(int argc , char ** argv){
    QApplication app(argc,argv);
    
	VideoConverter * conv = new VideoConverter();
	QImageAdapter adp(conv);
	adp.registerFilter(boost::bind(&filter,_1));
	
    VideoConverterWindow mainw(conv);
    mainw.show();
    
    return app.exec();
    
}
