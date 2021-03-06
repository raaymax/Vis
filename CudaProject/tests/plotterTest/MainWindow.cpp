
#include "MainWindow.h"
#include <QVBoxLayout>
#include <QTime>
#include <QDebug>
#include <QtCore/qmath.h>
#include <QTimer>
#include <plotter/Plot.h>
#include <QList>
#include <QPushButton>

MainWindow::MainWindow():QMainWindow(){
   // setLayout(new QVBoxLayout);
    plotter = new Plotter();
	setCentralWidget(plotter);
    timer = new QTimer();
    qsrand( QTime::currentTime().msec());
    
    plotter->setFrame(true);
    plotter->setScale(true);
    plotter->setScaleFactor(1);
    plot = plotter->createPlot(Qt::red);
 //   plotter->createPlot(Qt::blue);
    connect(timer,SIGNAL(timeout()),this,SLOT(newPoint()));
    timer->start(1000);
//    QPushButton * clear = new QPushButton(this);
   // connect(clear,SIGNAL(pressed()),this,SLOT(clearPlotter()));
}

void MainWindow::newPoint(){
    int i = 0;

	plot->add(qrand()%50+50);
    
    timer->start(100);
}
void MainWindow::clearPlotter(){
    plotter->clearPlots();
    timer->stop();
}



MainWindow::~MainWindow()
{

}

