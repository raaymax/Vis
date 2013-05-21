#include "Plot.h"
#include <QDebug>
#include <iostream>
#include <QPen>
#include "Plotter.h"

Plot::Plot(const QColor & plotColor, QGraphicsItem * parent):
	QGraphicsItem(parent),
	average(0),
	max(0),
	plotter(NULL),
	averagePen(plotColor),
	plotPen(plotColor)
{
	averagePen.setWidth(1);
	plotPen.setWidth(2);
}


void Plot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//	std::cout << "painting" << painter << std::endl;
	
	painter->setPen(averagePen);
	
	qreal av = boundingRect().height()-((plotter!=NULL)?getAverage()*plotter->getScale():getAverage());
	QString avg = "Avg: ";
	avg += QString::number(getAverage());
	painter->drawText(QPointF(5,av-5),avg);
	painter->drawLine(0,av,boundingRect().width(),av);

	painter->setPen(plotPen);
	QPolygonF poly(QVector<QPointF>::fromList(getPoints()));
	painter->drawPolyline(poly);
	
}

void Plot::setPlotter(Plotter * p){
	plotter = p;
}

QList<QPointF> Plot::getPoints(){

	return points;
}



void Plot::addValue(qreal val){
	list.append(val);
	qreal sum = 0; 
	for(QList<qreal>::iterator it = list.begin() ; it < list.end() ; it++){
		sum += (*it);
	}
	average = sum/list.count();
	if(val > max){ 
		max = val;
	}
	if(plotter != NULL) plotter->fit(getMaximum());
	
	
	points.clear();
	qreal step = boundingRect().width()/(list.count()-1);
	qreal x = 0;
	qreal yfix = boundingRect().height();
	for(QList<qreal>::iterator it = list.begin() ; it < list.end() ; it++){
		points.append(QPointF(x,yfix-((plotter!=NULL)?(*it)*plotter->getScale():(*it))));
		x+=step;
	}
	
	update();
}
qreal Plot::getMaximum(){
	return max;
}
qreal Plot::getAverage(){
	return average;
}

void Plot::reset(){
	average = 0;
	list.clear();
}

Plot::~Plot()
{

}

