#include "Plot.h"

Plot::Plot():
    Base_Plot(),
    label("Plot")
{

}
Plot::Plot(const QColor &c):
    Base_Plot(Points(),c),
    label("Plot")
{
    
}
Plot::Plot(const Points & p,const QColor &c):
    Base_Plot(p,c),
    label("Plot")
{
    
}

Plot::Plot(const Plot& other):
    Base_Plot(other),
    label("Plot")
{
}

Plot::~Plot()
{
    
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