#ifndef PLOTTER_H
#define PLOTTER_H
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QThread>

class Plot;

class Plotter : public QGraphicsView
{
	Q_OBJECT
public:
    Plotter(QWidget * parent = 0);
    virtual ~Plotter();
	void reset();
	void addPlot(Plot * plot);
	void fit(qreal _max);
	qreal getScale();
private:
	qreal max;
	QList<Plot *> plots;
	QGraphicsScene * scene;
};

#endif // PLOTTER_H
