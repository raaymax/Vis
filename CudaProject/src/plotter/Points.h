#ifndef POINTS_H
#define POINTS_H
#include <QList>
#include <QObject>

typedef qreal Point;
typedef QList<Point> Base_Points;

class Points:public QObject, public Base_Points
{
    Q_OBJECT
public:
    Points();
    Points(const Points& other);
    virtual ~Points();
    virtual Points& operator=(const Points& other);
    
    void push_front(const Point & p);
    void push_back(const Point & p);
    Point pop_front();
    Point pop_back();
    
    Point max() const;
    Point min() const;
    Point average() const;
    
};

#endif // POINTS_H
