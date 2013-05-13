#ifndef LEGEND_H
#define LEGEND_H

#include <QWidget>
#include <Plot.h>


class Legend : public QWidget
{
    Q_OBJECT
public:
    Legend(const QList<Plot >& plots);
protected:
    const QList<Plot >& plots;
};

#endif // LEGEND_H
