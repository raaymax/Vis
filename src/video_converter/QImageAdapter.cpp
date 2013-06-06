#include "QImageAdapter.h"
#include <QDebug>

cv::Mat qimage2mat(const QImage& qimage) {
	cv::Mat mat = cv::Mat(qimage.height(), qimage.width(), CV_8UC4, (uchar*)qimage.bits(), qimage.bytesPerLine());
	cv::Mat mat2 = cv::Mat(mat.rows, mat.cols, CV_8UC3 );
	int from_to[] = { 0,0,  1,1,  2,2 };
	cv::mixChannels( &mat, 1, &mat2, 1, from_to, 3 );
	return mat2;
};

QImage mat2qimage(const cv::Mat& mat) {
	cv::Mat rgb;
	cv::cvtColor(mat, rgb, CV_BGR2RGB);
	return QImage((const unsigned char*)(rgb.data), rgb.cols, rgb.rows, QImage::Format_RGB888);
}; 


QImageAdapter::QImageAdapter(VideoConverter * parent):
	parent(parent)
{

}

QImageAdapter::~QImageAdapter()
{

}

void QImageAdapter::registerFilter(boost::function<void(QImage & frame)> const & f){
	qDebug()<<"QImageAdapter: adding handler";
	parent->registerFilter(boost::bind(&QImageAdapter::process,this,_1,f));
}
void QImageAdapter::process(cv::Mat & frame , boost::function<void(QImage & frame)> const & filter){
//	qDebug()<< frame.cols<<" "<< frame.rows<<" "<< frame.step;
	QImage img= QImage((uchar*) frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
	
	filter(img);

	for(int y = 0 ; y < img.height() ; y++)
		for(int x = 0 ; x < img.width() ; x++){
			frame.data[y*frame.step + x*3] = qRed(img.pixel(x,y));
			frame.data[y*frame.step + x*3+1] = qGreen(img.pixel(x,y));
			frame.data[y*frame.step + x*3+2] = qBlue(img.pixel(x,y));
		}
		
}








