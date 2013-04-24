#include <iostream>
#include <QHBoxLayout>
#include <QMessageBox>
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "FilterManager.h"
#include "CpuGrayFilter.h"
#include "GpuGrayFilter.h"
#include "exceptions/IException.h"

MainWindow::MainWindow(QWidget * parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    gpuViewer(new ImageWidget()),
    cpuViewer(new ImageWidget()),
    fileDialog(new QFileDialog()),
    source(new ImageSource())
{
    ui->setupUi(this);
    gpuViewer->setImage(source->getImage());
    cpuViewer->setImage(source->getImage());
    gpuViewer->setFixedSize(512,512);
    cpuViewer->setFixedSize(512,512);
    ui->centralwidget->layout()->addWidget(gpuViewer);
    ui->centralwidget->layout()->addWidget(cpuViewer);
    fileDialog->setFilter("jpeg (*.jpg , *.jpeg)");
    
    connect(ui->actionOpen , SIGNAL(triggered()),this,SLOT(showFileDialog()));
    connect(fileDialog, SIGNAL(fileSelected(QString)),this,SLOT(run(QString)));
}
void MainWindow::showFileDialog(){
    fileDialog->show();
}

void MainWindow::run(const QString & filename){
    try{
        if(source != NULL)
            delete source;
        
        source = new ImageSource(filename); 
    
        Image img = source->getImage();
        FilterManager<CpuGrayFilter> filterCPU;
        filterCPU.process(img);
        std::cout<< "filter CPU time:" << filterCPU.getTime().total_microseconds() <<"us"<< std::endl;
        cpuViewer->setImage(img);
        

        Image img2 = source->getImage();
#ifdef USE_CUDA      
        FilterManager<GpuGrayFilter> filterGPU;
        filterGPU.process(img2);
        std::cout<< "filter GPU time:" << filterGPU.getTime().total_microseconds()<<"us" << std::endl;
#endif      
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

