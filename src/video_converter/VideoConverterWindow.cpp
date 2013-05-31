#include <QFileDialog>
#include "VideoConverterWindow.h"
#include "ui_VideoConverterWindow.h"

VideoConverterWindow::VideoConverterWindow( QWidget * parent ):
    QMainWindow(parent),
    ui(new Ui::VideoConverterWindow),
    plotter(new Plotter),
    conv(NULL),
    plot(NULL),
    isSourceChoosen(false),
    isOutputChoosen(false)
{
    ui->setupUi(this);
  //  plot = plotter->createPlot(Qt::red);
 //   ui->centralwidget->layout()->addWidget(plotter);
 //   ui->processButton->setEnabled(false);
 //   ui->progressBar->setRange(0,100);
//    ui->progressBar->setEnabled(false);
 //   ui->progressBar->setValue(0);
 //   connect(ui->sourceButton,SIGNAL(pressed()),this,SLOT(chooseSource()));
  //  connect(ui->outputButton,SIGNAL(pressed()),this,SLOT(chooseOutput()));
}

VideoConverterWindow::~VideoConverterWindow()
{
    delete conv;
}

void VideoConverterWindow::unlockProcessButtonIfReady(){
    if(isSourceChoosen and isOutputChoosen){
        conv = new VideoConverter(sourceFile,outputFile);
        connect(conv,SIGNAL(progress(double)),this,SLOT(setProgress(double)));
        ui->processButton->setEnabled(true);
        ui->progressBar->setEnabled(true);
    }
}

void VideoConverterWindow::setProgress(double progress){
    ui->progressBar->setValue(progress*100);
}

void VideoConverterWindow::chooseSource(){
    sourceFile = QFileDialog::getOpenFileName(this, tr("Open File"), ".",tr("Video (*.avi)"));
    ui->sourceLabel->setText(sourceFile);
    isSourceChoosen = true;
    unlockProcessButtonIfReady();
}
void VideoConverterWindow::chooseOutput(){
    outputFile = QFileDialog::getSaveFileName(this, tr("Save File"), ".", tr("Video (*.avi)"));
    isOutputChoosen = true;
    ui->outputLabel->setText(outputFile);
    unlockProcessButtonIfReady();
}