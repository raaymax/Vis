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
    explicit VideoConverterWindow( QWidget * parent = 0);
    virtual ~VideoConverterWindow();
public slots:
    void chooseSource();
    void chooseOutput();
    void setProgress(double);
   
private:
    void unlockProcessButtonIfReady();
    
    bool isSourceChoosen;
    bool isOutputChoosen;
    QString sourceFile;
    QString outputFile;
    VideoConverter * conv;
    Plot * plot;
    Plotter * plotter;
    Ui::VideoConverterWindow * ui;
};

#endif // VIDEOCONVERTERWINDOW_H
