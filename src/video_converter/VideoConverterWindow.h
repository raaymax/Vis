#ifndef VIDEOCONVERTERWINDOW_H
#define VIDEOCONVERTERWINDOW_H

#include <QMainWindow>
#include <plotter/Plotter.h>
#include "VideoConverter.h"


namespace Ui{
    class VideoConverterWindow;
}

class VideoConverterWindow : public QMainWindow
{
    Q_OBJECT
public:
	explicit VideoConverterWindow( VideoConverter * conv,QWidget * parent = 0);
    virtual ~VideoConverterWindow();
	
	Plot * getPlot(){return plot;}
public slots:
    void chooseSource();
    void chooseOutput();
    void setProgress(double);
    void startProcessing();
	void processingDone();
   
private:
    void unlockProcessButtonIfReady();
    
    QString sourceFile;
    QString outputFile;
    VideoConverter * conv;
    Plot * plot;
    Plotter * plotter;
    Ui::VideoConverterWindow * ui;
};

#endif // VIDEOCONVERTERWINDOW_H
