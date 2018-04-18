#ifndef GLSTATUSBAR_H
#define GLSTATUSBAR_H

#include <QtGui>

#include <GL/freeglut.h>

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#include <QVector>

struct Rgba;

class GLStatusBar : public QOpenGLWidget , private QOpenGLFunctions
{
    Q_OBJECT

public:
    GLStatusBar(QWidget*parent=0);

    void setSections(QVector<double> values, QVector<Rgba*> colors);

    void setBackGround(Rgba color);

protected:

    void initializeGL() Q_DECL_OVERRIDE;

    void resizeGL(int w, int h) Q_DECL_OVERRIDE;

    void paintGL() Q_DECL_OVERRIDE;



private:

    QVector<double> SectionValue;
    QVector<Rgba*>  SectionColor;
    QStringList     SectionLabel;

    Rgba*  BackGround;

};

#endif // GLSTATUSBAR_H
