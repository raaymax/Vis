#include "Plotter.h"
#include <QPainter>
#include <qpaintengine.h>
#include <QDebug>
#include <boost/concept_check.hpp>

Plotter::Plotter(QWidget * parent):
QWidget(parent),
frame_(true),
scale_(true),
scaleFactor_(1),
linesCount(4),
plotterPen(Qt::black)
{
	plotterPen.setWidth(2);
	// setFixedSize(500,150);
}

Plotter::~Plotter()
{
	foreach(Plot * p , plots_){
		delete p;
	}
}

void Plotter::initVars(int paddingLeft){
	w = width();
	h = height();
	w-=paddingLeft;
	
	maxValue = plots_.first()->max();
	minValue = plots_.first()->min();
	 
	foreach(const Plot *plot , plots_){
		if(maxValue < plot->max()) maxValue = plot->max();
		if(minValue > plot->min()) minValue = plot->min();
	}
	diffValue = maxValue-minValue;
	if(diffValue <= 0){ diffValue=1;maxValue=1; }
	correction = h/diffValue;
	startPoint = minValue;
	
//	qDebug() << w << " " << h << " " << maxValue<< " " << minValue<< " " << diffValue<< " " << startPoint<< " " << correction;
}

void Plotter::drawBackground(QPainter &p){
	//białe tło i wygładanie krawędzi
	p.setBrush(Qt::white);
	p.setPen(Qt::white);
	p.drawRect(0,0,w-1,h-1);
	p.setRenderHint(QPainter::Antialiasing);
}

void Plotter::drawScale(QPainter &p){
	//rysowanie skali 
	if(scale_){
		p.setPen(Qt::black);
		p.drawText(w+2,h,QString::number(minValue*scaleFactor_));
		p.drawText(w+2,10,QString::number(maxValue*scaleFactor_));
	}
	p.setPen(Qt::gray);
	for(int i = 0 ; i < linesCount ; i++){
		qreal lh = h/5*(i+1);
		qreal ll = (diffValue/5)*(linesCount-i)*scaleFactor_+minValue;
		p.drawLine(0,lh,w,lh);
		if(scale_){
			p.setPen(Qt::black);
			p.drawText(w+2,lh+4,QString::number(ll));
			p.setPen(Qt::gray);
		}
	}
	p.drawLine(0,0,w,0);
	p.drawLine(0,h,w,h);
}

void Plotter::drawPlots(QPainter &p){
	//rysowanie wykresów
	foreach(const Plot *plot , plots_){
		//średnia wartość z wykresu
		qreal plotY = h+startPoint*correction-(plot->average()*correction);
		p.setPen(plot->color());
		p.drawLine(0,plotY,w,plotY);
		plotterPen.setColor(plot->color());
		p.setPen(plotterPen);
		p.drawText(10,(plotY<25?25:plotY),
				   QString::number(plot->average()));
		
		
		const Points & pl = plot->points();
		qreal x = 0,prevVal=0;
		qreal step = w/(qreal)(pl.size()>1?pl.size()-1:1);
	//	qDebug() << step;
		bool start = true;
		foreach(const qreal & val, pl){
			if(!start){
				p.drawLine(x,h+startPoint*correction-(prevVal*correction),
						   x+step,h+startPoint*correction-(val*correction));
	//			qDebug() << x<<" "<<h+startPoint*correction-(prevVal*correction)<<" "<<x+step<<" "<<h+startPoint*correction-(val*correction);
				x += step;
			}else{
				start = !start;
			}
			prevVal = val;
		}
	}
}
void Plotter::drawFrame(QPainter &p){
	//ramka wokół wykresu
	p.setBrush(Qt::transparent);
	p.setPen(Qt::black);
	p.drawRect(0,0,w-1,h-1);
}

void Plotter::paintEvent( QPaintEvent* )
{
	QPainter p(this);
	int paddingLeft = 0;
	if(scale_)
		paddingLeft = 35;
	initVars(paddingLeft);
	
	drawBackground(p);

	drawScale(p);

	drawPlots(p);
	if(frame_)
		drawFrame(p);

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


