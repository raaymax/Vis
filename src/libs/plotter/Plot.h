#ifndef PLOT_H
#define PLOT_H
#include <QColor>
#include <QList>
#include <QPair>
#include <Points.h>

typedef QPair<Points, QColor> Base_Plot;
class Plotter;

class Plot : public QObject, protected Base_Plot
{
    Q_OBJECT
public:
    Plot(Plotter * parent);
    Plot(Plotter * parent, const QColor &c);
    Plot(Plotter * parent, const Points & p,const QColor &c);
    Plot(Plotter * parent, const Plot& other);
    
    virtual ~Plot();
    virtual Plot& operator=(const Plot& other);
    QColor & color();
    const QColor & color() const;
    Points & points();
    const Points & points() const;
    
    Point average() const{
        return points().average();
    }
    
    Point max() const{
        return points().max();
    }
    Point min() const{
        return points().min();
    }
    void add(Point p){
        points().append(p);
        if(default_max_points_count < points().count())
            points().pop_front();
        emit changed();
    }
    
    void clear(){
        first.clear();
        emit changed();
    }
    QString getLabel(){return label_;}
    void setLabel(QString lab){label_ = lab;}
signals:
    void changed();
    
private:
    void registerInPlotter();
    
    QString label_;
    Plotter * parent_;
    
    static int default_max_points_count;
};

#endif // PLOT_H
