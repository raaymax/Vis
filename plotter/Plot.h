#ifndef PLOT_H
#define PLOT_H
#include <QGraphicsItem>
#include <QWidget>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsScene>
#include <QColor>


class Plot: public QGraphicsItem
{
public:
    Plot(QGraphicsItem * parent = 0);
	QRectF boundingRect() const{
		return scene()->sceneRect();
	}
	QList<QPointF> getPoints();
	
	void reset();
	void addValue(qreal val);
	qreal getAverage();
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual ~Plot();
	QColor & getPlotColor(){return plotColor;}
	void setPlotColor(const QColor & c){plotColor=c;}
private:
	QColor plotColor;
	qreal average;
	QList<qreal> list;
};

#endif // PLOT_H
