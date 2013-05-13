#include "Legend.h"
#include <QHBoxLayout>
#include <QLabel>
#include <qstyle.h>

Legend::Legend(const QList<Plot >& plotsList):
    plots(plotsList)
{
    setLayout(new QVBoxLayout);

}



