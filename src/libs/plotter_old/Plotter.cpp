#include "Plotter.h"
#include <QHBoxLayout>
#include <QLayout>
#include <QGLWidget>
#include "Plot.h"

Plotter::Plotter(QWidget * parent):
	QGraphicsView(parent),
	scene(new QGraphicsScene()),
	max(1)
{
	setScene(scene);
	setFixedSize(1024,135);
	setRenderHint(QPainter::Antialiasing);
	setLineWidth(5);
	scene->setSceneRect(0,0,1024,128);
	setGeometry(0,0,1024,135);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void Plotter::addPlot(Plot * plot){
	plots.append(plot);
	scene->addItem(plot);
	plot->setPlotter(this);
}

void Plotter::fit(qreal _max){
	if(max < _max){
		max = _max;
		
	}
}

qreal Plotter::getScale(){
	return sceneRect().height()/max;
}

void Plotter::reset(){
	foreach(Plot * it ,plots){
		it->reset();
	}
	max = 1;
}

Plotter::~Plotter()
{

}

