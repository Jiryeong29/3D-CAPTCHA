#include <QGLViewer/qglviewer.h>

class QGLViewerStereo : public QGLViewer
{
	Q_OBJECT

public:
	QGLViewerStereo();
	virtual ~QGLViewerStereo();

	virtual void resizeGL(int width, int height);
	virtual void paintGL();
	virtual void preDraw(bool leftBuffer = true);
	virtual void preDrawStereo(bool leftBuffer = true);
	virtual void keyPressEvent(QKeyEvent *e);

public slots:
	virtual void ToggleStereo();
};