#include "Points.h"

Points::Points():
    Base_Points()
{

}

Points::Points(const Points& other):
    Base_Points(other)
{

}

Points::~Points()
{

}

Points& Points::operator=(const Points& other)
{
    Base_Points::operator=(other);
    return *this;
}



Point Points::max() const{
    Point max = first();
    foreach(const Point & p , *this){
        if(max < p) max = p;
    }
    return max;
}
Point Points::min() const{
    Point min = first();
    foreach(const Point & p , *this){
        if(min > p) min = p;
    }
    return min;
}