#include "Plotter.h"
#include <QPainter>
#include <qpaintengine.h>

Plotter::Plotter(QWidget * parent):
    QWidget(parent)
{
    setFixedSize(500,150);
}
void Plotter::paintEvent( QPaintEvent* ){
    QPainter p(this);
    int w = width();
    int h = height();
    
    //p.setBackground(QBrush(Qt::white));
    QPen pen(Qt::red);
    pen.setWidth(2);
    p.setPen(pen);
    
    p.setRenderHint(QPainter::Antialiasing);
    
    foreach(const QList<qreal> &plot , plots){
        qreal x = 0;
        qreal y = 0;
        qreal step = w/(plot.size()-1);
        foreach(const qreal & r, plot){
            if(plot.first() != r){
                p.drawLine(x,h-y,x+step,h-r);
                x += step;
            }
            y = r;
        }
    }
}
void Plotter::addPlot(QList<qreal> & plot){
    plots.append(plot);
}