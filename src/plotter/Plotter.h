#ifndef PLOTTER_H_
#define PLOTTER_H_

#include <QWidget>
#include <QList>
#include <QColor>
#include <QPair>
#include <QPen>
#include "Plot.h"

class QPainter;

class Plotter : public QWidget{
    Q_OBJECT
public:
	///TODO: Ustawianie rozmiarów wykresu
    Plotter(QWidget * parent = 0);
    virtual ~Plotter();
    Plot * createPlot();
    Plot * createPlot(const QColor &color);
    Plot * createPlot(const Points & plot);
    Plot * createPlot(const Points & plot, const QColor &color );
    
	Plot * getPlot(int i);
	//funkcja zwraca pierwszy napotkany wykres z daną etykietą
	Plot * getPlot(const QString& label);
    
    void registerPlot(Plot * plot);
    void detachPlot(Plot * plot);
    
    void clearPlots();
    void clearAll();
    
    QList<Plot* > & getPlots();
    
    void setFrame(bool f);
    void setScale(bool f);
    void setScaleFactor(qreal f);
protected:
    void paintEvent( QPaintEvent* );
private:
	
	void initVars(int paddingLeft);
	void drawBackground(QPainter &p);
	void drawScale(QPainter &p);
	void drawPlots(QPainter &p);
	void drawFrame(QPainter &p);
	
	uint w;
	uint h;
	uint linesCount;
	int startPoint;
	qreal minValue;
	qreal correction;
	qreal maxValue;
	qreal diffValue;
	QPen plotterPen;
    bool frame_;
    bool scale_;
    qreal scaleFactor_;
    QList<Plot* > plots_;
};


#endif
