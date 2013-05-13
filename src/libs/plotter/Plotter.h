#ifndef PLOTTER_H_
#define PLOTTER_H_

#include <QWidget>
#include <QList>
#include <QColor>
#include <QPair>
#include <Plot.h>

class Plotter : public QWidget, public QList<Plot* >{
    Q_OBJECT
public:
    Plotter(QWidget * parent = 0);
    Plot & addPlot();
    Plot & addPlot(const QColor &color);
    Plot & addPlot(const Points & plot);
    Plot & addPlot(const Points & plot, const QColor &color );
    
    void setFrame(bool f){frame = f;}
    void setScale(bool f){scale = f;}
    void setScaleFactor(qreal f){scaleFactor = f;}
protected:
    void paintEvent( QPaintEvent* );
private:
    bool frame;
    bool scale;
    qreal scaleFactor;
};


#endif