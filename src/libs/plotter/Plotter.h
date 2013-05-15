#ifndef PLOTTER_H_
#define PLOTTER_H_

#include <QWidget>
#include <QList>
#include <QColor>
#include <QPair>
#include <Plot.h>

class Plotter : public QWidget{
    Q_OBJECT
public:
    Plotter(QWidget * parent = 0);
    virtual ~Plotter();
    Plot * createPlot();
    Plot * createPlot(const QColor &color);
    Plot * createPlot(const Points & plot);
    Plot * createPlot(const Points & plot, const QColor &color );
    
    
    void registerPlot(Plot * plot);
    void detachPlot(Plot * plot);
    
    void clearPlots();
    void clearAll();
    
    QList<Plot* > & getPlots(){return plots;}
    
    void setFrame(bool f){frame = f;}
    void setScale(bool f){scale = f;}
    void setScaleFactor(qreal f){scaleFactor = f;}
protected:
    void paintEvent( QPaintEvent* );
private:
    bool frame;
    bool scale;
    qreal scaleFactor;
    QList<Plot* > plots;
};


#endif