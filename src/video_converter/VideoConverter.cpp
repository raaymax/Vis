#include "VideoConverter.h"
#include <QDebug>
VideoConverter::VideoConverter():
    cap(new cv::VideoCapture()),
    wr(new cv::VideoWriter())
{
    
}
VideoConverter::VideoConverter(const int & in , const QString & out):
    cap(new cv::VideoCapture(in)),
    wr(new cv::VideoWriter(out.toStdString(),CV_FOURCC('D','I','V','X'),cap->get(CV_CAP_PROP_FPS),cv::Size((int)cap->get(CV_CAP_PROP_FRAME_WIDTH),(int)cap->get(CV_CAP_PROP_FRAME_HEIGHT))))
{

}
VideoConverter::VideoConverter(
        const QString & in ,
        const QString & out
    ):
    cap(new cv::VideoCapture(in.toStdString())),
    wr(new cv::VideoWriter(out.toStdString(),CV_FOURCC('D','I','V','X'),cap->get(CV_CAP_PROP_FPS),cv::Size((int)cap->get(CV_CAP_PROP_FRAME_WIDTH),(int)cap->get(CV_CAP_PROP_FRAME_HEIGHT))))
{
    if(!cap->isOpened()) throw "ERROR.. cannot open file";
}

void VideoConverter::registerFilter(boost::function<void(cv::Mat & frame)> const & f)
{
    filters.append(f);
}
void VideoConverter::processFrame()
{
    cv::Mat frame;
    *cap >> frame;
    if(!filters.empty()){
		foreach(boost::function<void(cv::Mat & frame)> const & f , filters){
			f(frame);
		}
    }
    *wr << frame;
//	qDebug()<< (cap->get(CV_CAP_PROP_POS_FRAMES)+1) << "/" << cap->get(CV_CAP_PROP_FRAME_COUNT);
    emit progress((cap->get(CV_CAP_PROP_POS_FRAMES)+1)/cap->get(CV_CAP_PROP_FRAME_COUNT));
    emit frameProcessingDone();
}

bool VideoConverter::isDone()
{

    return ((int)cap->get(CV_CAP_PROP_POS_FRAMES))>=((int)cap->get(CV_CAP_PROP_FRAME_COUNT))-1;
}


void VideoConverter::processAll()
{
    while(!isDone()){
        processFrame();
    }
    wr->release();
    emit processingDone();
}


VideoConverter::~VideoConverter()
{
    delete cap;
    delete wr;
}

void VideoConverter::open(const int & in){
    cap->open(in);
}
void VideoConverter::open(const QString & in){
    cap->open(in.toStdString());
}
bool VideoConverter::isInputOpened(){
    return cap->isOpened();
}
bool VideoConverter::isOutputOpened(){
    return cap->isOpened();
}
bool VideoConverter::isOpened(){
    return cap->isOpened()&& wr->isOpened();
}

void VideoConverter::saveTo(const QString & out){
    wr->open(out.toStdString(),
             CV_FOURCC('D','I','V','X'),
             cap->get(CV_CAP_PROP_FPS),
             cv::Size((int)cap->get(CV_CAP_PROP_FRAME_WIDTH),
                      (int)cap->get(CV_CAP_PROP_FRAME_HEIGHT)));
	cap->set(CV_CAP_PROP_POS_FRAMES,0);
}
