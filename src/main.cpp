#include <Plotter.h>
#include <QApplication>
#include <QTimer>
#include "MainWindow.h"


int main(int argc , char ** argv){
    QApplication app(argc,argv);
   
    MainWindow mainw;
    mainw.show();
    
    return app.exec();
}
