#include "glstatusbar.h"
#include "rgb.h"

GLStatusBar::GLStatusBar(QWidget *parent)
    : QOpenGLWidget(parent)
{
    BackGround  = new Color;
    *BackGround = White;
}

void GLStatusBar::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(BackGround->r,BackGround->g,BackGround->b,BackGround->a);

}
void GLStatusBar::resizeGL(int w, int h)
{
    int side = qMin(w, h);
    glViewport((w - side) / 2, (h - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 1,0,1, 0, 1);
    glMatrixMode(GL_MODELVIEW);
}
void GLStatusBar::paintGL(){

    GLfloat percent=0.5f;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBegin(GL_QUADS);
            glColor3f(1.0, 1.0, 0);

            glVertex3f( 0.0f,    0.0f, 0.0f);
            glVertex3f( percent, 0.0f, 0.0f);
            glVertex3f( percent, 1.0f, 0.0f);
            glVertex3f( 0.0f,    1.0f, 0.0f);
        glEnd();

        percent=0.3f;
        glBegin(GL_QUADS);
            glColor3f(1.0, 0.0, 0.0);

            glVertex3f( 0.0f,    0.0f, 0.0f);
            glVertex3f( percent, 0.0f, 0.0f);
            glVertex3f( percent, 1.0f, 0.0f);
            glVertex3f( 0.0f,    1.0f, 0.0f);
        glEnd();

}

void GLStatusBar::setSections(QVector<double> values, QVector<Rgba*> colors){
    SectionValue=QVector<double>(values);
    SectionColor=QVector<Rgba*>(colors);
}
void GLStatusBar::setBackGround(Rgba color){
    *BackGround  =color;
}
