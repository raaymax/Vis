#ifndef PLOTTER_H
#define PLOTTER_H
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "Plot.h"

class Plotter : public QGraphicsView
{
	Q_OBJECT
public:
    Plotter(QWidget * parent = 0);
    virtual ~Plotter();
	void reset();
	void addPlot(Plot * plot);
	
private:
	QList<Plot *> plots;
	QGraphicsScene * scene;
};

#endif // PLOTTER_H
