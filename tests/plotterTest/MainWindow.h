#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Plotter.h>

class QTime;
class MainWindow: public QMainWindow{
    Q_OBJECT
public:
    MainWindow();
    virtual ~MainWindow();
public slots:
    void newPoint();
    void clearPlotter();
    
private:
    Plotter * plotter;
    QTimer * timer;
};

#endif // MAINWINDOW_H
