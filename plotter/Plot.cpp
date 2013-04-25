#include "Plot.h"
#include <QDebug>
#include <QPen>


Plot::Plot(QGraphicsItem * parent):
	QGraphicsItem(parent),
	average(0)
{
}


void Plot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QPen pen(plotColor);
	pen.setWidth(1);
	painter->setPen(pen);
	
	qreal av = boundingRect().height()-getAverage();
	QString avg = "Avg: ";
	avg += QString::number(getAverage());
	painter->drawText(QPointF(5,av-5),avg);
	painter->drawLine(0,av,boundingRect().width(),av);
	pen.setWidth(2);
	painter->setPen(pen);
	QPolygonF poly(QVector<QPointF>::fromList(getPoints()));
	painter->drawPolyline(poly);
	
}

QList<QPointF> Plot::getPoints(){
	QList<QPointF> points ;
	qreal step = boundingRect().width()/(list.count()-1);
	qreal x = 0;
	qreal yfix = boundingRect().height();
	for(QList<qreal>::iterator it = list.begin() ; it < list.end() ; it++){
		points.append(QPointF(x,yfix-(*it)));
		x+=step;
	}
	
	return points;
}



void Plot::addValue(qreal val){
	list.append(val);
	qreal sum = 0; 
	for(QList<qreal>::iterator it = list.begin() ; it < list.end() ; it++){
		sum += (*it);
	}
	average = sum/list.count();
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

