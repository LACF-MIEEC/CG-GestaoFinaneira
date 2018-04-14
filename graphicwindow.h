#ifndef GRAPHICWINDOW_H
#define GRAPHICWINDOW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>


class GraphicWindow : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    GraphicWindow(QWidget*parent=0);

    void initializeGL()
    {
        initializeOpenGLFunctions();
        glClearColor(0,1,0,0);
    }
};

#endif // GRAPHICWINDOW_H
