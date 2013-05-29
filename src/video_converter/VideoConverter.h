 
#ifndef VIDEOCONVERTER_H_
#define VIDEOCONVERTER_H_

#include <QString>
#include <QList>
#include <QObject>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <boost/function.hpp>

class VideoConverter: public QObject{
    Q_OBJECT
public:
    VideoConverter(const int & in , const QString & out);
    VideoConverter(const QString & in , const QString & out);
    
    virtual ~VideoConverter();
    void registerFilter(boost::function<void(cv::Mat & frame)> const & f);
    void processFrame();
    void processAll();
    bool isDone();
signals:
    void progress(double);
    void processingDone();
    void frameProcessingDone();
    
protected:
    QList<boost::function<void(cv::Mat & frame)> > filters;
    cv::VideoCapture cap;
    cv::VideoWriter wr;
};
#endif

