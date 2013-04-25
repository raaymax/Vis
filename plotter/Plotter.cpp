#include "Plotter.h"
#include <QHBoxLayout>
#include <QLayout>
#include "Plot.h"

Plotter::Plotter(QWidget * parent):
	QGraphicsView(parent),
	scene(new QGraphicsScene())
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
}

void Plotter::reset(){
	foreach(Plot * it ,plots){
		it->reset();
	}
}

Plotter::~Plotter()
{

}

