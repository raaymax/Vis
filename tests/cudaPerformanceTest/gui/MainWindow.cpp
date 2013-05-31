#include <iostream>
#include <QPaintEvent>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QLayout>
#include <QPushButton>
#include <FilterManager.h>
#include <GpuGrayFilter.h>
#include <CpuGrayFilter.h>
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "exceptions/IException.h"
#include <config.h>
#include <plotter/Plotter.h>

MainWindow::MainWindow(QWidget * parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    gpuViewer(new ImageWidget()),
    cpuViewer(new ImageWidget()),
    fileDialog(new QFileDialog()),
    source(new ImageSource()),
    plotter(new Plotter),
    times(20)
{
	gpuPlot = plotter->createPlot(Qt::red);
	cpuPlot = plotter->createPlot(Qt::green);
    ui->setupUi(this);
    gpuViewer->setImage(source->getImage());
    cpuViewer->setImage(source->getImage());
    gpuViewer->setFixedSize(512,384);
    cpuViewer->setFixedSize(512,384);
	ui->verticalLayout->addWidget(plotter);

    ui->horizontalLayout->addWidget(gpuViewer);
    ui->horizontalLayout->addWidget(cpuViewer);
	QPushButton * button = new QPushButton("Test");
	QPushButton * reset = new QPushButton("Reset");
	ui->verticalLayout->addWidget(button);
	ui->verticalLayout->addWidget(reset);
    fileDialog->setFilter("jpeg (*.jpg , *.jpeg)");
	fileDialog->setFileMode(QFileDialog::ExistingFiles);

    connect(ui->actionOpen , SIGNAL(triggered()),this,SLOT(showFileDialog()));
    connect(fileDialog, SIGNAL(fileSelected(QString)),this,SLOT(load(QString)));
	connect(fileDialog, SIGNAL(filesSelected(QStringList)),this,SLOT(load(QStringList)));
	connect(button,SIGNAL(pressed()),this,SLOT(run()));
	connect(reset,SIGNAL(pressed()),this,SLOT(reset()));
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
	plotter->clearPlots();
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
	plotter->clearPlots();
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
			cpuPlot->add(filterCPU.getTime().total_milliseconds());
			//std::cout<< "filter CPU time:" << filterCPU.getTime().total_microseconds() <<"us"<< std::endl;


#ifdef USE_CUDA      
			FilterManager<GpuGrayFilter> filterGPU;
			filterGPU.process(img2);
			gpuPlot->add(filterGPU.getTime().total_milliseconds());
			//std::cout<< "filter GPU time:" << filterGPU.getTime().total_microseconds()<<"us" << std::endl;
#endif

			cpuViewer->setImage(img);
			gpuViewer->setImage(img2);
			cpuViewer->repaint();
			gpuViewer->repaint();
			
		}
		
	}catch(IException & ex){
		QMessageBox msgBox;
		msgBox.setText(ex.getMessage());
		msgBox.exec();
	}
}

void MainWindow::reset(){
	plotter->clearPlots();
}


MainWindow::~MainWindow()
{
    delete ui;
}

