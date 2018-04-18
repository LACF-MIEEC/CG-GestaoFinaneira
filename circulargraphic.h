#ifndef CIRCULARGRAPHIC_H
#define CIRCULARGRAPHIC_H

#include <QtGui>

#include <GL/freeglut.h>

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#include <QVector>

struct Rgba;

class CircularGraphic: public QOpenGLWidget , private QOpenGLFunctions
{
    Q_OBJECT

public:
    CircularGraphic(QWidget*parent=0);

    void setRadius(double radius);

    void setSections(QVector<double> values, QVector<Rgba*> colors);

    void setBackGround(Rgba color);

protected:
    void initializeGL() Q_DECL_OVERRIDE;

    void resizeGL(int w, int h) Q_DECL_OVERRIDE;

    void paintGL() Q_DECL_OVERRIDE;



private:

    double  Radius;

    Rgba*    BackGround;

    QVector<double> SectionValue;
    QVector<Rgba*>  SectionColor;
    QStringList     SectionLabel;

};

#endif // CIRCULARGRAPHIC_H
