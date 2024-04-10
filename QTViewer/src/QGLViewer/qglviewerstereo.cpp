#include <QtGui>
#include "qglviewerstereo.h"

bool stereo = false;

QGLViewerStereo::QGLViewerStereo()
{
	camera()->setPhysicalScreenWidth(2);
}

QGLViewerStereo::~QGLViewerStereo()
{
}

void QGLViewerStereo::resizeGL(int width, int height)
{
	QGLWidget::resizeGL(width, height);
	glViewport(0, 0, GLint(width), GLint(height));
	camera()->setScreenWidthAndHeight(this->width(), this->height());

	/* this code generates the interlaced pattern
	to the stencil buffer for stereoscopic masking */	

	GLint gliY;
	// seting screen-corresponding geometry
	glViewport(0, 0, width, height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-0.5, width-0.5, -0.5, height-0.5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// clearing and configuring stencil drawing
	glDrawBuffer(GL_BACK);
	glEnable(GL_STENCIL_TEST);
	glClearStencil(0);
	glClear(GL_STENCIL_BUFFER_BIT);
	glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE); // colorbuffer is copied to stencil
	//glDisable(GL_DEPTH_TEST);
	glStencilFunc(GL_ALWAYS, 1, 1); // to avoid interaction with stencil content

	// drawing stencil pattern
	glColor4f(1, 1, 1, 0);	// alfa is 0 not to interfere with alpha tests
	for (gliY = 0; gliY < height; gliY += 2)
	{
		glLineWidth(1);
		glBegin(GL_LINES);
			glVertex2f(0, gliY);
			glVertex2f(width, gliY);
		glEnd();
	}
	glStencilOp (GL_KEEP, GL_KEEP, GL_KEEP); // disabling changes in stencil buffer
	glFlush();
}

void QGLViewerStereo::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int view=1; view>=0; --view)
	{
		if (stereo)
			preDrawStereo(view);
		else
			preDraw(view);
		//if (camera()->frame()->isManipulated())
		//	fastDraw();
		//else
			draw();
		postDraw();
	}

	emit drawFinished(true);
}

void QGLViewerStereo::preDraw(bool leftBuffer)
{
	glStencilFunc(leftBuffer? GL_NOTEQUAL : GL_EQUAL, 1, 1);
	camera()->loadProjectionMatrix();
	camera()->loadModelViewMatrix();
}

void QGLViewerStereo::preDrawStereo(bool leftBuffer)
{
	glStencilFunc(leftBuffer? GL_NOTEQUAL : GL_EQUAL, 1, 1);
	camera()->loadProjectionMatrixStereo(leftBuffer);
	camera()->loadModelViewMatrixStereo(leftBuffer);
}

void QGLViewerStereo::keyPressEvent(QKeyEvent *e)
{
	if(e->key() == Qt::Key_S)
		ToggleStereo();
	else
		QGLViewer::keyPressEvent(e);
}

void QGLViewerStereo::ToggleStereo()
{
	stereo = !stereo;
	updateGL();
}