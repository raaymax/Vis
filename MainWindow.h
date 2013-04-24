#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QFileDialog>
#include "ImageWidget.h"
#include "ImageSource.h"


namespace Ui{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow( QWidget * parent = 0);
    
    virtual ~MainWindow();
    
public slots:
    void showFileDialog();
    void run(const QString & filename);
private:
    ImageSource * source;
    ImageWidget * gpuViewer;
    ImageWidget * cpuViewer;
    QFileDialog * fileDialog;
    Ui::MainWindow * ui;
};

#endif // MAINWINDOW_H
