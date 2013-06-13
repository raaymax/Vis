#ifndef QIMAGEADAPTER_H
#define QIMAGEADAPTER_H
#include <QImage>
#include <boost/bind/bind.hpp>
#include "VideoConverter.h"


class QImageAdapter
{

public:
    QImageAdapter(VideoConverter * parent);
    virtual ~QImageAdapter();
	void registerFilter(boost::function<void(QImage & frame)> const & f);
	void process(cv::Mat & frame , boost::function<void(QImage & frame)> const & f);
private:
	VideoConverter * parent;
};

#endif // QIMAGEADAPTER_H

