#include "Plotter.h"
#include <QPainter>

Plotter::Plotter(QWidget * parent):
    QWidget(parent)
{
    
}
void Plotter::paintEvent( QPaintEvent* ){
    QPainter p(this);
    int w = width();
    int h = height();
    
    foreach(const QList<qreal> &plot , plots){
        qreal x = 0;
        qreal y = 0;
        qreal step = w/plot.size();
        foreach(const qreal & r, plot){
            p.drawLine(x,y,x+step,r);
            x += step;
            y = r;
        }
    }
}
void Plotter::addPlot(QList<qreal> & plot){
    plots.append(plot);
}