#include "QImageAdapter.h"

QImageAdapter::QImageAdapter(VideoConverter * parent):
	parent(parent)
{

}

QImageAdapter::~QImageAdapter()
{

}

void QImageAdapter::registerFilter(boost::function<void(QImage & frame)> const & f){
	parent->registerFilter(boost::bind(&QImageAdapter::process,this,_1,f));
}
void QImageAdapter::process(cv::Mat & frame , boost::function<void(QImage & frame)> const & filter){
	int width = frame.cols;
	int height = frame.rows;
	const uchar *qImageBuffer =(const uchar*)frame.data;
	
	QImage img(qImageBuffer,width , height, QImage::Format_RGB888);
	
	filter(img);
	
	for(int y = 0 ; y < width ; y++)
		for(int x = 0 ; x < height ; x++){
			frame.data[y*width*3 + x] = qRed(img.pixel(x,y));
			frame.data[y*width*3 + x+1] = qGreen(img.pixel(x,y));
			frame.data[y*width*3 + x+2] = qBlue(img.pixel(x,y));
		}
}
