#ifndef LINESGRAPHIC_H
#define LINESGRAPHIC_H

#include <QtGui>

#include <freeglut.h>

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#include <QVector>
#include <QPoint>

struct Rgba;
struct LinePoints{
    QVector<QPoint> Points;
};

class LinesGraphic: public QOpenGLWidget , private QOpenGLFunctions
{
    Q_OBJECT

public:
    LinesGraphic(QWidget*parent=0);

    void BackGroundColor(Rgba color);

protected:

    void initializeGL() Q_DECL_OVERRIDE;

    void resizeGL(int w, int h) Q_DECL_OVERRIDE;

    void paintGL() Q_DECL_OVERRIDE;

private:

    Rgba* BackGround;
    Rgba* GridColor;
    Rgba* AxesColor;
    Rgba* VLinesColor;

    QString XAxisLabel;
    QString YAxisLabel;

    bool LineLabeled;
    bool LineDots;

    bool Grid;
    bool AxesLabel;

    bool AxesScale;
    bool YScaleValue;
    bool XScaleValue;

    bool VLines;

    bool Arrows;

    int n_Points;
    int n_YTicks;
    int n_XTicks;
    int n_GridLines;
    int n_VLines;

    int WIDGET_WIDTH;
    int WIDGET_HEIGHT;


    QVector<LinePoints*> Lines;
    QVector<Rgba*> LineColor;
    QVector<Rgba*> DotsColor;
    QStringList LineLabels;
};

#endif // LINESGRAPHIC_H
