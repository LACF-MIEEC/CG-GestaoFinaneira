#include "linesgraphic.h"
#include "sorting.h"
#include "rgb.h"

bool xLessThan(const QPoint &p1, const QPoint &p2){
    return p1.x()<p2.x();
}
bool yLessThan(const QPoint &p1, const QPoint &p2){
    return p1.y()<p2.y();
}

LinesGraphic::LinesGraphic(QWidget*parent)
    :QOpenGLWidget(parent)
{

    BackGround   = new Color;
    AxesColor    = new Color;
    GridColor    = new Color;
    VLinesColor  = new Color;
    *BackGround  = White;
    *AxesColor   = Black;
    *GridColor   = LigthGrey;
    *VLinesColor = LigthGrey;
    VLinesColor->a=0.8f; //sets Transparency

    n_Points=80;
    n_XTicks=12;
    n_YTicks=18;
    n_GridLines=n_YTicks;
    n_VLines=n_XTicks;

    LineLabeled =false;
    LineDots=true;

    Grid=true;
    AxesLabel=true;

    AxesScale=true;
    YScaleValue=true;
    XScaleValue=true;

    VLines=true;

    Arrows=true;

    //          TEST VALUES
    QVector<QPoint> pontos,pontos2;
    LinePoints *linha=new LinePoints,*linha2 =new LinePoints;
    for(int i=0; i<n_XTicks; i++)
        pontos.append(QPoint(i+1, rand() % 100));
    linha->Points=pontos;
    Lines.append(linha);
    for(int i=0; i<n_XTicks; i++)
        pontos2.append(QPoint(i+1, rand() % 100));
    linha2->Points=pontos2;
    Lines.append(linha2);

    LineColor.append(&Green);
    LineColor.append(&Red);

    DotsColor.append(&Blue);
    DotsColor.append(&Black);

    XAxisLabel=QString("Abcissa");
    YAxisLabel=QString("Ordenada");
}

void LinesGraphic::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(BackGround->r,BackGround->g,BackGround->b,BackGround->a);

//    glEnable( GL_LINE_SMOOTH );
//    glEnable(GL_POINT_SMOOTH);
    glEnable( GL_POLYGON_SMOOTH );
//    glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
    glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );
