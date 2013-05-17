#include <iostream>
#include <QPaintEvent>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QLayout>
#include <QPushButton>
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
    gpuPlot(new Plot(QColor(255,0,0))),
    cpuPlot(new Plot(QColor(0,255,0))),
    times(20)
{
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
	QPushButton * button = new QPushButton("Test");
	ui->verticalLayout->addWidget(button);
    fileDialog->setFilter("jpeg (*.jpg , *.jpeg)");
	fileDialog->setFileMode(QFileDialog::ExistingFiles);
	plotter->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
	
	
    connect(ui->actionOpen , SIGNAL(triggered()),this,SLOT(showFileDialog()));
    connect(fileDialog, SIGNAL(fileSelected(QString)),this,SLOT(load(QString)));
	connect(fileDialog, SIGNAL(filesSelected(QStringList)),this,SLOT(load(QStringList)));
	connect(button,SIGNAL(pressed()),this,SLOT(run()));
}
void MainWindow::showFileDialog(){
    fileDialog->show();
}

void MainWindow::paintEvent(QPaintEvent *e)
{
	QMainWindow::paintEvent(e);
//	emit refreshed();
}

void MainWindow::load(const QString & filename){
	plotter->reset();
    try{
        ImageSource * source = new ImageSource(filename); 
        
        if(this->source != NULL)
            delete this->source;
        this->source = source;
		run();
		
    }catch(IException & ex){
        QMessageBox msgBox;
        msgBox.setText(ex.getMessage());
        msgBox.exec();
    }
}

void MainWindow::load(const QStringList & files){
	plotter->reset();
	try{
		ImageSource * source = new ImageSource(files); 
		
		if(this->source != NULL)
			delete this->source;
		this->source = source;
//		run();
		
	}catch(IException & ex){
		QMessageBox msgBox;
		msgBox.setText(ex.getMessage());
		msgBox.exec();
	}
}

void MainWindow::run(){
	if(source==NULL) return;
	try{
	
		Image img,img2;
		for(int i = 0 ; i < times ; i++){
			img2 = img = source->getImage();

			FilterManager<CpuGrayFilter> filterCPU;
			filterCPU.process(img);
			cpuPlot->addValue(filterCPU.getTime().total_milliseconds());
			//std::cout<< "filter CPU time:" << filterCPU.getTime().total_microseconds() <<"us"<< std::endl;

#ifdef USE_CUDA      
			FilterManager<GpuGrayFilter> filterGPU;
			filterGPU.process(img2);
			gpuPlot->addValue(filterGPU.getTime().total_milliseconds());
			//std::cout<< "filter GPU time:" << filterGPU.getTime().total_microseconds()<<"us" << std::endl;
#endif      
			cpuViewer->setImage(img);
			gpuViewer->setImage(img2);
			
			repaint();
			plotter->setFocus();
		}
		
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

