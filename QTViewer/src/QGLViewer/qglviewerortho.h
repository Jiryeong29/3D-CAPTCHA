#include <QGLViewer/qglviewer.h>

class CameraOrtho : public qglviewer::Camera
{
public:
	CameraOrtho(qreal zNear = -10000);
	virtual qreal zNear() const;
	
private:
	qreal _zNear;
};

class QGLViewerOrtho : public QGLViewer
{
Q_OBJECT

public:
	QGLViewerOrtho(qreal zNear = -10000);
	virtual void keyPressEvent(QKeyEvent* e);
};