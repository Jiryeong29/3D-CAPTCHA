#include "Viewer.h"

#include "gl/freeglut.h"
Viewer::Viewer(QWidget *parent)
{
    setParent(parent);
}

void Viewer::initializeGL()
{
    glClearColor(1, 1, 1, 1);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_NORMALIZE);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glFrontFace(GL_CCW);
    //glEnable(GL_LIGHTING);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glEnable(GL_LIGHT0);
    // float diffuse[] = { 1, 1, 1, 0 };
    // float ambient[] = { 1,1,1, 0 };
    // float specular[] = { 1, 1, 1, 0 };
    // float lightPos[] = { 10,0,0, 0 };
    // glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    // glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    // glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    // glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    GLfloat ambient[] = { 0.1,0.1,0.1 };
    GLfloat diffuse[] = { 0.4,0.4,0.4 };
    GLfloat light0Pos[] = { 100,100,100,0 };
    GLfloat light1Pos[] = { -100,100,100,0 };
    GLfloat specular[] = { 0.4,0.4,0.4 };
     glLightfv(GL_LIGHT0, GL_POSITION, light0Pos);       
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT1, GL_POSITION, light1Pos);
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
    glEnable(GL_LIGHT1);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 10);


    glPointSize(10);
    glLineWidth(3.0);
    restoreStateFromFile();
    setAnimationPeriod(100); // interval 0.1ÃÊ

    dc3.Init();

}


void Viewer::draw()
{
    dc3.Draw();
}

void Viewer::SetCamera(float ux, float uy, float uz, float dx, float dy, float dz)
{
    camera()->setUpVector(qglviewer::Vec(ux, uy, uz));
    camera()->setViewDirection(qglviewer::Vec(dx, dy, dz));
    camera()->fitSphere(qglviewer::Vec(0, 0, 0), 10);
    camera()->setSceneRadius(10);
    updateGL();
}

void Viewer::SetCameraFront()
{
    SetCamera(0, 0, 1, 0, -1, 0);
}

void Viewer::keyPressEvent(QKeyEvent *e)
{
    int key = e->key();
    if (key == Qt::Key_Left)
	dc3.arrowNum1--;
    else if (key == Qt::Key_Right)
	dc3.arrowNum1++;
    else if (key == Qt::Key_Up)
	dc3.arrowNum0++;
    else if (key == Qt::Key_Down)
	dc3.arrowNum0--;
    else if (key == Qt::Key_N) {
	if (animationIsStarted())
	    stopAnimation();
	else
	    startAnimation();
    }
    else if (key == Qt::Key_S) {
	saveStateToFile();
    }
    else if (key == Qt::Key_L) {
	restoreStateFromFile();
    }
    else if (key == Qt::Key_Comma) {
	setSceneRadius(sceneRadius() * 0.1);
    }
    else if (key == Qt::Key_Period) {
	setSceneRadius(sceneRadius() * 10.0);
    }
    else
	QGLViewerOrtho::keyPressEvent(e);

    updateGL();
}

void Viewer::mousePressEvent(QMouseEvent *e)
{
    QGLViewerOrtho::mousePressEvent(e);
}

void Viewer::mouseMoveEvent(QMouseEvent *e)
{
    QGLViewerOrtho::mouseMoveEvent(e);
}

void Viewer::mouseReleaseEvent(QMouseEvent *e)
{
    QGLViewerOrtho::mouseReleaseEvent(e);
}

void Viewer::animate()
{
    animateIdx++;
}
