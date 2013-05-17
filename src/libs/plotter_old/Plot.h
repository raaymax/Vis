#ifndef PLOT_H
#define PLOT_H
#include <QGraphicsItem>
#include <QWidget>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsScene>
#include <QColor>
#include <boost/concept_check.hpp>

class Plotter;
class Plot: public QGraphicsItem
{
public:
	Plot(const QColor & plotColor, QGraphicsItem * parent = 0);
	QRectF boundingRect() const{
		return scene()->sceneRect();
	}
	QList<QPointF> getPoints();
	void setPlotter(Plotter * p);
	void reset();
	void addValue(qreal val);
	qreal getMaximum();
	qreal getAverage();
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual ~Plot();
	QColor & getPlotColor(){return plotColor;}
	void setPlotColor(const QColor & c){plotColor=c;}
private:
	Plotter * plotter;
	QColor plotColor;
	qreal average;
	qreal max;
	QList<qreal> list;
	QList<QPointF> points;
	
	QPen averagePen;
    QPen plotPen;
};

#endif // PLOT_H
