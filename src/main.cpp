#include <Plotter.h>
#include <QApplication>
#include <QTimer>

int main(int argc , char ** argv){
    QApplication app(argc,argv);
    Plotter p;
    p.setFrame(false);
    p.setScale(true);
    p.setScaleFactor(1);
    Plot l;
    l.setLabel("Pierwszy");
    Points l2;
    Points l3;
    for(int i = 0 ; i < 20 ; i++){
        l.add(qrand()%40+40);
        l2.append(qrand()%40+20);
        l3.append(qrand()%40);
    }
    
    p.addPlot(l);
    p.addPlot(l2);
    p.addPlot(l3);
    
    return app.exec();
}
