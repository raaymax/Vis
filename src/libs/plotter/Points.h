#ifndef POINTS_H
#define POINTS_H
#include <QList>
#include <QObject>

typedef qreal Point;
typedef QList<qreal> Base_Points;

class Points:public QObject, public Base_Points
{
    Q_OBJECT
public:
    Points();
    Points(const Points& other);
    virtual ~Points();
    virtual Points& operator=(const Points& other);
    
    void push_front(Point p){
        prepend(p);
    }
    void push_back(Point p){
        append(p);
    }
    Point pop_front(){
        Point p = first();
        removeFirst();
        return p;
    }
    Point pop_back(){
        Point p = last();
        removeLast();
        return p;
    }
    
    Point max() const;
    Point min() const;
    Point average() const;
    
};

#endif // POINTS_H
