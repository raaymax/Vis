#include "Points.h"

Points::Points():
    Base_Points(){}

Points::Points(const Points& other):
    Base_Points(other){}

Points::~Points(){}

Points& Points::operator=(const Points& other)
{
    Base_Points::operator=(other);
    return *this;
}

void Points::push_front(const Point & p)
{
	prepend(p);
}
void Points::push_back(const Point & p)
{
	append(p);
}
Point Points::pop_front()
{
	Point p = first();
	removeFirst();
	return p;
}
Point Points::pop_back()
{
	Point p = last();
	removeLast();
	return p;
}

Point Points::max() const
{
    Point max = first();
    foreach(const Point & p , *this){
        if(max < p) max = p;
    }
    return max;
}
Point Points::min() const
{
    Point min = first();
    foreach(const Point & p , *this){
        if(min > p) min = p;
    }
    return min;
}

Point Points::average() const
{
    Point sum = 0;
    foreach(const Point & p , *this){
        sum += p;
    }
    return sum/count();
}
