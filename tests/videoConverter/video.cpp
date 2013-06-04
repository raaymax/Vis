#include <QApplication>
#include <video/VideoConverterWindow.h>


int main(int argc , char ** argv){
    QApplication app(argc,argv);
    
    VideoConverterWindow mainw;
    mainw.show();
    
    return app.exec();
    
}
