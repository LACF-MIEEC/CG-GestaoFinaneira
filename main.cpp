#include "mainwindow.h"
#include <QApplication>

#include "freeglut.h"

#include <QDebug>
#include <QDir>
#include <QSurfaceFormat>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    glutInit(&argc, argv);

//    QSurfaceFormat format;
//    format.setDepthBufferSize(24);
//    format.setStencilBufferSize(10);
//    format.setVersion(3, 7);
//    format.setProfile(QSurfaceFormat::CompatibilityProfile);
//    QSurfaceFormat::setDefaultFormat(format);


    MainWindow w;

    w.show();
    return a.exec();
}
