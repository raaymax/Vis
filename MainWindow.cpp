#include <iostream>
#include <QPaintEvent>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QLayout>
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "FilterManager.h"
#include "CpuGrayFilter.h"
#include "GpuGrayFilter.h"
#include "exceptions/IException.h"
#include "config.h"
#include "plotter/Plotter.h"

MainWindow::MainWindow(QWidget * parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    gpuViewer(new ImageWidget()),
    cpuViewer(new ImageWidget()),
    fileDialog(new QFileDialog()),
    source(new ImageSource()),
    gpuPlot(new Plot()),
    cpuPlot(new Plot()),
    times(100),
    refreshed(true)
{
	
	gpuPlot->setPlotColor(QColor(255,0,0));
	cpuPlot->setPlotColor(QColor(0,255,0));
    ui->setupUi(this);
    gpuViewer->setImage(source->getImage());
    cpuViewer->setImage(source->getImage());
    gpuViewer->setFixedSize(512,384);
    cpuViewer->setFixedSize(512,384);
	plotter = new Plotter();
	plotter->addPlot(gpuPlot);
	plotter->addPlot(cpuPlot);
	ui->verticalLayout->addWidget(plotter);
	//layout()->addWidget(new Plotter());
    ui->horizontalLayout->addWidget(gpuViewer);
    ui->horizontalLayout->addWidget(cpuViewer);
	
    fileDialog->setFilter("jpeg (*.jpg , *.jpeg)");
    
    connect(ui->actionOpen , SIGNAL(triggered()),this,SLOT(showFileDialog()));
    connect(fileDialog, SIGNAL(fileSelected(QString)),this,SLOT(run(QString)));
}
void MainWindow::showFileDialog(){
    fileDialog->show();
}

void MainWindow::run(const QString & filename){
	plotter->reset();
    try{
        ImageSource * source = new ImageSource(filename); 
        
        if(this->source != NULL)
            delete this->source;
        this->source = source;
		Image img,img2;
		for(int i = 0 ; i < times ; i++){
			img = source->getImage();
			FilterManager<CpuGrayFilter> filterCPU;
			filterCPU.process(img);
			cpuPlot->addValue(filterCPU.getTime().total_milliseconds());
	//		std::cout<< "filter CPU time:" << filterCPU.getTime().total_microseconds() <<"us"<< std::endl;

			img2 = source->getImage();
#ifdef USE_CUDA      
			FilterManager<GpuGrayFilter> filterGPU;
			filterGPU.process(img2);
			gpuPlot->addValue(filterGPU.getTime().total_milliseconds());
	//		std::cout<< "filter GPU time:" << filterGPU.getTime().total_microseconds()<<"us" << std::endl;
#endif      
		}
		cpuViewer->setImage(img);
		gpuViewer->setImage(img2);
    }catch(IException & ex){
        QMessageBox msgBox;
        msgBox.setText(ex.getMessage());
        msgBox.exec();
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}

