#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include "VideoConverterWindow.h"
#include "ui_VideoConverterWindow.h"

VideoConverterWindow::VideoConverterWindow(VideoConverter * conv, QWidget * parent ):
    QMainWindow(parent),
    ui(new Ui::VideoConverterWindow),
    plotter(new Plotter),
    plot(NULL),
    conv(conv)
{
    ui->setupUi(this);
    plot = plotter->createPlot(Qt::red);
    
    ui->plotterWidget->setLayout(new QHBoxLayout);
    ui->plotterWidget->layout()->addWidget(plotter);
    Plot::default_max_points_count = 1000;
    ui->processButton->setEnabled(false);
    ui->progressBar->setRange(0,100);
    ui->progressBar->setEnabled(false);
    ui->progressBar->setValue(0);
    connect(ui->sourceButton,SIGNAL(pressed()),this,SLOT(chooseSource()));
    connect(ui->outputButton,SIGNAL(pressed()),this,SLOT(chooseOutput()));
	connect(conv,SIGNAL(progress(double)),this,SLOT(setProgress(double)));
	connect(conv,SIGNAL(processingDone()),this,SLOT(processingDone()));
	connect(ui->processButton,SIGNAL(pressed()),this,SLOT(startProcessing()));
}

VideoConverterWindow::~VideoConverterWindow()
{
    delete conv;
}

void VideoConverterWindow::unlockProcessButtonIfReady(){
    if( conv->isOpened()){
		/*
        try{
            conv = new VideoConverter(sourceFile,outputFile);
        }catch(const char * msg){
            qDebug() << msg;
            return;
        }*/
        ui->processButton->setEnabled(true);
        ui->progressBar->setEnabled(true);
    }
}

void VideoConverterWindow::startProcessing(){
    conv->processAll();
}

void VideoConverterWindow::processingDone(){
	ui->processButton->setEnabled(false);
	ui->progressBar->setEnabled(false);
	ui->outputLabel->setText(" ");
	ui->progressBar->setValue(0);
	QMessageBox::information(this,"Processing Done","Operation finnished!");
}


void VideoConverterWindow::setProgress(double progress){
    ui->progressBar->setValue(progress*100);
 //   plot->add(progress*100);
}

void VideoConverterWindow::chooseSource(){
    sourceFile = QFileDialog::getOpenFileName(this, tr("Open File"), ".",tr("Video (*.avi)"));
    conv->open(sourceFile);
    if(conv->isInputOpened()){
        ui->sourceLabel->setText(sourceFile);
        unlockProcessButtonIfReady();
    }else{
        QMessageBox::warning(this,"Problem with file","Could not open file.");

    }
}
void VideoConverterWindow::chooseOutput(){
    outputFile = QFileDialog::getSaveFileName(this, tr("Save File"), ".", tr("Video (*.avi)"));
    conv->saveTo(outputFile);
    if(conv->isOutputOpened()){
        ui->outputLabel->setText(outputFile);
        unlockProcessButtonIfReady();
    }else{
        QMessageBox::warning(this,"Problem with file","Could not open file.");
        
    }
}
