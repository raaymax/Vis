#include "Plot.h"
#include "Plotter.h"

int Plot::default_max_points_count = 100;

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

QColor & Plot::color(){
    return second;
}

const QColor & Plot::color() const{
    return second;
}
Points & Plot::points(){
    return first;
}
const Points & Plot::points() const{
    return first;
}

void Plot::registerInPlotter(){
    parent_->registerPlot(this);
    connect(this,SIGNAL(changed()),parent_,SLOT(update()));
}
