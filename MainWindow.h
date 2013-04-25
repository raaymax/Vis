#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QFileDialog>
#include "ImageWidget.h"
#include "ImageSource.h"
#include <plotter/Plot.h>
#include <plotter/Plotter.h>
#include <QPaintEvent>

namespace Ui{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
	const int times;
	
    explicit MainWindow( QWidget * parent = 0);
    
    virtual ~MainWindow();
public slots:
    void showFileDialog();
    void run(const QString & filename);
	
private:
	bool refreshed;
    ImageSource * source;
    ImageWidget * gpuViewer;
    ImageWidget * cpuViewer;
	Plot * gpuPlot;
	Plot * cpuPlot;
	Plotter * plotter;
    QFileDialog * fileDialog;
    Ui::MainWindow * ui;
};

#endif // MAINWINDOW_H
