#include "Plotter.h"
#include <QPainter>
#include <qpaintengine.h>
#include <QDebug>

Plotter::Plotter(QWidget * parent):
    QWidget(parent),
    frame_(true),
    scale_(true),
    scaleFactor_(1)
{
   // setFixedSize(500,150);
}

Plotter::~Plotter()
{
	foreach(Plot * p , plots_){
        delete p;
    }
}

void Plotter::paintEvent( QPaintEvent* )
{
    QPainter p(this);
    qreal w = width();
    qreal h = height();
    if(scale_) w-=40;
	
	//białe tło i wygładanie krawędzi
    p.setBrush(Qt::white);
    p.setPen(Qt::white);
    p.drawRect(0,0,w-1,h-1);
    p.setRenderHint(QPainter::Antialiasing);
    
	//obliczanie korekty do skalowania
	qreal max = plots_.first()->max();
	foreach(const Plot *plot , plots_){
        if(max < plot->max()) max = plot->max();
    }
    qreal a = h/max;
    int linesCount = 4;
    
	
	//rysowanie skali
	if(scale_){
        p.setPen(Qt::black);
        p.drawText(w+2,h,QString::number(0));
		p.drawText(w+2,10,QString::number(max*scaleFactor_));
    }
    p.setPen(Qt::gray);
    for(int i = 0 ; i < linesCount ; i++){
        qreal lh = h/5*(i+1);
		qreal ll = (max/5)*(linesCount-i)*scaleFactor_;
        p.drawLine(0,lh,w,lh);
		if(scale_){
            p.setPen(Qt::black);
            p.drawText(w+2,lh+4,QString::number(ll));
            p.setPen(Qt::gray);
        }
    }
    p.drawLine(0,0,w,0);
    p.drawLine(0,h,w,h);
    
    
    QPen pen(Qt::black);
    pen.setWidth(2);
    p.setPen(pen);
	
	//rysowanie wykresów
	foreach(const Plot *plot , plots_){
		p.setPen(plot->color());
		p.drawLine(0,h-(plot->average()*a),w,h-(plot->average()*a));
		
        const Points & pl = plot->points();
        pen.setColor(plot->color());
        p.setPen(pen);
        
        
        qreal x = 0;
        qreal y = 0;
        qreal step = w/(pl.size()-1);
        bool start = true;
        foreach(const qreal & r, pl){
            if(!start){
                p.drawLine(x,h-(y*a),x+step,h-(r*a));
                x += step;
            }else{
                 start = !start;
            }
            y = r;
        }
    }
    
    //ramka wokół wykresu
    p.setPen(Qt::black);
	if(frame_) p.drawRect(0,0,w-1,h-1);
}

Plot * Plotter::createPlot()
{
    return new Plot(this);
}

Plot * Plotter::createPlot(const QColor & col)
{
    return new Plot(this,col);
}

Plot * Plotter::createPlot(const Points & plot)
{
    QColor col(qrand()%256,qrand()%256,qrand()%256);
    return createPlot(plot,col);
}

Plot * Plotter::createPlot(const Points & plot,const QColor & col)
{
    return new Plot(this,plot,col);
}

Plot * Plotter::getPlot(int i)
{
	return plots_.at(i);
}

Plot * Plotter::getPlot(const QString& label)
{
	foreach(Plot * p , plots_){
		if(p->getLabel() == label)return p;
	}
	return NULL;
}

void Plotter::registerPlot(Plot * plot)
{
	if(plots_.indexOf(plot)==-1){
		plots_.append(plot);
    }
    
}

void Plotter::detachPlot(Plot * plot)
{
	plots_.removeAll(plot);
}

void Plotter::clearPlots(){
	foreach(Plot * p , plots_){
        p->clear();
    }
}

void Plotter::clearAll(){
	foreach(Plot * p , plots_){
        delete p;
    }
    plots_.clear();
}

QList<Plot* > & Plotter::getPlots()
{
	return plots_;
}

void Plotter::setFrame(bool f)
{
	frame_ = f;
}

void Plotter::setScale(bool f)
{
	scale_ = f;
}

void Plotter::setScaleFactor(qreal f)
{
	scaleFactor_ = f;
}





