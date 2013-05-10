#ifndef PLOTTER_H_
#define PLOTTER_H_
#include <QWidget>
#include <QList>

class Plotter : public QWidget{
    Q_OBJECT
public:
    Plotter(QWidget * parent = 0);
    void paintEvent( QPaintEvent* );
    void addPlot(QList<qreal> & plot);
private:
    QList<QList<qreal> > plots;
};


#endif