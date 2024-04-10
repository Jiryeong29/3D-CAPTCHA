#include "QGLViewerOrtho.h"
#include <QWheelEvent>

CameraOrtho::CameraOrtho(qreal zNear)
{
	_zNear = zNear;
}

qreal CameraOrtho::zNear() const
{
	if (type() == ORTHOGRAPHIC)
		return _zNear;
	else
		return Camera::zNear();
}

QGLViewerOrtho::QGLViewerOrtho(qreal zNear)
{
	qglviewer::Camera* c = camera();
	setCamera(new CameraOrtho(zNear));
	camera()->setType(qglviewer::Camera::ORTHOGRAPHIC);
	delete c;
}

void QGLViewerOrtho::keyPressEvent(QKeyEvent* e)
{
	if (e->key() == Qt::Key_P)
		if (camera()->type() == qglviewer::Camera::ORTHOGRAPHIC)
			camera()->setType(qglviewer::Camera::PERSPECTIVE);
		else
			camera()->setType(qglviewer::Camera::ORTHOGRAPHIC);
	else
		QGLViewer::keyPressEvent(e);
}