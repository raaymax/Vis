#include "VideoConverterWindow.h"
#include "ui_VideoConverterWindow.h"

VideoConverterWindow::VideoConverterWindow( QWidget * parent ):
    QMainWindow(parent),
    ui(new Ui::VideoConverterWindow),
    plotter(new Plotter),
    conv(NULL)
{
    plot = plotter->createPlot(Qt::red);
    this->ui->centralwidget->layout()->addWidget(plotter);
}

VideoConverterWindow::~VideoConverterWindow()
{

}

