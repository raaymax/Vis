#include "VideoConverter.h"


VideoConverter::VideoConverter(const int & in , const QString & out):
    cap(in),
    wr(out.toStdString(),CV_FOURCC('D','I','V','X'),cap.get(CV_CAP_PROP_FPS),cv::Size((int)cap.get(CV_CAP_PROP_FRAME_WIDTH),(int)cap.get(CV_CAP_PROP_FRAME_HEIGHT)))
{

}
VideoConverter::VideoConverter(
        const QString & in ,
        const QString & out
    ):
        cap(in.toStdString()),
        wr(out.toStdString(),CV_FOURCC('D','I','V','X'),cap.get(CV_CAP_PROP_FPS),cv::Size((int)cap.get(CV_CAP_PROP_FRAME_WIDTH),(int)cap.get(CV_CAP_PROP_FRAME_HEIGHT)))
{
    
}

void VideoConverter::registerFilter(boost::function<void(cv::Mat & frame)> const & f)
{
    filters.append(f);
}
void VideoConverter::processFrame()
{
    cv::Mat frame;
    cap >> frame;
    foreach(boost::function<void(cv::Mat & frame)> const & f , filters){
        f(frame);
    }
    wr << frame;
    emit progress(cap.get(CV_CAP_PROP_POS_FRAMES)/cap.get(CV_CAP_PROP_FRAME_COUNT));
    emit frameProcessingDone();
}

bool VideoConverter::isDone()
{
    return ((int)cap.get(CV_CAP_PROP_POS_FRAMES))>=((int)cap.get(CV_CAP_PROP_FRAME_COUNT))-1;
}


void VideoConverter::processAll()
{
    while(!isDone()){
        processFrame();
    }
    emit processingDone();
}


VideoConverter::~VideoConverter()
{
    
}

