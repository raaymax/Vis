#include "Plotter.h"
#include <QPainter>
#include <qpaintengine.h>
#include <QDebug>

Plotter::Plotter(QWidget * parent):
    QWidget(parent),
    frame(true),
    scale(true),
    scaleFactor(1)
    
{
    setFixedSize(500,150);
}
void Plotter::paintEvent( QPaintEvent* ){
    QPainter p(this);
    
    qreal w = width();
    if(scale) w-=40;

    qreal h = height();
    
    p.setBrush(Qt::white);
    p.setPen(Qt::white);
    p.drawRect(0,0,w-1,h-1);
    //p.setBackground(QBrush(Qt::white));
   
    p.setRenderHint(QPainter::Antialiasing);
    
    qreal max = first()->max();
    foreach(const Plot *plot , *this){
        if(max < plot->max()) max = plot->max();
    }
    qreal a = h/max;
    qDebug() << max;
    int linesCount = 4;
    
    if(scale){
        p.setPen(Qt::black);
        p.drawText(w+2,h,QString::number(0));
        p.drawText(w+2,10,QString::number(max*scaleFactor));
    }
    
    p.setPen(Qt::gray);
    
    for(int i = 0 ; i < linesCount ; i++){
        qreal lh = h/5*(i+1);
        qreal ll = (max/5)*(linesCount-i)*scaleFactor;
        p.drawLine(0,lh,w,lh);
        if(scale){
            p.setPen(Qt::black);
            p.drawText(w+2,lh+4,QString::number(ll));
            p.setPen(Qt::gray);
        }
    }
    p.drawLine(0,0,w,0);
    p.drawLine(0,h,w,h);
    
    //QBrush brush();
    QPen pen(Qt::black);
    p.setPen(pen);
    pen.setWidth(2);
    
    foreach(const Plot *plot , *this){
        const Points & pl = plot->points();
        pen.setColor(plot->color());
        p.setPen(pen);
        
        qreal x = 0;
        qreal y = 0;
        qreal step = w/(pl.size()-1);
        foreach(const qreal & r, pl){
            if(pl.first() != r){
                p.drawLine(x,h-(y*a),x+step,h-(r*a));
                x += step;
            }
            y = r;
        }
    }
    p.setPen(Qt::black);
    if(frame) p.drawRect(0,0,w-1,h-1);
}
Plot & Plotter::addPlot(){
    append(new Plot());
    return *last();
}

Plot & Plotter::addPlot(const QColor & col){
    append(new Plot(col));
    return *last();
}

Plot & Plotter::addPlot(const Points & plot){
    QColor col(qrand()%256,qrand()%256,qrand()%256);
    addPlot(plot,col);
    return *last();
}

Plot & Plotter::addPlot(const Points & plot,const QColor & col){
    append(new Plot(plot,col));
    return *last();
}