//    glHint( GL_POINT_SMOOTH_HINT, GL_NICEST );

    glEnable(GL_BLEND);

}
void LinesGraphic::resizeGL(int w, int h)
{
    int side = qMin(w, h);
    glViewport((w - side) / 2, (h - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(AxesLabel)
        glOrtho(-0.2, 1.1,-0.2,1.1, -1, 1);
    else
        glOrtho(-0.1, 1.1,-0.1,1.1, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    WIDGET_WIDTH=w;
    WIDGET_HEIGHT=h;
}
void LinesGraphic::BackGroundColor(Rgba color){
    *BackGround  =color;
}

void LinesGraphic::paintGL(){


    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);



    double x_min=-0.06, x_max=1.06;
    double y_min=-0.06, y_max=1.06;

    for(int l=0;l<Lines.size();l++){ //Finds the Global Maxima and Minima (3D)
        //Plot Lines
        QPolygon P(Lines.at(l)->Points);               //Creates a Polygon with the points
        QRect Box = P.boundingRect();                 //Set a Box around it
        x_min = qMin(Box.left(),(int)x_min);
        x_max = qMax(Box.right(),(int)x_max);
        y_min = qMin(Box.top(),(int)y_min);
        y_max = qMax(Box.bottom(),(int)y_max);
    }

//AXIS AND REFERENCES

    // Plot Axes
    glColor4f(AxesColor->r,AxesColor->g,AxesColor->b,AxesColor->a);
    glLineWidth(1);
    glBegin(GL_LINE_STRIP);//Horizontal Axis
    glVertex3f(0.0f,0.0f,0.0f);
    glVertex3f(1.05f,0.0f,0.0f);
    glEnd();
    glBegin(GL_LINE_STRIP);//Vertical Axis
    glVertex3f(0.0f,0.0f,0.0f);
    glVertex3f(0.0f,1.05f,0.0f);
    glEnd();

    if(AxesLabel){//Set Axis Labels
        std::string label;
        double StringWidth=0;
        label= XAxisLabel.toStdString();
        for(int j=0;j<label.length();j++){
            StringWidth+=glutBitmapWidth(GLUT_BITMAP_HELVETICA_12, label.at(j));
        }
        StringWidth= StringWidth/(double)WIDGET_WIDTH;
        glRasterPos2f( 0.5f-StringWidth/2 , -0.15f );
        for(int j=0;j<label.length();j++){
            glutBitmapCharacter( GLUT_BITMAP_HELVETICA_12, label.at(j) );
        }

        StringWidth=0;
        label= YAxisLabel.toStdString();
        for(int j=0;j<label.length();j++){
            StringWidth+=glutBitmapWidth(GLUT_BITMAP_HELVETICA_12, label.at(j));
        }
        StringWidth= StringWidth/(double)WIDGET_HEIGHT;

        double x, y;

        for(int j=0;j<label.length();j++){ // Vertical Text
            x=-0.15f + ( glutBitmapWidth(GLUT_BITMAP_HELVETICA_12, label.at(j)) / (2*(double)WIDGET_WIDTH));
            y=0.5f + StringWidth/2 - ((double)j)*(StringWidth/label.length()+0.025);

            glRasterPos2f(x,y);
            glutBitmapCharacter( GLUT_BITMAP_HELVETICA_12, label.at(j) );
        }
    }

    if(Arrows){ //Plot Arrows
        glBegin(GL_POLYGON);// Y Arrow
        glVertex3f(-0.01f,  1.02f,  0.0f);
        glVertex3f( 0.01f,  1.02f,  0.0f);
        glVertex3f( 0.0f,   1.05f,   0.0f);
        glEnd();

        glBegin(GL_POLYGON);// X Arrow
        glVertex3f(1.03f, -0.02f,  0.0f);
        glVertex3f(1.03f,  0.02f,  0.0f);
        glVertex3f(1.05f,  0.0f,   0.0f);
        glEnd();


    }

    if(Grid){//Plot Grid
        double grid_Tick = (y_max-y_min)/(n_GridLines);
        for(int y=1; y<(n_GridLines+1); y++){//Grid
            glPointSize(1);
            glColor4f(GridColor->r,GridColor->g,GridColor->b,GridColor->a);
            for(double i=1;i<n_Points;i++){
                glBegin(GL_POINTS);
                glVertex3f(i/n_Points,(y*grid_Tick-y_min)/y_max,0.0f);
                glEnd();
            }
        }
    }

    if(VLines){//Plot Vertical Lines
        double vline_Tick = (x_max-x_min)/(n_VLines);
        glLineWidth(0.7f);
        glColor4f(VLinesColor->r,VLinesColor->g,VLinesColor->b,VLinesColor->a);
        for(int x=1; x<(n_VLines+1); x++){//Grid
            glBegin(GL_LINE_STRIP);
            glVertex3f((x*vline_Tick-x_min)/x_max,0.0f,0.0f);
            glVertex3f((x*vline_Tick-x_min)/x_max,1.0f,0.0f);
            glEnd();
        }
    }

    if(AxesScale){ // Plot Scale, if enabled
        glLineWidth(1.0f);
        glColor4f(AxesColor->r,AxesColor->g,AxesColor->b,AxesColor->a);

        std::string sValue;

        double s_YTick = (y_max-y_min)/n_YTicks;
        double s_XTick = (x_max-x_min)/n_XTicks;
        double y, x;

        for(int i=1; i<(n_YTicks+1); i++){ // y Scale
            y=(i*s_YTick-y_min)/y_max;
            glBegin(GL_LINES);
            glVertex3f(-0.01f, y, 0.0f);
            glVertex3f( 0.005f, y, 0.0f);
            glEnd();

            if(YScaleValue){ //Plots Scale Value, if Active
                sValue=std::to_string((int)(i*s_YTick));
                glRasterPos2f( -0.05f, y-0.01f );
                for(int j=0;j<sValue.length();j++){
                    glutBitmapCharacter( GLUT_BITMAP_HELVETICA_10, sValue.at(j) );
                }
            }
        }

        for(int i=1; i<(n_XTicks+1); i++){ // x scale
            x=(i*s_XTick-x_min)/x_max;
            glBegin(GL_LINES);
            glVertex3f(x, -0.02f, 0.0f);
            glVertex3f(x,  0.005f, 0.0f);
            glEnd();

            if(XScaleValue){ //Plots Scale Value, if Active
                sValue=std::to_string((int)(i*s_XTick));
                glRasterPos2f( x-0.01f , -0.08f );
                for(int j=0;j<sValue.length();j++){

                    glutBitmapCharacter( GLUT_BITMAP_HELVETICA_12, sValue.at(j) );
                }
            }
        }

    }

// DATA

    glLineWidth(1.5f);
//    int xSignal,ySignal;


    for(int l=0;l<Lines.size();l++){ // Sorts X Data and Plot all Lines

        qSort(Lines.at(l)->Points.begin(), Lines.at(l)->Points.end(), xLessThan);//Sort X

        glBegin(GL_LINE_STRIP);
        glColor4f(LineColor.at(l)->r,LineColor.at(l)->g,LineColor.at(l)->b,LineColor.at(l)->a);

        for(int i=0; ( i<Lines.at(l)->Points.size() ); i++){

            glVertex3f((Lines.at(l)->Points.at(i).x()-x_min)/x_max,(Lines.at(l)->Points.at(i).y()-y_min)/y_max,0.0f);
/*
//            if((i+1)<Lines.at(l)->Points.size()){// Extra Points For Smothing

//                if((Lines.at(l)->Points.at(i).x())<(Lines.at(l)->Points.at(i+1).x())){
//                    xSignal=1;}else{xSignal=-1;}
//                if((Lines.at(l)->Points.at(i).y())<(Lines.at(l)->Points.at(i+1).y())){
//                    ySignal=1;}else{ySignal=-1;}

//                glVertex3f( ((Lines.at(l)->Points.at(i).x()-x_min)/x_max)+xSignal*
//                            ((Lines.at(l)->Points.at(i+1).x()-x_min)/x_max)*0.03,
//                            ((Lines.at(l)->Points.at(i).y()-y_min)/y_max)+ySignal*
//                            ((Lines.at(l)->Points.at(i+1).y()-y_min)/y_max)*0.04,
//                            0.0f);

//                xSignal=-xSignal;
//                ySignal=-ySignal;

//                glVertex3f( ((Lines.at(l)->Points.at(i+1).x()-x_min)/x_max)+xSignal*
//                            ((Lines.at(l)->Points.at(i).x()-x_min)/x_max)*0.03,
//                            ((Lines.at(l)->Points.at(i+1).y()-y_min)/y_max)+ySignal*
//                            ((Lines.at(l)->Points.at(i).y()-y_min)/y_max)*0.04,
//                            0.0f);
//            }*/
        }

        glEnd();

        glPointSize(5);
        if(LineDots){ // Plot Line Dots, if active;
            glColor4f(DotsColor.at(l)->r,DotsColor.at(l)->g,DotsColor.at(l)->b,DotsColor.at(l)->a);

            for(int i=0; ( i<Lines.at(l)->Points.size() ); i++){
                glBegin(GL_POINTS);
                glVertex3f((Lines.at(l)->Points.at(i).x()-x_min)/x_max,(Lines.at(l)->Points.at(i).y()-y_min)/y_max,0.0f);
                glEnd();
            }
        }
    }



}



