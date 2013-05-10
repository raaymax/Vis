#include <Plotter.h>
#include <QApplication>

int main(int argc , char ** argv){
    QApplication app(argc,argv);
    
    Plotter p;
    QList<qreal> l;
    l.append(100);
    l.append(30);
    l.append(60);
    l.append(10);
    l.append(80);
    l.append(90);
    p.addPlot(l);
    p.show();
    
    return app.exec();
}
