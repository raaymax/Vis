#ifndef PLOT_H
#define PLOT_H
#include <QColor>
#include <QList>
#include <QPair>
#include <Points.h>

typedef QPair<Points, QColor> Base_Plot;

class Plot : public Base_Plot
{
    
public:
    Plot();
    Plot(Points & p, QColor &c);
    Plot(const Plot& other);
    virtual ~Plot();
    virtual Plot& operator=(const Plot& other);
    QColor & color();
    const QColor & color() const;
    Points & points();
    const Points & points() const;
    Point max() const{
        return points().max();
    }
    Point min() const{
        return points().min();
    }
    void add(Point p){
        points().append(p);
    }
    QString getLabel(){return label;}
    void setLabel(QString lab){label = lab;}
    
private:
    QString label;
    
};

#endif // PLOT_H
