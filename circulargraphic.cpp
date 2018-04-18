#include "circulargraphic.h"
#include "rgb.h"

bool LessThan(const double &p1, const double &p2){
    return p1<p2;
}

CircularGraphic::CircularGraphic(QWidget *parent)
    : QOpenGLWidget(parent)
{
    Radius=0.7;
    BackGround  = new Color;
    *BackGround = White;

   /* SectionValue.append(0.3f);
    SectionColor.append(&Red);

    SectionValue.append(0.4f);
    SectionColor.append(&Blue);

    SectionValue.append(0.3f);
    SectionColor.append(&LigthGrey);*/
}

void CircularGraphic::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(BackGround->r,BackGround->g,BackGround->b,BackGround->a);


        glEnable( GL_LINE_SMOOTH );
//        glEnable(GL_POINT_SMOOTH);
        glEnable( GL_POLYGON_SMOOTH );
        glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
        glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );
    //    glHint( GL_POINT_SMOOTH_HINT, GL_NICEST );

        glEnable(GL_BLEND);
}
void CircularGraphic::resizeGL(int w, int h)
{
    int side = qMin(w, h);
    glViewport((w - side) / 2, (h - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1,-1,1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}
void CircularGraphic::paintGL(){


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    double SliceStart,SliceEnd;
    SliceStart  =0;
    SliceEnd    =0;

    for(int s=SectionValue.size()-1;s>=0;s--){

        SliceEnd    +=SectionValue.at(s)*2*PI;

        glBegin(GL_POLYGON);
        glColor4f(SectionColor.at(s)->r, SectionColor.at(s)->g, SectionColor.at(s)->b,SectionColor.at(s)->a);

        for(double i=SliceStart;(i < 2 * PI)&&(i<SliceEnd);i += PI / 24){
            glVertex3f(cos(i+PI/2) * Radius, sin(i+PI/2) * Radius, 0.0);
        }
        glVertex3f(cos(SliceEnd+PI/2) * Radius, sin(SliceEnd+PI/2) * Radius, 0.0);

        glVertex3f(0.0f, 0.0f, 0.0f);

        glEnd();

        SliceStart  +=SectionValue.at(s)*2*PI;

    }

    qSort(SectionValue.begin(), SectionValue.end(), LessThan);//Sort X

    SliceStart  =0;
    SliceEnd    =0;
    for(int s=SectionValue.size()-1;s>=0;s--){

        SliceEnd    +=SectionValue.at(s)*2*PI;
        glLineWidth(1);
        glBegin(GL_LINE_STRIP);
        glColor4f(Black.r, Black.g, Black.b,Black.a);

        for(double i=SliceStart;(i < 2 * PI)&&(i<SliceEnd);i += PI / 24){
            glVertex3f(cos(i+PI/2) * Radius, sin(i+PI/2) * Radius, 0.0);
        }
        glVertex3f(cos(SliceEnd+PI/2) * Radius, sin(SliceEnd+PI/2) * Radius, 0.0);

        glVertex3f(0.0f, 0.0f, 0.0f);

        glEnd();

        SliceStart  +=SectionValue.at(s)*2*PI;

    }
}

void CircularGraphic::setRadius(double radius){
    Radius  =radius;
}
void CircularGraphic::setSections(QVector<double> values, QVector<Rgba*> colors){
    SectionValue=QVector<double>(values);
    SectionColor=QVector<Rgba*>(colors);
}
void CircularGraphic::setBackGround(Rgba color){
    *BackGround  =color;
}
