#include <iostream>
#include <QPaintEvent>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QLayout>
#include <QPushButton>
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "exceptions/IException.h"
#include <config.h>
#include <plotter/Plotter.h>
#include <Runner.h>
#include <testFilter.h>
#include <boost/bind/bind.hpp>

MainWindow::MainWindow(QWidget * parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    gpuViewer(new ImageWidget()),
    cpuViewer(new ImageWidget()),
    fileDialog(new QFileDialog()),
    source(new ImageSource()),
    plotter(new Plotter),
    times(1)
{
	debug("in");
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
	debug("out");
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
		debug("in");
        ImageSource * source = new ImageSource(filename); 
        
        if(this->source != NULL)
            delete this->source;
        this->source = source;
		run();
		debug("out");
    }catch(IException & ex){
        QMessageBox msgBox;
        msgBox.setText(ex.getMessage());
        msgBox.exec();
    }
}

void MainWindow::load(const QStringList & files){
	plotter->clearPlots();
	try{
		debug("in");
		ImageSource * source = new ImageSource(files); 
		
		if(this->source != NULL)
			delete this->source;
		this->source = source;
//		run();
		debug("out");
	}catch(IException & ex){
		QMessageBox msgBox;
		msgBox.setText(ex.getMessage());
		msgBox.exec();
	}
}

void MainWindow::run(){
	debug("init");
	TestFilter cpuFilter(CPU);
	debug("init cpu done");
	TestFilter gpuFilter(GPU);
	debug("init gpu done");
	if(source==NULL) return;
	try{
		debug("in");

		for(int i = 0 ; i < times ; i++){
			debug("loop start");
			
			source->setType(CPU);
			Image img = source->getImage();
		
			Runner<Image> filterCPU(bind(&TestFilter::process, &cpuFilter, _1));
			filterCPU.run(img);
			cpuPlot->add(filterCPU.getTime().total_milliseconds());
			//std::cout<< "filter CPU time:" << filterCPU.getTime().total_microseconds() <<"us"<< std::endl;
//#if 0
//#ifdef USE_CUDA
			source->setType(GPU);
			Image img2 = source->getImage();
			assert(img2.getType() == GPU);
			
			Runner<Image> filterGPU(bind(&TestFilter::process, &gpuFilter, _1));
			filterGPU.run(img2);
			gpuPlot->add(filterGPU.getTime().total_milliseconds());
			
			//std::cout<< "filter GPU time:" << filterGPU.getTime().total_microseconds()<<"us" << std::endl;
//#endif

			cpuViewer->setImage(img);
			gpuViewer->setImage(img2);
			cpuViewer->repaint();
			gpuViewer->repaint();
			source->loadNext();
			debug("loop end");
		}
		debug("out");
	}catch(IException & ex){
		QMessageBox msgBox;
		msgBox.setText(ex.getMessage());
		msgBox.exec();
	}
	debug("exit");
}

void MainWindow::reset(){
	plotter->clearPlots();
}


MainWindow::~MainWindow()
{
    delete ui;
}

