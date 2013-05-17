#include "Plot.h"
#include "Plotter.h"

int Plot::default_max_points_count = 10;

Plot::Plot(Plotter * parent):
    parent_(parent),
    Base_Plot(),
    label_("Plot")
{
    registerInPlotter();
}
Plot::Plot(Plotter * parent, const QColor &c):
    parent_(parent),
    Base_Plot(Points(),c),
    label_("Plot")
{
    registerInPlotter();
}
Plot::Plot(Plotter * parent, const Points & p,const QColor &c):
    parent_(parent),
    Base_Plot(p,c),
    label_("Plot")
{
    registerInPlotter();
}

Plot::Plot(Plotter * parent, const Plot& other):
    parent_(parent),
    Base_Plot(other),
    label_("Plot")
{
    registerInPlotter();
}

Plot::~Plot()
{
    parent_->detachPlot(this);
    disconnect(this,SIGNAL(changed()),parent_,SLOT(update()));
}

Plot& Plot::operator=(const Plot& other)
{   
    Base_Plot::operator=(other);
    return *this;
}

void Plot::setColor(const QColor & color)
{
    second = color;
}

const QColor & Plot::color() const
{
    return second;
}
Points & Plot::points()
{
    return first;
}
const Points & Plot::points() const
{
    return first;
}

Point Plot::average() const
{
	return points().average();
}

Point Plot::max() const
{
	return points().max();
}
Point Plot::min() const
{
	return points().min();
}
void Plot::add(Point p)
{
	points().append(p);
	if(default_max_points_count < points().count())
		points().pop_front();
	emit changed();
}

void Plot::clear()
{
	first.clear();
	emit changed();
}

const QString & Plot::getLabel()const
{
	return label_;
}

void Plot::setLabel(const QString & lab)
{
	label_ = lab;
	emit labelChanged();
}

void Plot::registerInPlotter()
{
    parent_->registerPlot(this);
    connect(this,SIGNAL(changed()),parent_,SLOT(update()));
}
