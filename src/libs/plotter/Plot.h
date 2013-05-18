/**
 * @todo indywidualna zmiana maksymalnei ilości punktów
 */

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
    friend class Plotter;
    Plot(Plotter * parent);
    Plot(Plotter * parent, const QColor &c);
    Plot(Plotter * parent, const Points & p,const QColor &c);
    Plot(Plotter * parent, const Plot& other);
public:    
    virtual ~Plot();
    virtual Plot& operator=(const Plot& other);
	
    void setColor(const QColor & color);
    const QColor & color() const;
    Points & points();
    const Points & points() const;
    
    Point average() const;
    Point max() const;
    Point min() const;
	
    void add(Point p);
    void clear();
	
    const QString & getLabel()const;
    void setLabel(const QString & lab);
signals:
    void changed();
	void labelChanged();
    
private:
    void registerInPlotter();
    
    QString label_;
    Plotter * parent_;
    
    static int default_max_points_count;
};

#endif // PLOT_H
